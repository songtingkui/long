#include <windows.h>
#include <ansi_c.h>
#include "animate.h"
#include <cvirte.h>		
#include <userint.h>
#include "Hello.h"
#include "MQTTAsync.h"
#include <utility.h>
#include "tencentcloud.h"
#include "user.h"

int panelHandle;
int panelHandle2;
int panelHandle3;
int panelHandle4;
int panelHandle5;

//信号机数据
float 	Attribute_U[32];
float 	Attribute_I[32];
int 	Attribute_Warn[32];
int  	Attribute_Mark[32] = {0};

int Changeu_Mark;		//修改电压面板标志

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
	tencentConnect();
	Sleep(1000);
	
	//主设备订阅
	Mqtt_subscription ();
	
	RunUserInterface ();
	tencentDisconnect();
	

	
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

//子面板退出函数
int CVICALLBACK Quit_S1 (int panel, int event, void *callbackData,
							  int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_GOT_FOCUS:

			break;
		case EVENT_LOST_FOCUS:

			break;
		case EVENT_CLOSE:
			DiscardPanel (panelHandle2);
			break;
	}
	return 0;
}

int CVICALLBACK Quit_S2 (int panel, int event, void *callbackData,
							  int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_GOT_FOCUS:

			break;
		case EVENT_LOST_FOCUS:

			break;
		case EVENT_CLOSE:
			DiscardPanel (panelHandle5);
			break;
	}
	return 0;
}

int CVICALLBACK Quit_X (int panel, int event, void *callbackData,
							  int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_GOT_FOCUS:

			break;
		case EVENT_LOST_FOCUS:

			break;
		case EVENT_CLOSE:
			DiscardPanel (panelHandle3);
			break;
	}
	return 0;
}

int CVICALLBACK Quit_ChageV (int panel, int event, void *callbackData,
					  				int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_GOT_FOCUS:

			break;
		case EVENT_LOST_FOCUS:

			break;
		case EVENT_CLOSE:
			DiscardPanel (panelHandle4);
			break;
	}
	return 0;
}


