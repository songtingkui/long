#include <windows.h>
#include <ansi_c.h>
#include "animate.h"
#include <cvirte.h>		
#include <userint.h>
#include "Hello.h"



int panelHandle;
int panelHandle2;
int panelHandle3;
int panelHandle4;
int panelHandle5;



//画轨道斜线
void DrawLine (void)
{

	SetCtrlAttribute (panelHandle, PANEL_CANVAS_3, ATTR_PEN_WIDTH, 8);
	SetCtrlAttribute (panelHandle, PANEL_CANVAS_3, ATTR_PEN_COLOR, 0xFFFFFFL);

	int x, y;
	GetCtrlAttribute (panelHandle, PANEL_CANVAS_3, ATTR_WIDTH, &x);							//取PANEL_CANVA的SATTR_WIDTH（赋值给x）
	GetCtrlAttribute (panelHandle, PANEL_CANVAS_3, ATTR_HEIGHT, &y);						////取PANEL_CANVA的ATTR_HEIGHT（赋值给y）原点

	CanvasDrawLine (panelHandle, PANEL_CANVAS_3, MakePoint (0, y), MakePoint (x, 0)); 		//（MakePoint (0, 2)第一个点，MakePoint (x, 2)第二个点）

}



///////////////////main***********************
int main (int argc, char *argv[])
{
	if (InitCVIRTE (0, argv, 0) == 0)
		return -1;	/* out of memory */
	
	if ((panelHandle = LoadPanel (0, "Hello.uir", PANEL)) < 0)
		return -1;
	

	//画轨道斜线
	DrawLine ();
	DisplayPanel (panelHandle);

	//子设备连接
//	tencentConnect();
//	Sleep(1000);
	
	//主设备订阅
//	Mqtt_subscription ();
	
	RunUserInterface ();


	
	DiscardPanel (panelHandle);
	return 0;
}
	
//主面板退出函数
int CVICALLBACK Quit_all (int panel, int event, void *callbackData,
								int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_GOT_FOCUS:

			break;
		case EVENT_LOST_FOCUS:

			break;
		case EVENT_CLOSE:
			QuitUserInterface (0);
			break;
	}
	return 0;
}
