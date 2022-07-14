/*
 * Copyright (C) 2020-2021 Suzhou Tiancheng Software Ltd.
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <stdio.h>
#include <string.h>

#include "regdef.h"
#include "mips.h"
#include "cpu.h"



void c_exception_handler(unsigned int *sp)
{
    
	while (1)           // 产生例外之后... dead loop 
      ;
}