int CVICALLBACK X_Information (int panel, int control, int event,
						 void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_COMMIT:
			
			int effective_mark = 0;			//第一位是否有效（是否有第一位）
				
			if ((panelHandle3 = LoadPanel (0, "Hello.uir", PANEL_3)) < 0)
			return -1;
				
			if (Attribute_Mark[X_TRACK_ONE] == 1)
			{
				SetCtrlVal (panelHandle3, PANEL_3_STRING_4,"1");				//灯号
				SetCtrlVal (panelHandle3, PANEL_3_NUMERIC_2,Attribute_I[X_TRACK_ONE]);
				SetCtrlVal (panelHandle3, PANEL_3_NUMERIC_1,Attribute_U[X_TRACK_ONE]);
				if(Attribute_Warn[X_TRACK_ONE] == 1)
				{
					SetCtrlVal (panelHandle3, PANEL_3_STRING_3,"异常");
				}
				else
				{
					SetCtrlVal (panelHandle3, PANEL_3_STRING_3,"正常");
				}
				effective_mark = 1;
				
			}
			else if (Attribute_Mark[X_TRACK_TWO] == 1)
			{
				SetCtrlVal (panelHandle3, PANEL_3_STRING_4,"2");				//灯号
				SetCtrlVal (panelHandle3, PANEL_3_NUMERIC_2,Attribute_I[X_TRACK_TWO]);
				SetCtrlVal (panelHandle3, PANEL_3_NUMERIC_1,Attribute_U[X_TRACK_TWO]);
				
				if(Attribute_Warn[X_TRACK_TWO] == 1)
				{
					SetCtrlVal (panelHandle3, PANEL_3_STRING_3,"异常");
				}
				else
				{
					SetCtrlVal (panelHandle3, PANEL_3_STRING_3,"正常");
				}
				effective_mark = 1;
			}
			else if (Attribute_Mark[X_TRACK_THREE] == 1)
			{
				SetCtrlVal (panelHandle3, PANEL_3_STRING_4,"3");				//灯号
				SetCtrlVal (panelHandle3, PANEL_3_NUMERIC_2,Attribute_I[X_TRACK_THREE]);
				SetCtrlVal (panelHandle3, PANEL_3_NUMERIC_1,Attribute_U[X_TRACK_THREE]);
				
				if(Attribute_Warn[X_TRACK_THREE] == 1)
				{
					SetCtrlVal (panelHandle3, PANEL_3_STRING_3,"异常");
				}
				else
				{
					SetCtrlVal (panelHandle3, PANEL_3_STRING_3,"正常");
				}
				effective_mark = 1;
			}
			else if (Attribute_Mark[X_TRACK_FOUR] == 1)
			{
				SetCtrlVal (panelHandle3, PANEL_3_STRING_4,"4");				//灯号
				SetCtrlVal (panelHandle3, PANEL_3_NUMERIC_2,Attribute_I[X_TRACK_FOUR]);
				SetCtrlVal (panelHandle3, PANEL_3_NUMERIC_1,Attribute_U[X_TRACK_FOUR]);
				
				if(Attribute_Warn[X_TRACK_FOUR] == 1)
				{
					SetCtrlVal (panelHandle3, PANEL_3_STRING_3,"异常");
				}
				else
				{
					SetCtrlVal (panelHandle3, PANEL_3_STRING_3,"正常");
				}
				effective_mark = 1;
			}
			else if (Attribute_Mark[X_TRACK_FIVE] == 1)
			{
				SetCtrlVal (panelHandle3, PANEL_3_STRING_4,"5");				//灯号
				SetCtrlVal (panelHandle3, PANEL_3_NUMERIC_2,Attribute_I[X_TRACK_FIVE]);
				SetCtrlVal (panelHandle3, PANEL_3_NUMERIC_1,Attribute_U[X_TRACK_FIVE]);
				
				if(Attribute_Warn[X_TRACK_FIVE] == 1)
				{
					SetCtrlVal (panelHandle3, PANEL_3_STRING_3,"异常");
				}
				else
				{
					SetCtrlVal (panelHandle3, PANEL_3_STRING_3,"正常");
				}
				effective_mark = 1;
			}
			
			
			if (effective_mark == 1)
			{
				if (Attribute_Mark[X_TRACK_TWO]  && Attribute_Mark[X_TRACK_ONE] == 1)
				{
					SetCtrlVal (panelHandle3, PANEL_3_STRING_5,"2");				//灯号
					SetCtrlVal (panelHandle3, PANEL_3_NUMERIC_3,Attribute_I[X_TRACK_TWO]);
					SetCtrlVal (panelHandle3, PANEL_3_NUMERIC_4,Attribute_U[X_TRACK_TWO]);
					
					if(Attribute_Warn[X_TRACK_TWO] == 1)
					{
						SetCtrlVal (panelHandle3, PANEL_3_STRING_6,"异常");
					}
					else
					{
						SetCtrlVal (panelHandle3, PANEL_3_STRING_6,"正常");
					}
					
				}
				else if (Attribute_Mark[X_TRACK_THREE] && (Attribute_Mark[X_TRACK_ONE] || Attribute_Mark[X_TRACK_TWO]) == 1)
				{
					SetCtrlVal (panelHandle3, PANEL_3_STRING_5,"3");				//灯号
					SetCtrlVal (panelHandle3, PANEL_3_NUMERIC_3,Attribute_I[X_TRACK_THREE]);
					SetCtrlVal (panelHandle3, PANEL_3_NUMERIC_4,Attribute_U[X_TRACK_THREE]);
					
					if(Attribute_Warn[X_TRACK_THREE] == 1)
					{
						SetCtrlVal (panelHandle3, PANEL_3_STRING_6,"异常");
					}
					else
					{
						SetCtrlVal (panelHandle3, PANEL_3_STRING_6,"正常");
					}
				
				}
				else if (Attribute_Mark[X_TRACK_FOUR] && (Attribute_Mark[X_TRACK_ONE] || Attribute_Mark[X_TRACK_TWO] || Attribute_Mark[X_TRACK_THREE]) == 1)
				{
					SetCtrlVal (panelHandle3, PANEL_3_STRING_5,"4");				//灯号
					SetCtrlVal (panelHandle3, PANEL_3_NUMERIC_3,Attribute_I[X_TRACK_FOUR]);
					SetCtrlVal (panelHandle3, PANEL_3_NUMERIC_4,Attribute_U[X_TRACK_FOUR]);
					
					if(Attribute_Warn[X_TRACK_FOUR] == 1)
					{
						SetCtrlVal (panelHandle3, PANEL_3_STRING_6,"异常");
					}
					else
					{
						SetCtrlVal (panelHandle3, PANEL_3_STRING_6,"正常");
					}
				}
				else if (Attribute_Mark[X_TRACK_FIVE] && (Attribute_Mark[X_TRACK_ONE] || Attribute_Mark[X_TRACK_TWO] || Attribute_Mark[X_TRACK_THREE] || Attribute_Mark[X_TRACK_FOUR]) == 1)
				{
					SetCtrlVal (panelHandle3, PANEL_3_STRING_5,"5");						//灯号
					SetCtrlVal (panelHandle3, PANEL_3_NUMERIC_3,Attribute_I[X_TRACK_FIVE]);
					SetCtrlVal (panelHandle3, PANEL_3_NUMERIC_4,Attribute_U[X_TRACK_FIVE]);
					
					if(Attribute_Warn[X_TRACK_FIVE] == 1)
					{
						SetCtrlVal (panelHandle3, PANEL_3_STRING_6,"异常");
					}
					else
					{
						SetCtrlVal (panelHandle3, PANEL_3_STRING_6,"正常");
					}

				}
				}
			DisplayPanel(panelHandle3);
			
			break;
	}
	return 0;
}

