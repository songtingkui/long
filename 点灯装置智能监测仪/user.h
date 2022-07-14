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
extern volatile unsigned int g_send_dtmf_mark;      // 本端DTMF信号发送中标志
extern volatile unsigned int g_recv_dtmf_mark;      // 本端接收DTMF特征码标志
extern volatile unsigned int g_mqtt_connect_ok;     // MQTT连接正常

//--------------------------------------------------------------------------------------------------
#define MQTT_SEND_SPACE (1 * 60 * 1000UL)           // MQTT数据上报间隔时间

/*
* DTMF打包数据: 1标志（0/F）， 7数据，1校验（累加为0）
*           D0: Send_voltage             下发电压        0 获取数据值   1 电压控制
*           D1-D3: Signal_location       信号机位置      0-7 (000 - 111)
*
*           D0-D3: Signal_type           信号机类型      0调车 2出站(上行) 3出站(下行) 4进站（方向1）
*
*           D0-D3: Signal_track          信号机股道      0-15(0000 - 1111)
*
*           D0-D3: Signal_voltage        L
*
*           D0-D3: Signal_voltage        H 信号机电压    0-255( 0000 0000 -1111 1111)
*
*              D0: Signal_deputy         信号机主副灯丝  0主灯丝(正常)  1副灯丝(告警)
*           D2-D3: Signal_current        H 信号机电流
*
*           D0-D3: Signal_current        L 信号机电流    高低位0-63(00 0000 - 11 1111)
*/

typedef struct XHJ_attribute
{
    unsigned int  index;                        // 信号机数据处理序号
    unsigned int  onTick;                       // 信号机更新数据时钟
    unsigned char Signal_name[9];               // 信号机名称
    
    unsigned char Signal_type;                  // 信号机类型    4bit
    unsigned char Signal_track;                 // 信号机股道    4bit
    unsigned char Signal_location;              // 信号机位置    3bit

    float Signal_voltage;                       // 信号机实时电压
    float Signal_current;                       // 信号机实时电流
    float Set_voltage;                          // 信号机设置电压
    
    unsigned char Signal_alarm;                 // 信号机主灯丝熔断告警: D0状态，D1首次，D2离线
    unsigned char Signal_online;                // 信号机监控设备在线否

    unsigned int  x, y, r;                      // 信号机GUI显示位置

    unsigned int  onColoridx;                   // 信号机亮显示颜色idx
    unsigned int  offColoridx;                  // 信号机灭显示颜色idx
    
    struct tm t;
} XHJ_attribute_t;

#define XHJ_ID_MAX  11                          // 信号机灯位总数
extern XHJ_attribute_t g_XHJ_attribute[XHJ_ID_MAX];

#define MAIN_GRID_MAX_ROWS  9                   // 主列表显示总行数
extern volatile unsigned int g_xhj_show_pos;    // 信号机显示列表起点

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

