/******************************************************************************
 *                       @ Copyright 2014 - 2020                              *
 *                           www.diysoon.com                                  *
 ******************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "bsp.h"
#include "ns16550.h"
#include "L610_Init.h"
#include "rtthread.h"

//-----------------------------------------------------------------------------
// ������������ʵ��: ��о1B��L610��ͨѶ.
//-----------------------------------------------------------------------------

/*
 * ͨ�� UART1 �� L610 ģ�鷢�� AT ����
 */
static int send_at_command(char *buf)
{
    int rt;

    rt = ls1x_uart_write(devUART1, buf, strlen(buf), (void *)NULL);
    printk("UART1-TX: %s", buf);

    return rt;
}

/*
 * �� UART1 ��ȡ L610 ģ���Ӧ����Ϣ
 *
 * ����:    verstr:     �����յ��ַ������Ƿ�������ַ���
 *          endstr:     ���յ��ַ����Դ˽�β
 *          waitms:     ���յȴ���ʱ
 *
 * ����:    >0:         �����ַ��� verstr
 *          <=0:        ���մ���
 */
static int wait_for_reply(const char *verstr, const char *endstr, int waitms)
{
    char tmp[258], *ptr = tmp;
    char end[66];
    int  rt = 0, tmo;

    // Ĭ�ϳ�ʱ��1000ms
    tmo = waitms > 0 ? waitms : 1000;

    // ������ý����ַ���
    if ((endstr == NULL) || (strlen(endstr) == 0))
    {
        rt_thread_delay(tmo);
        rt = ls1x_uart_read(devUART1, ptr, 3, (void *)0);
    }
    else
    {
        /*
         * AT�����ַ������� "\r\n" ����
         */
        snprintf(end, 64, "%s\r\n", endstr);

        while (tmo > 0)
        {
            /*
             * ÿ�ζ���ʱ2ms
             */
            int readed = ls1x_uart_read(devUART1, ptr, 256 - rt, (void *)0);
            if (readed > 0)
            {
                ptr += readed;
                *ptr = 0;

                // ���������ַ���?
                rt  += readed;
                if ((rt >= 256) || strstr(tmp, end))
                {
                    break;
                }
            }

            rt_thread_delay(20);
            tmo -= 20;
        }
    }

    /*
     * AT�����ַ������� "\r\n" ����
     */
    if (rt <= 2)
    {
        return -1;
    }
    printk("UART1-RX: %s", tmp);

    // ��������ж��ַ�
    if ((verstr != NULL) && (strlen(verstr) > 0))
    {
        if (strstr(tmp, verstr) != NULL)
            return rt;
        else
            return -1;
    }

    return rt;
}


//-----------------------------------------------------------------------------


/**
 * ���ģ��ATָ��״̬���ظ�OK������������ATָ�������
 * ���buffer��
 * ��ӦATָ�AT
 */
void l610_at_check(void)
{
    do
    {
        send_at_command("AT\r\n");
    }
    while (wait_for_reply(NULL, "OK", 1000) <= 0);
}

/**
 * ���SIM��״̬�����SIM��״̬��������ģ����޷�������������ͨ��
 * ��ӦATָ�� ��AT+CPIN?
 */
void l610_cpin_check(void)
{
    do
    {
        send_at_command("AT+CPIN?\r\n");
    }
    while (wait_for_reply("+CPIN: READY", "OK", 1000) <= 0);
}

/**
 * ��ѯEPS�����Ƿ����,���ģ�������Ƿ�����
 * ��ӦATָ�AT+CEREG?
 */
void l610_eps_check(void)
{
    do
    {
        send_at_command("AT+CEREG?\r\n");
    }
    while (wait_for_reply("+CEREG: 0", "OK", 1000) <= 0);
}

/**
 * ������Ӫ�̷���IP
 * ��ӦATָ�AT+mipcall =
 * ��Ӫ�̲�ͬ����ָ��������
 */
void l610_ip_allo(void)
{
    // �ȶϿ�MQTT����ֹӰ���������
    send_at_command("AT+TCMQTTDISCONN\r\n");
    wait_for_reply(NULL, NULL, 1000);

    do
    {
        send_at_command("AT+MIPCALL=0\r\n");
        wait_for_reply(NULL, NULL, 1000);

        // ������Ӫ�̷��� IP
        send_at_command("AT+MIPCALL=1,\"ctnet\"\r\n");
        wait_for_reply(NULL, "OK", 2000);
        wait_for_reply(NULL, NULL, 1000);

        // ����Ƿ����IP
        send_at_command("AT+MIPCALL?\r\n");
    }
    while (wait_for_reply("+MIPCALL: 1", "OK", 1000) <= 0);
}

