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
函数功能:         检测中断是否打开
输入参数:

输出参数:         无
函数返回值说明:    1 全局中断打开   0 全局中断关闭
使用的资源:        无
***********************************************************************/
INT8U IsGlobalIntOpen(void)
{
    unsigned int val = 0;
    asm volatile("mfc0  %0, $12":"=r" (val));

    return val&0x01;
}

/***********************************************************************
函数功能:         关闭总中断函数
输入参数:         无

输出参数:         无
函数返回值说明:
使用的资源:    	  无
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
函数功能:         打开总中断函数
输入参数:         无

输出参数:         无
函数返回值说明:
使用的资源:    	  无
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
函数功能:         ADC初始化配置
输入参数:         无

输出参数:         无
函数返回值说明:
使用的资源:    	  无
***********************************************************************/
void ls1d_ADC_int(void)
{
   WriteKeyReg(spPMU_ChipCtrl->adc_on, 1);    //设置ADCI0为常开
   WriteKeyReg(spPMU_ChipCtrl->adc_en, 7);    //关闭ADCI0为模拟信号
}

/***********************************************************************
函数功能:         测量端口及结果
输入参数:         channel

输出参数:         result
函数返回值说明:
使用的资源:    	  无
***********************************************************************/
INT32U ls1d_ADC_MEASURE(volatile char channel)
{
	PMU_AdcCtrl = 0x100 | channel;                //开始测量与选择测量端口,2分频
	while((PMU_AdcCtrl & (1<<8)));               //判断测量是否结束

	INT32U result = PMU_AdcDat;                  //测量结果整合

	return result;
}

/***********************************************************************
函数功能:         测量ADC_I4电压 ，测量ADC_I5电压
输入参数:         无

输出参数:         result3
函数返回值说明:
使用的资源:    	  无
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
函数功能:         测量电流值
输入参数:         无

输出参数:         result3
函数返回值说明:
使用的资源:    	  无
***********************************************************************/
INT32U ls1d_ADC_SORT3(void)
{
    int resul1,resul2,resul3;

    resul1 = ls1d_ADC_MEASURE(2);
    resul2 = ls1d_ADC_MEASURE(6);

    resul3 = 2683UL * resul2 / resul1;

    return resul3;
}


