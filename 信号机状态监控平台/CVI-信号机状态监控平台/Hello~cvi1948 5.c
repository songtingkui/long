#include <windows.h>
#include <ansi_c.h>
#include "animate.h"
#include <cvirte.h>		
#include <userint.h>
#include "Hello.h"
#include "MQTTAsync.h"
#include "tencentcloud.h"




static int panelHandle;


#define ProductID		"OD4TDTVVHH"
#define DeviceName		"teleseme2"
#define DeviceSecret	"5m/ngRvsEHDZR0kS9A0DTw=="

#define QOS         1
#define TIMEOUT     10000L

char ADDRESS[256];
char CLIENTID[256];
char USERNAME[256];
char PASSWORD[256];


//回调打印------断开连接
void onDisconnect(void* context, MQTTAsync_successData* response)
{
	printf("Successful disconnection\n");
}

void onDisconnectFailure(void* context, MQTTAsync_failureData* response)
{
	printf("Disconnect failed\n");
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
	MQTTAsync client = (MQTTAsync)context;
	MQTTAsync_connectOptions conn_opts = MQTTAsync_connectOptions_initializer;
	int rc;

	printf("\nConnection lost\n");
	printf("     cause: %s\n", cause);

	printf("Reconnecting\n");
	conn_opts.keepAliveInterval = 120;
	conn_opts.cleansession = 1;
	conn_opts.onSuccess = onConnect;
	conn_opts.onFailure = onConnectFailure;
	conn_opts.context = client;
	conn_opts.username = USERNAME;
	conn_opts.password = PASSWORD;
	if ((rc = MQTTAsync_connect(client, &conn_opts)) != MQTTASYNC_SUCCESS)
	{
		printf("Failed to start connect, return code %d\n", rc);
 	}
}
char Date[256];
//接受到
int messageArrived(void* context, char* topicName, int topicLen, MQTTAsync_message* message)
{
	char date[256];
	uint32_t Date_U;
	uint32_t Date_I;
	uint32_t Date_Warn;
	char Date_ID;
	
 	printf("Message arrived\n");
    printf("     topic: %s\n", topicName);
	
    printf("   message: %.*s\n", message->payloadlen, (char*)message->payload);
	SetCtrlVal (panelHandle, PANEL_STRING_4, (char*)message->payload);
	
	GetCtrlVal (panelHandle, PANEL_STRING_4, date);
	
//	sscanf(date,"\"method\":\"report\",\"params\":{\"I\":%d,\"U\":%d,\"Warn\":%d,\"ID\":%s}",&Date_I,&Date_U,&Date_Warn,&Date_ID);
	sscanf(date,"\"method\":\"report\",\"params\":{\"I\":%d,\"U\":%d,\"Warn\":%d,\"ID\":%s}",&Date_I,&Date_U,&Date_Warn,&Date_ID);
	
//	{ "method":"report", "params":{"V":12,"I":81,"Warn":0,"ID":"D1-1-2"} }
    MQTTAsync_freeMessage(&message);
    MQTTAsync_free(topicName);
	return 1;
}

void onSubscribe(void* context, MQTTAsync_successData* response)
{
	printf("Subscribe succeeded\n");
}

void onSubscribeFailure(void* context, MQTTAsync_failureData* response)
{
	printf("Subscribe failed, rc %d\n", response->code);
}


MQTTAsync client;

int main (int argc, char *argv[])
{
	if (InitCVIRTE (0, argv, 0) == 0)
		return -1;	/* out of memory */
	
	if ((panelHandle = LoadPanel (0, "Hello.uir", PANEL)) < 0)
		return -1;
	DisplayPanel (panelHandle);
	
	// 腾讯云三元素转换链接信息
	tencentcloud(ProductID, DeviceName, DeviceSecret, ADDRESS, CLIENTID, USERNAME, PASSWORD);

	MQTTAsync_connectOptions conn_opts = MQTTAsync_connectOptions_initializer;
	int rc;

	if ((rc = MQTTAsync_create(&client, ADDRESS, CLIENTID, MQTTCLIENT_PERSISTENCE_NONE, NULL)) != MQTTASYNC_SUCCESS)
	{
		printf("Failed to create client object, return code %d\n", rc);
		rc = EXIT_FAILURE;
		goto exit;
	}

	if ((rc = MQTTAsync_setCallbacks(client, client, connlost, messageArrived, NULL)) != MQTTASYNC_SUCCESS)
	{
		printf("Failed to set callback, return code %d\n", rc);
		rc = EXIT_FAILURE;
		goto destroy_exit;
	}

	conn_opts.keepAliveInterval = 120;
	conn_opts.cleansession = 1;
	conn_opts.onSuccess = onConnect;
	conn_opts.onFailure = onConnectFailure;
	conn_opts.context = client;
	conn_opts.username = USERNAME;
	conn_opts.password = PASSWORD;
	
	if ((rc = MQTTAsync_connect(client, &conn_opts)) != MQTTASYNC_SUCCESS)
	{
		printf("Failed to start connect, return code %d\n", rc);
		rc = EXIT_FAILURE;
		goto destroy_exit;
	}

	RunUserInterface ();
	
destroy_exit:	
	MQTTAsync_destroy(&client);
exit:
	DiscardPanel (panelHandle);
		
	return 0;
}
	
