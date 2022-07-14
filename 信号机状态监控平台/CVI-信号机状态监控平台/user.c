#include <windows.h>
#include <ansi_c.h>
#include "animate.h"
#include <cvirte.h>
#include <userint.h>
#include "Hello.h"
#include "MQTTAsync.h"
#include "tencentcloud.h"
#include "user.h"
#include "tencentcloud.h"



MQTTAsync g_client[32];

void ledALLon(void)
{
	SetCtrlVal (panelHandle, PANEL_LED_1, 1);
	SetCtrlVal (panelHandle, PANEL_LED_2, 1);
	SetCtrlVal (panelHandle, PANEL_LED_3, 1);
	SetCtrlVal (panelHandle, PANEL_LED_4, 1);
	SetCtrlVal (panelHandle, PANEL_LED_5, 1);
	SetCtrlVal (panelHandle, PANEL_LED_6, 1);
	SetCtrlVal (panelHandle, PANEL_LED_7, 1);
	SetCtrlVal (panelHandle, PANEL_LED_8, 1);
	SetCtrlVal (panelHandle, PANEL_LED_9, 1);
	SetCtrlVal (panelHandle, PANEL_LED_10, 1);
	SetCtrlVal (panelHandle, PANEL_LED_11, 1);
	
}

void LedOn(void)
{
	
	//亮灯X-1
	SetCtrlVal (panelHandle, PANEL_LED_1, Attribute_Mark[X_TRACK_ONE]);
	SetCtrlVal (panelHandle, PANEL_LED_2, Attribute_Mark[X_TRACK_TWO]);
	SetCtrlVal (panelHandle, PANEL_LED_3, Attribute_Mark[X_TRACK_THREE]);
	SetCtrlVal (panelHandle, PANEL_LED_4, Attribute_Mark[X_TRACK_FOUR]);
	SetCtrlVal (panelHandle, PANEL_LED_5, Attribute_Mark[X_TRACK_FIVE]);
	//亮灯X-2
	SetCtrlVal (panelHandle, PANEL_LED_6, Attribute_Mark[S_TRACK1_ONE]);
	SetCtrlVal (panelHandle, PANEL_LED_7, Attribute_Mark[S_TRACK1_TWO]);
	SetCtrlVal (panelHandle, PANEL_LED_8, Attribute_Mark[S_TRACK1_THREE]);
	//亮灯X-3
	SetCtrlVal (panelHandle, PANEL_LED_9,  Attribute_Mark[S_TRACK2_ONE]);
	SetCtrlVal (panelHandle, PANEL_LED_10, Attribute_Mark[S_TRACK2_TWO]);
	SetCtrlVal (panelHandle, PANEL_LED_11, Attribute_Mark[S_TRACK2_THREE]);
	
	SetCtrlVal (panelHandle, PANEL_LED_12,  Attribute_Mark[D_TRACK1_ONE]);
	SetCtrlVal (panelHandle, PANEL_LED_13, Attribute_Mark[D_TRACK1_TWO]);
}

void onDisconnect(void* context, MQTTAsync_successData* response)
{
	printf("Successful disconnection\n");
}

void onDisconnectFailure(void* context, MQTTAsync_failureData* response)
{
	printf("Disconnect failed\n");
}

void onSubscribe(void* context, MQTTAsync_successData* response)
{
	printf("Subscribe succeeded\n");
}

void onSubscribeFailure(void* context, MQTTAsync_failureData* response)
{
	printf("Subscribe failed, rc %d\n", response->code);
}

void onSend(void* context, MQTTAsync_successData* response)
{
	//MQTTAsync client = (MQTTAsync)context;
	//MQTTAsync_disconnectOptions opts = MQTTAsync_disconnectOptions_initializer;
	//int rc;

	printf("Message with token value %d delivery confirmed\n", response->token);

	//opts.onSuccess = onDisconnect;
	//opts.context = client;

	//if ((rc = MQTTAsync_disconnect(client, &opts)) != MQTTASYNC_SUCCESS)
	//{
	//	printf("Failed to start sendMessage, return code %d\n", rc);
	//	exit(EXIT_FAILURE);
	//}
}

