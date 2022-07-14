/*
 * user.h
 *
 * created: 2022/6/16
 *  author: 
 */

#ifndef _USER_H
#define _USER_H

#include "time.h"
#include <stdbool.h>

//--------------------------------------------------------------------------------------------------
extern volatile unsigned int g_send_dtmf_mark;      // ����DTMF�źŷ����б�־
extern volatile unsigned int g_recv_dtmf_mark;      // ���˽���DTMF�������־
extern volatile unsigned int g_mqtt_connect_ok;     // MQTT��������

//--------------------------------------------------------------------------------------------------
#define MQTT_SEND_SPACE (1 * 60 * 1000UL)           // MQTT�����ϱ����ʱ��

/*
* DTMF�������: 1��־��0/F���� 7���ݣ�1У�飨�ۼ�Ϊ0��
*           D0: Send_voltage             �·���ѹ        0 ��ȡ����ֵ   1 ��ѹ����
*           D1-D3: Signal_location       �źŻ�λ��      0-7 (000 - 111)
*
*           D0-D3: Signal_type           �źŻ�����      0���� 2��վ(����) 3��վ(����) 4��վ������1��
*
*           D0-D3: Signal_track          �źŻ��ɵ�      0-15(0000 - 1111)
*
*           D0-D3: Signal_voltage        L
*
*           D0-D3: Signal_voltage        H �źŻ���ѹ    0-255( 0000 0000 -1111 1111)
*
*              D0: Signal_deputy         �źŻ�������˿  0����˿(����)  1����˿(�澯)
*           D2-D3: Signal_current        H �źŻ�����
*
*           D0-D3: Signal_current        L �źŻ�����    �ߵ�λ0-63(00 0000 - 11 1111)
*/

typedef struct XHJ_attribute
{
    unsigned int  index;                        // �źŻ����ݴ������
    unsigned int  onTick;                       // �źŻ���������ʱ��
    unsigned char Signal_name[9];               // �źŻ�����
    
    unsigned char Signal_type;                  // �źŻ�����    4bit
    unsigned char Signal_track;                 // �źŻ��ɵ�    4bit
    unsigned char Signal_location;              // �źŻ�λ��    3bit

    float Signal_voltage;                       // �źŻ�ʵʱ��ѹ
    float Signal_current;                       // �źŻ�ʵʱ����
    float Set_voltage;                          // �źŻ����õ�ѹ
    
    unsigned char Signal_alarm;                 // �źŻ�����˿�۶ϸ澯: D0״̬��D1�״Σ�D2����
    unsigned char Signal_online;                // �źŻ�����豸���߷�

    unsigned int  x, y, r;                      // �źŻ�GUI��ʾλ��

    unsigned int  onColoridx;                   // �źŻ�����ʾ��ɫidx
    unsigned int  offColoridx;                  // �źŻ�����ʾ��ɫidx
    
    struct tm t;
} XHJ_attribute_t;

#define XHJ_ID_MAX  11                          // �źŻ���λ����
extern XHJ_attribute_t g_XHJ_attribute[XHJ_ID_MAX];

#define MAIN_GRID_MAX_ROWS  9                   // ���б���ʾ������
extern volatile unsigned int g_xhj_show_pos;    // �źŻ���ʾ�б����

////////////////////////////////////////////////////////////////////////////////////////////////////

extern bool is_show_grid(void);
extern void update_allGrid(void);
extern void update_allCircle(void);
extern void update_grid(XHJ_attribute_t *pAttrib);
extern void update_Circle(XHJ_attribute_t *pAttrib);

extern unsigned int FindXHJindex(unsigned int index);
extern void L610_send(XHJ_attribute_t *pAttrib);
extern void send_dtmf_string(unsigned char *dtmf, int len);

extern void start_my_gui(void);
extern void dtmf_thread_init(void);
extern void L610_thread_init(void);
extern void Polling_thread_init(void);

#endif // _USER_H