//退出函数
int CVICALLBACK qq (int panel, int event, void *callbackData,
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

//发布函数
int CVICALLBACK MqttSend (int panel, int control, int event,
						  void *callbackData, int eventData1, int eventData2)
{
	int rc;
	char PAYLOAD[1024];
	char TOPIC[1024];
	
	//https://cloud.tencent.com/document/product/1081/34916
	switch (event)
	{
		case EVENT_COMMIT:
			MQTTAsync_responseOptions pub_opts = MQTTAsync_responseOptions_initializer;
			MQTTAsync_message pubmsg = MQTTAsync_message_initializer;
				
			pub_opts.onSuccess = onSend;
			pub_opts.onFailure = onSendFailure;
			pub_opts.context = client;

			GetCtrlVal (panelHandle, PANEL_STRING, TOPIC);
			GetCtrlVal (panelHandle, PANEL_STRING_2, PAYLOAD);
			
			pubmsg.payload = PAYLOAD;
			pubmsg.payloadlen = (int)strlen(PAYLOAD);
			pubmsg.qos = QOS;
			pubmsg.retained = 0;
	
			if ((rc = MQTTAsync_sendMessage(client, TOPIC, &pubmsg, &pub_opts)) != MQTTASYNC_SUCCESS)
			{
				printf("Failed to start sendMessage, return code %d\n", rc);
				exit(EXIT_FAILURE);
			}
			break;
	}
	return 0;
}

//订阅-------接收函数
int CVICALLBACK MqttRecv (int panel, int control, int event,
						  void *callbackData, int eventData1, int eventData2)
{
	char TOPIC[1024];

	switch (event)
	{
		case EVENT_COMMIT:
			MQTTAsync_responseOptions opts = MQTTAsync_responseOptions_initializer;
			int rc;

			GetCtrlVal (panelHandle, PANEL_STRING_3, TOPIC);
			
			opts.onSuccess = onSubscribe;
			opts.onFailure = onSubscribeFailure;
			opts.context = client;

			//MQTTAsync_subscribe函数返回值 !=0打印
			
			if ((rc = MQTTAsync_subscribe(client, TOPIC, QOS, &opts)) != MQTTASYNC_SUCCESS)
			{
				printf("Failed to start subscribe, return code %d\n", rc);
				
			}
			break;
	}
	return 0;
}

//划线函数
int CVICALLBACK DrawLine (int panel, int control, int event,
						  void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_COMMIT:
			
			int x, y;
			//SetCtrlAttribute (panelHandle, PANEL_CANVAS, ATTR_HEIGHT, 3);
			SetCtrlAttribute (panelHandle, PANEL_CANVAS, ATTR_PEN_WIDTH, 3);
			
			
			GetCtrlAttribute (panelHandle, PANEL_CANVAS, ATTR_WIDTH, &x);		//取PANEL_CANVA的SATTR_WIDTH（赋值给x）
			GetCtrlAttribute (panelHandle, PANEL_CANVAS, ATTR_HEIGHT, &y);		////取PANEL_CANVA的ATTR_HEIGHT（赋值给y）原点

			//CanvasDrawLine (panelHandle, PANEL_CANVAS, MakePoint (0, 2), MakePoint (x, 2));
			
			CanvasDrawLine (panelHandle, PANEL_CANVAS, MakePoint (0, 2), MakePoint (x, 2));    //（MakePoint (0, 2)第一个点，MakePoint (x, 2)第二个点）
			/*SetCtrlAttribute (panelHandle, PANEL_CANVAS_2, ATTR_PEN_WIDTH, 3);
			
			GetCtrlAttribute (panelHandle, PANEL_CANVAS_2, ATTR_WIDTH, &x);
			GetCtrlAttribute (panelHandle, PANEL_CANVAS_2, ATTR_HEIGHT, &y);

			CanvasDrawLine (panelHandle, PANEL_CANVAS_2, MakePoint (0, 2), MakePoint (x, 2));*/
			break;
	}
	return 0;
}