void onSendFailure(void* context, MQTTAsync_failureData* response)
{
	MQTTAsync client = (MQTTAsync)context;
	MQTTAsync_disconnectOptions opts = MQTTAsync_disconnectOptions_initializer;
	int rc;

	printf("Message send failed token %d error code %d\n", response->token, response->code);

	opts.onSuccess = onDisconnect;
	opts.onFailure = onDisconnectFailure;
	opts.context = client;
	if ((rc = MQTTAsync_disconnect(client, &opts)) != MQTTASYNC_SUCCESS)
	{
		printf("Failed to start disconnect, return code %d\n", rc);
		exit(EXIT_FAILURE);
	}
}

void onConnectFailure(void* context, MQTTAsync_failureData* response)
{
	printf("Connect failed, rc %d\n", response ? response->code : 0);
}


void onConnect(void* context, MQTTAsync_successData* response)
{
	printf("Successful connection\n");
}


void connlost(void *context, char *cause)
{
	printf("\nConnection lost\n");
//	printf("     cause: %s\n", cause);
	
}


//接收回调函数（含有一些多余打印）
int messageArrived(void* context, char* topicName, int topicLen, MQTTAsync_message* message)
{
	char date[1024] ,*chr;
	char Date_ID[256];
	double dateTime;
	
	int signal_type;
	int signal_track;
	int signal_lampId;
	
	int Attribute_Count;
	
	printf("Message arrived\n");
	printf("     topic: %s\n", topicName);

	memcpy(date, message->payload, message->payloadlen);
	date[message->payloadlen] = 0;
	printf("   message: %s\n", date);

	//GetCtrlVal (panelHandle, PANEL_STRING_4, date);

	//处理前序号归0
	Attribute_Count = 0;
	
	
	chr = strstr(date, "datetimes");
	if (NULL != chr)
	{
		GetCurrentDateTime (&dateTime);
		FormatDateTimeStringAnsi(dateTime, "{\"datetimes\":\"%Y-%m-%d %H:%M:%S\"}", date, 1024);
		Mqtt_Send(date,"$thing/up/property/8G6SX32L49/PC",g_client[0]);	
		SetCtrlVal (panelHandle, PANEL_STRING_4, date);
		
	}
	else
	{
		chr = strstr(date, "\"ID\":");
		if (NULL != chr)
		{
			sscanf(chr, "\"ID\":\"%6s", Date_ID);
		}

		//获取信号机号和灯序号（Attribute_Count）和灯号（Attribute_Number = b）第34+6
		sscanf(&Date_ID[0], "%d-%d-%d",&signal_type,&signal_track,&signal_lampId);

		printf("%d-%d-%d\n",signal_type,signal_track,signal_lampId);
		
		if (signal_type == 4)  //'X'
		{
			if (signal_track == 0)
			{
				switch(signal_lampId)
				{
					case 1:
						Attribute_Count = X_TRACK_ONE;
						 Mqtt_Send(date,"$thing/up/property/OLMJUNLIUQ/X_0_1",g_client[Attribute_Count]);	
						break;
					case 2:
						Attribute_Count = X_TRACK_TWO;
						Mqtt_Send(date,"$thing/up/property/OLMJUNLIUQ/X_0_2",g_client[Attribute_Count]);	
						break;
					case 3:
						Attribute_Count = X_TRACK_THREE;
						Mqtt_Send(date,"$thing/up/property/OLMJUNLIUQ/X_0_3",g_client[Attribute_Count]);	
						break;
					case 4:
						Attribute_Count = X_TRACK_FOUR;
						Mqtt_Send(date,"$thing/up/property/OLMJUNLIUQ/X_0_4",g_client[Attribute_Count]);	
						break;
					case 5:
						Attribute_Count = X_TRACK_FIVE;
						Mqtt_Send(date,"$thing/up/property/OLMJUNLIUQ/X_0_5",g_client[Attribute_Count]);	
						break;
				}
			}
			
		}
		else if (signal_type == 2)
		{
			if (signal_track == 1)
			{
			
				switch(signal_lampId)
				{
					case 1:
						Attribute_Count = S_TRACK1_ONE;
						Mqtt_Send(date,"$thing/up/property/OLMJUNLIUQ/S_1_1",g_client[Attribute_Count]);	
						break;
					case 2:
						Attribute_Count = S_TRACK1_TWO;
						Mqtt_Send(date,"$thing/up/property/OLMJUNLIUQ/S_1_2",g_client[Attribute_Count]);	
						break;
					case 3:
						Attribute_Count = S_TRACK1_THREE;
						Mqtt_Send(date,"$thing/up/property/OLMJUNLIUQ/S_1_3",g_client[Attribute_Count]);	
						break;
				}
			}
			else if (signal_track == 2)
			{
			
				switch(signal_lampId)
				{
					case 1:
						Attribute_Count = S_TRACK2_ONE;
						Mqtt_Send(date,"$thing/up/property/OLMJUNLIUQ/S_2_1",g_client[Attribute_Count]);	
						break;
					case 2:
						Attribute_Count = S_TRACK2_TWO;
						Mqtt_Send(date,"$thing/up/property/OLMJUNLIUQ/S_2_2",g_client[Attribute_Count]);	
						break;
					case 3:
						Attribute_Count = S_TRACK2_THREE;
						Mqtt_Send(date,"$thing/up/property/OLMJUNLIUQ/S_2_3",g_client[Attribute_Count]);	
						break;
				}
			}
			
		}
		
		//按ID存入对应电流、电压、告警信息
		
		chr = strstr(date, "\"I\":");
		if (NULL != chr)
		{
			sscanf(chr, "\"I\":%f", &Attribute_I[Attribute_Count]);
		}

		chr = strstr(date, "\"U\":");
		if (NULL != chr)
		{
			sscanf(chr, "\"U\":%f", &Attribute_U[Attribute_Count]);
		}

		//取告警值
		chr = strstr(date, "\"Warn\":");
		if (NULL != chr)
		{
			sscanf(chr, "\"Warn\":%d", &Attribute_Warn[Attribute_Count]);
			printf("\"Warn\":%d", Attribute_Warn[Attribute_Count]);
			if (Attribute_Warn[Attribute_Count] < 4)
			{
				
				Attribute_Mark[Attribute_Count] = 1;
				
			}
			else
			{
				Attribute_Mark[Attribute_Count] = 0;
			}
		}

		
		//故障弹窗
		if (Attribute_Warn[Attribute_Count] == 3)
		{
			SetCtrlAttribute(panelHandle, PANEL_LED_10, ATTR_LABEL_VISIBLE, 1);
		}

		
		
	}
	//获取信号机ID
	if ((Attribute_Mark[X_TRACK_ONE] || Attribute_Mark[X_TRACK_TWO] || Attribute_Mark[X_TRACK_FOUR] || Attribute_Mark[X_TRACK_FIVE]) == 0)
	{
		Attribute_Mark[X_TRACK_THREE] = 1;
	}
	else
	{
		Attribute_Mark[X_TRACK_THREE] = 0;
	}
	if ((Attribute_Mark[S_TRACK1_ONE] || Attribute_Mark[S_TRACK1_THREE]) == 0)
	{
		Attribute_Mark[S_TRACK1_TWO]  = 1;
	}
	else
	{
		Attribute_Mark[S_TRACK1_TWO] = 0;
	}
	
	if ((Attribute_Mark[S_TRACK2_ONE] || Attribute_Mark[S_TRACK2_THREE]) == 0)
	{
		Attribute_Mark[S_TRACK2_TWO]  = 1;
	}
	else
	{
		Attribute_Mark[S_TRACK2_TWO] = 0;
	}
	
	if (Attribute_Mark[D_TRACK1_ONE] == 0)
	{
		Attribute_Mark[D_TRACK1_TWO]  = 1;
	}
	else
	{
		Attribute_Mark[D_TRACK1_TWO] = 0;
	}
	
	MQTTAsync_freeMessage(&message);
	MQTTAsync_free(topicName);
	
	//信号机有亮灯标志的灯亮
	LedOn();
	//printf(" %s\n",date);
	return 1;
}

