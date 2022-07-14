/*
 * Copyright (C) 2020-2021 Suzhou Tiancheng Software Ltd.
 *
 * SPDX-License-Identifier: Apache-2.0
 */

/*
 * demo_gui.c
 *
 *  Created on: 2015-1-26
 *      Author: Bian
 */

/*
 * �ٶ�: XPT2046_DRV ʹ��800*480 ������
 *       GT1151_DRV  ʹ��480*800 ������
 *
 * �����ֱ���, ��Ҫ�޸� grid/button ��λ�ò���
 */

#include "bsp.h"

#ifdef BSP_USE_FB

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "user.h"
#include "ls1x_fb.h"
#include "ls1x_rtc.h"
#include "simple-gui/simple_gui.h"
#include "pic_data2.h"

#define BUTTON_WIDTH		120
#define BUTTON_HEIGHT		42

/******************************************************************************
 * show message
 ******************************************************************************/

volatile unsigned int g_xhj_show_pos = 0;

static volatile int last_x   = -1;
static volatile int last_y   = -1;
static volatile int last_dx  = -1;

void gui_info(const char *str, int x, int y)
{
    if ((str == NULL) || (x < 0) || (y < 0))
        return;

    /* clear last */
    if ((last_x > 0) && (last_y > 0))
    {
        FillRect(last_x, last_y, last_x + last_dx, last_y + 16, cidxBLACK);
    }

    last_dx = PutString(x, y, (char *)str, cidxBRTWHITE);

    last_x = x;
    last_y = y;
}

/******************************************************************************
 * defined functions
 ******************************************************************************/

int clear_screen(void)
{
    /* fill screen color silver
     */
    ls1x_dc_ioctl(devDC, IOCTRL_FB_CLEAR_BUFFER, (void *)GetColor(cidxSILVER));

    return 0;
}

static int create_main_objects(void);

static void set_objects_active_group(int group);

/******************************************************************************
 * main frame
 ******************************************************************************/

#define MAIN_GROUP	0x00010000

static TGrid *grid_main = NULL;

static int create_grid_main(void)
{
    TColumn *p_column;
    TRect    rect;

    rect.left   = 20;
    rect.top    = 100;

#ifdef XPT2046_DRV
    rect.right  = 638;
    rect.bottom = 438;
    grid_main = create_grid(&rect, MAIN_GRID_MAX_ROWS, 7, MAIN_GROUP | 0x0001, MAIN_GROUP);
#elif defined(GT1151_DRV)
    rect.right  = 460;
    rect.bottom = 492;
    grid_main = create_grid(&rect, 12, 3, MAIN_GROUP | 0x0001, MAIN_GROUP);
#endif

    if (grid_main == NULL)
        return -1;

    /* column 0 */
    p_column = grid_get_column(grid_main, 0);
    p_column->align = align_center;
    grid_set_column_title(p_column, "�� ��");
    grid_set_column_width(grid_main, 0, 50);

    /* column 0 */
    p_column = grid_get_column(grid_main, 1);
    p_column->align = align_center;
    grid_set_column_title(p_column, "�źŻ�");
    grid_set_column_width(grid_main, 1, 65);

    /* column 1 */
    p_column = grid_get_column(grid_main, 2);
    p_column->align = align_center;
    grid_set_column_title(p_column, "�� λ");
    grid_set_column_width(grid_main, 2, 55);

    /* column 2 */
    p_column = grid_get_column(grid_main, 3);
    p_column->align = align_center;
    grid_set_column_title(p_column, "�� ѹ");
    grid_set_column_width(grid_main, 3, 80);

    /* column 3 */
    p_column = grid_get_column(grid_main, 4);
    p_column->align = align_center;
    grid_set_column_title(p_column, "�� ��");
    grid_set_column_width(grid_main, 4, 80);

    /* column 4 */
    p_column = grid_get_column(grid_main, 5);
    p_column->align = align_center;
    grid_set_column_title(p_column, "��˿״̬");
    grid_set_column_width(grid_main, 5, 90);

    /* column 5 */
    p_column = grid_get_column(grid_main, 6);
    p_column->align = align_center;
    grid_set_column_title(p_column, "���ݸ���ʱ��");
    grid_set_column_width(grid_main, 6, 200);

    return 0;
}

/*
 * right: 160*480, button to navigate
 */
static void main_onclick_0001(unsigned msg, void *param)
{
    TButton *btnTip = (TButton *)param;
    if (!btnTip->visible)
    {
        return;
    }

    if (g_xhj_show_pos > 0)
    {
        g_xhj_show_pos--;
        update_allGrid();
    }
    else
    {
        gui_info(" ��ʾ������ǰ�棡", 280, 230);
        rt_thread_sleep(1000);
    }

    grid_main->layout_changed = true;
}

