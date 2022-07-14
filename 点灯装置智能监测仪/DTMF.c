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
volatile unsigned int g_send_dtmf_mark;                 // ����DTMF�źŷ����б�־
volatile unsigned int g_recv_dtmf_mark;                 // ���˽���DTMF�������־

//--------------------------------------------------------------------------------------------------
static unsigned int dtmf_send_idx;                      // DTMF��ƵCODE���ͼ�����
static short int *dtmf_send_mak;                        // DTMF��ƵCODE������ָ��

static rt_thread_t m_dtmf_thread;                       // DTMF���ռ�������߳�

//--------------------------------------------------------------------------------------------------

// DTMF��ʱDAC���
static void pwmtimer_callback_pwm0(void *pwm, int *stopit)
{
    int dat;

    // ����ѹ��
    dat = dtmf_send_mak[dtmf_send_idx] * 10 / DTMF_SEND_VOL;
    set_mcp4725_dac(busI2C0, (unsigned short int)((unsigned short int)dat + 0x8000) >> 4);

    dtmf_send_idx++;
    if (dtmf_send_idx >= (DTMF_CodeCount / 2))
    {
        // ���ͽ�����ֹͣ��ʱ��
        ls1x_pwm_timer_stop(devPWM0);
    }
}

// ����ָ������DTMF����
void send_dtmf_string(unsigned char *dtmf, int len)
{
    int i;
    pwm_cfg_t cfg;

    // �����źű�־
    g_send_dtmf_mark = 1;
    g_recv_dtmf_mark = 0;

    if (len > 0)
    {
        // ����DAC���Ͷ�ʱ����16K
        cfg.hi_ns = 62500;
        cfg.lo_ns = 62500;
        cfg.mode  = PWM_CONTINUE_TIMER;
        cfg.isr   = NULL;
        cfg.cb    = pwmtimer_callback_pwm0;
        cfg.event = NULL;

        // ��������DTMF����
        for (i = 0; i < len; i++)
        {
            dtmf_send_idx = 0;
            dtmf_send_mak = (short int *)DTMF_CharData[dtmf[i] & 0x0F];
            ls1x_pwm_timer_start(devPWM0, &cfg);

            // DAC��ʱ�Զ�����
            rt_thread_delay(30 + 15);
        }
    }

    g_send_dtmf_mark = 0;
}

////////////////////////////////////////////////////////////////////////////////////////////////////

// DTMF�������ַֽ⴦��
unsigned int Dtmfdispose(unsigned char *pBuf, unsigned int *pVoltage, unsigned int *pCurrent, unsigned int *pAlarm)
{
    unsigned int index;

    // �źŻ�ID: ���ͣ��ɵ�����λ
    index  = (pBuf[1] >> 1) & 0x0007;
    index |= (pBuf[3] << 4) & 0x00F0;
    index |= (pBuf[2] << 8) & 0x0F00;

    // �ź�״̬��
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

    // GPIO��ʼ��
    gpio_enable(42, DIR_IN);
    gpio_enable(43, DIR_IN);
    gpio_enable(44, DIR_IN);
    gpio_enable(45, DIR_IN);
    gpio_enable(46, DIR_IN);

    // DTMF���� & ����ѭ��
    while (1)
    {
        // ���ռ�������
        RecvCount = 0;
        g_recv_dtmf_mark = 0;

        // �ȴ�ѭ������
        do
        {
            // L
            while (0 == gpio_read(46))
            {
                rt_thread_delay(2);

                if (0 != RecvCount)
                {
                    // ���ճ�ʱ100MS
                    if ((unsigned int)(rt_tick_get() - tickcount) >= 100)
                    {
                        // ���ռ�������
                        RecvCount = 0;
                        g_recv_dtmf_mark = 0;
                    }
                }
            }

            if (0 == g_send_dtmf_mark)
            {
                // ��¼��ǰʱ��
                tickcount = rt_tick_get();

                // ��ȡDTMF��
                ch  = (gpio_read(42) << 3);
                ch |= (gpio_read(43) << 2);
                ch |= (gpio_read(44) << 1);
                ch |= (gpio_read(45) << 0);

                // �洢 & У��
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

        // ���У��
        if (0 != (check & 0x0F))
        {
            continue;
        }

        // DTMF�������
        index = Dtmfdispose(RecvBuff, &voltage, &current, &alarm);

        // �źŻ����Է���
        index = FindXHJindex(index);
        if (index < XHJ_ID_MAX)
        {
            L610Send = 0;
            printk("DTMF-RX: %d - %d - %d", index, voltage, alarm);

            // �豸�����߲���
            if (0 == g_XHJ_attribute[index].Signal_online)
            {
                L610Send = 1;
            }
            else if (alarm != (g_XHJ_attribute[index].Signal_alarm & 0x01))
            {
                // ��˿״̬�״α仯��־
                alarm |= 0x02;

                L610Send = 1;
            }
            else
            {
                // ��鱨�ͼ��ʱ�䣺1����
                if ((rt_tick_t)(rt_tick_get() - g_XHJ_attribute[index].onTick) >= rt_tick_from_millisecond(MQTT_SEND_SPACE))
                {
                    L610Send = 1;
                }
            }

            // �����źŻ���ʵʱ����
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

