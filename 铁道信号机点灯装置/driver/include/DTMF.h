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

#ifndef DTMF_H_
#define DTMF_H_

#ifdef __cplusplus
extern "C" {
#endif


void DTMF_Init(void);
void DTMF_send(void);
void DTMF_send_high(INT32U TX);
void USART1_SEND_time(void);

void send_dtmf_init(void);
void send_dtmf_string(INT8U *dtmf, INT32U len);

#ifdef __cplusplus
}
#endif

#endif /* LS1C101_GPIO_H_ */
