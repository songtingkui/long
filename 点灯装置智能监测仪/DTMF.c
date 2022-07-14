/*
 * DTMF.c
 *
 * created: 2022/6/24
 *  author:
 */

#include <stdint.h>
#include "bsp.h"
#include "rtthread.h"
#include "ls1b_gpio.h"
#include "ls1x_pwm.h"
#include "i2c/mcp4725.h"
#include "ls1x_i2c_bus.h"
#include "user.h"
#include "DTMF.h"
#include "ls1x_rtc.h"

//--------------------------------------------------------------------------------------------------
volatile unsigned int g_send_dtmf_mark;                 // 本端DTMF信号发送中标志
volatile unsigned int g_recv_dtmf_mark;                 // 本端接收DTMF特征码标志

//--------------------------------------------------------------------------------------------------
static unsigned int dtmf_send_idx;                      // DTMF音频CODE发送计数器
static short int *dtmf_send_mak;                        // DTMF音频CODE缓冲区指针

static rt_thread_t m_dtmf_thread;                       // DTMF接收及命令处理线程

//--------------------------------------------------------------------------------------------------

// DTMF定时DAC输出
static void pwmtimer_callback_pwm0(void *pwm, int *stopit)
{
    int dat;

    // 幅度压缩
    dat = dtmf_send_mak[dtmf_send_idx] * 10 / DTMF_SEND_VOL;
    set_mcp4725_dac(busI2C0, (unsigned short int)((unsigned short int)dat + 0x8000) >> 4);

    dtmf_send_idx++;
    if (dtmf_send_idx >= (DTMF_CodeCount / 2))
    {
        // 发送结束，停止定时器
        ls1x_pwm_timer_stop(devPWM0);
    }
}

// 发送指定长度DTMF码字
void send_dtmf_string(unsigned char *dtmf, int len)
{
    int i;
    pwm_cfg_t cfg;

    // 发送信号标志
    g_send_dtmf_mark = 1;
    g_recv_dtmf_mark = 0;

    if (len > 0)
    {
        // 配置DAC发送定时器：16K
        cfg.hi_ns = 62500;
        cfg.lo_ns = 62500;
        cfg.mode  = PWM_CONTINUE_TIMER;
        cfg.isr   = NULL;
        cfg.cb    = pwmtimer_callback_pwm0;
        cfg.event = NULL;

        // 单个发送DTMF码字
        for (i = 0; i < len; i++)
        {
            dtmf_send_idx = 0;
            dtmf_send_mak = (short int *)DTMF_CharData[dtmf[i] & 0x0F];
            ls1x_pwm_timer_start(devPWM0, &cfg);

            // DAC定时自动结束
            rt_thread_delay(30 + 15);
        }
    }

    g_send_dtmf_mark = 0;
}

////////////////////////////////////////////////////////////////////////////////////////////////////

// DTMF命令码字分解处理
unsigned int Dtmfdispose(unsigned char *pBuf, unsigned int *pVoltage, unsigned int *pCurrent, unsigned int *pAlarm)
{
    unsigned int index;

    // 信号机ID: 类型，股道，灯位
    index  = (pBuf[1] >> 1) & 0x0007;
    index |= (pBuf[3] << 4) & 0x00F0;
    index |= (pBuf[2] << 8) & 0x0F00;

    // 信号状态量
    *pVoltage = (pBuf[4] & 0x0F) | ((pBuf[5] << 4) & 0xF0);
    *pAlarm   = pBuf[6] & 0x01;
    *pCurrent = ((pBuf[6] << 2) & 0x30) | (pBuf[7] & 0x0F);

    return index;
}

