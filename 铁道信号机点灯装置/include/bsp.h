/*
 * Copyright (C) 2020-2021 Suzhou Tiancheng Software Ltd.
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#ifndef _LS1c_BSP_H
#define _LS1c_BSP_H

/*
 * ÄÚÖÃ¾§Õñ
 */
extern unsigned int freq_inner_8M;

//-----------------------------------------------------------------------------
// NS16550 devices
//-----------------------------------------------------------------------------

#define BSP_USE_UART0       1
#define BSP_USE_UART1       1
#define BSP_USE_UART2       0

//-----------------------------------------------------------------------------
// functions
//-----------------------------------------------------------------------------

extern void delay_us(unsigned int us);
extern void delay_ms(unsigned int ms);

extern unsigned int get_clock_ticks(void);

#endif // _LS1c_BSP_H

