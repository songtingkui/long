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

#ifndef NUMERAL_H_
#define NUMERAL_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "ls1c101.h"

void BOMA_Init(void);

int BOMA1(void);
int BOMA2(void);
int BOMA3(void);
int BOMA4(void);


#ifdef __cplusplus
}
#endif

#endif /* LS1C101_GPIO_H_ */
