/*
 * polling.c
 *
 * created: 2022/6/24
 *  author:
 */

#include <stdio.h>
#include "rtthread.h"
#include "ls1x_fb.h"
#include "user.h"
#include "ls1x_rtc.h"

//--------------------------------------------------------------------------------------------------
static rt_thread_t m_polling_thread = NULL;

//--------------------------------------------------------------------------------------------------
XHJ_attribute_t g_XHJ_attribute[XHJ_ID_MAX] =
{
    // 序号, 时钟, 名称, 类型, 股道, 位置, 电压, 电流, 设置, 告警, 在线, x, y, r, 亮色, 灭色
    // 进站五显：黄、绿、红、黄、白
    {0,  0, "X",    4, 0, 1, 0, 0, 0, 0, 0, 162, 182, 10, cidxBRTYELLOW, cidxSILVER, {-1}},
    {1,  0, "X",    4, 0, 2, 0, 0, 0, 0, 0, 142, 182, 10, cidxBRTGREEN,  cidxSILVER, {-1}},
    {2,  0, "X",    4, 0, 3, 0, 0, 0, 0, 0, 122, 182, 10, cidxBRTRED,    cidxSILVER, {-1}},
    {3,  0, "X",    4, 0, 4, 0, 0, 0, 0, 0, 102, 182, 10, cidxBRTYELLOW, cidxSILVER, {-1}},
    {4,  0, "X",    4, 0, 5, 0, 0, 0, 0, 0,  82, 182, 10, cidxBRTWHITE,  cidxSILVER, {-1}},

    // 非自动闭塞出站三显：绿、红、白
    {5,  0, "S1",   2, 1, 1, 0, 0, 0, 0, 0, 330, 157, 10, cidxBRTGREEN, cidxSILVER, {-1}},
    {6,  0, "S1",   2, 1, 2, 0, 0, 0, 0, 0, 350, 157, 10, cidxBRTRED,   cidxSILVER, {-1}},
    {7,  0, "S1",   2, 1, 3, 0, 0, 0, 0, 0, 370, 157, 10, cidxBRTWHITE, cidxSILVER, {-1}},

    {8,  0, "SⅡ",  2, 2, 1, 0, 0, 0, 0, 0, 325, 220, 10, cidxBRTGREEN, cidxSILVER, {-1}},
    {9,  0, "SⅡ",  2, 2, 2, 0, 0, 0, 0, 0, 345, 220, 10, cidxBRTRED,   cidxSILVER, {-1}},
    {10, 0, "SⅡ",  2, 2, 3, 0, 0, 0, 0, 0, 365, 220, 10, cidxBRTWHITE, cidxSILVER, {-1}}
};

//--------------------------------------------------------------------------------------------------

// 通过ID查找信号机数据索引号
unsigned int FindXHJindex(unsigned int index)
{
    unsigned int i, idx;

    for (i = 0; i < XHJ_ID_MAX; i++)
    {
        // 信号机ID: 类型8，股道4，灯位0
        idx  = g_XHJ_attribute[i].Signal_location & 0x0007;
        idx |= (g_XHJ_attribute[i].Signal_track << 4) & 0x00F0;
        idx |= (g_XHJ_attribute[i].Signal_type << 8) & 0x0F00;

        if (idx == index)
        {
            break;
        }
    }

    return i;
}

// DTMF打包数据
static uint32_t Dtmfpack(XHJ_attribute_t *pAttrib, unsigned char *outBuf)
{
    uint32_t i, val, check;

    // 传输标志码
    outBuf[0] = 0x0F;

    outBuf[1] = (pAttrib->Signal_location << 1) & 0x0E;
    if (0 != pAttrib->Set_voltage)
    {
        outBuf[1] |= 1;
    }

    outBuf[2] = pAttrib->Signal_type & 0x0F;
    outBuf[3] = pAttrib->Signal_track & 0x0F;

    // 设置电压
    val = (uint32_t)(pAttrib->Set_voltage * 10);
    outBuf[4]  = (val >> 0) & 0x0F;
    outBuf[5]  = (val >> 4) & 0x0F;

    // 校验码
    check = 0;
    for (i = 0; i < 6; i++)
    {
        check += outBuf[i];
    }
    outBuf[6] = (-check) & 0x0F;

    return 7;
}

static void polling_thread(void *arg)
{
    unsigned int  sendNum, len;
    unsigned char dtmf[16];

    // 设备起始编号
    sendNum = 0;
    rt_thread_delay(1000);

    while (1)
    {
        // 查询打包
        len = Dtmfpack((XHJ_attribute_t *)&g_XHJ_attribute[sendNum], dtmf);
        send_dtmf_string(dtmf, len);

        // 等待下位机响应
        rt_thread_delay(100);
        if (0 != g_recv_dtmf_mark)
        {
            rt_thread_delay(300);
        }
        else
        {
            // 设备离线操作
            if (0 != g_XHJ_attribute[sendNum].Signal_online)
            {
                g_XHJ_attribute[sendNum].Signal_online--;
                if (0 == g_XHJ_attribute[sendNum].Signal_online)
                {
                    g_XHJ_attribute[sendNum].Signal_voltage = 0;
                    g_XHJ_attribute[sendNum].Signal_current = 0;
                    g_XHJ_attribute[sendNum].Signal_alarm  |= 0x04;
                    
                    if (!is_show_grid())
                    {
                        update_Circle((XHJ_attribute_t *)&g_XHJ_attribute[sendNum]);
                    }
                    else
                    {
                        update_grid((XHJ_attribute_t *)&g_XHJ_attribute[sendNum]);
                    }

                    g_XHJ_attribute[sendNum].onTick = rt_tick_get();
                    L610_send((XHJ_attribute_t *)&g_XHJ_attribute[sendNum]);
                }
            }
        }

        // 后续设备
        sendNum++;
        if (sendNum >= XHJ_ID_MAX)
        {
            sendNum = 0;
        }

        {
            struct tm t;
            char info_buf[32];

            ls1x_rtc_get_datetime(&t);
            sprintf(info_buf, "%04d-%02d-%02d %02d:%02d:%02d",
                    t.tm_year+1900, t.tm_mon+1, t.tm_mday, t.tm_hour, t.tm_min, t.tm_sec);

            FillRect (640, 453, 800, 469, cidxSILVER);
            PutString(640, 453, info_buf, cidxVIOLET);
        }
    }
}

void Polling_thread_init(void)
{
    m_polling_thread = rt_thread_create("pollingthread",
                                        polling_thread,
                                        NULL,         // arg
                                        1024*4,       // statck size
                                        5,            // priority
                                        30);          // slice ticks

    if (m_polling_thread == NULL)
    {
        rt_kprintf("create polling thread fail!\r\n");
    }
    else
    {
        rt_thread_startup(m_polling_thread);
    }
}

