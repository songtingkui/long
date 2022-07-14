 /**************************************************************************/
/* LabWindows/CVI User Interface Resource (UIR) Include File              */
/*                                                                        */
/* WARNING: Do not add to, delete from, or otherwise modify the contents  */
/*          of this include file.                                         */
/**************************************************************************/


#ifdef __cplusplus
    extern "C" {
#endif

#define ProductID				"OLMJUNLIUQ"							//产品子设备ＩＤ，全部相同
#define RCVTOPIC       			"8G6SX32L49/PC/data"        		//只有主设备订阅 （唯一）
#define PRIMARY_SENDTOPIC		"$thing/up/property/8G6SX32L49/PC"	//不同设备不同（删除）

#define QOS             1
extern MQTTAsync g_client[32];
		

#define X_TRACK_ONE			4
#define X_TRACK_TWO			5
#define X_TRACK_THREE		6
#define X_TRACK_FOUR		7
#define X_TRACK_FIVE		8

#define S_TRACK1_ONE		9
#define S_TRACK1_TWO		10
#define S_TRACK1_THREE		11

#define S_TRACK2_ONE		12
#define S_TRACK2_TWO		13
#define S_TRACK2_THREE		14

#define D_TRACK1_ONE		15
#define D_TRACK1_TWO		16

#define CHANGE_X_MARK		1
#define CHANGE_S1_MARK		2
#define CHANGE_S2_MARK		3

#define CURRENT_MIN			0.2		//亮灯标志有效的 最小值

#define printf 				//		


extern int panelHandle;		
extern int panelHandle2;
extern int panelHandle3;
extern int panelHandle4;		

extern float 	Attribute_U[32];
extern float 	Attribute_I[32];
extern int 		Attribute_Warn[32];
extern int 		Attribute_Mark[32];

void tencentConnect(void);
void tencentDisconnect(void);

void LedOn(void);
int Mqtt_Send(char *Content,char *Topic, MQTTAsync Client);

int  Mqtt_subscription (void);
void DrawLine (void); 										//画轨道斜线

void onSubscribeFailure(void* context, MQTTAsync_failureData* response);
void onSubscribe(void* context, MQTTAsync_successData* response);
void onConnectFailure(void* context, MQTTAsync_failureData* response);
void onDisconnect(void* context, MQTTAsync_successData* response);
void onDisconnectFailure(void* context, MQTTAsync_failureData* response);
void onSend(void* context, MQTTAsync_successData* response);
void onSendFailure(void* context, MQTTAsync_failureData* response);
void onConnectFailure(void* context, MQTTAsync_failureData* response);
void onConnect(void* context, MQTTAsync_successData* response);
void connlost(void *context, char *cause);
int messageArrived(void* context, char* topicName, int topicLen, MQTTAsync_message* message);   //设备登陆函数
void tencentTransform(void);																	//子设备登陆
//void Mqtt_Sendmessage (char *pPAYLOAD,char *psendTopic,void *pclient);	//Mqtt发布消息函数
void  Mqtt_Sendmasage (void);
#ifdef __cplusplus
    }
#endif