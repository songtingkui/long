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


INT32U g_u32usartcommt;             // ���ռ�����
INT8U  g_u8SendStatusMark;          // DTMF����Ӧ���־

static INT8U g_u8usartBuffer[16];   // ���ջ�����
static INT32U g_u32comreciTick;     // ���ճ�ʱ������


/***********************************************************************
��������:         ���ճ�ʼ��
�������:         ��

�������:         ��
��������ֵ˵��:
ʹ�õ���Դ:    	  ��
***********************************************************************/
void recv_dtmf_init(void)
{
    // DTMF���ռ�����
    g_u32usartcommt    = 0;
    g_u8SendStatusMark = 0;
    g_u32comreciTick   = 0;

    // �رմ����������
    spPMU_ChipCtrl->tsensor_off = 1;

    // ���ö˿�ģʽ������
    gpio_enable(23, DIR_IN, GPIO_HIGH);
    gpio_enable(24, DIR_IN, GPIO_HIGH);
    gpio_enable(25, DIR_IN, GPIO_HIGH);
    gpio_enable(26, DIR_IN, GPIO_HIGH);
    gpio_enable(27, DIR_IN, GPIO_HIGH);

    // ����ExINT
    PMU_ExintCLr  = bit(15);
    PMU_ExintPol  = 0;
    PMU_ExintEdge = bit(15);
    PMU_ExintEn   = bit(15);
//  PMU_CmdSts   |= CMDSR_EXINTEN;
}

/***********************************************************************
��������:         ����DTMF
�������:         ��

�������:         ��
��������ֵ˵��:
ʹ�õ���Դ:    	  ��
***********************************************************************/
static INT8U u8_recv_dtmf_chk;

void recv_dtmf_loop(void)
{
    INT32U dtmf;

    if (PMU_ExintSrc & bit(15))
    {
        // ����ⲿ�жϱ�־
        PMU_ExintCLr = bit(15);

        // ����
        dtmf  = gpio_read(27) << 0;
        dtmf |= gpio_read(26) << 1;
        dtmf |= gpio_read(25) << 2;
        dtmf |= gpio_read(24) << 3;

        // ����ʱ��
        g_u32comreciTick = get_clock_ticks();

        // ���ս���
        switch(g_u32usartcommt)
        {
            case 0:
                if (0x0F != dtmf)
                {
                    break;
                }

                // У������
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
��������:         DTMF�����
�������:         ��

�������:         ��
��������ֵ˵��:
ʹ�õ���Դ:    	  ��
***********************************************************************/
void recv_dtmf_check(void)
{
    INT32U val;

    // ����У��
    if (0 == (u8_recv_dtmf_chk & 0x0F))
    {
        // �źŻ�IDʶ��
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

        // ����ʶ��
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

        // ������λ����Ӧ��־
        g_u8SendStatusMark = 1;
    }
}


/***********************************************************************
��������:         �����źŻ�״̬����
�������:         ��

�������:         ��
��������ֵ˵��:
ʹ�õ���Դ:    	  ��
***********************************************************************/
void send_XHJstatus(void)
{
    int i;
    INT8U sendBuf[10], val, current_val;

    // ʶ���־
    sendBuf[0] = 0x00;

    // �źŻ�ID
    sendBuf[1] = 0x00 | ((g_stroadwayData.led_place << 1) & 0x0E);
    sendBuf[2] = g_stroadwayData.led_type;
    sendBuf[3] = g_stroadwayData.led_number;

    // ������
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

    // У��
    val = 0;
    for (i = 0; i < 8; i++)
    {
        val += sendBuf[i];
    }
    sendBuf[8] = (-val) & 0x0F;

    send_dtmf_string(sendBuf, 9);
}

