#include "gui.h"
#include "Key.h"
#include "lcd.h"
#include "PMS5003.h"
#include "DHT12.h"


uint8_t bk_value=40;
STRGUI GUI_Menu;
__IO uint16_t gui_tick=0;
extern uint8_t Key;
extern RTC_TimeTypeDef nTime;
extern RTC_DateTypeDef nDate;
extern uint16_t VBat;
extern uint8_t WIFI_Status;

void GUI_IncTick()
{
	gui_tick++;
}

//------------------------按键处理程序-----------------
void Key_Process()
{
	if(Key==S_key1)
	{
		GUI_Menu.page++;
		if(GUI_Menu.page==MAX_PAGE)
			GUI_Menu.page=0;
		GUI_Menu.page_init=0;
	}
}

void GUI_Init(void)
{
	GUI_Menu.page=PAGE1;
	GUI_Menu.page_init=0;
}

//extern uint8_t WIFI_Status,teststatus;
void Page1_Display()
{
	uint8_t str[10];
	int16_t Temp,Humi,HCHO;
	
	if(GUI_Menu.page_init==0)//初始化固定显示内容
	{
		GUI_Menu.page_init=1;
		DrawHLine(0,239,35,WHITE);
		
		DrawHLine(10,229,235,WHITE);
		DrawVLine(120,240,290,WHITE);
		DrawHLine(10,229,295,WHITE);
		DrawHLine(10,229,345,WHITE);

		GUI_Dispstr_12x24(80,45,WHITE,BLACK,(uint8_t*)"PM2.5",5);
		GUI_Rectangle(10,190,54,194,GREEN);GUI_Rectangle(54,190,98,194,YELLOW);GUI_Rectangle(98,190,142,194,ORANGE);
		GUI_Rectangle(142,190,186,194,BLUE);GUI_Rectangle(186,190,230,194,RED);
		GUI_DispHZ_16x16(24,203,WHITE,BLACK,(uint8_t*)"优",1);
		GUI_DispHZ_16x16(68,203,WHITE,BLACK,(uint8_t*)"良",1);
		GUI_DispHZ_16x16(104,203,WHITE,BLACK,(uint8_t*)"轻度",2);
		GUI_DispHZ_16x16(148,203,WHITE,BLACK,(uint8_t*)"中度",2);
		GUI_DispHZ_16x16(192,203,WHITE,BLACK,(uint8_t*)"重度",2);
		GUI_Dispstr_8x16(10,237,WHITE,BLACK,(uint8_t*)"PM1.0",5);GUI_Dispstr_8x16(130,237,WHITE,BLACK,(uint8_t*)"PM10",4);
		GUI_DispHZ_24x24(15,305,GREEN,BLACK,(uint8_t*)"标",1);GUI_DispHZ_24x24(50,305,WHITE,BLACK,(uint8_t*)"温度",2);GUI_DispHZ_24x24(200,305,WHITE,BLACK,(uint8_t*)"℃",1);
		GUI_DispHZ_24x24(15,360,GREEN,BLACK,(uint8_t*)"图",1);GUI_DispHZ_24x24(50,360,WHITE,BLACK,(uint8_t*)"湿度",2);GUI_Dispstr_12x24(200,360,WHITE,BLACK,(uint8_t*)"%",1);
		
	}
	else
	{
		if(gui_tick<1000)return;//每秒更新一次
		gui_tick=0;
		
		#ifdef PMS5003_ST
			Temp = PMS5003_Data.Temperature;
			Humi = PMS5003_Data.Humidity;
		  HCHO = PMS5003_Data.HCHO;
		#else
			Temp = DHT12_Temperature;
			Humi = DHT12_Humidity;
		#endif
		
		str[0] = (PMS5003_Data.PM2_5/100)%10+0x30;
		str[1] = (PMS5003_Data.PM2_5/10)%10+0x30;
		str[2] = (PMS5003_Data.PM2_5/1)%10+0x30;
		uint16_t color;
		if(PMS5003_Data.PM2_5<50)//优
		{
			color=GREEN;
			GUI_Disp_Arrow(10+PMS5003_Data.PM2_5*44/50,185);
		}
		else if(PMS5003_Data.PM2_5<100)//良
		{
			color=YELLOW;
			GUI_Disp_Arrow(54+(PMS5003_Data.PM2_5-50)*44/50,185);
		}
		else if(PMS5003_Data.PM2_5<150)//轻度
		{
			color=ORANGE;
			GUI_Disp_Arrow(98+(PMS5003_Data.PM2_5-100)*44/50,185);
		}
		else if(PMS5003_Data.PM2_5<200)//中度
		{
			color=BLUE;
			GUI_Disp_Arrow(142+(PMS5003_Data.PM2_5-150)*44/50,185);
		}
		else//重度
		{
			color=RED;
			GUI_Disp_Arrow(186+(PMS5003_Data.PM2_5-200)*44/100,185);
		}
		GUI_DispNumber_48x76(48,85,color,BLACK,str,3);//显示PM2.5
		
		
		str[0] = (PMS5003_Data.PM1_0/100)%10+0x30;
		str[1] = (PMS5003_Data.PM1_0/10)%10+0x30;
		str[2] = (PMS5003_Data.PM1_0/1)%10+0x30;
		GUI_Dispstr_16x32(40,256,color,BLACK,str,3);//显示PM1.0
		
		str[0] = (PMS5003_Data.PM10/100)%10+0x30;
		str[1] = (PMS5003_Data.PM10/10)%10+0x30;
		str[2] = (PMS5003_Data.PM10/1)%10+0x30;
		GUI_Dispstr_16x32(160,256,color,BLACK,str,3);//显示PM10

		
		str[0] = (Temp/100)%10+0x30;
		str[1] = (Temp/10)%10+0x30;
		str[2] = '.';
		str[3] = (Temp)%10+0x30;
		GUI_Dispstr_16x32(120,298,GREEN,BLACK,str,4);//显示温度
		
		str[0] = (Humi/100)%10+0x30;
		str[1] = (Humi/10)%10+0x30;
		str[2] = '.';
		str[3] = (Humi)%10+0x30;
		GUI_Dispstr_16x32(120,353,GREEN,BLACK,str,4);//显示湿度
		
		
		GUI_DispBattery(190,15,VBat);
		
		GUI_DispDateTime(5,15,nDate,nTime);//显示时间
		
		if(WIFI_Status<3)
			GUI_DispHZ_16x16(170,15,RED,BLACK,(uint8_t *)"断",1);//显示wifi状态
		else
			GUI_DispHZ_16x16(170,15,WHITE,BLACK,(uint8_t *)"联",1);

	}
}

