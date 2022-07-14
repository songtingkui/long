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
 * ȫ�ֿ����� 
 */
HW_PMU_t *g_pmu = (HW_PMU_t *)LS1C101_PMU_BASE;

#if 1
/*
 * ʹ���ⲿ 8M ʱ������
 */
static void OSC_init_outer(void)
{
    g_pmu->ChipCtrl &= ~CHIPCTRL_8M_SEL;
    g_pmu->ChipCtrl |= CHIPCTRL_8M_EN;
    
    /*
     * �˴�, CAUSE_DC ���ر���, delay ������ѭ�� 
     */
    /*
    {
        register unsigned int cause;
        mips_get_cause(cause);
        mips_set_cause(cause & ~CAUSE_DC);  
    } */
    
    delay_ms(10);  /* ������ʱ��˯���������ʱ��ʧЧ? ��loop ����ѭ�� */

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
    // �˳�˯��״̬
    g_pmu->CommandW = 0;        // CMDSR_SLEEP_EN;

    // ��λ�˿�Ĭ�ϣ�GPIO������

    //
    Clock_initialize();         /* initialize system ticker */

//    OSC_init_outer();         // ����Ϊ�ⲿʱ�� TODO delay_ms() ������

//    console_init(115200);       /* initialize Console */

  
    /* Enable all interrupts */
    mips_unmask_interrupt(SR_IMASK | SR_IE);

    /* goto main function */
    main();
}


