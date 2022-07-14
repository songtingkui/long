/*
 * Copyright (C) 2020-2021 Suzhou Tiancheng Software Ltd.
 *
 * SPDX-License-Identifier: Apache-2.0
 */

/*
 * Loongson 1c101 Bare Program, Sample main file
 */

#include <stdio.h>
#include "string.h"
#include "bsp.h"
#include "ls1c101.h"
#include "ls1c101_gpio.h"
#include "numeral.h"
#include "PWM.h"
#include "ADC.h"
#include "UART.h"
#include "DTMF.h"



int main(void)
{
    INT32U Tick;

    // GPIO��ʼ��
    g_pmu->IOSEL0 = 0x55555555;
    g_pmu->IOSEL1 = 0x55555555;
    g_pmu->IOSEL2 = 0x55555555;
    g_pmu->IOSEL3 = 0x55555555;

    // BOMA��ʼ��
    BOMA_Init();

    // ADC��ʼ��
    ls1d_ADC_int();

    // pwm�������
    ls1c101_PWM_Init();

    // DTMF��ʼ��
    send_dtmf_init();
    recv_dtmf_init();

    // ��ι���Ļ��Ḵλ, 5��
    g_pmu->WdtFeed = WDTFEED_FOOD;

    // ��ʼ����ѹ, �ȴ�100ms
    ls1c101_set_voltage(g_stroadwayData.set_voltage);

    Tick = get_clock_ticks();
    do
    {
        ls1c101_adj_voltage(ls1d_ADC_SORT2());
    }
    while ((INT32U)(get_clock_ticks() - Tick) < 100ul);

    for (;;)
    {
        // ��ι���Ļ��Ḵλ, 5��
        g_pmu->WdtFeed = WDTFEED_FOOD;

        // ʵʱ���±���ID
        g_stroadwayData.led_type   = BOMA1() & 0x0F;
        g_stroadwayData.led_place  = BOMA2() & 0x07;
        g_stroadwayData.led_number = BOMA3() & 0x0F;

        // ����dtmf����Ҫʵʱ���
        recv_dtmf_loop();
        if (g_u32usartcommt >= DTMF_RECV_MAX)
        {
            // DTMF�����
            recv_dtmf_check();
            g_u32usartcommt = 0;
        }

        // adc��ѹ���
        g_stroadwayData.zu_voltage = ls1d_ADC_SORT2();
        g_stroadwayData.fu_voltage = ls1d_ADC_SORT1();

        //adc�������
        g_stroadwayData.current = ls1d_ADC_SORT3();

        // ִ�е�˿�л�
        if (0 == g_stroadwayData.isMainLed)
        {
            // ������׼ֵ
            if (g_stroadwayData.current <= CRIENT_MIN)
            {
                // ����˿�л� ���2Ϊ�ߵ�ƽ
                gpio_write(2,GPIO_HIGH);
                g_stroadwayData.isMainLed = 1;
            }
        }

        // �������ѹ����
        ls1c101_adj_voltage(g_stroadwayData.zu_voltage);

        // ���������Ӧ��־
        if (0 != g_u8SendStatusMark)
        {
            g_u8SendStatusMark = 0;

            //DTMF����
            send_XHJstatus();
        }
    }

    /*
     * Never goto here!
     */
    return 0;
}

/*
 * @@ End
 */
