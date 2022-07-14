/*
 * Copyright (C) 2020-2021 Suzhou Tiancheng Software Ltd.
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include "bsp.h"

#include "cpu.h"
#include "mips.h"

#include "ls1c101.h"

#include "clock.h"

extern void console_init(unsigned int baudrate);
extern int main(void);

/******************************************************************************
 * 全局控制器 
 */
HW_PMU_t *g_pmu = (HW_PMU_t *)LS1C101_PMU_BASE;

#if 1
/*
 * 使用外部 8M 时钟配置
 */
static void OSC_init_outer(void)
{
    g_pmu->ChipCtrl &= ~CHIPCTRL_8M_SEL;
    g_pmu->ChipCtrl |= CHIPCTRL_8M_EN;
    
    /*
     * 此处, CAUSE_DC 被关闭了, delay 成了死循环 
     */
    /*
    {
        register unsigned int cause;
        mips_get_cause(cause);
        mips_set_cause(cause & ~CAUSE_DC);  
    } */
    
    delay_ms(10);  /* 不加延时，睡眠起来后会时钟失效? 用loop 计数循环 */

    while (g_pmu->CmdSts & CMDSR_8M_FAIL)
    {
        g_pmu->ChipCtrl &= ~CHIPCTRL_8M_SEL;
    }

    g_pmu->ChipCtrl |= CHIPCTRL_8M_SEL;
}
#endif

/****************************************************************************** 
 * LS1x bsp start
 */
void bsp_start(void)
{
    // 退出睡眠状态
    g_pmu->CommandW = 0;        // CMDSR_SLEEP_EN;

    // 复位端口默认：GPIO，输入

    //
    Clock_initialize();         /* initialize system ticker */

//    OSC_init_outer();         // 设置为外部时钟 TODO delay_ms() 不运行

//    console_init(115200);       /* initialize Console */

  
    /* Enable all interrupts */
    mips_unmask_interrupt(SR_IMASK | SR_IE);

    /* goto main function */
    main();
}