static void dtmf_thread(void *arg)
{
    unsigned int  ch, check;
    unsigned int  tickcount;
    unsigned int  RecvCount;
    unsigned char RecvBuff[16];
    unsigned int  L610Send;
    unsigned int  index, voltage, current, alarm;

    // GPIO初始化
    gpio_enable(42, DIR_IN);
    gpio_enable(43, DIR_IN);
    gpio_enable(44, DIR_IN);
    gpio_enable(45, DIR_IN);
    gpio_enable(46, DIR_IN);

    // DTMF接收 & 分析循环
    while (1)
    {
        // 接收计数清零
        RecvCount = 0;
        g_recv_dtmf_mark = 0;

        // 等待循环接收
        do
        {
            // L
            while (0 == gpio_read(46))
            {
                rt_thread_delay(2);

                if (0 != RecvCount)
                {
                    // 接收超时100MS
                    if ((unsigned int)(rt_tick_get() - tickcount) >= 100)
                    {
                        // 接收计数清零
                        RecvCount = 0;
                        g_recv_dtmf_mark = 0;
                    }
                }
            }

            if (0 == g_send_dtmf_mark)
            {
                // 记录当前时间
                tickcount = rt_tick_get();

                // 读取DTMF码
                ch  = (gpio_read(42) << 3);
                ch |= (gpio_read(43) << 2);
                ch |= (gpio_read(44) << 1);
                ch |= (gpio_read(45) << 0);

                // 存储 & 校验
                switch (RecvCount)
                {
                    case 0:
                        if (0 != ch)
                        {
                            break;
                        }
                        check = 0;
                        g_recv_dtmf_mark = 1;

                    default:
                        check += ch;
                        RecvBuff[RecvCount] = ch;
                        RecvCount++;
                        break;
                }
            }

            // H
            while (1 == gpio_read(46))
            {
                rt_thread_delay(2);
            }
        }
        while (RecvCount < 9);

        // 检查校验
        if (0 != (check & 0x0F))
        {
            continue;
        }

        // DTMF命令分析
        index = Dtmfdispose(RecvBuff, &voltage, &current, &alarm);

        // 信号机属性分析
        index = FindXHJindex(index);
        if (index < XHJ_ID_MAX)
        {
            L610Send = 0;
            printk("DTMF-RX: %d - %d - %d", index, voltage, alarm);

            // 设备上线线操作
            if (0 == g_XHJ_attribute[index].Signal_online)
            {
                L610Send = 1;
            }
            else if (alarm != (g_XHJ_attribute[index].Signal_alarm & 0x01))
            {
                // 灯丝状态首次变化标志
                alarm |= 0x02;

                L610Send = 1;
            }
            else
            {
                // 检查报送间隔时间：1分钟
                if ((rt_tick_t)(rt_tick_get() - g_XHJ_attribute[index].onTick) >= rt_tick_from_millisecond(MQTT_SEND_SPACE))
                {
                    L610Send = 1;
                }
            }

            // 更新信号机的实时数据
            g_XHJ_attribute[index].Signal_voltage = voltage / 10.0;
            g_XHJ_attribute[index].Signal_current = current / 10.0;
            g_XHJ_attribute[index].Signal_alarm   = alarm;
            g_XHJ_attribute[index].Signal_online  = 2;
            ls1x_rtc_get_datetime(&g_XHJ_attribute[index].t);

            if (!is_show_grid())
            {
                update_Circle((XHJ_attribute_t *)&g_XHJ_attribute[index]);
            }
            else
            {
                update_grid((XHJ_attribute_t *)&g_XHJ_attribute[index]);
            }

            if (0 != L610Send)
            {
                g_XHJ_attribute[index].onTick = rt_tick_get();
                L610_send((XHJ_attribute_t *)&g_XHJ_attribute[index]);
            }
        }
    }
}

void dtmf_thread_init(void)
{
    m_dtmf_thread = rt_thread_create("dtmfthread",
                                     dtmf_thread,
                                     NULL,          // arg
                                     1024*4,        // statck size
                                     3,             // priority
                                     10);           // slice ticks

    if (m_dtmf_thread == NULL)
    {
        rt_kprintf("create dtmf thread fail!\r\n");
    }
    else
    {
        rt_thread_startup(m_dtmf_thread);
    }
}

