/*
 * Copyright (C) 2020-2021 Suzhou Tiancheng Software Ltd.
 *
 * SPDX-License-Identifier: Apache-2.0
 */

/*
 * ls1b_gpio.h
 *
 *  Created on: 2014-8-31
 *      Author: Bian
 */

#ifndef LS1C101_GPIO_H_
#define LS1C101_GPIO_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "ls1c101.h"

#define DIR_IN      1
#define DIR_OUT     0

#define GPIO_LOW	0
#define GPIO_HIGH	1

#define GPIO_COUNT  64

/*
 * 使能GPIO端口
 * 参数:    ioNum   gpio端口序号
 *          dir     gpio方向. DIR_IN: 输入, DIR_OUT: 输出
 */
static inline void gpio_enable(int ioNum, int dir, int out)
{
    if ((ioNum >= 0) && (ioNum < GPIO_COUNT))
    {
        unsigned int register regIndex = ioNum / 16;
        unsigned int register bitVal   = 3 << ((ioNum % 16) * 2);
		*((volatile unsigned int *)(&g_pmu->IOSEL0) + regIndex) &= (~bitVal);
		
        if (DIR_IN == dir)
		{
			g_pmu->GPIOBit[ioNum] = 0;
        }
		else
		{
			if(GPIO_HIGH == out)
			{
				g_pmu->GPIOBit[ioNum] = 0x3;
			}
			else 
			{
				g_pmu->GPIOBit[ioNum] = 0x2;
			}
		}
    }
}

/*
 * 读GPIO端口, 该GPIO被设置为输入模式
 * 参数:    ioNum   gpio端口序号
 * 返回:    0或者1
 */
static inline int gpio_read(int ioNum)
{
    if ((ioNum >= 0) && (ioNum < GPIO_COUNT))
    {
		g_pmu->GPIOBit[ioNum] = 0;
		return g_pmu->GPIOBit[ioNum];
	}
	else
	{
		return -1;
	}
}

/*
 * 写GPIO端口, 该GPIO被设置为输出模式
 * 参数:    ioNum   gpio端口序号
 *          val     0或者1
 */
static inline void gpio_write(int ioNum, int out)
{
    if ((ioNum >= 0) && (ioNum < GPIO_COUNT))
    {
		if(GPIO_HIGH == out)
		{
			g_pmu->GPIOBit[ioNum] = 0x3;
		}
		else 
		{
			g_pmu->GPIOBit[ioNum] = 0x2;
		}
    }
}

/*
 * 关闭GPIO功能, 端口恢复默认设置
 * 参数:    ioNum   gpio端口序号
 */
static inline void gpio_disable(int ioNum)
{
    if ((ioNum >= 0) && (ioNum < GPIO_COUNT))
	{
		unsigned int register regIndex = ioNum / 16;
		
		*((volatile unsigned int *)(&g_pmu->IOSEL0) + regIndex) &= (~(3 << ((ioNum % 16) * 2)));
		*((volatile unsigned int *)(&g_pmu->IOSEL0) + regIndex) |= (1 << ((ioNum % 16) * 2));
	}
}

#ifdef __cplusplus
}
#endif

#endif /* LS1C101_GPIO_H_ */
