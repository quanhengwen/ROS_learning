#include "stm32f0xx_hal.h"
#include "usbd_cdc_if.h"
#include "usb_task.h"
#include "rtc.h"
#include "PMS5003.h"
#include "DHT12.h"
#include "ESP12S.h"
#include "usart.h"

extern USBD_HandleTypeDef hUsbDeviceFS;
extern uint8_t UserRxBufferFS[APP_RX_DATA_SIZE];
extern uint8_t UserTxBufferFS[APP_TX_DATA_SIZE];

extern PMS5003_t PMS5003_Data;
extern uint8_t SSID[20];//"lelele";
extern uint8_t Password[20];//"15690323041YangLe";
extern uint8_t WIFI_Status;
RTC_DateTypeDef setDate;
RTC_TimeTypeDef setTime;
								
/* USB_SendMess function */
void USB_SendMess(void)
{

    uint32_t buffsize;
    if(UserTxBufPtrOut != UserTxBufPtrIn)
    {
        if(UserTxBufPtrOut > UserTxBufPtrIn) /* Rollback */
        {
            buffsize= UserTxBufPtrIn;
        }
        else 
				{
            buffsize = UserTxBufPtrIn - UserTxBufPtrOut;
        }
				if(UserRxBufferFS[UserTxBufPtrOut]==0x5A && UserRxBufferFS[UserTxBufPtrOut+1]==0xA5)//判断帧头
				{
					uint8_t sum=0;
					for(uint8_t i=0;i<buffsize-1;i++)
					{
						sum += UserRxBufferFS[UserTxBufPtrOut+i];
					}
					if(buffsize==(UserRxBufferFS[UserTxBufPtrOut+3]+5) && sum ==UserRxBufferFS[UserTxBufPtrOut+buffsize-1])//判断帧长度 与校验和
					{
						switch(UserRxBufferFS[UserTxBufPtrOut+2])//判断帧类型
						{
							case 0x01://设置系统时间
								setDate.Year=UserRxBufferFS[UserTxBufPtrOut+4];
								setDate.Month=UserRxBufferFS[UserTxBufPtrOut+5];
								setDate.Date=UserRxBufferFS[UserTxBufPtrOut+6];
								setTime.Hours=UserRxBufferFS[UserTxBufPtrOut+7];
								setTime.Minutes=UserRxBufferFS[UserTxBufPtrOut+8];
								setTime.Seconds=UserRxBufferFS[UserTxBufPtrOut+9];
								SetDateTime(&setDate,&setTime);
								UserTxBufferFS[0]=0x5A;
								UserTxBufferFS[1]=0xA5;
								UserTxBufferFS[2]=0x02;
								UserTxBufferFS[3]=0x01;
								UserTxBufferFS[4]=0x01;
								UserTxBufferFS[5]=0x03;
								CDC_Transmit_FS(UserTxBufferFS,6); 
								break;
							case 0x03://读取环境数据
								memset(UserTxBufferFS,0,41);
								UserTxBufferFS[0]=0x5A;
								UserTxBufferFS[1]=0xA5;
								UserTxBufferFS[2]=0x04;
								UserTxBufferFS[3]=0x24;
								UserTxBufferFS[4]=PMS5003_Data.PM1_0>>8;
								UserTxBufferFS[5]=PMS5003_Data.PM1_0;
								UserTxBufferFS[6]=PMS5003_Data.PM2_5>>8;
								UserTxBufferFS[7]=PMS5003_Data.PM2_5;
								UserTxBufferFS[8]=PMS5003_Data.PM10>>8;
								UserTxBufferFS[9]=PMS5003_Data.PM10;
								#ifdef PMS5003_ST
									UserTxBufferFS[10] = PMS5003_Data.Temperature>>8;
									UserTxBufferFS[11] = PMS5003_Data.Temperature;
									UserTxBufferFS[12] = PMS5003_Data.Humidity>>8;
									UserTxBufferFS[13] = PMS5003_Data.Humidity;
									UserTxBufferFS[14] = PMS5003_Data.HCHO>>8;
									UserTxBufferFS[15] = PMS5003_Data.HCHO;
								#else
									UserTxBufferFS[10] = DHT12_Temperature>>8;
									UserTxBufferFS[11] = DHT12_Temperature;
									UserTxBufferFS[12] = DHT12_Humidity>>8;
									UserTxBufferFS[13] = DHT12_Humidity;
								#endif
								UserTxBufferFS[40]=0;
								for(uint8_t i=0;i<40;i++)
								{
									UserTxBufferFS[40]+=UserTxBufferFS[i];
								}
								CDC_Transmit_FS(UserTxBufferFS,41); 
								break;
							case 0x05://设置SSID和Password
								memset(SSID,0,sizeof(SSID));
								memset(Password,0,sizeof(Password));
								{
									uint8_t i=0,j=0;
									for(i=4;i<24;i++,j++)
									{
										SSID[j]=UserRxBufferFS[UserTxBufPtrOut+i];
										if(UserRxBufferFS[UserTxBufPtrOut+i]==0x00)
										{
											break;
										}
									}
									j=0;
									for(i++;i<44;i++,j++)
									{
										Password[j]=UserRxBufferFS[UserTxBufPtrOut+i];
										if(UserRxBufferFS[UserTxBufPtrOut+i]==0x00)
										{
											break;
										}
									}
								}
								ESP12S_Init(&huart1);
								WIFI_Status = 0;			
								UserTxBufferFS[0]=0x5A;
								UserTxBufferFS[1]=0xA5;
								UserTxBufferFS[2]=0x06;
								UserTxBufferFS[3]=0x01;
								UserTxBufferFS[4]=0x05;
								UserTxBufferFS[5]=0x0B;
								CDC_Transmit_FS(UserTxBufferFS,6); 
								break;
							default:
								break;
								
						}
					}
				}
				UserTxBufPtrOut += buffsize; 
				USBD_CDC_SetRxBuffer(&hUsbDeviceFS, &UserRxBufferFS[UserTxBufPtrOut]);
				USBD_CDC_ReceivePacket(&hUsbDeviceFS);
    }
}