//mqtt订阅函数
int  Mqtt_subscription (void)
{
	MQTTAsync_responseOptions opts = MQTTAsync_responseOptions_initializer;
	int rc;
	
	opts.onSuccess = onSubscribe;
	opts.onFailure = onSubscribeFailure;
	opts.context = g_client[0];
	
	//MQTTAsync_subscribe函数返回值 !=0打印
	if ((rc = MQTTAsync_subscribe(g_client[0], RCVTOPIC, QOS, &opts)) != MQTTASYNC_SUCCESS)
	{
		printf("Failed to start subscribe, return code %d\n", rc);
	}
		
	return 0;
}


//发布函数		
/*参数：
*      Content：发布内容
*      Topic：  发布主题 
	   Client	发布客户端(g_client[])
*/
int Mqtt_Send(char *Content,char *Topic, MQTTAsync Client)		
{
	int rc;
	MQTTAsync_responseOptions pub_opts = MQTTAsync_responseOptions_initializer;
	MQTTAsync_message pubmsg = MQTTAsync_message_initializer;

	pub_opts.onSuccess = onSend;
	pub_opts.onFailure = onSendFailure;
	pub_opts.context = Client;							


	pubmsg.payload = Content;
	pubmsg.payloadlen = (int)strlen(Content);
	pubmsg.qos = QOS;
	pubmsg.retained = 1;

	if ((rc = MQTTAsync_sendMessage(Client, Topic, &pubmsg, &pub_opts)) != MQTTASYNC_SUCCESS)
	{
		printf("Failed to start sendMessage, return code %d\n", rc);
		exit(EXIT_FAILURE);
	}

	return 0;
}


