/*
 * user.c
 *
 * created: 2022/6/16
 *  author:
 */

#include <stdint.h>
#include <stdio.h>
#include <string.h>

#include "bsp.h"
#include "rtthread.h"
#include "ns16550.h"
#include "user.h"
#include "time.h"
#include "L610/L610_Init.h"
#include "ls1x_fb.h"
#include "ls1x_rtc.h"

//--------------------------------------------------------------------------------------------------
volatile unsigned int g_mqtt_connect_ok = 0;
static rt_thread_t m_L610_thread = NULL;

//--------------------------------------------------------------------------------------------------

static void mqtt_showinfo(char *info)
{
    FillRect (60, 453, 540, 469, cidxSILVER);
    PutString(60, 453, info, cidxVIOLET);
}

void L610_send(XHJ_attribute_t *pAttrib)
{
    char buf[260];

    if (!g_mqtt_connect_ok)
    {
        return;
    }

    sprintf(buf, "发送: %s - V = %.1f, I = %.1f", pAttrib->Signal_name, pAttrib->Signal_voltage, pAttrib->Signal_current);
    mqtt_showinfo(buf);

    // {"method":"report","params":{"V":33}}
    // 电压、电流：1位小数
    // 告警：0主灯丝，1副灯丝，3首次主灯切换副灯丝，>=4离线
    // ID: 信号机类型-信号机股道-信号机灯位
    // 信号机类型：0调车 2出站(上行) 3出站(下行) 4进站（方向1）
    snprintf(buf, 256, "{\\\"method\\\":\\\"report\\\",\\\"params\\\":{\\\"U\\\":%.1f,\\\"I\\\":%.1f,\\\"Warn\\\":%d,\\\"ID\\\":\\\"%d-%d-%d\\\"}}", \
             pAttrib->Signal_voltage, pAttrib->Signal_current, pAttrib->Signal_alarm, \
             pAttrib->Signal_type, pAttrib->Signal_track, pAttrib->Signal_location);

    l610_fabu_xiaoxi(buf);
}

static void L610_process(char *pMsg)
{
    char *ptr, *pOut;
    float voltage;
    struct tm t;
    unsigned int index, type, track, location;

    switch (l610_get_dingyue(pMsg, &pOut))
    {
        case 0:
            // +TCMQTTRCVPUB: "7SIG0VBSLF/X2/data",38,"{"method":"report","params":{"ID":"4-0-1","U":12.3}}"
            ptr = strstr(pOut, "{\"method\":\"report\",\"params\":{");
            if (NULL != ptr)
            {
                ptr += sizeof("{\"method\":\"report\",\"params\":{") - 1;
                if (4 == sscanf(ptr, "\"ID\":\"%d-%d-%d\",\"U\":%f}", &type, &track, &location, &voltage))
                {
                    // 信号机ID: 类型，股道，灯位
                    index  = location & 0x0007;
                    index |= (track << 4) & 0x00F0;
                    index |= (type  << 8) & 0x0F00;

                    // 信号机ID分析
                    index = FindXHJindex(index);
                    if (index < XHJ_ID_MAX)
                    {
                        char buf[32];
                        sprintf(buf, "收到: %s - V = %.1f", g_XHJ_attribute[index].Signal_name, voltage);
                        mqtt_showinfo(buf);

                        g_XHJ_attribute[index].Set_voltage = voltage;
                    }
                }
                break;
            }

            // +TCMQTTRCVPUB: "7SIG0VBSLF/X2/data",24,"{"datetimes":"2022-06-29 12:12:12"}"
            ptr = strstr(pOut, "{\"datetimes\":\"");
            if (NULL != ptr)
            {
                ptr += sizeof("{\"datetimes\":\"") - 1;
                if (6 == sscanf(ptr, "%d-%d-%d %d:%d:%d\"}", \
                                &t.tm_year, &t.tm_mon, &t.tm_mday, &t.tm_hour, &t.tm_min, &t.tm_sec))
                {
                    mqtt_showinfo("收到: datetimes");
                    g_mqtt_connect_ok = 1;

                    // 系统时钟设置RTC
                    t.tm_year -= 1900;
                    t.tm_mon  -= 1;
                    t.tm_sec  += 2;
                    ls1x_rtc_set_datetime(&t);
                }
                break;
            }
            break;
    }
}

//--------------------------------------------------------------------------------------------------

static void L610_thread(void *arg)
{
    unsigned int rt;
    char tmp[258], *ptr;

    g_mqtt_connect_ok = 0;

    // 初始化串口
    ls1x_uart_init(devUART1, NULL);
    ls1x_uart_open(devUART1, NULL);

    // 初始化L610
    mqtt_showinfo("L610模块初始化");
    l610_at_check();
    mqtt_showinfo("L610模块正常");
    l610_cpin_check();
    mqtt_showinfo("SIM卡初始正常");
    l610_eps_check();
    mqtt_showinfo("4G网络连接正常");
    l610_ip_allo();
    mqtt_showinfo("获得终端IP地址");
    rt_thread_delay(1000);

    // 初始化MQTT
//  l610_xinxi_shezhi();                    // 平台信息设置参数, L610模块掉电保存
    mqtt_showinfo("MQTT应用初始化");
    l610_MQTT_connect();
    mqtt_showinfo("MQTT已连接服务器");
    l610_dingyue_xiaoxi();
    mqtt_showinfo("数据Top订阅成功");

    // 发送时间同步消息
    l610_fabu_xiaoxi("{\\\"datetimes\\\":\\\"\\\"}");
    mqtt_showinfo("等待时钟同步信号");

    // 接收订阅信息处理
    while (1)
    {
        // 设置AT数据包接收初值
        rt  = 0;
        ptr = tmp;

        while (1)
        {
            // 2ms间隔接收
            int readed = ls1x_uart_read(devUART1, ptr, 256 - rt, (void *)0);
            if (readed > 0)
            {
                ptr += readed;
                rt  += readed;

                if ((rt >= 2) && ('\r' == tmp[rt-2]) && ('\n' == tmp[rt-1]))
                {
                    *ptr = 0;
                    break;
                }

                if (rt >= 256)
                {
                    // 清除超长AT数据包接收
                    rt  = 0;
                    ptr = tmp;
                }
            }
            
            rt_thread_delay(20);
        }

        // 订阅信息处理
        ptr = strstr(tmp, "+TCMQTTRCVPUB: ");
        if (ptr != NULL)
        {
            printk("UART1-RX: %s", ptr);
            L610_process(ptr);
        }
    }
}

void L610_thread_init(void)
{
    m_L610_thread = rt_thread_create("L610thread",
                                     L610_thread,
                                     NULL,         // arg
                                     1024*4,       // statck size
                                     11,           // priority
                                     5);          // slice ticks

    if (m_L610_thread == NULL)
    {
        rt_kprintf("create L610 thread fail!\r\n");
    }
    else
    {
        rt_thread_startup(m_L610_thread);
    }
}