static void main_onclick_0002(unsigned msg, void *param)
{
    TButton *btnTip = (TButton *)param;
    printk("print me \"%s\"\r\n", btnTip->caption);

    if (btnTip->tag == 0)
    {
        TButton *btn;

        btn = find_button(MAIN_GROUP | 0x0001);
        if (NULL != btn)
        {
            btn->visible        = false;
            btn->layout_changed = true;
        }

        btn = find_button(MAIN_GROUP | 0x0004);
        if (NULL != btn)
        {
            btn->visible        = false;
            btn->layout_changed = true;
        }

        // ��ʾվ��ͼ
        fb_displaybmp(20, 100, 619, 339, gImage_pic_data2);
        update_allCircle();

        strcpy(btnTip->caption, "ʵʱ����");
        btnTip->tag = 1;
    }
    else
    {
        TButton *btn;

        grid_main->layout_changed = true;

        btn = find_button(MAIN_GROUP | 0x0001);
        if (NULL != btn)
        {
            btn->visible        = true;
            btn->layout_changed = true;
        }

        btn = find_button(MAIN_GROUP | 0x0004);
        if (NULL != btn)
        {
            btn->visible        = true;
            btn->layout_changed = true;
        }

        strcpy(btnTip->caption, "վ �� ͼ");
        btnTip->tag = 0;
    }

    btnTip->layout_changed = true;
}

static void main_onclick_0003(unsigned msg, void *param)
{
    if (is_show_grid())
    {
        g_xhj_show_pos = 0;
        update_allGrid();

        grid_main->layout_changed = true;
    }
    else
    {
        update_allCircle();
    }
}

static void main_onclick_0004(unsigned msg, void *param)
{
    TButton *btnTip = (TButton *)param;
    if (!btnTip->visible)
    {
        return;
    }

    if ((g_xhj_show_pos + MAIN_GRID_MAX_ROWS) < XHJ_ID_MAX)
    {
        g_xhj_show_pos++;
        update_allGrid();
    }
    else
    {
        gui_info(" ��ʾ��������棡", 280, 230);
        rt_thread_sleep(1000);
    }

    grid_main->layout_changed = true;
}

static int create_buttons_main(void)
{
    TRect rect;

    rect.left   = 660;
    rect.top    = 122;
    rect.right  = rect.left + BUTTON_WIDTH;
    rect.bottom = rect.top + BUTTON_HEIGHT;
    new_button(&rect, MAIN_GROUP | 0x0001, MAIN_GROUP, "���Ϲ���", main_onclick_0001);

    rect.left   = 660;
    rect.top    = 207;
    rect.right  = rect.left + BUTTON_WIDTH;
    rect.bottom = rect.top + BUTTON_HEIGHT;
    new_button(&rect, MAIN_GROUP | 0x0002, MAIN_GROUP, "վ �� ͼ", main_onclick_0002);

    rect.left   = 660;
    rect.top    = 292;
    rect.right  = rect.left + BUTTON_WIDTH;
    rect.bottom = rect.top + BUTTON_HEIGHT;
    new_button(&rect, MAIN_GROUP | 0x0003, MAIN_GROUP, "ˢ����ʾ", main_onclick_0003);

    rect.left   = 660;
    rect.top    = 377;
    rect.right  = rect.left + BUTTON_WIDTH;
    rect.bottom = rect.top + BUTTON_HEIGHT;
    new_button(&rect, MAIN_GROUP | 0x0004, MAIN_GROUP, "���¹���", main_onclick_0004);

    return 0;
}

static int create_main_objects(void)
{
    if (clear_screen() != 0)
        return -1;

    if (get_buttons_count(MAIN_GROUP) == 0)
        create_buttons_main();

    if (grid_main == NULL)
        create_grid_main();

    set_objects_active_group(MAIN_GROUP);

    return 0;
}

/******************************************************************************
 * object set active
 ******************************************************************************/

static void set_objects_active_group(int group)
{
    set_gui_active_group(group);
}

/******************************************************************************
 * app with simple-gui & xyplot
 ******************************************************************************/

void start_my_gui(void)
{
    if (fb_open() != 0)
        return;

    if (!ls1x_dc_started())
        return;

    init_simple_gui_env();          /* gui enviroment */
    create_main_objects();	        /* main objects */

#if BSP_USE_OS
    start_gui_monitor_task();	    /* start button click event task */
#else
    paint_my_simple_gui();          /* just draw It */
#endif

#if defined(USE_YAFFS2) && defined(GT1151_DRV)
    fb_showbmp(20, 580, "/ndd/photo/logo_160.bmp");
#endif
}

void gui_drawtext_in_grid(int row, int col, const char *str)
{
    if (!ls1x_dc_started())
        return;

    if (grid_main != NULL)
        grid_set_cell_text(grid_main, row, col, str);
}

#endif

////////////////////////////////////////////////////////////////////////////////////////////////////

bool is_show_grid(void)
{
    TButton *btn;

    btn = find_button(MAIN_GROUP | 0x0002);
    if (NULL == btn)
    {
        return true;
    }

    if (0 == btn->tag)
    {
        return true;
    }

    return false;
}

