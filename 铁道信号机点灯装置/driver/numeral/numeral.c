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
#include "numeral.h"
#include "uart.h"

/***********************************************************************
函数功能:         初始化配置拨码GPIO
输入参数:         无

输出参数:         无
函数返回值说明:
使用的资源:    	  无
***********************************************************************/
void BOMA_Init(void)
{
    gpio_enable(28,DIR_IN,0);
    gpio_enable(29,DIR_IN,0);
    gpio_enable(30,DIR_IN,0);
    gpio_enable(31,DIR_IN,0);

    gpio_enable(34,DIR_IN,1);
    gpio_enable(33,DIR_IN,1);
    gpio_enable(35,DIR_IN,1);
    gpio_enable(32,DIR_IN,1);

    gpio_enable(38,DIR_IN,1);
    gpio_enable(36,DIR_IN,1);
    gpio_enable(39,DIR_IN,1);
    gpio_enable(37,DIR_IN,1);

    gpio_enable(47,DIR_IN,1);
    gpio_enable(44,DIR_IN,1);
    gpio_enable(46,DIR_IN,1);
    gpio_enable(45,DIR_IN,1);

    gpio_enable(2,DIR_OUT,0);
    g_stroadwayData.isMainLed  = 0;

    // 本机ID
    g_stroadwayData.led_type   = BOMA1() & 0x0F;
    g_stroadwayData.led_place  = BOMA2() & 0x07;
    g_stroadwayData.led_number = BOMA3() & 0x0F;
    g_stroadwayData.set_voltage= 6000 + BOMA4() * ((15000 - 6000) / 15);
}

/***********************************************************************
函数功能:         BOMA1
输入参数:         无

输出参数:         无
函数返回值说明:
使用的资源:    	  无
***********************************************************************/
int BOMA1(void)
{
    int BOMA_val;

    BOMA_val  = (gpio_read(29) << 0);
    BOMA_val |= (gpio_read(30) << 1);
    BOMA_val |= (gpio_read(31) << 2);
    BOMA_val |= (gpio_read(28) << 3);

    return (~BOMA_val) & 0x0F;
}

/***********************************************************************
函数功能:         BOMA2
输入参数:         无

输出参数:         无
函数返回值说明:
使用的资源:    	  无
***********************************************************************/
int BOMA2(void)
{
    int BOMA_val;

    BOMA_val  = (gpio_read(33) << 0);
    BOMA_val |= (gpio_read(35) << 1);
    BOMA_val |= (gpio_read(32) << 2);
    BOMA_val |= (gpio_read(34) << 3);

    return (~BOMA_val) & 0x0F;
}

/***********************************************************************
函数功能:         BOMA3
输入参数:         无

输出参数:         无
函数返回值说明:
使用的资源:    	  无
***********************************************************************/
int BOMA3(void)
{
    int BOMA_val;

    BOMA_val  = (gpio_read(36) << 0);
    BOMA_val |= (gpio_read(39) << 1);
    BOMA_val |= (gpio_read(37) << 2);
    BOMA_val |= (gpio_read(38) << 3);

    return (~BOMA_val) & 0x0F;
}

/***********************************************************************
函数功能:         BOMA4
输入参数:         无

输出参数:         无
函数返回值说明:
使用的资源:    	  无
***********************************************************************/
int BOMA4(void)
{
    int BOMA_val;

    BOMA_val  = (gpio_read(44) << 0);
    BOMA_val |= (gpio_read(46) << 1);
    BOMA_val |= (gpio_read(45) << 2);
    BOMA_val |= (gpio_read(47) << 3);

    return (~BOMA_val) & 0x0F;
}

