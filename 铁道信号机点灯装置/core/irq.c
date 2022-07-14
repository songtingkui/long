/*
 * Copyright (C) 2020-2021 Suzhou Tiancheng Software Ltd.
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <stdio.h>

#include "cpu.h"
#include "mips.h"

#include "irq.h"
#include "ls1c101.h"

//-----------------------------------------------------------------------------
// 中断 
//-----------------------------------------------------------------------------

const static irq_handler_t isr_table[] =
{
    ls1c101_software_isr,  // IP0
    ls1c101_ticker_isr,    // IP1
    ls1c101_wakeup_isr,    // IP2
    ls1c101_touch_isr,     // IP3
    ls1c101_uart2_isr,     // IP4

/* 
 * IP5 Interrupts 
 */
    ls1c101_batfail_isr,
    ls1c101_c32kfail_isr,
    ls1c101_c8mfail_isr,
    ls1c101_rtc_isr,
    ls1c101_adc_isr,

/* 
 * IP6 Interrupts 
 */
    ls1c101_timer_isr,     // INTC:0
    ls1c101_i2c_isr,       // INTC:1
    ls1c101_uart1_isr,     // INTC:2
    ls1c101_uart0_isr,     // INTC:3
    ls1c101_flash_isr,     // INTC:4
    ls1c101_spi_isr,       // INTC:5
    ls1c101_vpwm_isr,      // INTC:6
    ls1c101_dma_isr,       // INTC:7

/* 
 * IP7 Interrupts 
 */
    ls1c101_gpio0_isr,     // GPIO[7:0]
    ls1c101_gpio1_isr,
    ls1c101_gpio2_isr,
    ls1c101_gpio3_isr,
    ls1c101_gpio4_isr,
    ls1c101_gpio5_isr,
    ls1c101_gpio6_isr,
    ls1c101_gpio7_isr,

    ls1c101_gpio16_isr,    // GPIO[23:16]
    ls1c101_gpio17_isr,
    ls1c101_gpio18_isr,
    ls1c101_gpio19_isr,
    ls1c101_gpio20_isr,
    ls1c101_gpio21_isr,
    ls1c101_gpio22_isr,
    ls1c101_gpio23_isr,

    ls1c101_gpio32_isr,    // GPIO[39:32]
    ls1c101_gpio33_isr,
    ls1c101_gpio34_isr,
    ls1c101_gpio35_isr,
    ls1c101_gpio36_isr,
    ls1c101_gpio37_isr,
    ls1c101_gpio38_isr,
    ls1c101_gpio39_isr,

    ls1c101_gpio48_isr,    // GPIO[55:48]
    ls1c101_gpio49_isr,
    ls1c101_gpio50_isr,
    ls1c101_gpio51_isr,
    ls1c101_gpio52_isr,
    ls1c101_gpio53_isr,
    ls1c101_gpio54_isr,
    ls1c101_gpio55_isr,
};

/*
 * 默认中断 
 */
static void mips_default_isr(void *arg)
{
	register unsigned int sr;
	register unsigned int cause;
	register unsigned int vector = (unsigned int)arg;

	mips_get_sr(sr);
	mips_get_cause(cause);

	return;
}

/******************************************************************************
 * 中断函数定义为"弱函数" 
 */
__WEAK void ls1c101_software_isr(void *arg)     // IP0
{
    mips_default_isr(arg);
}

__WEAK void ls1c101_ticker_isr(void *arg)      // IP1
{
    mips_default_isr(arg);
}

__WEAK void ls1c101_wakeup_isr(void *arg)       // IP2
{
    mips_default_isr(arg);
}

__WEAK void ls1c101_touch_isr(void *arg)        // IP3
{
    mips_default_isr(arg);
}

__WEAK void ls1c101_uart2_isr(void *arg)        // IP4
{
    mips_default_isr(arg);
}

/* 
 * IP5 Interrupts 
 */