void update_grid(XHJ_attribute_t *pAttrib)
{
    int idx;
    char buf[32];

    // ����Grid��ʾλ��: ͷ��β
    idx = pAttrib->index;
    if (idx < g_xhj_show_pos)
    {
        return;
    }

    if ((idx - g_xhj_show_pos) >= MAIN_GRID_MAX_ROWS)
    {
        return;
    }

    idx -= g_xhj_show_pos;

    // 0���, 1�źŻ�, 2��λ, 3��ѹ, 4����, 5��˿״̬, 6���ݸ���ʱ��
    sprintf(buf, "%d", pAttrib->index + 1);
    gui_drawtext_in_grid(idx, 0, buf);

    if (1 == pAttrib->Signal_location)
    {
        gui_drawtext_in_grid(idx, 1, (const char *)pAttrib->Signal_name);
    }
    else
    {
        gui_drawtext_in_grid(idx, 1, NULL);
    }

    sprintf(buf, "%d", pAttrib->Signal_location);
    gui_drawtext_in_grid(idx, 2, buf);

    if (0 != pAttrib->Signal_online)
    {
        sprintf(buf, "%.1f", pAttrib->Signal_voltage);
        gui_drawtext_in_grid(idx, 3, buf);

        sprintf(buf, "%.1f", pAttrib->Signal_current);
        gui_drawtext_in_grid(idx, 4, buf);

        if (1 == (pAttrib->Signal_alarm & 0x01))
        {
            gui_drawtext_in_grid(idx, 5, "����˿");
        }
        else
        {
            gui_drawtext_in_grid(idx, 5, "����˿");
        }
    }
    else
    {
        gui_drawtext_in_grid(idx, 3, NULL);
        gui_drawtext_in_grid(idx, 4, NULL);
        gui_drawtext_in_grid(idx, 5, NULL);
    }

    if (-1 != pAttrib->t.tm_sec)
    {
        sprintf(buf, "%04d-%02d-%02d %02d:%02d:%02d", pAttrib->t.tm_year+1900, pAttrib->t.tm_mon+1, pAttrib->t.tm_mday, pAttrib->t.tm_hour, pAttrib->t.tm_min, pAttrib->t.tm_sec);
        gui_drawtext_in_grid(idx, 6, buf);
    }
    else
    {
        gui_drawtext_in_grid(idx, 6, NULL);
    }
}

void update_allGrid(void)
{
    unsigned int i;

    for (i = 0; i < XHJ_ID_MAX; i++)
    {
        update_grid(&g_XHJ_attribute[i]);
    }
}

void update_Circle(XHJ_attribute_t *pAttrib)
{
    if (1 == (pAttrib->Signal_alarm & 0x01))
    {
        // ����˿
        fb_circle(grid_main->rect.left + pAttrib->x - 1, grid_main->rect.top + pAttrib->y - 5, pAttrib->r - 0, 0, cidxBRTVIOLET);
        fb_circle(grid_main->rect.left + pAttrib->x - 1, grid_main->rect.top + pAttrib->y - 5, pAttrib->r - 1, 0, cidxBRTVIOLET);
    }

    if (0 != pAttrib->Signal_online)
    {
        fb_circle(grid_main->rect.left + pAttrib->x - 1, grid_main->rect.top + pAttrib->y - 5, pAttrib->r - 2, 1, pAttrib->onColoridx);
    }
    else
    {
        fb_circle(grid_main->rect.left + pAttrib->x - 1, grid_main->rect.top + pAttrib->y - 5, pAttrib->r - 2, 1, pAttrib->offColoridx);
    }
}

void update_allCircle(void)
{
    unsigned int i, off;

    // ȫ����
    off = 0;
    for (i = 0; i < 5; i++)
    {
        off |= g_XHJ_attribute[i].Signal_online;
        update_Circle(&g_XHJ_attribute[i]);
    }
    if (0 == off)
    {
        // Ĭ�ϵ�λ
        fb_circle(grid_main->rect.left + g_XHJ_attribute[2].x - 1, grid_main->rect.top + g_XHJ_attribute[2].y - 5, g_XHJ_attribute[2].r - 2, 1, g_XHJ_attribute[2].onColoridx);
    }

    off = 0;
    for (; i < 8; i++)
    {
        off |= g_XHJ_attribute[i].Signal_online;
        update_Circle(&g_XHJ_attribute[i]);
    }
    if (0 == off)
    {
        fb_circle(grid_main->rect.left + g_XHJ_attribute[6].x - 1, grid_main->rect.top + g_XHJ_attribute[6].y - 5, g_XHJ_attribute[6].r - 2, 1, g_XHJ_attribute[6].onColoridx);
    }

    off = 0;
    for (; i < XHJ_ID_MAX; i++)
    {
        off |= g_XHJ_attribute[i].Signal_online;
        update_Circle(&g_XHJ_attribute[i]);
    }
    if (0 == off)
    {
        fb_circle(grid_main->rect.left + g_XHJ_attribute[9].x - 1, grid_main->rect.top + g_XHJ_attribute[9].y - 5, g_XHJ_attribute[9].r - 2, 1, g_XHJ_attribute[9].onColoridx);
    }

    fb_circle(grid_main->rect.left + 226 - 1, grid_main->rect.top + 182 - 5, 10 - 2, 1, cidxSILVER);
    fb_circle(grid_main->rect.left + 206 - 1, grid_main->rect.top + 182 - 5, 10 - 2, 1, cidxBRTBLUE);
}

