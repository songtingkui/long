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

//�źŻ�����
float 	Attribute_U[32];
float 	Attribute_I[32];
int 	Attribute_Warn[32];
int  	Attribute_Mark[32] = {0};

int Changeu_Mark;		//�޸ĵ�ѹ����־

///////////////////main***********************
int main (int argc, char *argv[])
{
	if (InitCVIRTE (0, argv, 0) == 0)
		return -1;	/* out of memory */
	
	if ((panelHandle = LoadPanel (0, "Hello.uir", PANEL)) < 0)
		return -1;
		
	//�����б��
	DrawLine ();
	
	DisplayPanel (panelHandle);
	
	
	
	//���豸����
	tencentConnect();
	Sleep(1000);
	
	//���豸����
	Mqtt_subscription ();
	
	RunUserInterface ();
	tencentDisconnect();
	

	
	DiscardPanel (panelHandle);
	return 0;
}
	
//������˳�����
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

//������˳�����
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
			
			int effective_mark = 0;			//��һλ�Ƿ���Ч���Ƿ��е�һλ��
				
			if ((panelHandle3 = LoadPanel (0, "Hello.uir", PANEL_3)) < 0)
			return -1;
				
			if (Attribute_Mark[X_TRACK_ONE] == 1)
			{
				SetCtrlVal (panelHandle3, PANEL_3_STRING_4,"1");				//�ƺ�
				SetCtrlVal (panelHandle3, PANEL_3_NUMERIC_2,Attribute_I[X_TRACK_ONE]);
				SetCtrlVal (panelHandle3, PANEL_3_NUMERIC_1,Attribute_U[X_TRACK_ONE]);
				if(Attribute_Warn[X_TRACK_ONE] == 1)
				{
					SetCtrlVal (panelHandle3, PANEL_3_STRING_3,"�쳣");
				}
				else
				{
					SetCtrlVal (panelHandle3, PANEL_3_STRING_3,"����");
				}
				effective_mark = 1;
				
			}
			else if (Attribute_Mark[X_TRACK_TWO] == 1)
			{
				SetCtrlVal (panelHandle3, PANEL_3_STRING_4,"2");				//�ƺ�
				SetCtrlVal (panelHandle3, PANEL_3_NUMERIC_2,Attribute_I[X_TRACK_TWO]);
				SetCtrlVal (panelHandle3, PANEL_3_NUMERIC_1,Attribute_U[X_TRACK_TWO]);
				
				if(Attribute_Warn[X_TRACK_TWO] == 1)
				{
					SetCtrlVal (panelHandle3, PANEL_3_STRING_3,"�쳣");
				}
				else
				{
					SetCtrlVal (panelHandle3, PANEL_3_STRING_3,"����");
				}
				effective_mark = 1;
			}
			else if (Attribute_Mark[X_TRACK_THREE] == 1)
			{
				SetCtrlVal (panelHandle3, PANEL_3_STRING_4,"3");				//�ƺ�
				SetCtrlVal (panelHandle3, PANEL_3_NUMERIC_2,Attribute_I[X_TRACK_THREE]);
				SetCtrlVal (panelHandle3, PANEL_3_NUMERIC_1,Attribute_U[X_TRACK_THREE]);
				
				if(Attribute_Warn[X_TRACK_THREE] == 1)
				{
					SetCtrlVal (panelHandle3, PANEL_3_STRING_3,"�쳣");
				}
				else
				{
					SetCtrlVal (panelHandle3, PANEL_3_STRING_3,"����");
				}
				effective_mark = 1;
			}
			else if (Attribute_Mark[X_TRACK_FOUR] == 1)
			{
				SetCtrlVal (panelHandle3, PANEL_3_STRING_4,"4");				//�ƺ�
				SetCtrlVal (panelHandle3, PANEL_3_NUMERIC_2,Attribute_I[X_TRACK_FOUR]);
				SetCtrlVal (panelHandle3, PANEL_3_NUMERIC_1,Attribute_U[X_TRACK_FOUR]);
				
				if(Attribute_Warn[X_TRACK_FOUR] == 1)
				{
					SetCtrlVal (panelHandle3, PANEL_3_STRING_3,"�쳣");
				}
				else
				{
					SetCtrlVal (panelHandle3, PANEL_3_STRING_3,"����");
				}
				effective_mark = 1;
			}
			else if (Attribute_Mark[X_TRACK_FIVE] == 1)
			{
				SetCtrlVal (panelHandle3, PANEL_3_STRING_4,"5");				//�ƺ�
				SetCtrlVal (panelHandle3, PANEL_3_NUMERIC_2,Attribute_I[X_TRACK_FIVE]);
				SetCtrlVal (panelHandle3, PANEL_3_NUMERIC_1,Attribute_U[X_TRACK_FIVE]);
				
				if(Attribute_Warn[X_TRACK_FIVE] == 1)
				{
					SetCtrlVal (panelHandle3, PANEL_3_STRING_3,"�쳣");
				}
				else
				{
					SetCtrlVal (panelHandle3, PANEL_3_STRING_3,"����");
				}
				effective_mark = 1;
			}
			
			
			if (effective_mark == 1)
			{
				if (Attribute_Mark[X_TRACK_TWO]  && Attribute_Mark[X_TRACK_ONE] == 1)
				{
					SetCtrlVal (panelHandle3, PANEL_3_STRING_5,"2");				//�ƺ�
					SetCtrlVal (panelHandle3, PANEL_3_NUMERIC_3,Attribute_I[X_TRACK_TWO]);
					SetCtrlVal (panelHandle3, PANEL_3_NUMERIC_4,Attribute_U[X_TRACK_TWO]);
					
					if(Attribute_Warn[X_TRACK_TWO] == 1)
					{
						SetCtrlVal (panelHandle3, PANEL_3_STRING_6,"�쳣");
					}
					else
					{
						SetCtrlVal (panelHandle3, PANEL_3_STRING_6,"����");
					}
					
				}
				else if (Attribute_Mark[X_TRACK_THREE] && (Attribute_Mark[X_TRACK_ONE] || Attribute_Mark[X_TRACK_TWO]) == 1)
				{
					SetCtrlVal (panelHandle3, PANEL_3_STRING_5,"3");				//�ƺ�
					SetCtrlVal (panelHandle3, PANEL_3_NUMERIC_3,Attribute_I[X_TRACK_THREE]);
					SetCtrlVal (panelHandle3, PANEL_3_NUMERIC_4,Attribute_U[X_TRACK_THREE]);
					
					if(Attribute_Warn[X_TRACK_THREE] == 1)
					{
						SetCtrlVal (panelHandle3, PANEL_3_STRING_6,"�쳣");
					}
					else
					{
						SetCtrlVal (panelHandle3, PANEL_3_STRING_6,"����");
					}
				
				}
				else if (Attribute_Mark[X_TRACK_FOUR] && (Attribute_Mark[X_TRACK_ONE] || Attribute_Mark[X_TRACK_TWO] || Attribute_Mark[X_TRACK_THREE]) == 1)
				{
					SetCtrlVal (panelHandle3, PANEL_3_STRING_5,"4");				//�ƺ�
					SetCtrlVal (panelHandle3, PANEL_3_NUMERIC_3,Attribute_I[X_TRACK_FOUR]);
					SetCtrlVal (panelHandle3, PANEL_3_NUMERIC_4,Attribute_U[X_TRACK_FOUR]);
					
					if(Attribute_Warn[X_TRACK_FOUR] == 1)
					{
						SetCtrlVal (panelHandle3, PANEL_3_STRING_6,"�쳣");
					}
					else
					{
						SetCtrlVal (panelHandle3, PANEL_3_STRING_6,"����");
					}
				}
				else if (Attribute_Mark[X_TRACK_FIVE] && (Attribute_Mark[X_TRACK_ONE] || Attribute_Mark[X_TRACK_TWO] || Attribute_Mark[X_TRACK_THREE] || Attribute_Mark[X_TRACK_FOUR]) == 1)
				{
					SetCtrlVal (panelHandle3, PANEL_3_STRING_5,"5");						//�ƺ�
					SetCtrlVal (panelHandle3, PANEL_3_NUMERIC_3,Attribute_I[X_TRACK_FIVE]);
					SetCtrlVal (panelHandle3, PANEL_3_NUMERIC_4,Attribute_U[X_TRACK_FIVE]);
					
					if(Attribute_Warn[X_TRACK_FIVE] == 1)
					{
						SetCtrlVal (panelHandle3, PANEL_3_STRING_6,"�쳣");
					}
					else
					{
						SetCtrlVal (panelHandle3, PANEL_3_STRING_6,"����");
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
				SetCtrlVal (panelHandle2, PANEL_2_STRING_4,"1");				//�ƺ�
				SetCtrlVal (panelHandle2, PANEL_2_NUMERIC_2,Attribute_I[S_TRACK1_ONE]);
				SetCtrlVal (panelHandle2, PANEL_2_NUMERIC_1,Attribute_U[S_TRACK1_ONE]);
					
				if(Attribute_Warn[S_TRACK1_ONE] == 1)
				{
					SetCtrlVal (panelHandle2, PANEL_2_STRING_3,"�쳣");
				}
				else
				{
					SetCtrlVal (panelHandle2, PANEL_2_STRING_3,"����");
				}	
			}
			else if(Attribute_Mark[S_TRACK1_TWO] == 1)
			{
				SetCtrlVal (panelHandle2, PANEL_2_STRING_4,"2");				//�ƺ�
				SetCtrlVal (panelHandle2, PANEL_2_NUMERIC_2,Attribute_I[S_TRACK1_TWO]);
				SetCtrlVal (panelHandle2, PANEL_2_NUMERIC_1,Attribute_U[S_TRACK1_TWO]);
					
				if(Attribute_Warn[S_TRACK1_TWO] == 1)
				{
					SetCtrlVal (panelHandle2, PANEL_2_STRING_3,"�쳣");
				}
				else
				{
					SetCtrlVal (panelHandle2, PANEL_2_STRING_3,"����");
				}	
			}
			else if(Attribute_Mark[S_TRACK1_THREE] == 1)
			{
				SetCtrlVal (panelHandle2, PANEL_2_STRING_4,"3");				//�ƺ�
				SetCtrlVal (panelHandle2, PANEL_2_NUMERIC_2,Attribute_I[S_TRACK1_THREE]);
				SetCtrlVal (panelHandle2, PANEL_2_NUMERIC_1,Attribute_U[S_TRACK1_THREE]);
					
				if(Attribute_Warn[S_TRACK1_THREE] == 1)
				{
					SetCtrlVal (panelHandle2, PANEL_2_STRING_3,"�쳣");
				}
				else
				{
					SetCtrlVal (panelHandle2, PANEL_2_STRING_3,"����");
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
				SetCtrlVal (panelHandle5, PANEL_5_STRING_4,"1");				//�ƺ�
				SetCtrlVal (panelHandle5, PANEL_5_NUMERIC_2,Attribute_I[S_TRACK2_ONE]);
				SetCtrlVal (panelHandle5, PANEL_5_NUMERIC_1,Attribute_U[S_TRACK2_ONE]);
					
				if(Attribute_Warn[S_TRACK2_ONE] == 1)
				{
					SetCtrlVal (panelHandle5, PANEL_5_STRING_3,"�쳣");
				}
				else
				{
					SetCtrlVal (panelHandle5, PANEL_5_STRING_3,"����");
				}	
			}
			else if(Attribute_Mark[S_TRACK2_TWO] == 1)
			{
				SetCtrlVal (panelHandle5, PANEL_5_STRING_4,"2");				//�ƺ�
				SetCtrlVal (panelHandle5, PANEL_5_NUMERIC_2,Attribute_I[S_TRACK2_TWO]);
				SetCtrlVal (panelHandle5, PANEL_5_NUMERIC_1,Attribute_U[S_TRACK2_TWO]);
					
				if(Attribute_Warn[S_TRACK2_TWO] == 1)
				{
					SetCtrlVal (panelHandle5, PANEL_5_STRING_3,"�쳣");
				}
				else
				{
					SetCtrlVal (panelHandle5, PANEL_5_STRING_3,"����");
				}	
			}
			else if(Attribute_Mark[S_TRACK2_THREE] == 1)
			{
				SetCtrlVal (panelHandle5, PANEL_5_STRING_4,"3");				//�ƺ�
				SetCtrlVal (panelHandle5, PANEL_5_NUMERIC_2,Attribute_I[S_TRACK2_THREE]);
				SetCtrlVal (panelHandle5, PANEL_5_NUMERIC_1,Attribute_U[S_TRACK2_THREE]);
					
				if(Attribute_Warn[S_TRACK2_THREE] == 1)
				{
					SetCtrlVal (panelHandle5, PANEL_5_STRING_3,"�쳣");
				}
				else
				{
					SetCtrlVal (panelHandle5, PANEL_5_STRING_3,"����");
				}	
			}			
			
			DisplayPanel(panelHandle5);
			
			break;
	}
	return 0;
}

//�ص�����-----�޸ĵ�ѹ��嵯��
int CVICALLBACK Change_U (int panel, int control, int event,
						  void *callbackData, int eventData1, int eventData2)
{
	
	switch (event)
	{
		case EVENT_COMMIT:
			
			if ((panelHandle4 = LoadPanel (0, "Hello.uir", PANEL_4)) < 0)
				return -1;
			
			if (panel == panelHandle3)		//�޸�X�źŻ���ѹ
			{
				SetCtrlVal(panelHandle4,PANEL_4_STRING,"X");
				DisplayPanel (panelHandle4);
				DiscardPanel (panelHandle3);
				Changeu_Mark = CHANGE_X_MARK;
			}
			
			if (panel == panelHandle2)		//�޸�S-1�źŻ���ѹ
			{
				SetCtrlVal(panelHandle4,PANEL_4_STRING,"S-1");
				DisplayPanel (panelHandle4);
				DiscardPanel (panelHandle2);
				Changeu_Mark = CHANGE_S1_MARK;
			}
			if (panel == panelHandle5)		//�޸�S-���źŻ���ѹ
			{
				SetCtrlVal(panelHandle4,PANEL_4_STRING,"S-��");
				DisplayPanel (panelHandle4);
				DiscardPanel (panelHandle5);
				Changeu_Mark = CHANGE_S2_MARK;
			}
			
			break;
			
	}
	return 0;
}


//�޸ĵ�ѹ********************
//�����豸���͸�1B�ҷ�����   ��Ӧ�豸
int CVICALLBACK Correction_U (int panel, int control, int event,
							  void *callbackData, int eventData1, int eventData2)
{
	
	if ((panelHandle3 = LoadPanel (0, "Hello.uir", PANEL_3)) < 0)
				return -1;
	
	unsigned int lamp_ID;		//�ƺ�
	float lamp_U;
	
	char content[1024];
	
	switch (event)
	{
		case EVENT_COMMIT:
										
			GetCtrlVal (panelHandle4, PANEL_4_NUMERIC_3, &lamp_ID);			//ȡ�޸ĵƺ�
			GetCtrlVal (panelHandle4, PANEL_4_NUMERIC_2, &lamp_U); 		    //ȡ�޸ĵ�ѹ
			
			switch (Changeu_Mark)
			{
				case CHANGE_X_MARK:
				
					//���ݴ��
					sprintf(content,"{ \"method\":\"report\", \"params\":{\"U\":%.1f,\"ID\":\"4-00-%d\"} }",lamp_U,lamp_ID);	
					Mqtt_Send(content,PRIMARY_SENDTOPIC,g_client[0]);
					
					DiscardPanel (panelHandle4);

					break;
				case CHANGE_S1_MARK:
					//���ݴ��
					sprintf(content,"{ \"method\":\"report\", \"params\":{\"U\":%.1f,\"ID\":\"2-01-%d\"} }",lamp_U,lamp_ID);	
					Mqtt_Send(content,PRIMARY_SENDTOPIC,g_client[0]);
					
					DiscardPanel (panelHandle4);
					
					break;
				case CHANGE_S2_MARK:
				
					//���ݴ��
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
