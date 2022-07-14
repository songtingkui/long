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

#ifndef PWM_H_
#define PWM_H_

#ifdef __cplusplus
extern "C" {
#endif


void ls1c101_PWM_Init(void);

void ls1c101_set_voltage(int voltage);
void ls1c101_adj_voltage(int voltage);

#ifdef __cplusplus
}
#endif

#endif /* LS1C101_GPIO_H_ */
