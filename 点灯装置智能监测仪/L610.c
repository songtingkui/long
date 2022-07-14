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

    sprintf(buf, "����: %s - V = %.1f, I = %.1f", pAttrib->Signal_name, pAttrib->Signal_voltage, pAttrib->Signal_current);
    mqtt_showinfo(buf);

    // {"method":"report","params":{"V":33}}
    // ��ѹ��������1λС��
    // �澯��0����˿��1����˿��3�״������л�����˿��>=4����
    // ID: �źŻ�����-�źŻ��ɵ�-�źŻ���λ
    // �źŻ����ͣ�0���� 2��վ(����) 3��վ(����) 4��վ������1��
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
                    // �źŻ�ID: ���ͣ��ɵ�����λ
                    index  = location & 0x0007;
                    index |= (track << 4) & 0x00F0;
                    index |= (type  << 8) & 0x0F00;

                    // �źŻ�ID����
                    index = FindXHJindex(index);
                    if (index < XHJ_ID_MAX)
                    {
                        char buf[32];
                        sprintf(buf, "�յ�: %s - V = %.1f", g_XHJ_attribute[index].Signal_name, voltage);
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
                    mqtt_showinfo("�յ�: datetimes");
                    g_mqtt_connect_ok = 1;

                    // ϵͳʱ������RTC
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

    // ��ʼ������
    ls1x_uart_init(devUART1, NULL);
    ls1x_uart_open(devUART1, NULL);

    // ��ʼ��L610
    mqtt_showinfo("L610ģ���ʼ��");
    l610_at_check();
    mqtt_showinfo("L610ģ������");
    l610_cpin_check();
    mqtt_showinfo("SIM����ʼ����");
    l610_eps_check();
    mqtt_showinfo("4G������������");
    l610_ip_allo();
    mqtt_showinfo("����ն�IP��ַ");
    rt_thread_delay(1000);

    // ��ʼ��MQTT
//  l610_xinxi_shezhi();                    // ƽ̨��Ϣ���ò���, L610ģ����籣��
    mqtt_showinfo("MQTTӦ�ó�ʼ��");
    l610_MQTT_connect();
    mqtt_showinfo("MQTT�����ӷ�����");
    l610_dingyue_xiaoxi();
    mqtt_showinfo("����Top���ĳɹ�");

    // ����ʱ��ͬ����Ϣ
    l610_fabu_xiaoxi("{\\\"datetimes\\\":\\\"\\\"}");
    mqtt_showinfo("�ȴ�ʱ��ͬ���ź�");

    // ���ն�����Ϣ����
    while (1)
    {
        // ����AT���ݰ����ճ�ֵ
        rt  = 0;
        ptr = tmp;

        while (1)
        {
            // 2ms�������
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
                    // �������AT���ݰ�����
                    rt  = 0;
                    ptr = tmp;
                }
            }
            
            rt_thread_delay(20);
        }

        // ������Ϣ����
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

