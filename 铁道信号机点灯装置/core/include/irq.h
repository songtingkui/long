/*
 * Copyright (C) 2020-2021 Suzhou Tiancheng Software Ltd.
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#ifndef _LS1C101_IRQ_H
#define _LS1C101_IRQ_H

/******************************************************************************
 * 中断句柄类型
 */
typedef void(*irq_handler_t) (void *);

/******************************************************************************
 * 中断函数表索引, 50个 
 */
#define LS1C101_IRQ_SOFTWARE           0       // IP0
#define LS1C101_IRQ_TICKER             1       // IP1
#define LS1C101_IRQ_WAKEUP             2       // IP2
#define LS1C101_IRQ_TOUCH              3       // IP3
#define LS1C101_IRQ_UART2              4       // IP4

/* IP5 Interrupts */
#define LS1C101_IRQ_BATFAIL            5
#define LS1C101_IRQ_C32KFAIL           6
#define LS1C101_IRQ_C8MFAIL            7
#define LS1C101_IRQ_RTC                8
#define LS1C101_IRQ_ADC                9

/* IP6 Interrupts */
#define LS1C101_IRQ_TIMER              10      // INTC:0
#define LS1C101_IRQ_I2C                11      // INTC:1
#define LS1C101_IRQ_UART1              12      // INTC:2
#define LS1C101_IRQ_UART0              13      // INTC:3
#define LS1C101_IRQ_FLASH              14      // INTC:4
#define LS1C101_IRQ_SPI                15      // INTC:5
#define LS1C101_IRQ_VPWM               16      // INTC:6
#define LS1C101_IRQ_DMA                17      // INTC:7

/* IP7 Interrupts */
#define LS1C101_IRQ_GPIO_BASE          18
#define LS1C101_IRQ_GPIO0              18      // GPIO[7:0]
#define LS1C101_IRQ_GPIO1              19
#define LS1C101_IRQ_GPIO2              20
#define LS1C101_IRQ_GPIO3              21
#define LS1C101_IRQ_GPIO4              22
#define LS1C101_IRQ_GPIO5              23
#define LS1C101_IRQ_GPIO6              24
#define LS1C101_IRQ_GPIO7              25
#define LS1C101_IRQ_GPIO16             26      // GPIO[23:16]
#define LS1C101_IRQ_GPIO17             27
#define LS1C101_IRQ_GPIO18             28
#define LS1C101_IRQ_GPIO19             29
#define LS1C101_IRQ_GPIO20             30
#define LS1C101_IRQ_GPIO21             31
#define LS1C101_IRQ_GPIO22             32
#define LS1C101_IRQ_GPIO23             33
#define LS1C101_IRQ_GPIO32             34      // GPIO[39:32]
#define LS1C101_IRQ_GPIO33             35
#define LS1C101_IRQ_GPIO34             36
#define LS1C101_IRQ_GPIO35             37
#define LS1C101_IRQ_GPIO36             38
#define LS1C101_IRQ_GPIO37             39
#define LS1C101_IRQ_GPIO38             40
#define LS1C101_IRQ_GPIO39             41
#define LS1C101_IRQ_GPIO48             42      // GPIO[55:48]
#define LS1C101_IRQ_GPIO49             43
#define LS1C101_IRQ_GPIO50             44
#define LS1C101_IRQ_GPIO51             45
#define LS1C101_IRQ_GPIO52             46
#define LS1C101_IRQ_GPIO53             47
#define LS1C101_IRQ_GPIO54             48
#define LS1C101_IRQ_GPIO55             49

/******************************************************************************
 * 中断函数定义为"弱函数" 
 */

#define __WEAK  __attribute__((weak))

__WEAK void ls1c101_software_isr(void *arg);    // IP0
__WEAK void ls1c101_ticker_isr(void *arg);      // IP1
__WEAK void ls1c101_wakeup_isr(void *arg);      // IP2
__WEAK void ls1c101_touch_isr(void *arg);       // IP3
__WEAK void ls1c101_uart2_isr(void *arg);       // IP4

/* 
 * IP5 Interrupts 
 */
__WEAK void ls1c101_batfail_isr(void *arg);
__WEAK void ls1c101_c32kfail_isr(void *arg);
__WEAK void ls1c101_c8mfail_isr(void *arg);
__WEAK void ls1c101_rtc_isr(void *arg);
__WEAK void ls1c101_adc_isr(void *arg);

/* 
 * IP6 Interrupts 
 */
__WEAK void ls1c101_timer_isr(void *arg);       // INTC:0
__WEAK void ls1c101_i2c_isr(void *arg);         // INTC:1
__WEAK void ls1c101_uart1_isr(void *arg);       // INTC:2
__WEAK void ls1c101_uart0_isr(void *arg);       // INTC:3
__WEAK void ls1c101_flash_isr(void *arg);       // INTC:4
__WEAK void ls1c101_spi_isr(void *arg);         // INTC:5
__WEAK void ls1c101_vpwm_isr(void *arg);        // INTC:6
__WEAK void ls1c101_dma_isr(void *arg);         // INTC:7

/* 
 * IP7 Interrupts 
 */
__WEAK void ls1c101_gpio0_isr(void *arg);       // GPIO[7:0]
__WEAK void ls1c101_gpio1_isr(void *arg);
__WEAK void ls1c101_gpio2_isr(void *arg);
__WEAK void ls1c101_gpio3_isr(void *arg);
__WEAK void ls1c101_gpio4_isr(void *arg);
__WEAK void ls1c101_gpio5_isr(void *arg);
__WEAK void ls1c101_gpio6_isr(void *arg);
__WEAK void ls1c101_gpio7_isr(void *arg);

__WEAK void ls1c101_gpio16_isr(void *arg);      // GPIO[23:16]
__WEAK void ls1c101_gpio17_isr(void *arg);
__WEAK void ls1c101_gpio18_isr(void *arg);
__WEAK void ls1c101_gpio19_isr(void *arg);
__WEAK void ls1c101_gpio20_isr(void *arg);
__WEAK void ls1c101_gpio21_isr(void *arg);
__WEAK void ls1c101_gpio22_isr(void *arg);
__WEAK void ls1c101_gpio23_isr(void *arg);

__WEAK void ls1c101_gpio32_isr(void *arg);      // GPIO[39:32]
__WEAK void ls1c101_gpio33_isr(void *arg);
__WEAK void ls1c101_gpio34_isr(void *arg);
__WEAK void ls1c101_gpio35_isr(void *arg);
__WEAK void ls1c101_gpio36_isr(void *arg);
__WEAK void ls1c101_gpio37_isr(void *arg);
__WEAK void ls1c101_gpio38_isr(void *arg);
__WEAK void ls1c101_gpio39_isr(void *arg);

__WEAK void ls1c101_gpio48_isr(void *arg);      // GPIO[55:48]
__WEAK void ls1c101_gpio49_isr(void *arg);
__WEAK void ls1c101_gpio50_isr(void *arg);
__WEAK void ls1c101_gpio51_isr(void *arg);
__WEAK void ls1c101_gpio52_isr(void *arg);
__WEAK void ls1c101_gpio53_isr(void *arg);
__WEAK void ls1c101_gpio54_isr(void *arg);
__WEAK void ls1c101_gpio55_isr(void *arg);

#endif // _LS1C101_IRQ_H

