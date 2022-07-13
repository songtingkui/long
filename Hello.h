/**************************************************************************/
/* LabWindows/CVI User Interface Resource (UIR) Include File              */
/*                                                                        */
/* WARNING: Do not add to, delete from, or otherwise modify the contents  */
/*          of this include file.                                         */
/**************************************************************************/

#include <userint.h>

#ifdef __cplusplus
    extern "C" {
#endif

     /* Panels and Controls: */

#define  PANEL                            1       /* callback function: Quit_all */
#define  PANEL_CANVAS_13                  2       /* control type: canvas, callback function: (none) */
#define  PANEL_CANVAS_11                  3       /* control type: canvas, callback function: (none) */
#define  PANEL_CANVAS_12                  4       /* control type: canvas, callback function: (none) */
#define  PANEL_CANVAS_18                  5       /* control type: canvas, callback function: (none) */
#define  PANEL_CANVAS_14                  6       /* control type: canvas, callback function: (none) */
#define  PANEL_CANVAS_9                   7       /* control type: canvas, callback function: (none) */
#define  PANEL_CANVAS_7                   8       /* control type: canvas, callback function: (none) */
#define  PANEL_CANVAS_4                   9       /* control type: canvas, callback function: (none) */
#define  PANEL_CANVAS_3                   10      /* control type: canvas, callback function: (none) */
#define  PANEL_TEXTMSG_10                 11      /* control type: textMsg, callback function: (none) */
#define  PANEL_TEXTMSG_11                 12      /* control type: textMsg, callback function: (none) */
#define  PANEL_TEXTMSG_9                  13      /* control type: textMsg, callback function: (none) */
#define  PANEL_TEXTMSG_8                  14      /* control type: textMsg, callback function: (none) */
#define  PANEL_TEXTMSG_7                  15      /* control type: textMsg, callback function: (none) */
#define  PANEL_LED_7                      16      /* control type: LED, callback function: (none) */
#define  PANEL_LED_8                      17      /* control type: LED, callback function: (none) */
#define  PANEL_LED_9                      18      /* control type: LED, callback function: (none) */
#define  PANEL_TEXTMSG_12                 19      /* control type: textMsg, callback function: (none) */
#define  PANEL_TEXTMSG_3                  20      /* control type: textMsg, callback function: (none) */
#define  PANEL_TEXTMSG                    21      /* control type: textMsg, callback function: (none) */
#define  PANEL_LED_4                      22      /* control type: LED, callback function: (none) */
#define  PANEL_LED_5                      23      /* control type: LED, callback function: (none) */
#define  PANEL_LED_11                     24      /* control type: LED, callback function: (none) */
#define  PANEL_LED_10                     25      /* control type: LED, callback function: (none) */
#define  PANEL_LED_6                      26      /* control type: LED, callback function: (none) */
#define  PANEL_TEXTMSG_6                  27      /* control type: textMsg, callback function: (none) */
#define  PANEL_TEXTMSG_4                  28      /* control type: textMsg, callback function: (none) */
#define  PANEL_LED_3                      29      /* control type: LED, callback function: (none) */
#define  PANEL_LED_2                      30      /* control type: LED, callback function: (none) */
#define  PANEL_LED                        31      /* control type: LED, callback function: (none) */

#define  PANEL_2                          2       /* callback function: Quit_S1 */
#define  PANEL_2_STRING_3                 2       /* control type: string, callback function: (none) */
#define  PANEL_2_STRING_4                 3       /* control type: string, callback function: (none) */
#define  PANEL_2_NUMERIC_2                4       /* control type: numeric, callback function: (none) */
#define  PANEL_2_NUMERIC_1                5       /* control type: numeric, callback function: (none) */
#define  PANEL_2_COMMANDBUTTON_7          6       /* control type: command, callback function: Change_U */

#define  PANEL_3                          3       /* callback function: Quit_X */
#define  PANEL_3_STRING_6                 2       /* control type: string, callback function: (none) */
#define  PANEL_3_STRING_3                 3       /* control type: string, callback function: (none) */
#define  PANEL_3_STRING_5                 4       /* control type: string, callback function: (none) */
#define  PANEL_3_STRING_4                 5       /* control type: string, callback function: (none) */
#define  PANEL_3_NUMERIC_3                6       /* control type: numeric, callback function: (none) */
#define  PANEL_3_NUMERIC_2                7       /* control type: numeric, callback function: (none) */
#define  PANEL_3_NUMERIC_4                8       /* control type: numeric, callback function: (none) */
#define  PANEL_3_NUMERIC_1                9       /* control type: numeric, callback function: (none) */
#define  PANEL_3_COMMANDBUTTON_7          10      /* control type: command, callback function: Change_U */

#define  PANEL_4                          4       /* callback function: Quit_ChageV */
#define  PANEL_4_NUMERIC_2                2       /* control type: numeric, callback function: (none) */
#define  PANEL_4_NUMERIC_3                3       /* control type: numeric, callback function: (none) */
#define  PANEL_4_COMMANDBUTTON_7          4       /* control type: command, callback function: Correction_U */
#define  PANEL_4_STRING                   5       /* control type: string, callback function: (none) */

#define  PANEL_5                          5       /* callback function: Quit_S2 */
#define  PANEL_5_STRING_3                 2       /* control type: string, callback function: (none) */
#define  PANEL_5_STRING_4                 3       /* control type: string, callback function: (none) */
#define  PANEL_5_NUMERIC_2                4       /* control type: numeric, callback function: (none) */
#define  PANEL_5_NUMERIC_1                5       /* control type: numeric, callback function: (none) */
#define  PANEL_5_COMMANDBUTTON_7          6       /* control type: command, callback function: Change_U */


     /* Control Arrays: */

#define  CTRLARRAY                        1

     /* Menu Bars, Menus, and Menu Items: */

          /* (no menu bars in the resource file) */


     /* Callback Prototypes: */

int  CVICALLBACK Change_U(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK Correction_U(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK Quit_all(int panel, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK Quit_ChageV(int panel, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK Quit_S1(int panel, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK Quit_S2(int panel, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK Quit_X(int panel, int event, void *callbackData, int eventData1, int eventData2);


#ifdef __cplusplus
    }
#endif