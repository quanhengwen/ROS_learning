#include "ESP12S.h"
#include "string.h"
#include "usart.h"
#include "gui.h"
#include "rtc.h"
#include "lcd.h"
#include "MQTTPacket.h"
#include "transport.h"
#include "cJSON.h"
#include "DHT12.h"
#include <stdlib.h>
#include "PMS5003.h"

extern RTC_TimeTypeDef nTime;
extern RTC_DateTypeDef nDate;

__IO uint16_t Atcmd_tick=0;
__IO uint32_t ESP12_Tick=0;


//uint8_t teststatus=0;
char *topic="";//订阅主题

uint8_t SSID[20]="WIN4540";//WIFI;
uint8_t Password[20]="66666666";//wifi密码
uint8_t Gateway[16]="192.168.0.1";
uint8_t IP[16]="192.168.0.11";
uint8_t ESP12S_RevBuf[ESP12S_BUF_LEN];
uint8_t ESP12S_RevByte;
uint8_t ESP12S_RevFlag=0;

static uint8_t sendstr[70]="";
uint8_t WIFI_Status=1;
uint16_t Revcnt=0;

void ATCMD_IncTick()
{
    Atcmd_tick++;
//    MQTT_tick++;
    ESP12_Tick++;
//    if(MQTT_tick>100)
//    {
//        MQTT_RevFlag=1;
//        Revcnt=0;
//    }
}



void ESP12S_Init(UART_HandleTypeDef *huart)
{
    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_8, GPIO_PIN_RESET);
    Atcmd_tick=0;
    while(Atcmd_tick<200);
    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_8, GPIO_PIN_SET);
    Atcmd_tick=0;
    while(Atcmd_tick<200);
		Clr_RxBuf();
//	while(ConnectWiFi(huart)!=0);
//	while(TCP_UDP_Mode(huart)!=0);
//
//	while(Send_Data(huart,"123",0,3)!=0);
//	while(Send_Data(huart,"GET https://api.seniverse.com/v3/weather/now.json?key=nyldnfnczklzs&location=shijiazhuang&language=zh-Hans&unit=c\n\n",1,118)!=0);
//	while(Send_Data(huart,"123",2,3)!=0);
}



//判断str中是否包含substr,包含返回1  不包含返回0
uint8_t Hand(char* substr,uint16_t *index,uint16_t start_index)
{
    uint16_t i,flag=0;
    char *p;
    for(i=start_index; i<ESP12S_BUF_LEN; i++)
    {
        if(ESP12S_RevBuf[i]==*substr)
        {
            flag=1;
            p=substr;
            while(*p)
            {
                if(ESP12S_RevBuf[i]==*p)
                {
                    *p++;
                    i++;
                }
                else
                {
                    flag=0;
                    break;
                }
            }
            if(flag==1)
            {
                *index = i;
                break;
            }
        }
    }
    return flag;
}
//清空接收缓冲区
void Clr_RxBuf()
{
    for(uint16_t i=0; i<ESP12S_BUF_LEN; i++)
    {
        ESP12S_RevBuf[i]=0;
    }
    Revcnt=0;
}

//------------------发送AT指令-----------------
//参数1：huart 串口号
//参数2：cmd AT指令
//参数3：timeout 单次发送的超时时间
//参数4：res 要判断的返回结果
//参数5：count 尝试次数
//返回值：ATCMD_REVOK 发送且收到回复  ATCMD_TIMEOUT 超时
ATCMD_StatusTypeDef AT_CMD(UART_HandleTypeDef *huart,uint8_t* cmd,uint16_t timeout,const char* res,uint8_t count)
{
    static ATCMD_StatusTypeDef atcmd_status=ATCMD_START;
    static uint8_t cnt=1;
    uint16_t temp;
    switch(atcmd_status)
    {
    case ATCMD_START:
        cnt = count;
        atcmd_status=ATCMD_SEND;
        break;
    case ATCMD_SEND:
        Clr_RxBuf();
        //HAL_UART_Receive_IT(&huart1, ESP12S_RevBuf, 5); //串口1DMA接收数据
        HAL_UART_Transmit_IT(huart,cmd,strlen((const char*)cmd));
        atcmd_status=ATCMD_WAIT_REV;
        Atcmd_tick=0;
        break;
    case ATCMD_WAIT_REV:
        if(Atcmd_tick<timeout)
        {
            if(Hand((char*)res,&temp,0))//
            {
                atcmd_status=ATCMD_REVOK;
            }
        }
        else
        {
            if(cnt>0)//再次发送
                atcmd_status=ATCMD_SEND;
            else
                atcmd_status=ATCMD_TIMEOUT;
            cnt--;
        }
        break;
    case ATCMD_REVOK:
    case ATCMD_TIMEOUT:
        atcmd_status=ATCMD_START;
    default:
        break;
    }
    return atcmd_status;
}