//画轨道斜线
void DrawLine (void)
{
	//定位亮红灯、蓝灯
	Attribute_Mark[X_TRACK_THREE] = 1;
	Attribute_Mark[S_TRACK1_TWO]  = 1;
	Attribute_Mark[S_TRACK2_TWO]  = 1;
	Attribute_Mark[D_TRACK1_TWO]  = 1;
	
	SetCtrlVal (panelHandle, PANEL_LED_3, Attribute_Mark[X_TRACK_THREE]);
	SetCtrlVal (panelHandle, PANEL_LED_7, Attribute_Mark[S_TRACK1_TWO]);
	SetCtrlVal (panelHandle, PANEL_LED_10, Attribute_Mark[S_TRACK2_TWO]);
	SetCtrlVal (panelHandle, PANEL_LED_13, Attribute_Mark[D_TRACK1_TWO]);
	
	//隐藏告警
	SetCtrlAttribute(panelHandle, PANEL_LED_4, ATTR_LABEL_VISIBLE, 0);
	SetCtrlAttribute(panelHandle, PANEL_LED_3, ATTR_LABEL_VISIBLE, 0);
	SetCtrlAttribute(panelHandle, PANEL_LED_9, ATTR_LABEL_VISIBLE, 0);
	SetCtrlAttribute(panelHandle, PANEL_LED_10, ATTR_LABEL_VISIBLE, 0);
	
	SetCtrlAttribute (panelHandle, PANEL_CANVAS_3, ATTR_PEN_WIDTH, 9);
	SetCtrlAttribute (panelHandle, PANEL_CANVAS_3, ATTR_PEN_COLOR, 0xFFFFFFL);

	int x, y;
	GetCtrlAttribute (panelHandle, PANEL_CANVAS_3, ATTR_WIDTH, &x);							//取PANEL_CANVA的SATTR_WIDTH（赋值给x）
	GetCtrlAttribute (panelHandle, PANEL_CANVAS_3, ATTR_HEIGHT, &y);						////取PANEL_CANVA的ATTR_HEIGHT（赋值给y）原点

	CanvasDrawLine (panelHandle, PANEL_CANVAS_3, MakePoint (0, y), MakePoint (x, 0)); 		//（MakePoint (0, 2)第一个点，MakePoint (x, 2)第二个点）

}



