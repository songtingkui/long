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
// 以下两个函数实现: 龙芯1B与L610的通讯.
//-----------------------------------------------------------------------------

/*
 * 通过 UART1 向 L610 模块发送 AT 命令
 */
static int send_at_command(char *buf)
{
    int rt;

    rt = ls1x_uart_write(devUART1, buf, strlen(buf), (void *)NULL);
    printk("UART1-TX: %s", buf);

    return rt;
}

/*
 * 从 UART1 读取 L610 模块的应答信息
 *
 * 参数:    verstr:     检查接收的字符串中是否包含该字符串
 *          endstr:     接收的字符串以此结尾
 *          waitms:     接收等待超时
 *
 * 返回:    >0:         包含字符串 verstr
 *          <=0:        接收错误
 */
static int wait_for_reply(const char *verstr, const char *endstr, int waitms)
{
    char tmp[258], *ptr = tmp;
    char end[66];
    int  rt = 0, tmo;

    // 默认超时：1000ms
    tmo = waitms > 0 ? waitms : 1000;

    // 检查设置结束字符否
    if ((endstr == NULL) || (strlen(endstr) == 0))
    {
        rt_thread_delay(tmo);
        rt = ls1x_uart_read(devUART1, ptr, 3, (void *)0);
    }
    else
    {
        /*
         * AT接收字符总是以 "\r\n" 结束
         */
        snprintf(end, 64, "%s\r\n", endstr);

        while (tmo > 0)
        {
            /*
             * 每次读超时2ms
             */
            int readed = ls1x_uart_read(devUART1, ptr, 256 - rt, (void *)0);
            if (readed > 0)
            {
                ptr += readed;
                *ptr = 0;

                // 包含结束字符串?
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
     * AT接收字符总是以 "\r\n" 结束
     */
    if (rt <= 2)
    {
        return -1;
    }
    printk("UART1-RX: %s", tmp);

    // 检查设置判断字符
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
 * 检测模块AT指令状态，回复OK可以正常发送AT指令，结束后
 * 清除buffer。
 * 对应AT指令：AT
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
 * 检查SIM卡状态，如果SIM卡状态不正常，模块就无法正常建立无线通信
 * 对应AT指令 ：AT+CPIN?
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
 * 查询EPS服务是否可用,检查模块网络是否正常
 * 对应AT指令：AT+CEREG?
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
 * 请求运营商分配IP
 * 对应AT指令：AT+mipcall =
 * 运营商不同本条指令有区别
 */
void l610_ip_allo(void)
{
    // 先断开MQTT，防止影响后续操作
    send_at_command("AT+TCMQTTDISCONN\r\n");
    wait_for_reply(NULL, NULL, 1000);

    do
    {
        send_at_command("AT+MIPCALL=0\r\n");
        wait_for_reply(NULL, NULL, 1000);

        // 请求运营商分配 IP
        send_at_command("AT+MIPCALL=1,\"ctnet\"\r\n");
        wait_for_reply(NULL, "OK", 2000);
        wait_for_reply(NULL, NULL, 1000);

        // 检查是否分配IP
        send_at_command("AT+MIPCALL?\r\n");
    }
    while (wait_for_reply("+MIPCALL: 1", "OK", 1000) <= 0);
}

//-----------------------------------------------------------------------------

/**
 * 设置 MQTT 连接参数并连接
 * 对应AT指令：AT+TCMQTTCONN=1,5000,60,0,1
 */
void l610_MQTT_connect(void)
{
    do
    {
        send_at_command("AT+TCMQTTDISCONN\r\n");
        wait_for_reply(NULL, NULL, 1000);

        send_at_command("AT+TCMQTTCONN=1,5000,60,0,1\r\n");

        // 如果输入合法,首先返回 OK,接下来返回设备信息设置成功与否
        wait_for_reply(NULL, "OK", 1000);
    }
    while (wait_for_reply("+TCMQTTCONN: ", "OK", 10000) <= 0);
}

/**
 * 平台信息设置参数
 * 对应AT指令：AT+TCDEVINFOSET=1,"productId","devicename","deviceSecret"
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

        // 如果输入合法,首先返回 OK,接下来返回设备信息设置成功与否
        wait_for_reply(NULL, "OK", 1000);
    }
    while (wait_for_reply("+TCDEVINFOSET: ", "OK", 1000) <= 0);
}

/**
 * 订阅消息
 * 对应AT指令：AT+TCMQTTSUB=" $thing/up/property/OD4TDTVVHH/teleseme2 ",1
 * 注意：同一Top下可以发送 腾讯系统信息，也可以是用户自定义信息
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

        // 如果输入合法,首先返回 OK,接下来返回设备信息设置成功与否
        wait_for_reply(NULL, "OK", 1000);
    }
    while (wait_for_reply("+TCMQTTSUB: ", "OK", 10000) <= 0);
}

/**
 * 订阅消息: Top序号
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
 * 发布消息 (JSON格式)
 * 对应AT指令：AT+TCMQTTPUB="topic",qos,"message"
 */
void l610_fabu_xiaoxi(char *data)
{
    send_at_command(SENDTOPIC);
    send_at_command(QOS);

    send_at_command(",\"");
    send_at_command(data);
    send_at_command("\"\r\n");
}

