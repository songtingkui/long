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

    // GPIO初始化
    g_pmu->IOSEL0 = 0x55555555;
    g_pmu->IOSEL1 = 0x55555555;
    g_pmu->IOSEL2 = 0x55555555;
    g_pmu->IOSEL3 = 0x55555555;

    // BOMA初始化
    BOMA_Init();

    // ADC初始化
    ls1d_ADC_int();

    // pwm控制输出
    ls1c101_PWM_Init();

    // DTMF初始化
    send_dtmf_init();
    recv_dtmf_init();

    // 不喂狗的话会复位, 5秒
    g_pmu->WdtFeed = WDTFEED_FOOD;

    // 初始化电压, 等待100ms
    ls1c101_set_voltage(g_stroadwayData.set_voltage);

    Tick = get_clock_ticks();
    do
    {
        ls1c101_adj_voltage(ls1d_ADC_SORT2());
    }
    while ((INT32U)(get_clock_ticks() - Tick) < 100ul);

    for (;;)
    {
        // 不喂狗的话会复位, 5秒
        g_pmu->WdtFeed = WDTFEED_FOOD;

        // 实时更新本机ID
        g_stroadwayData.led_type   = BOMA1() & 0x0F;
        g_stroadwayData.led_place  = BOMA2() & 0x07;
        g_stroadwayData.led_number = BOMA3() & 0x0F;

        // 接收dtmf，需要实时检查
        recv_dtmf_loop();
        if (g_u32usartcommt >= DTMF_RECV_MAX)
        {
            // DTMF命令处理
            recv_dtmf_check();
            g_u32usartcommt = 0;
        }

        // adc电压检测
        g_stroadwayData.zu_voltage = ls1d_ADC_SORT2();
        g_stroadwayData.fu_voltage = ls1d_ADC_SORT1();

        //adc电流检测
        g_stroadwayData.current = ls1d_ADC_SORT3();

        // 执行灯丝切换
        if (0 == g_stroadwayData.isMainLed)
        {
            // 电流标准值
            if (g_stroadwayData.current <= CRIENT_MIN)
            {
                // 副灯丝切换 输出2为高电平
                gpio_write(2,GPIO_HIGH);
                g_stroadwayData.isMainLed = 1;
            }
        }

        // 输出主电压调节
        ls1c101_adj_voltage(g_stroadwayData.zu_voltage);

        // 检查命令响应标志
        if (0 != g_u8SendStatusMark)
        {
            g_u8SendStatusMark = 0;

            //DTMF发送
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
