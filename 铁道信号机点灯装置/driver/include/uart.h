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
    INT8U led_type;             // �źŻ�����
    INT8U led_place;	        // ��λ
    INT8U led_number;	        // �ɵ���

    INT32U set_voltage;         // ��λ���趨��ѹ
    INT32U zu_voltage;          // ����˿��ǰ��ѹ
    INT32U fu_voltage;          // ����˿��ǰ��ѹ

    INT8U isMainLed;	        // ������˿״̬��0����1����
    INT32U current;	            // ����
} BLINKER_DataDef;

BLINKER_DataDef	g_stroadwayData;


#define DTMF_RECV_MAX   7                               // DTMF�����

extern BLINKER_DataDef g_stroadwayData;	                // ����״̬����
extern INT32U g_u32usartcommt;                          // DTMF���ճ���
extern INT8U g_u8SendStatusMark;                        // DTMF����Ӧ���־


void recv_dtmf_init(void);                              // DTMF���ճ�ʼ��
void recv_dtmf_loop(void);                              // DTMF���ݽ���ѭ��
void recv_dtmf_check(void);                             // DTMF�����
void send_XHJstatus(void);                              // �����źŻ�״̬����

#ifdef __cplusplus
}
#endif

#endif /* LS1C101_GPIO_H_ */