//------------重新设置SSID并连接WIFI-------------
//连接成功返回0  返回1表示错误  返回2正在连接
uint8_t ReConnectWiFi(UART_HandleTypeDef *huart)
{
    static uint8_t status=0;//
    static ATCMD_StatusTypeDef res;
    //static uint8_t tempstr[70]="";

    switch(status)
    {
    case 0:
        res = AT_CMD(huart,(uint8_t*)"AT+CWMODE_DEF=1\r\n",1000,"OK",3);//设置为STA模式
        if(res==ATCMD_REVOK)
            status=1;
        else if(res==ATCMD_TIMEOUT)
        {
            status=0;
            return 1;
        }
        break;
    case 1:
        sendstr[0]=0;
        strcat((char*)sendstr,"AT+CWJAP_DEF=\"");
        strcat((char*)sendstr,(const char*)SSID);
        strcat((char*)sendstr,"\",\"");
        strcat((char*)sendstr,(const char*)Password);
        strcat((char*)sendstr,"\"\r\n");
        res = AT_CMD(huart,sendstr,1000,"OK",3);//设置SSID和密码
        if(res==ATCMD_REVOK)
            status=2;
        else if(res==ATCMD_TIMEOUT)
        {
            status=1;
            return 1;
        }
        break;
    case 2://设置静态IP
//			strcat((char*)tempstr,"AT+CIPSTA_DEF=\"");
//			strcat((char*)tempstr,(const char*)IP);
//			strcat((char*)tempstr,"\",\"");
//			strcat((char*)tempstr,(const char*)Gateway);
//			strcat((char*)tempstr,"\",255.255.255.0\"");
//			strcat((char*)tempstr,"\r\n");
//			res = AT_CMD(huart,tempstr,1000,"OK",3);
        res = AT_CMD(huart,"AT+CWDHCP_DEF=1,1\r\n",1000,"OK",3);//开起DHCP
        if(res==ATCMD_REVOK)
            status=3;
        else if(res==ATCMD_TIMEOUT)
        {
            status=2;
            return 1;
        }
        break;
    case 3:
        res = AT_CMD(huart,"ATE0\r\n",1000,"OK",3);//关闭回显
        if(res==ATCMD_REVOK)
            status=4;
        else if(res==ATCMD_TIMEOUT)
        {
            status=3;
            return 1;
        }
        break;
    case 4:
        status=0;
        return 0;
    default:
        break;
    }
    return 2;
}



//建立TCP连接
uint8_t TCP_Mode(UART_HandleTypeDef *huart)
{
    static uint8_t status=0;//
    static ATCMD_StatusTypeDef res;

    switch(status)
    {
    case 0:
        res = AT_CMD(huart,(uint8_t*)"AT+CIPMUX=0\r\n",1000,"OK",3);//单连接
        if(res==ATCMD_REVOK)
            status=1;
        else if(res==ATCMD_TIMEOUT)
        {
            status=0;
            return 1;
        }
        break;
    case 1:
        res = AT_CMD(huart,(uint8_t*)"AT+CIPSTART=\"TCP\",\"ProductKey.iot-as-mqtt.cn-shanghai.aliyuncs.com\",1883\r\n",1000,"OK",3);//ProductKey换成自己的
        //res = AT_CMD(huart,(uint8_t*)"AT+CIPSTART=\"TCP\",\"192.168.137.1\",1883\r\n",1000,"OK",3);
        if(res==ATCMD_REVOK)
            status=2;
        else if(res==ATCMD_TIMEOUT)
        {
            status=1;
            return 1;
        }
        break;
    case 2:
        res = AT_CMD(huart,(uint8_t*)"AT+CIPMODE=1\r\n",1000,"OK",3);//透传模式
        if(res==ATCMD_REVOK)
            status=3;
        else if(res==ATCMD_TIMEOUT)
        {
            status=2;
            return 1;
        }
        break;
    case 3:			//准备发送数据 透传
        res = AT_CMD(huart,"AT+CIPSEND\r\n",1000,">",3);
        if(res==ATCMD_REVOK)
            status=4;
        else if(res==ATCMD_TIMEOUT)
        {
            status=3;
            return 1;
        }
        break;
    case 4:
        status=0;
        return 0;
    default:
        break;
    }
    return 2;
}
unsigned char buf[200];