__WEAK void ls1c101_batfail_isr(void *arg)
{
    mips_default_isr(arg);
}

__WEAK void ls1c101_c32kfail_isr(void *arg)
{
    mips_default_isr(arg);
}

__WEAK void ls1c101_c8mfail_isr(void *arg)
{
    mips_default_isr(arg);
}

__WEAK void ls1c101_rtc_isr(void *arg)
{
    mips_default_isr(arg);
}

__WEAK void ls1c101_adc_isr(void *arg)
{
    mips_default_isr(arg);
}

/* 
 * IP6 Interrupts 
 */
__WEAK void ls1c101_timer_isr(void *arg)        // INTC:0
{
    mips_default_isr(arg);
}

__WEAK void ls1c101_i2c_isr(void *arg)          // INTC:1
{
    mips_default_isr(arg);
}

__WEAK void ls1c101_uart1_isr(void *arg)        // INTC:2
{
    mips_default_isr(arg);
}

__WEAK void ls1c101_uart0_isr(void *arg)        // INTC:3
{
    mips_default_isr(arg);
}

__WEAK void ls1c101_flash_isr(void *arg)        // INTC:4
{
    mips_default_isr(arg);
}

__WEAK void ls1c101_spi_isr(void *arg)          // INTC:5
{
    mips_default_isr(arg);
}

__WEAK void ls1c101_vpwm_isr(void *arg)         // INTC:6
{
    mips_default_isr(arg);
}

__WEAK void ls1c101_dma_isr(void *arg)          // INTC:7
{
    mips_default_isr(arg);
}

/* 
 * IP7 Interrupts 
 */
__WEAK void ls1c101_gpio0_isr(void *arg)        // GPIO[7:0]
{
    mips_default_isr(arg);
}

__WEAK void ls1c101_gpio1_isr(void *arg)
{
    mips_default_isr(arg);
}

__WEAK void ls1c101_gpio2_isr(void *arg)
{
    mips_default_isr(arg);
}

__WEAK void ls1c101_gpio3_isr(void *arg)
{
    mips_default_isr(arg);
}

__WEAK void ls1c101_gpio4_isr(void *arg)
{
    mips_default_isr(arg);
}

__WEAK void ls1c101_gpio5_isr(void *arg)
{
    mips_default_isr(arg);
}

__WEAK void ls1c101_gpio6_isr(void *arg)
{
    mips_default_isr(arg);
}

__WEAK void ls1c101_gpio7_isr(void *arg)
{
    mips_default_isr(arg);
}

__WEAK void ls1c101_gpio16_isr(void *arg)       // GPIO[23:16]
{
    mips_default_isr(arg);
}

__WEAK void ls1c101_gpio17_isr(void *arg)
{
    mips_default_isr(arg);
}

__WEAK void ls1c101_gpio18_isr(void *arg)
{
    mips_default_isr(arg);
}

__WEAK void ls1c101_gpio19_isr(void *arg)
{
    mips_default_isr(arg);
}

__WEAK void ls1c101_gpio20_isr(void *arg)
{
    mips_default_isr(arg);
}

__WEAK void ls1c101_gpio21_isr(void *arg)
{
    mips_default_isr(arg);
}

__WEAK void ls1c101_gpio22_isr(void *arg)
{
    mips_default_isr(arg);
}

__WEAK void ls1c101_gpio23_isr(void *arg)
{
    mips_default_isr(arg);
}

__WEAK void ls1c101_gpio32_isr(void *arg)       // GPIO[39:32]
{
    mips_default_isr(arg);
}

__WEAK void ls1c101_gpio33_isr(void *arg)
{
    mips_default_isr(arg);
}

__WEAK void ls1c101_gpio34_isr(void *arg)
{
    mips_default_isr(arg);
}

__WEAK void ls1c101_gpio35_isr(void *arg)
{
    mips_default_isr(arg);
}

