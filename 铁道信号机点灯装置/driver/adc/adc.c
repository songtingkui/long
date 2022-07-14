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


/***********************************************************************
��������:         ����ж��Ƿ��
�������:

�������:         ��
��������ֵ˵��:    1 ȫ���жϴ�   0 ȫ���жϹر�
ʹ�õ���Դ:        ��
***********************************************************************/
INT8U IsGlobalIntOpen(void)
{
    unsigned int val = 0;
    asm volatile("mfc0  %0, $12":"=r" (val));

    return val&0x01;
}

/***********************************************************************
��������:         �ر����жϺ���
�������:         ��

�������:         ��
��������ֵ˵��:
ʹ�õ���Դ:    	  ��
***********************************************************************/
void DisableInt(void)
{
    asm volatile(					\
		"nop;nop;nop;\n"			\
		"mfc0   $8, $12;\n"			\
		"li     $9, 0xffff00fe;\n"	\
		"and    $10, $8, $9;\n"		\
		"mtc0   $10, $12;\n"		\
		"nop;nop;nop;\n"			\
		:::"$8","$9","$10"			\
		);
}

/***********************************************************************
��������:         �����жϺ���
�������:         ��

�������:         ��
��������ֵ˵��:
ʹ�õ���Դ:    	  ��
***********************************************************************/
void EnableInt(void)
{
    asm volatile(					\
        "nop;nop;nop;\n"			\
        "mfc0   $8, $12;\n"			\
        "li     $9, 0xffff00fe;\n"	\
        "and    $10, $8, $9;\n"		\
        "li     $9, 0xff01;\n"		\
        "or     $8, $10, $9;\n"		\
        "mtc0   $8, $12;\n"			\
        "nop;nop;nop;\n"			\
        :::"$8","$9","$10"			\
        );
}


/***********************************************************************
��������:         ADC��ʼ������
�������:         ��

�������:         ��
��������ֵ˵��:
ʹ�õ���Դ:    	  ��
***********************************************************************/
void ls1d_ADC_int(void)
{
   WriteKeyReg(spPMU_ChipCtrl->adc_on, 1);    //����ADCI0Ϊ����
   WriteKeyReg(spPMU_ChipCtrl->adc_en, 7);    //�ر�ADCI0Ϊģ���ź�
}

/***********************************************************************
��������:         �����˿ڼ����
�������:         channel

�������:         result
��������ֵ˵��:
ʹ�õ���Դ:    	  ��
***********************************************************************/
INT32U ls1d_ADC_MEASURE(volatile char channel)
{
	PMU_AdcCtrl = 0x100 | channel;                //��ʼ������ѡ������˿�,2��Ƶ
	while((PMU_AdcCtrl & (1<<8)));               //�жϲ����Ƿ����

	INT32U result = PMU_AdcDat;                  //�����������

	return result;
}

/***********************************************************************
��������:         ����ADC_I4��ѹ ������ADC_I5��ѹ
�������:         ��

�������:         result3
��������ֵ˵��:
ʹ�õ���Դ:    	  ��
***********************************************************************/
INT32U ls1d_ADC_SORT1(void)
{
    int result1,result2,result3;

    result1 = ls1d_ADC_MEASURE(3);
    result2 = ls1d_ADC_MEASURE(4);

    result3 = 12730UL * result2 / result1;

    return result3;
}

INT32U ls1d_ADC_SORT2(void)
{
    int resul1,resul2,resul3;

    resul1 = ls1d_ADC_MEASURE(3);
    resul2 = ls1d_ADC_MEASURE(5);

    resul3 = 12730UL * resul2 / resul1;

    return resul3;
}

/***********************************************************************
��������:         ��������ֵ
�������:         ��

�������:         result3
��������ֵ˵��:
ʹ�õ���Դ:    	  ��
***********************************************************************/
INT32U ls1d_ADC_SORT3(void)
{
    int resul1,resul2,resul3;

    resul1 = ls1d_ADC_MEASURE(2);
    resul2 = ls1d_ADC_MEASURE(6);

    resul3 = 2683UL * resul2 / resul1;

    return resul3;
}