void mqtt_connect(UART_HandleTypeDef *huart)
{
    int32_t len;
//		int msgid = 1;
//		int req_qos = 0;
	
    MQTTPacket_connectData data = MQTTPacket_connectData_initializer;//配置部分可变头部的值
    
//    MQTTString topicString = MQTTString_initializer;
    int buflen = sizeof(buf);
		memset(buf,0,buflen);
    data.clientID.cstring = "xxx|securemode=3,signmethod=hmacsha1|";//客户端标识，用于区分每个客户端xxx为自定义，后面为固定格式
    data.keepAliveInterval = 120;//保活计时器，定义了服务器收到客户端消息的最大时间间隔
    data.cleansession = 1;//该标志置1服务器必须丢弃之前保持的客户端的信息，将该连接视为“不存在”
    data.username.cstring = "";//用户名 DeviceName&ProductKey
    data.password.cstring = "";//密码，工具生成
    len = MQTTSerialize_connect(buf, buflen, &data); /*1 构造连接报文*/

    transport_sendPacketBuffer(huart,buf, len);//发送连接请求
    {
        unsigned char sessionPresent, connack_rc;
        do
        {
            while(MQTTPacket_read(buf, buflen, transport_getdata) != CONNACK)//对接收到的报文进行解析
            {
                ;
            }
        }
        while(MQTTDeserialize_connack(&sessionPresent, &connack_rc, buf, buflen) != 1 || connack_rc != 0);
    }
}
int mqtt_publish(UART_HandleTypeDef *huart,char *pTopic,char *pMessage)
{
		static uint8_t err_cnt=0;
    int32_t len;
    MQTTString topicString = MQTTString_initializer;
    int msglen = strlen(pMessage);//计算发布消息的长度
    int buflen = sizeof(buf);

		if (MQTTPacket_read(buf, buflen, transport_getdata) == PUBREC)//接收到发布信息的回复
		{
				unsigned char packettype = 0;
				unsigned char dup_ack = 0;
				unsigned short packetid = 0;

				MQTTDeserialize_ack(&packettype,&dup_ack,&packetid,buf,buflen);
				err_cnt=0;
		}
		else//没接收到回复
		{
				err_cnt++;
				if(err_cnt>3)//连续三次没收到回复  重新初始化WIFI模块
				{
					err_cnt=0;
					ESP12S_Init(huart);
					WIFI_Status=0;
				}
		}
		Clr_RxBuf();
    memset(buf,0,buflen);
    topicString.cstring = pTopic;//"设备topic列表中的第一条";
    len = MQTTSerialize_publish(buf, buflen, 0, 2, 0, 0, topicString, (unsigned char*)pMessage, msglen); /*2 构造发布消息的报文*/

    transport_sendPacketBuffer(huart,buf,len);//发送消息
		free(pMessage);
    return 0;
}

void ESP12_Task(UART_HandleTypeDef *huart)
{
//    uint8_t res=0;

    switch(WIFI_Status)
    {
    case 0://重新设置并连接WIFI
        if(ReConnectWiFi(huart)==0)
            WIFI_Status=1;
        break;
    case 1://连接tcp服务器
        if(TCP_Mode(huart)==0)
        {
            WIFI_Status=2;
            ESP12_Tick=0;
            Clr_RxBuf();
        }
        break;
    case 2://连接MQTT服务器
        mqtt_connect(huart);
				WIFI_Status=3;
				ESP12_Tick = MQTT_INTERVAL_TIME;
        break;
    case 3://发送MQTT数据
        if(ESP12_Tick>=MQTT_INTERVAL_TIME)
        { 
						cJSON * pJsonRoot = NULL;
						pJsonRoot = cJSON_CreateObject();//
						if ( NULL == pJsonRoot )
						{
								break ;
						}
						cJSON_AddStringToObject(pJsonRoot, "id", "rty");//
						cJSON_AddStringToObject(pJsonRoot, "method", "thing.event.property.post");//
						cJSON * pJsonChild = cJSON_CreateObject();//
						if ( NULL == pJsonChild )
						{
								cJSON_Delete(pJsonChild);
								break ;
						}
						cJSON_AddNumberToObject(pJsonChild, "pm2_5", PMS5003_Data.PM2_5);
						#ifdef PMS5003_ST
							cJSON_AddNumberToObject(pJsonChild, "humi", PMS5003_Data.Humidity/10);
							cJSON_AddNumberToObject(pJsonChild, "temp", PMS5003_Data.Temperature/10.0);
						#else
							cJSON_AddNumberToObject(pJsonChild, "humi", DHT12_Humidity/10);
							cJSON_AddNumberToObject(pJsonChild, "temp", DHT12_Temperature/10.0);
						#endif
						
						cJSON_AddItemToObject(pJsonRoot, "params", pJsonChild);//
	
						char* lpJsonStr = cJSON_Print(pJsonRoot);
						cJSON_Delete(pJsonRoot);//
						if(lpJsonStr==NULL)
						{
							break ;
						}
						mqtt_publish(huart,topic,lpJsonStr);
            free(lpJsonStr);
						ESP12_Tick=0;
        }
        break;
    default:
        break;
    }
}