//-----------------------------------------------------------------------------

/**
 * ���� MQTT ���Ӳ���������
 * ��ӦATָ�AT+TCMQTTCONN=1,5000,60,0,1
 */
void l610_MQTT_connect(void)
{
    do
    {
        send_at_command("AT+TCMQTTDISCONN\r\n");
        wait_for_reply(NULL, NULL, 1000);

        send_at_command("AT+TCMQTTCONN=1,5000,60,0,1\r\n");

        // �������Ϸ�,���ȷ��� OK,�����������豸��Ϣ���óɹ����
        wait_for_reply(NULL, "OK", 1000);
    }
    while (wait_for_reply("+TCMQTTCONN: ", "OK", 10000) <= 0);
}

/**
 * ƽ̨��Ϣ���ò���
 * ��ӦATָ�AT+TCDEVINFOSET=1,"productId","devicename","deviceSecret"
 */
#if 1
#define ProductID		"\"8G6SX32L49\","
#define DeviceName		"\"LONG1B\","
#define DeviceSecret	"\"9XKS81ZD6nfpsMkm6LD3jA==\"\r\n"
#else
#define ProductID		"\"7SIG0VBSLF\","
#define DeviceName		"\"X2\","
#define DeviceSecret	"\"hIpysiiPCGRepk/jk3tacA==\"\r\n"
#endif

void l610_xinxi_shezhi(void)
{
    do
    {
        send_at_command("AT+TCDEVINFOSET=1,");
        send_at_command(ProductID);
        send_at_command(DeviceName);
        send_at_command(DeviceSecret);

        // �������Ϸ�,���ȷ��� OK,�����������豸��Ϣ���óɹ����
        wait_for_reply(NULL, "OK", 1000);
    }
    while (wait_for_reply("+TCDEVINFOSET: ", "OK", 1000) <= 0);
}

/**
 * ������Ϣ
 * ��ӦATָ�AT+TCMQTTSUB=" $thing/up/property/OD4TDTVVHH/teleseme2 ",1
 * ע�⣺ͬһTop�¿��Է��� ��Ѷϵͳ��Ϣ��Ҳ�������û��Զ�����Ϣ
 */

#if 1
#define RCVTOPIC        "\"8G6SX32L49/LONG1B/data\","
#define SENDTOPIC		"AT+TCMQTTPUB=\"$thing/up/property/8G6SX32L49/LONG1B\","
#else
#define RCVTOPIC        "\"7SIG0VBSLF/X2/data\","
#define SENDTOPIC		"AT+TCMQTTPUB=\"$thing/up/property/7SIG0VBSLF/X2\","
#endif
#define QOS             "1"

void l610_dingyue_xiaoxi(void)
{
    do
    {
        send_at_command("AT+TCMQTTSUB=");
        send_at_command(RCVTOPIC);
        send_at_command(QOS);
        send_at_command("\r\n");

        // �������Ϸ�,���ȷ��� OK,�����������豸��Ϣ���óɹ����
        wait_for_reply(NULL, "OK", 1000);
    }
    while (wait_for_reply("+TCMQTTSUB: ", "OK", 10000) <= 0);
}

/**
 * ������Ϣ: Top���
 * +TCMQTTRCVPUB: "7SIG0VBSLF/X2/data",38,"{"method":"report","params":{"V":123}}"
 */
int l610_get_dingyue(char *data, char **pOut)
{
    *pOut = strstr(data, RCVTOPIC);
    if (NULL != *pOut)
    {
        *pOut += sizeof(RCVTOPIC);
        return 0;
    }

    return -1;
}

/**
 * ������Ϣ (JSON��ʽ)
 * ��ӦATָ�AT+TCMQTTPUB="topic",qos,"message"
 */
void l610_fabu_xiaoxi(char *data)
{
    send_at_command(SENDTOPIC);
    send_at_command(QOS);

    send_at_command(",\"");
    send_at_command(data);
    send_at_command("\"\r\n");
}

