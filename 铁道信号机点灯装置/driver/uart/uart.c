/*
 * Copyright (C) 2020-2021 Suzhou Tiancheng Software Ltd.
 *
 * SPDX-License-Identifier: Apache-2.0
 */

/*
 * ls1x_gpio.c
 *
 * created: 2020/11/2
 *  author: Bian
 */

#include <stdio.h>
#include "bsp.h"
#include "ls1c101_gpio.h"
#include "ls1c101.h"
#include "uart.h"
#include "adc.h"
#include "pwm.h"
#include "dtmf.h"


INT32U g_u32usartcommt;             // 接收计数器
INT8U  g_u8SendStatusMark;          // DTMF命令应答标志

static INT8U g_u8usartBuffer[16];   // 接收缓冲区
static INT32U g_u32comreciTick;     // 接收超时计数器


/***********************************************************************
函数功能:         接收初始化
输入参数:         无

输出参数:         无
函数返回值说明:
使用的资源:    	  无
***********************************************************************/
void recv_dtmf_init(void)
{
    // DTMF接收计数器
    g_u32usartcommt    = 0;
    g_u8SendStatusMark = 0;
    g_u32comreciTick   = 0;

    // 关闭触摸按键检查
    spPMU_ChipCtrl->tsensor_off = 1;

    // 配置端口模式：输入
    gpio_enable(23, DIR_IN, GPIO_HIGH);
    gpio_enable(24, DIR_IN, GPIO_HIGH);
    gpio_enable(25, DIR_IN, GPIO_HIGH);
    gpio_enable(26, DIR_IN, GPIO_HIGH);
    gpio_enable(27, DIR_IN, GPIO_HIGH);

    // 配置ExINT
    PMU_ExintCLr  = bit(15);
    PMU_ExintPol  = 0;
    PMU_ExintEdge = bit(15);
    PMU_ExintEn   = bit(15);
//  PMU_CmdSts   |= CMDSR_EXINTEN;
}

/***********************************************************************
函数功能:         接收DTMF
输入参数:         无

输出参数:         无
函数返回值说明:
使用的资源:    	  无
***********************************************************************/
static INT8U u8_recv_dtmf_chk;

void recv_dtmf_loop(void)
{
    INT32U dtmf;

    if (PMU_ExintSrc & bit(15))
    {
        // 清除外部中断标志
        PMU_ExintCLr = bit(15);

        // 接收
        dtmf  = gpio_read(27) << 0;
        dtmf |= gpio_read(26) << 1;
        dtmf |= gpio_read(25) << 2;
        dtmf |= gpio_read(24) << 3;

        // 接收时间
        g_u32comreciTick = get_clock_ticks();

        // 接收进程
        switch(g_u32usartcommt)
        {
            case 0:
                if (0x0F != dtmf)
                {
                    break;
                }

                // 校验清零
                u8_recv_dtmf_chk = 0;

            default:
                u8_recv_dtmf_chk += dtmf;
                g_u8usartBuffer[g_u32usartcommt] = dtmf;
                g_u32usartcommt++;
                break;
        }
    }
    else if (0 != g_u32usartcommt)
    {
        if ((INT32U)(get_clock_ticks() - g_u32comreciTick) >= 100ul)
        {
            g_u32usartcommt = 0;
        }
    }
}

/***********************************************************************
函数功能:         DTMF命令处理
输入参数:         无

输出参数:         无
函数返回值说明:
使用的资源:    	  无
***********************************************************************/
void recv_dtmf_check(void)
{
    INT32U val;

    // 建议校验
    if (0 == (u8_recv_dtmf_chk & 0x0F))
    {
        // 信号机ID识别
        if (g_stroadwayData.led_type != (g_u8usartBuffer[2] & 0x0F))
        {
            return ;
        }

        if (g_stroadwayData.led_place != ((g_u8usartBuffer[1] >> 1) & 0x07))
        {
            return ;
        }

        if (g_stroadwayData.led_number != g_u8usartBuffer[3])
        {
            return ;
        }

        // 操作识别
        if (0 != (g_u8usartBuffer[1] & 0x01))
        {
            val  = (INT8U)((g_u8usartBuffer[4] & 0x0F) | ((g_u8usartBuffer[5] << 4) & 0xF0));
            val *= 100UL;
            
            if (g_stroadwayData.set_voltage != val)
            {
                g_stroadwayData.set_voltage = val;
                ls1c101_set_voltage(g_stroadwayData.set_voltage);
            }
        }

        // 设置上位机响应标志
        g_u8SendStatusMark = 1;
    }
}


/***********************************************************************
函数功能:         发送信号机状态数据
输入参数:         无

输出参数:         无
函数返回值说明:
使用的资源:    	  无
***********************************************************************/
void send_XHJstatus(void)
{
    int i;
    INT8U sendBuf[10], val, current_val;

    // 识别标志
    sendBuf[0] = 0x00;

    // 信号机ID
    sendBuf[1] = 0x00 | ((g_stroadwayData.led_place << 1) & 0x0E);
    sendBuf[2] = g_stroadwayData.led_type;
    sendBuf[3] = g_stroadwayData.led_number;

    // 主副？
    if (0 == g_stroadwayData.isMainLed)
    {
        val = g_stroadwayData.zu_voltage / 100;
    }
    else
    {
        val = g_stroadwayData.fu_voltage / 100;
    }
    sendBuf[4] = (val >> 0) & 0x0F;
    sendBuf[5] = (val >> 4) & 0x0F;

    current_val = (g_stroadwayData.current / 100) & 0x3F;
    sendBuf[6] = ((current_val >> 2) & 0x0C) | (g_stroadwayData.isMainLed & 0x01);
    sendBuf[7] =  (current_val >> 0) & 0x0F;

    // 校验
    val = 0;
    for (i = 0; i < 8; i++)
    {
        val += sendBuf[i];
    }
    sendBuf[8] = (-val) & 0x0F;

    send_dtmf_string(sendBuf, 9);
}