void Page2_Display()
{
	if(GUI_Menu.page_init==0)//初始化固定显示内容
	{
		GUI_Menu.page_init=1;
	}
	else
	{
		if(gui_tick<1000)return;//每秒更新一次
		gui_tick=0;
	}
}

void Page3_Display()
{
	if(GUI_Menu.page_init==0)//初始化固定显示内容
	{
		GUI_Menu.page_init=1;
	}
	else
	{
		if(gui_tick<1000)return;//每秒更新一次
		gui_tick=0;
	}
}

void Page4_Display()
{
	if(GUI_Menu.page_init==0)//初始化固定显示内容
	{
		GUI_Menu.page_init=1;
		
	}
	else
	{
		if(gui_tick<1000)return;//每秒更新一次
		gui_tick=0;
		
		

	}
}

void Page5_Display()
{
	if(GUI_Menu.page_init==0)//初始化固定显示内容
	{
		GUI_Menu.page_init=1;
	}
	else
	{
		if(gui_tick<1000)return;//每秒更新一次
		gui_tick=0;
	}
}

void GUI_Task()
{
	//--------------显示------------------
	switch(GUI_Menu.page)
	{
		case PAGE1:
			Page1_Display();
			break;
		case PAGE2:
			Page2_Display();
			break;
		case PAGE3:
			Page3_Display();
			break;
		case PAGE4:
			Page4_Display();
			break;
		case PAGE5:
			Page5_Display();
			break;
		default:
			break;
	}
	if(Key==S_key1)
	{
		if(bk_value>=10)
		{
			bk_value=bk_value-10;
		}
		else
		{
			bk_value=80;
		}
		TFT_BK(bk_value);
	}
}


