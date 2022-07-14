/*
 * Copyright (C) 2020-2021 Suzhou Tiancheng Software Ltd.
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <stdio.h>

#include "bsp.h"

#include "cpu.h"
#include "mips.h"

#include "clock.h"

#define CLOCK_INT_MASK  SR_IM1

/*
 * In "mips_timer.S"
 */
extern void mips_set_timer(unsigned int timer_clock_interval);
extern unsigned int mips_get_timer(void);

/*
 * global Variable
 */
unsigned int freq_inner_8M = 0;

/*
 * local Variable
 */
static unsigned int mips_timer_step = 0;            /* tick 每次累加计数的 */

static volatile unsigned int Clock_driver_ticks;    /* Clock ticks since initialization */

/*
 *  Clock_isr
 *
 *  This is the clock tick interrupt handler.
 */
void ls1c101_ticker_isr(void *arg)
{
	Clock_driver_ticks += 1;
    mips_set_timer(mips_timer_step);
}

/*
 * Clock_initialize
 */
void Clock_initialize(void)
{
    // register unsigned int cause;
    
	Clock_driver_ticks = 0;
	
	mips_mask_interrupt(CLOCK_INT_MASK);

    /*
     * divided by 2: LS1x-counter plus 1 by two instructions. 
     *
     * 这个内置晶振频率在寄存器 0xBF0201B0 中?
     *
     */
    freq_inner_8M = 8000000;//(*(volatile unsigned int *)0xBF0201B0) * 1000;
    mips_timer_step  = freq_inner_8M / 1000;

    mips_set_timer(mips_timer_step);  

 //   printf("\r\nClock_mask: %x, step=%i\n", CLOCK_INT_MASK, mips_timer_step);

    /* Enable Clock */
    mips_unmask_interrupt(CLOCK_INT_MASK);
    
    mips_enable_dc();
}

void Clock_exit(void)
{
    mips_mask_interrupt(CLOCK_INT_MASK);
}

/******************************************************************************/

unsigned int get_clock_ticks(void)
{
    return Clock_driver_ticks;
}

/****************************************************************************** 
 * 延时程序 
 */
void delay_us(unsigned int us)
{
	register unsigned int startVal;
	register unsigned int endVal;
	register unsigned int curVal;
	asm volatile ("mfc0 %0, $9;" : "=&r"(startVal));
	endVal = startVal + us * (mips_timer_step / 1000);
	while (1)
    {
		asm volatile ("mfc0 %0, $9;" : "=&r"(curVal));
		if (((endVal > startVal) && (curVal >= endVal)) ||
		    ((endVal < startVal) && (curVal < startVal) && (curVal >= endVal)))
			break;
	}
}

void delay_ms(unsigned int ms)
{
#if 0
    register unsigned int endVal;
    endVal = get_clock_ticks() + ms;
    while (get_clock_ticks() <= endVal)
        continue;
#else
    delay_us(ms*1000);
#endif
}