int CVICALLBACK S1_Information (int panel, int control, int event,
						 void *callbackData, int eventData1, int eventData2)
{
	
	switch (event)
	{
		case EVENT_COMMIT:
			if ((panelHandle2 = LoadPanel (0, "Hello.uir", PANEL_2)) < 0)
				return -1;
				
			if ( Attribute_Mark[S_TRACK1_ONE] == 1)
			{
				SetCtrlVal (panelHandle2, PANEL_2_STRING_4,"1");				//灯号
				SetCtrlVal (panelHandle2, PANEL_2_NUMERIC_2,Attribute_I[S_TRACK1_ONE]);
				SetCtrlVal (panelHandle2, PANEL_2_NUMERIC_1,Attribute_U[S_TRACK1_ONE]);
					
				if(Attribute_Warn[S_TRACK1_ONE] == 1)
				{
					SetCtrlVal (panelHandle2, PANEL_2_STRING_3,"异常");
				}
				else
				{
					SetCtrlVal (panelHandle2, PANEL_2_STRING_3,"正常");
				}	
			}
			else if(Attribute_Mark[S_TRACK1_TWO] == 1)
			{
				SetCtrlVal (panelHandle2, PANEL_2_STRING_4,"2");				//灯号
				SetCtrlVal (panelHandle2, PANEL_2_NUMERIC_2,Attribute_I[S_TRACK1_TWO]);
				SetCtrlVal (panelHandle2, PANEL_2_NUMERIC_1,Attribute_U[S_TRACK1_TWO]);
					
				if(Attribute_Warn[S_TRACK1_TWO] == 1)
				{
					SetCtrlVal (panelHandle2, PANEL_2_STRING_3,"异常");
				}
				else
				{
					SetCtrlVal (panelHandle2, PANEL_2_STRING_3,"正常");
				}	
			}
			else if(Attribute_Mark[S_TRACK1_THREE] == 1)
			{
				SetCtrlVal (panelHandle2, PANEL_2_STRING_4,"3");				//灯号
				SetCtrlVal (panelHandle2, PANEL_2_NUMERIC_2,Attribute_I[S_TRACK1_THREE]);
				SetCtrlVal (panelHandle2, PANEL_2_NUMERIC_1,Attribute_U[S_TRACK1_THREE]);
					
				if(Attribute_Warn[S_TRACK1_THREE] == 1)
				{
					SetCtrlVal (panelHandle2, PANEL_2_STRING_3,"异常");
				}
				else
				{
					SetCtrlVal (panelHandle2, PANEL_2_STRING_3,"正常");
				}	
			}			
			
			DisplayPanel(panelHandle2);

			break;
	}
		return 0;
}
				

int CVICALLBACK S2_Information (int panel, int control, int event,
						 void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_COMMIT:
			if ((panelHandle5 = LoadPanel (0, "Hello.uir", PANEL_5)) < 0)
				return -1;
				
			if ( Attribute_Mark[S_TRACK2_ONE] == 1)
			{
				SetCtrlVal (panelHandle5, PANEL_5_STRING_4,"1");				//灯号
				SetCtrlVal (panelHandle5, PANEL_5_NUMERIC_2,Attribute_I[S_TRACK2_ONE]);
				SetCtrlVal (panelHandle5, PANEL_5_NUMERIC_1,Attribute_U[S_TRACK2_ONE]);
					
				if(Attribute_Warn[S_TRACK2_ONE] == 1)
				{
					SetCtrlVal (panelHandle5, PANEL_5_STRING_3,"异常");
				}
				else
				{
					SetCtrlVal (panelHandle5, PANEL_5_STRING_3,"正常");
				}	
			}
			else if(Attribute_Mark[S_TRACK2_TWO] == 1)
			{
				SetCtrlVal (panelHandle5, PANEL_5_STRING_4,"2");				//灯号
				SetCtrlVal (panelHandle5, PANEL_5_NUMERIC_2,Attribute_I[S_TRACK2_TWO]);
				SetCtrlVal (panelHandle5, PANEL_5_NUMERIC_1,Attribute_U[S_TRACK2_TWO]);
					
				if(Attribute_Warn[S_TRACK2_TWO] == 1)
				{
					SetCtrlVal (panelHandle5, PANEL_5_STRING_3,"异常");
				}
				else
				{
					SetCtrlVal (panelHandle5, PANEL_5_STRING_3,"正常");
				}	
			}
			else if(Attribute_Mark[S_TRACK2_THREE] == 1)
			{
				SetCtrlVal (panelHandle5, PANEL_5_STRING_4,"3");				//灯号
				SetCtrlVal (panelHandle5, PANEL_5_NUMERIC_2,Attribute_I[S_TRACK2_THREE]);
				SetCtrlVal (panelHandle5, PANEL_5_NUMERIC_1,Attribute_U[S_TRACK2_THREE]);
					
				if(Attribute_Warn[S_TRACK2_THREE] == 1)
				{
					SetCtrlVal (panelHandle5, PANEL_5_STRING_3,"异常");
				}
				else
				{
					SetCtrlVal (panelHandle5, PANEL_5_STRING_3,"正常");
				}	
			}			
			
			DisplayPanel(panelHandle5);
			
			break;
	}
	return 0;
}

