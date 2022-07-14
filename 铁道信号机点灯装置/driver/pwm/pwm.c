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
#include "uart.h"
#include "adc.h"


//�����������
#define  PWM_PLUSH_CONT     5000                // PWMһ������������ĸ���

volatile static INT32U PWM_Step;                // PWM�ߵ͵�ƽ����
volatile static INT32U PWM_High;                // PWM�ߵ�ƽ���������

void ls1c101_PWM_low(void);
void ls1c101_PWM_High(void);


/***********************************************************************
��������:         PWM��ʼ��
�������:         ��

�������:         ��
��������ֵ˵��:
ʹ�õ���Դ:    	  ��
***********************************************************************/
void ls1c101_PWM_Init(void)
{
    PWM_Step = 0;
    PWM_High = 100;

    TIMER_CFG = 0;
    TIMER_CNT = 0;
    TIMER_CMP = PWM_High;
    TIMER_STP = PWM_PLUSH_CONT - PWM_High;
    TIMER_CFG = 0x107;

    gpio_enable(1, DIR_OUT, GPIO_HIGH);
    INT_EN = INTC_TIMER;
}

/***********************************************************************
��������:         PWM�ж�����
�������:         ��

�������:         ��
��������ֵ˵��:
ʹ�õ���Դ:    	  ��
***********************************************************************/
void ls1c101_timer_isr(void *arg)
{
    if (0 == PWM_Step)
    {
        gpio_write(1, GPIO_LOW);

        PWM_Step = 1;
        TIMER_CFG = TIMER_CFG;
    }
    else
    {
        PWM_Step  = 0;

        TIMER_CFG = 0;
        TIMER_CNT = 0;
        TIMER_CMP = PWM_High;
        TIMER_STP = PWM_PLUSH_CONT - PWM_High;
        TIMER_CFG = 0x107;

        gpio_write(1, GPIO_HIGH);
    }
}


/***********************************************************************
��������:         �����ѹ����
�������:         ��

�������:         ��
��������ֵ˵��:
ʹ�õ���Դ:    	  ��
***********************************************************************/
void ls1c101_set_voltage(int voltage)
{
    if (voltage >= 15000)
    {
        voltage = 15000;
    }
    else if (voltage <= 5000)
    {
        voltage = 5000;
    }

    if (voltage > 12000)
    {
        PWM_High = (15000 - voltage) * 2400 / 1000;
    }
    else
    {
        PWM_High = 2000 + (15000 - voltage) * 167 / 1000;
    }
}

/***********************************************************************
��������:         �����ѹ�Զ�����
�������:         ��

�������:         ��
��������ֵ˵��:
ʹ�õ���Դ:    	  ��
***********************************************************************/
void ls1c101_adj_voltage(int voltage)
{
    //���������ѹ
    if (voltage < g_stroadwayData.set_voltage)
    {
        ls1c101_PWM_low();
    }

    if (voltage > g_stroadwayData.set_voltage)
    {
        ls1c101_PWM_High();
    }
}


////////////////////////////////////////////////////////////////////////////////////////////////////


/***********************************************************************
��������:         �����ѹ��С
�������:         ��

�������:         ��
��������ֵ˵��:
ʹ�õ���Դ:    	  ��
***********************************************************************/
void ls1c101_PWM_High(void)
{
    if (PWM_High <= 3000)
    {
        PWM_High += 1;
    }
    else if (PWM_High <= 4800)
    {
        PWM_High += 5;
    }
}

/***********************************************************************
��������:         �����ѹ����
�������:         ��

�������:         ��
��������ֵ˵��:
ʹ�õ���Դ:    	  ��
***********************************************************************/
void ls1c101_PWM_low(void)
{
    if (PWM_High >= 3000)
    {
        PWM_High -= 5;
    }
    else if (PWM_High >= 100)
    {
        PWM_High -= 1;
    }
}