__WEAK void ls1c101_gpio36_isr(void *arg)
{
    mips_default_isr(arg);
}

__WEAK void ls1c101_gpio37_isr(void *arg)
{
    mips_default_isr(arg);
}

__WEAK void ls1c101_gpio38_isr(void *arg)
{
    mips_default_isr(arg);
}

__WEAK void ls1c101_gpio39_isr(void *arg)
{
    mips_default_isr(arg);
}

__WEAK void ls1c101_gpio48_isr(void *arg)       // GPIO[55:48]
{
    mips_default_isr(arg);
}

__WEAK void ls1c101_gpio49_isr(void *arg)
{
    mips_default_isr(arg);
}

__WEAK void ls1c101_gpio50_isr(void *arg)
{
    mips_default_isr(arg);
}

__WEAK void ls1c101_gpio51_isr(void *arg)
{
    mips_default_isr(arg);
}

__WEAK void ls1c101_gpio52_isr(void *arg)
{
    mips_default_isr(arg);
}

__WEAK void ls1c101_gpio53_isr(void *arg)
{
    mips_default_isr(arg);
}

__WEAK void ls1c101_gpio54_isr(void *arg)
{
    mips_default_isr(arg);
}

__WEAK void ls1c101_gpio55_isr(void *arg)
{
    mips_default_isr(arg);
}

//-----------------------------------------------------------------------------
// 中断响应 
//-----------------------------------------------------------------------------