//回调函数-----修改电压面板弹出
int CVICALLBACK Change_U (int panel, int control, int event,
						  void *callbackData, int eventData1, int eventData2)
{
	
	switch (event)
	{
		case EVENT_COMMIT:
			
			if ((panelHandle4 = LoadPanel (0, "Hello.uir", PANEL_4)) < 0)
				return -1;
			
			if (panel == panelHandle3)		//修改X信号机电压
			{
				SetCtrlVal(panelHandle4,PANEL_4_STRING,"X");
				DisplayPanel (panelHandle4);
				DiscardPanel (panelHandle3);
				Changeu_Mark = CHANGE_X_MARK;
			}
			
			if (panel == panelHandle2)		//修改S-1信号机电压
			{
				SetCtrlVal(panelHandle4,PANEL_4_STRING,"S-1");
				DisplayPanel (panelHandle4);
				DiscardPanel (panelHandle2);
				Changeu_Mark = CHANGE_S1_MARK;
			}
			if (panel == panelHandle5)		//修改S-Ⅱ信号机电压
			{
				SetCtrlVal(panelHandle4,PANEL_4_STRING,"S-Ⅱ");
				DisplayPanel (panelHandle4);
				DiscardPanel (panelHandle5);
				Changeu_Mark = CHANGE_S2_MARK;
			}
			
			break;
			
	}
	return 0;
}


//修改电压********************
//用主设备发送给1B且发送至   对应设备
int CVICALLBACK Correction_U (int panel, int control, int event,
							  void *callbackData, int eventData1, int eventData2)
{
	
	if ((panelHandle3 = LoadPanel (0, "Hello.uir", PANEL_3)) < 0)
				return -1;
	
	unsigned int lamp_ID;		//灯号
	float lamp_U;
	
	char content[1024];
	
	switch (event)
	{
		case EVENT_COMMIT:
										
			GetCtrlVal (panelHandle4, PANEL_4_NUMERIC_3, &lamp_ID);			//取修改灯号
			GetCtrlVal (panelHandle4, PANEL_4_NUMERIC_2, &lamp_U); 		    //取修改电压
			
			switch (Changeu_Mark)
			{
				case CHANGE_X_MARK:
				
					//内容打包
					sprintf(content,"{ \"method\":\"report\", \"params\":{\"U\":%.1f,\"ID\":\"4-00-%d\"} }",lamp_U,lamp_ID);	
					Mqtt_Send(content,PRIMARY_SENDTOPIC,g_client[0]);
					
					DiscardPanel (panelHandle4);

					break;
				case CHANGE_S1_MARK:
					//内容打包
					sprintf(content,"{ \"method\":\"report\", \"params\":{\"U\":%.1f,\"ID\":\"2-01-%d\"} }",lamp_U,lamp_ID);	
					Mqtt_Send(content,PRIMARY_SENDTOPIC,g_client[0]);
					
					DiscardPanel (panelHandle4);
					
					break;
				case CHANGE_S2_MARK:
				
					//内容打包
					sprintf(content,"{ \"method\":\"report\", \"params\":{\"U\":%.1f,\"ID\":\"2-02-%d\"} }",lamp_U,lamp_ID);	
					Mqtt_Send(content,PRIMARY_SENDTOPIC,g_client[0]);

					DiscardPanel (panelHandle4);
					
					break;
			}
			
			
			
			break;
	}
	return 0;
}

int CVICALLBACK D1_Information (int panel, int control, int event,
								void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_COMMIT:

			break;
	}
	return 0;
}
