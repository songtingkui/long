/*
 * Copyright (C) 2020-2021 Suzhou Tiancheng Software Ltd.
 *
 * SPDX-License-Identifier: Apache-2.0
 */

/*
 * Loongson 1B RT-Thread Sample main file
 */
#include <stdint.h>
#include <stdio.h>
#include "bsp.h"

#include "rtthread.h"
#include "user.h"
#include "ls1x_rtc.h"

#if defined(BSP_USE_FB)
#include "ls1x_fb.h"
#ifdef XPT2046_DRV
char LCD_display_mode[] = LCD_800x480;
#include "spi/xpt2046.h"
#elif defined(GT1151_DRV)
char LCD_display_mode[] = LCD_480x800;
#else
#error "在bsp.h中选择配置 XPT2046_DRV 或者 GT1151_DRV"
"XPT2046_DRV:  用于800*480 横屏的触摸屏."
"GT1151_DRV:   用于480*800 竖屏的触摸屏."
"如果都不选择, 注释掉本 error 信息, 然后自定义: LCD_display_mode[]"
#endif
#endif

/******************************************************************************
 * main()函数
 ******************************************************************************/
int main(int argc, char** argv)
{
    struct tm t;

    rt_kprintf("\r\nWelcome to RT-Thread.\r\n\r\n");

    ls1x_drv_init();            		/* Initialize device drivers */

    rt_ls1x_drv_init();         		/* Initialize device drivers for RTT */

    install_3th_libraries();      		/* Install 3th libraies */

//	do_touchscreen_calibrate();         /* 触摸屏校正 */
    start_touchscreen_task();           /* touch_callback_t */

    start_my_gui(); 					/* start simple gui */

    dtmf_thread_init();                 // DTMF接收线程

    L610_thread_init();                 // L610连接腾讯云

    Polling_thread_init();              // 设备定时查询线程

    // 初始化 RTC 时间
    t.tm_year = 2022-1900;
    t.tm_mon  = 6-1;
    t.tm_mday = 29;
    t.tm_hour = 18;
    t.tm_min  = 18;
    t.tm_sec  = 18;
    ls1x_rtc_set_datetime(&t);

    rt_kprintf("main() is exit!\r\n");

    /*
     * Finsh as another thread...
     */
    return 0;
}

/*
 * @@ End
 */