void c_interrupt_handler(void *arg)
{
	register unsigned int sr, cause, tmp;
    HW_PMU_t *pmu = (HW_PMU_t *)LS1C101_PMU_BASE;

	mips_get_sr(sr);
	mips_get_cause(cause);

	cause &= (sr & SR_IMASK);
	cause >>= CAUSE_IPSHIFT;

	/*
	 * IP0 Software0 Interrupt 
	 */
	if (cause & 0x01)
	{
	    ls1c101_software_isr((void *)LS1C101_IRQ_SOFTWARE);
	}

	/*
	 * IP1 CP0 Count/Compare Interrupt 
	 */
	if (cause & 0x02)
	{
	    ls1c101_ticker_isr((void *)LS1C101_IRQ_TICKER);
	}

	/*
	 * IP2 WAKEUP Interrupt 
	 */
	if ((cause & 0x04) & (pmu->CmdSts & (CMDSR_INTSRC_WAKE | CMDSR_INTEN_WAKE)))
	{
	    ls1c101_wakeup_isr((void *)LS1C101_IRQ_WAKEUP);
	    pmu->CommandW |= CMDSR_INTSRC_WAKE;
	}

	/*
	 * IP3 Touch Interrupt 
	 */
	if ((cause & 0x08) & (pmu->CmdSts & (CMDSR_INTSRC_TOUCH | CMDSR_INTEN_TOUCH)))
	{
	    ls1c101_touch_isr((void *)LS1C101_IRQ_TOUCH);
	    pmu->CommandW |= CMDSR_INTSRC_TOUCH;
	}

	/*
	 * IP4 UART2 Interrupt 
	 */
	if ((cause & 0x10) & (pmu->CmdSts & (CMDSR_INTSRC_UART2 | CMDSR_INTEN_UART2)))
	{
	    ls1c101_uart2_isr((void *)LS1C101_IRQ_UART2);
	    pmu->CommandW |= CMDSR_INTSRC_UART2;
	}

	/*
	 * IP5 INTC Interrupt 
	 */
	if (cause & 0x20)
	{
	    tmp = pmu->CmdSts;
	    
	    if (tmp & (CMDSR_INTSRC_ADC | CMDSR_INTEN_ADC))
	        ls1c101_adc_isr((void *)LS1C101_IRQ_ADC);
	        
	    if (tmp & (CMDSR_INTSRC_RTC | CMDSR_INTEN_RTC))
	        ls1c101_rtc_isr((void *)LS1C101_IRQ_RTC);
	    
	    if (tmp & (CMDSR_INTSRC_8MFAIL | CMDSR_INTEN_8MFAIL))
	        ls1c101_c8mfail_isr((void *)LS1C101_IRQ_C8MFAIL);
	    
	    if (tmp & (CMDSR_INTSRC_32KFAIL | CMDSR_INTEN_32KFAIL))
	        ls1c101_c32kfail_isr((void *)LS1C101_IRQ_C32KFAIL);
	    
	    if (tmp & (CMDSR_INTSRC_BATFAIL | CMDSR_INTEN_BATFAIL))
	        ls1c101_batfail_isr((void *)LS1C101_IRQ_BATFAIL);
	    
        pmu->CommandW |= CMDSR_INTSRC_ADC | 
                         CMDSR_INTSRC_RTC | 
                         CMDSR_INTSRC_8MFAIL |
                         CMDSR_INTSRC_32KFAIL |
                         CMDSR_INTSRC_BATFAIL;
    }

	/*
	 * IP6 INTC Interrupt
	 */
	if (cause & 0x40)
	{
	    HW_INTC_t *intc = (HW_INTC_t *)LS1C101_INTC_BASE;
	    tmp = (unsigned int)(intc->en & intc->out);
	    
	    if (tmp & INTC_DMA)
	        ls1c101_dma_isr((void *)LS1C101_IRQ_DMA);
	    if (tmp & INTC_VPWM)
	        ls1c101_vpwm_isr((void *)LS1C101_IRQ_VPWM);
	    if (tmp & INTC_SPI)
	        ls1c101_spi_isr((void *)LS1C101_IRQ_SPI);
        if (tmp & INTC_FLASH)
            ls1c101_flash_isr((void *)LS1C101_IRQ_FLASH);
        if (tmp & INTC_UART0)
            ls1c101_uart0_isr((void *)LS1C101_IRQ_UART0);
        if (tmp & INTC_UART1)  
            ls1c101_uart1_isr((void *)LS1C101_IRQ_UART1);
        if (tmp & INTC_I2C)  
            ls1c101_i2c_isr((void *)LS1C101_IRQ_I2C);
        if (tmp & INTC_TIMER)  
            ls1c101_timer_isr((void *)LS1C101_IRQ_TIMER);
          
	    intc->clr = 0xFF;         // clear interrupt flag
	}

    /*
     * IP7 External Interrupt: GPIO
     */     
	if ((cause & 0x80) && (pmu->CmdSts & CMDSR_INTSRC_EXTINT))
	{
	    int i;
	    tmp = pmu->ExIntEn & pmu->ExIntSrc;
	    for (i=0; i<32; i++)
	    {
            if (tmp & bit(i))
            {
                isr_table[LS1C101_IRQ_GPIO_BASE + i]((void *)LS1C101_IRQ_GPIO_BASE + i);
            }
        }

        pmu->CommandW |= CMDSR_INTSRC_EXTINT;
	}
}

//-----------------------------------------------------------------------------
// SW0/SW1 Interrupt Support
//-----------------------------------------------------------------------------

/* Generate a software interrupt */
int assert_sw_irq(unsigned int irqnum)
{
    register unsigned int cause;

    if (irqnum <= 1) 
    {
        mips_get_cause(cause);
        cause = cause | ((irqnum + 1) << CAUSE_IPSHIFT);
        mips_set_cause(cause);

        return irqnum;
    } 
    else 
    {
        return -1;
    }
}

/* Clear a software interrupt */
int negate_sw_irq(unsigned int irqnum)
{
	register unsigned int cause;

    if (irqnum <= 1)
    {
        mips_get_cause(cause);
        cause = cause & ~((irqnum + 1) << CAUSE_IPSHIFT);
        mips_set_cause(cause);

        return irqnum;
    }
    else 
    {
        return -1;
    }
}

//-----------------------------------------------------------------------------


