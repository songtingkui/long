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

#ifndef ADC_H_
#define ADC_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "ls1c101.h"

#define CRIENT_MIN    500                          // 主灯丝断丝识别电流值

INT32U ls1d_ADC_MEASURE(volatile char channel);
INT32U ls1d_ADC_SORT1(void);
INT32U ls1d_ADC_SORT2(void);
INT32U ls1d_ADC_SORT3(void);
void ls1d_ADC_int(void);

#ifdef __cplusplus
}
#endif

#endif /* LS1C101_GPIO_H_ */
