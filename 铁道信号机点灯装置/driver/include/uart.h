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

#ifndef UART_H_
#define UART_H_

#ifdef __cplusplus
extern "C" {
#endif

typedef struct
{
    INT8U led_type;             // 信号机类型
    INT8U led_place;	        // 灯位
    INT8U led_number;	        // 股道号

    INT32U set_voltage;         // 上位机设定电压
    INT32U zu_voltage;          // 主灯丝当前电压
    INT32U fu_voltage;          // 副灯丝当前电压

    INT8U isMainLed;	        // 主副灯丝状态（0主，1副）
    INT32U current;	            // 电流
} BLINKER_DataDef;

BLINKER_DataDef	g_stroadwayData;


#define DTMF_RECV_MAX   7                               // DTMF命令长度

extern BLINKER_DataDef g_stroadwayData;	                // 控制状态数据
extern INT32U g_u32usartcommt;                          // DTMF接收长度
extern INT8U g_u8SendStatusMark;                        // DTMF命令应答标志


void recv_dtmf_init(void);                              // DTMF接收初始化
void recv_dtmf_loop(void);                              // DTMF数据接收循环
void recv_dtmf_check(void);                             // DTMF命令处理
void send_XHJstatus(void);                              // 发送信号机状态数据

#ifdef __cplusplus
}
#endif

#endif /* LS1C101_GPIO_H_ */