//设备连接腾讯云函数
static void tencentmqtt(char *pProductID,char * pDeviceName,char *pDeviceSecret,MQTTAsync *pClient)
{
	char ADDRESS[256];
	char CLIENTID[256];
	char USERNAME[256];
	char PASSWORD[256];

	// 腾讯云三元素转换链接信息
	tencentcloud(pProductID, pDeviceName, pDeviceSecret, ADDRESS, CLIENTID, USERNAME, PASSWORD);

	int rc;
	MQTTAsync_connectOptions conn_opts = MQTTAsync_connectOptions_initializer;
	if ((rc = MQTTAsync_create(pClient, ADDRESS, CLIENTID, MQTTCLIENT_PERSISTENCE_NONE, NULL)) != MQTTASYNC_SUCCESS)
	{
		printf("Failed to create client object, return code %d\n", rc);
		exit(EXIT_FAILURE);
	}

	if ((rc = MQTTAsync_setCallbacks(*pClient, 0, connlost, messageArrived, NULL)) != MQTTASYNC_SUCCESS)
	{
		printf("Failed to set callback, return code %d\n", rc);
		exit(EXIT_FAILURE);
	}

	conn_opts.keepAliveInterval = 30;
	conn_opts.cleansession = 0;
	conn_opts.onSuccess = onConnect;
	conn_opts.onFailure = onConnectFailure;
	conn_opts.context = *pClient;
	conn_opts.username = USERNAME;
	conn_opts.password = PASSWORD;

	if ((rc = MQTTAsync_connect(*pClient, &conn_opts)) != MQTTASYNC_SUCCESS)
	{
		printf("Failed to start connect, return code %d\n", rc);
		exit(EXIT_FAILURE);
	}
}


void tencentDisconnect(void)
{
	//关闭&释放连接量
	for (int i = 0; i < 16; i++)
	{
		if (g_client[i] != NULL)
		{
			int rc;
			MQTTAsync_disconnectOptions opts = MQTTAsync_disconnectOptions_initializer;

			opts.onSuccess = onDisconnect;
			opts.onFailure = onDisconnectFailure;
			opts.context = g_client[i];

			if ((rc = MQTTAsync_disconnect(g_client[i], &opts)) != MQTTASYNC_SUCCESS)
			{
				printf("Failed to start disconnect, return code %d\n", rc);
				exit(EXIT_FAILURE);
			}

			MQTTAsync_destroy(&g_client[i]);
			g_client[i] = NULL;
		}
	}
}


//子设备连接
void tencentConnect(void)
{
	//初始化连接量
	for (int i = 0; i < 16; i++)
	{
		g_client[i] = NULL;
	}
	//主设备
	tencentmqtt("8G6SX32L49","PC","XK0+ec9ch6KBMwiPQAro+g==",&g_client[0]);

	//下行信号机1-5
	tencentmqtt(ProductID,"X_0_1","8NrcGwTAhlbvGSm+tg1jhQ==",&g_client[X_TRACK_ONE]);
	tencentmqtt(ProductID,"X_0_2","3PpV4IxC35n1jzifjMtJQA==",&g_client[X_TRACK_TWO]);
	tencentmqtt(ProductID,"X_0_3","nfvpmtkBMwZfNCZvx8GiiA==",&g_client[X_TRACK_THREE]);
	tencentmqtt(ProductID,"X_0_4","UlzrHR9FYF2iTWFW8VHVYA==",&g_client[X_TRACK_FOUR]);
	tencentmqtt(ProductID,"X_0_5","Zn6Pzzb2ktyHHCCLn1cLZg==",&g_client[X_TRACK_FIVE]);

	//S1信号机1-3
	tencentmqtt(ProductID,"S_1_1","VIK6MZvEL3kvcxoozp3CSA==",&g_client[S_TRACK1_ONE]);
	tencentmqtt(ProductID,"S_1_2","Y1yFBaN1EzqWGvA5ST/gcA==",&g_client[S_TRACK1_TWO]);
	tencentmqtt(ProductID,"S_1_3","+ieJoXF76e4VW12i/ETU/g==",&g_client[S_TRACK1_THREE]);

	//S2信号机1-3
	tencentmqtt(ProductID,"S_2_1","UIbi8BxLQUtpUdSYdgh/kQ==",&g_client[S_TRACK2_ONE]);
	tencentmqtt(ProductID,"S_2_2","C9AyqE2R4o3+E84TbrpuJA==",&g_client[S_TRACK2_TWO]);
	tencentmqtt(ProductID,"S_2_3","uQJ6T2GUhExcIEwhaN+I4w==",&g_client[S_TRACK2_THREE]);
}

