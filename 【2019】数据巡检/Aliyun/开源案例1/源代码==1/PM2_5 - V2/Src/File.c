#include "stm32f0xx_hal.h"
#include "fatfs.h"
#include "File.h"
#include "rtc.h"

extern uint8_t SSID[20];
extern uint8_t Password[20];
extern uint8_t DstIP[16];
extern uint8_t DstPort[10];
extern RTC_DateTypeDef nDate;
extern uint8_t databuf[20];

__IO uint16_t  WriteFile_Tickms=0,WriteFile_Tick_S;

void File_IncTick()
{
	WriteFile_Tickms++;
	if(WriteFile_Tickms>1000)
	{
		WriteFile_Tickms=0;
		WriteFile_Tick_S++;
	}
}

FIL file1,wfile;
FRESULT res;
UINT br,bw;
uint8_t writefilename[12];

void ReadParam()
{
	uint8_t buf[80];
	uint8_t i=0,j=0;
	res = f_open(&file1,"wifi.txt",FA_OPEN_EXISTING|FA_READ);
	res = f_read(&file1,buf,80,&br);
	if(res!=FR_OK)return;
	//WIFI名称
	for(i=0;j<20;i++,j++)
	{
		if(buf[i]==';')
		{
			SSID[j]=0;
			i++;
			break;
		}
		else
		{
			SSID[j]=buf[i];
		}
	}
	//WIFI 密码
	for(j=0;j<20;i++,j++)
	{
		if(buf[i]==';')
		{
			Password[j]=0;
			i++;
			break;
		}
		else
		{
			Password[j]=buf[i];
		}
	}
	//远程IP
	for(j=0;j<20;i++,j++)
	{
		if(buf[i]==';')
		{
			DstIP[j]=0;
			i++;
			break;
		}
		else
		{
			DstIP[j]=buf[i];
		}
	}
	//端口号
	for(j=0;j<20;i++,j++)
	{
		if(buf[i]==';')
		{
			DstPort[j]=0;
			i++;
			break;
		}
		else
		{
			DstPort[j]=buf[i];
		}
	}
	
	res = f_close(&file1);
}

//文件系统写入数据
void WriteData()
{
	uint8_t lastDate=0;
	
	if(WriteFile_Tick_S<WRITE_FILE_TIME) return;
	
	if(nDate.Date != lastDate)//日期更新 新建文件
	{
		lastDate = nDate.Date;
		
		res = f_open(&wfile,(const char*)writefilename,FA_OPEN_EXISTING|FA_WRITE);
		if(res == FR_OK)
		{
			res = f_lseek(&wfile,f_size(&wfile));//文件存在  指针到末尾
		}
		else
		{
			res = f_open(&wfile,(const char*)writefilename,FA_CREATE_NEW|FA_WRITE);
		}
	}
	
	res = f_write(&wfile,databuf,20,&bw);
	
}
