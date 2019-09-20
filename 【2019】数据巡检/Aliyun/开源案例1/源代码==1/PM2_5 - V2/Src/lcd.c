#include "lcd.h"
#include "font.h"
#include "tim.h"
#include "gui.h"

unsigned int id;
//extern WEATHER_t Weather;

//const uint8_t WEATHERCODE[25][8]={"      晴","    多云","晴间多云","      阴","    阵雨","  雷阵雨","    冰雹","    小雨","    中雨","    大雨","    暴雨","  雨夹雪",
//"    小雪","    中雪","    大雪","    暴雪","  沙尘暴","      雾","      霾","      风","    飓风","    未知"};//天气代码所代表的天气


//液晶背光  0~99
void TFT_BK(uint8_t status)
{
    HAL_TIM_PWM_Start(&htim2,TIM_CHANNEL_2);
    __HAL_TIM_SET_COMPARE(&htim2, TIM_CHANNEL_2, 99-status);//PWM控制背光亮度
}




void LCD_RST(void)
{
    SET_TFT_RESET;
    SET_TFT_WR;
    SET_TFT_RD;
    HAL_Delay(10);
    CLR_TFT_RESET;
    HAL_Delay(20);
    SET_TFT_RESET;
    HAL_Delay(150);
    CLR_TFT_CS;
    TFT_BK(40);
}


void LCD_Write_DATA(unsigned int dat)
{

    CLR_TFT_CS;
    SET_TFT_RS;					//data
    GPIO_TFT_DATA = (GPIO_TFT_DATA&0x00FF)|(dat<<8);
    CLR_TFT_WR;
    SET_TFT_WR;
    SET_TFT_CS;
}
void LCD_Write_DATA_16(unsigned int dat)
{
    CLR_TFT_CS;
    SET_TFT_RS;					//data
    GPIO_TFT_DATA = (GPIO_TFT_DATA&0x00FF)|(dat&0xff00);
    CLR_TFT_WR;
    SET_TFT_WR;
    GPIO_TFT_DATA = (GPIO_TFT_DATA&0x00FF)|(dat<<8);
    CLR_TFT_WR;
    SET_TFT_WR;
    SET_TFT_CS;
}

void LCD_Write_CMD(unsigned int cmd)
{
    CLR_TFT_CS;
    CLR_TFT_RS;					//cmd
    GPIO_TFT_DATA = (GPIO_TFT_DATA&0x00FF)|(cmd<<8);
    CLR_TFT_WR;
    SET_TFT_WR;
    SET_TFT_CS;
}


void LCD_INIT(void)
{

    LCD_RST();
    /******************************************???????***************/
    LCD_Write_CMD(0xE9);
    LCD_Write_DATA(0x20);
    LCD_Write_CMD(0x11); //Exit Sleep
    HAL_Delay(100);
    LCD_Write_CMD(0xD1);
    LCD_Write_DATA(0x00);
    LCD_Write_DATA(0x71);
    LCD_Write_DATA(0x19);
    LCD_Write_CMD(0xD0);
    LCD_Write_DATA(0x07);
    LCD_Write_DATA(0x01);
    LCD_Write_DATA(0x08);
    LCD_Write_CMD(0x36);
    LCD_Write_DATA(0x48);
    LCD_Write_CMD(0x3A);
    LCD_Write_DATA(0x05);
    LCD_Write_CMD(0xC1);
    LCD_Write_DATA(0x10);
    LCD_Write_DATA(0x10);
    LCD_Write_DATA(0x02);
    LCD_Write_DATA(0x02);
    LCD_Write_CMD(0xC0); //Set Default Gamma
    LCD_Write_DATA(0x00);
    LCD_Write_DATA(0x35);
    LCD_Write_DATA(0x00);
    LCD_Write_DATA(0x00);
    LCD_Write_DATA(0x01);
    LCD_Write_DATA(0x02);
    LCD_Write_CMD(0xC5); //Set frame rate
    LCD_Write_DATA(0x04);
    LCD_Write_CMD(0xD2); //power setting
    LCD_Write_DATA(0x01);
    LCD_Write_DATA(0x44);
    LCD_Write_CMD(0xC8); //Set Gamma
    LCD_Write_DATA(0x04);
    LCD_Write_DATA(0x67);
    LCD_Write_DATA(0x35);
    LCD_Write_DATA(0x04);
    LCD_Write_DATA(0x08);
    LCD_Write_DATA(0x06);
    LCD_Write_DATA(0x24);
    LCD_Write_DATA(0x01);
    LCD_Write_DATA(0x37);
    LCD_Write_DATA(0x40);
    LCD_Write_DATA(0x03);
    LCD_Write_DATA(0x10);
    LCD_Write_DATA(0x08);
    LCD_Write_DATA(0x80);
    LCD_Write_DATA(0x00);
    LCD_Write_CMD(0x2A);
    LCD_Write_DATA(0x00);
    LCD_Write_DATA(0x00);
    LCD_Write_DATA(0x00);
    LCD_Write_DATA(0xeF);
    LCD_Write_CMD(0x2B);
    LCD_Write_DATA(0x00);
    LCD_Write_DATA(0x00);
    LCD_Write_DATA(0x01);
    LCD_Write_DATA(0x8F);
    LCD_Write_CMD(0x29); //display on
    LCD_Write_CMD(0x2C); //display on

    TFT_BK(40);
		LCD_BRUSH(BLACK);
}


/****????:LCD??														**/
/****????:Xstart x???,  Ystart y???, Xend x??,  Yend y??																**/
/****?????:?																**/
/****??:																				**/
/***************************************************/
void LCD_SET_WIN(unsigned int Xstart, unsigned int Ystart,unsigned int Xend, unsigned int Yend)
{
    LCD_Write_CMD(0x2A);

//	LCD_Write_DATA(Xstart>>8);
//	LCD_Write_DATA(Xstart);
    LCD_Write_DATA_16(Xstart);
//	LCD_Write_DATA((Xend-1)>>8);
//	LCD_Write_DATA(Xend-1);//320
    LCD_Write_DATA_16(Xend-1);
    LCD_Write_CMD(0x2B);

//	LCD_Write_DATA(Ystart>>8);
//	LCD_Write_DATA(Ystart);
    LCD_Write_DATA_16(Ystart);
//	LCD_Write_DATA((Yend-1)>>8);
//	LCD_Write_DATA(Yend-1);//480
    LCD_Write_DATA_16(Yend-1);
    LCD_Write_CMD(0x2C);
}
void LCD_Draw_Point(unsigned int x,unsigned int y,unsigned int color)
{
    LCD_Write_CMD(0x002A);
    LCD_Write_DATA((x>>8)&0xff);
    LCD_Write_DATA(x&0xff);
    LCD_Write_DATA(((x+1)>>8)&0xff);
    LCD_Write_DATA((x+1)&0xff);

    LCD_Write_CMD(0x002B);
    LCD_Write_DATA((y>>8)&0xff);
    LCD_Write_DATA(y&0xff);
    LCD_Write_DATA(((y+1)>>8)&0xff);
    LCD_Write_DATA((y+1)&0xff);

    LCD_Write_CMD(0x002C);
    LCD_Write_DATA_16(color);

}
/***************************************************/
/****????:LCD????												**/
/****????:color:????										**/
/****?????:?																**/
/****??:																				**/
/***************************************************/
void LCD_BRUSH(unsigned int color)
{
    unsigned int i,j;
    LCD_SET_WIN(0,0,240,400);

    for(i=0; i<240; i++)
    {
        for(j=0; j<400; j++)
        {
            LCD_Write_DATA_16(color);
        }
    }
}


/***************************************************/
/****????:??????												**/
/****????:Xstart x???,  Ystart y???, Xend x??,  Yend y?? color:????										**/
/****?????:?																**/
/****??:																				**/
/***************************************************/

void GUI_Rectangle(unsigned int Xstart,unsigned int Ystart,unsigned int Xend, unsigned int Yend,unsigned int color)
{

    unsigned int i,j;

    LCD_SET_WIN(Xstart,Ystart,Xend,Yend);
    for(i=Xstart; i<Xend; i++)
    {
        for(j=Ystart; j<Yend; j++)
        {
            LCD_Write_DATA_16(color);
        }
    }

}

/***************************************************/
/****????:?????????												**/
/****????:Xstart x???,  Ystart y???,  										**/
/****?????:color ,16?????																**/
/****??:																				**/
/***************************************************/
unsigned int GUI_Read_Dot(unsigned int x, unsigned int y)
{
    unsigned int color ;
    unsigned char c1,c2;
    LCD_Write_CMD(0x2A);
    LCD_Write_DATA((x&0xff00)>>8);
    LCD_Write_DATA((x&0x00ff));
    LCD_Write_DATA(((x&0xff00)>>8)+1);
    LCD_Write_DATA((x&0x00ff+1));
    LCD_Write_CMD(0x2B);
    LCD_Write_DATA((y&0xff00)>>8);
    LCD_Write_DATA((y&0x00ff));
    LCD_Write_DATA((y&0xff00)>>8);
    LCD_Write_DATA((y&0x00ff));

    LCD_Write_CMD(0x2C);

    SET_TFT_RS;					//data
    CLR_TFT_CS;
    CLR_TFT_RD;

    c1 = GPIO_TFT_DATA_IN;

    SET_TFT_RD;

    CLR_TFT_RD;

    c2 = GPIO_TFT_DATA_IN;

    SET_TFT_RD;

    SET_TFT_CS;

    color = (c1 <<8)|c2;

    return color;

}
/***************************************************/
/****????:??????												**/
/****????:Xstart x???,  Ystart y???,  color:????										**/
/****?????:?																**/
/****??:																				**/
/***************************************************/

void GUI_Point(unsigned int x, unsigned int y,unsigned int color)
{
    LCD_Write_CMD(0x2A);
    LCD_Write_DATA((x&0xff00)>>8);
    LCD_Write_DATA((x&0x00ff));
    LCD_Write_DATA(((x&0xff00)>>8)+1);
    LCD_Write_DATA((x&0x00ff+1));
    LCD_Write_CMD(0x2B);
    LCD_Write_DATA((y&0xff00)>>8);
    LCD_Write_DATA((y&0x00ff));
    LCD_Write_DATA((y&0xff00)>>8);
    LCD_Write_DATA((y&0x00ff));

    LCD_Write_CMD(0x2C);

    LCD_Write_DATA(color>>8);
    LCD_Write_DATA(color);
}

//在x y位置显示n个数字字符  dat为字符指针
void GUI_DispNumber_48x76(uint16_t x,uint16_t y,uint16_t color,uint16_t b_color,uint8_t *dat,uint8_t n)
{
    uint16_t j,pos,t,ch;
    uint8_t temp;

    for(j=0; j<n; j++)
    {
        if(dat[j]=='.')
        {
            LCD_SET_WIN(x+8,y+56,x+16,y+64);  //
            for(pos=0; pos<64; pos++)
            {
                LCD_Write_DATA_16(color);
            }
            x=x+24;
        }
        else if(dat[j]=='-')
        {
            ch=5016;
            LCD_SET_WIN(x,y,x+24,y+76);  //
            for(pos=0; pos<228; pos++)
            {
                temp=Digital_Num_48x76[ch+pos];
                for(t=0; t<8; t++)
                {
                    if(temp&0x01)LCD_Write_DATA_16(color);
                    else LCD_Write_DATA_16(b_color);
                    temp>>=1;
                }
            }
            x=x+24;
        }
        else if(dat[j]==':')
        {
            ch=5244;
            LCD_SET_WIN(x,y,x+24,y+76);  //
            for(pos=0; pos<228; pos++)
            {
                temp=Digital_Num_48x76[ch+pos];
                for(t=0; t<8; t++)
                {
                    if(temp&0x01)LCD_Write_DATA_16(color);
                    else LCD_Write_DATA_16(b_color);
                    temp>>=1;
                }
            }
            x=x+24;
        }
        else
        {
            if(dat[j]=='+')ch=4560;
            else ch=(dat[j]-0x30)*456;
            LCD_SET_WIN(x,y,x+48,y+76);  //
            for(pos=0; pos<456; pos++)
            {
                temp=Digital_Num_48x76[ch+pos];
                for(t=0; t<8; t++)
                {
                    if(temp&0x01)LCD_Write_DATA_16(color);
                    else LCD_Write_DATA_16(b_color);
                    temp>>=1;
                }
            }
            x=x+48;
        }
    }
}
//在x y位置显示n个数字字符  dat为字符指针
void GUI_DispNumber_16x32(uint16_t x,uint16_t y,uint16_t color,uint16_t b_color,uint8_t *dat,uint8_t n)
{
    uint16_t j,pos,t,ch;
    uint8_t temp;

    for(j=0; j<n; j++)
    {
        ch=(dat[j]-0x30)<<6;
        LCD_SET_WIN(x,y,x+16,y+32);  //
        for(pos=0; pos<64; pos++)
        {
            temp=Digital_Num_16x32[ch+pos];
            for(t=0; t<8; t++)
            {
                if(temp&0x01)LCD_Write_DATA_16(color);
                else LCD_Write_DATA_16(b_color);
                temp>>=1;
            }
        }
        x+=20;
    }
}

//在x y位置显示n个宋体字符  dat为字符指针
void GUI_Dispstr_16x32(uint16_t x,uint16_t y,uint16_t color,uint16_t b_color,uint8_t *dat,uint8_t n)
{
    uint16_t j,pos,t,ch;
    uint8_t temp;

    for(j=0; j<n; j++)
    {
        if(dat[j]=='-') ch=768;
        else if(dat[j]==':') ch=704;
				else if(dat[j]=='P') ch=832;
				else if(dat[j]=='M') ch=896;
				else if(dat[j]=='.') ch=640;
        else ch=(dat[j]-0x30)<<6;

        LCD_SET_WIN(x,y,x+16,y+32);  //
        for(pos=0; pos<64; pos++)
        {
            temp=Str_16x32[ch+pos];
            for(t=0; t<8; t++)
            {
                if(temp&0x01)LCD_Write_DATA_16(color);
                else LCD_Write_DATA_16(b_color);
                temp>>=1;
            }
        }
        x+=16;
    }
}

//在x y位置显示n个宋体字符  dat为字符指针
void GUI_Dispstr_12x24(uint16_t x,uint16_t y,uint16_t color,uint16_t b_color,uint8_t *dat,uint8_t n)
{
    uint16_t j,pos,t,ch;
    uint8_t temp;

    for(j=0; j<n; j++)
    {
        if(dat[j]=='.') ch=480;
				else if(dat[j]=='P') ch=528;
				else if(dat[j]=='M') ch=576;
				else if(dat[j]=='%') ch=624;
				else if(dat[j]=='-') ch=672;
        else ch=(dat[j]-0x30)*48;

        LCD_SET_WIN(x,y,x+16,y+24);  //
        for(pos=0; pos<48; pos++)
        {
            temp=Str_12x24[ch+pos];
            for(t=0; t<8; t++)
            {
                if(temp&0x01)LCD_Write_DATA_16(color);
                else LCD_Write_DATA_16(b_color);
                temp>>=1;
            }
        }
        x+=12;
    }
}
//在x y位置显示n个宋体字符  dat为字符指针
void GUI_Dispstr_8x16(uint16_t x,uint16_t y,uint16_t color,uint16_t b_color,uint8_t *dat,uint8_t n)
{
    uint16_t j,pos,t,ch;
    uint8_t temp;

    for(j=0; j<n; j++)
    {
        if(dat[j]=='u') ch=160;
				else if(dat[j]=='g') ch=176;
				else if(dat[j]=='/') ch=192;
				else if(dat[j]=='m') ch=208;
				else if(dat[j]=='-') ch=224;
				else if(dat[j]=='T') ch=240;
				else if(dat[j]=='D') ch=256;
				else if(dat[j]==':') ch=272;
				else if(dat[j]=='P') ch=304;
				else if(dat[j]=='M') ch=320;
				else if(dat[j]=='.') ch=336;
				else if(dat[j]==' '||dat[j]==0) ch=288;
        else ch=(dat[j]-0x30)*16;

        LCD_SET_WIN(x,y,x+8,y+16);  //
        for(pos=0; pos<16; pos++)
        {
            temp=Str_8x16[ch+pos];
            for(t=0; t<8; t++)
            {
                if(temp&0x01)LCD_Write_DATA_16(color);
                else LCD_Write_DATA_16(b_color);
                temp>>=1;
            }
        }
        x+=8;
    }
}
//在x y位置显示n个汉字  dat为字符指针
void GUI_DispHZ_32x32(uint16_t x,uint16_t y,uint16_t color,uint16_t b_color,uint8_t *dat,uint8_t n)
{
    uint16_t j,pos,t,i;
    uint8_t temp;

    n=n<<1;
    for(j=0; j<n; j+=2)
    {
        for(i=0; i<70; i++)
        {
            if(dat[j]==Hzk32x32[i].index[0]&&dat[j+1]==Hzk32x32[i].index[1])
                break;
        }
        if(i==70)return;

        LCD_SET_WIN(x,y,x+32,y+32);  //
        for(pos=0; pos<128; pos++)
        {
            temp=Hzk32x32[i].zimo[pos];
            for(t=0; t<8; t++)
            {
                if(temp&0x01)LCD_Write_DATA_16(color);
                else LCD_Write_DATA_16(b_color);
                temp>>=1;
            }
        }
        x+=32;
    }
}
//在x y位置显示n个汉字  dat为字符指针
void GUI_DispHZ_16x16(uint16_t x,uint16_t y,uint16_t color,uint16_t b_color,const uint8_t *dat,uint8_t n)
{
    uint16_t j,pos,t,i;
    uint8_t temp;

    n=n<<1;
    for(j=0; j<n; j+=2)
    {
        for(i=0; i<70; i++)
        {
            if(dat[j]==Hzk16x16[i].index[0]&&dat[j+1]==Hzk16x16[i].index[1])
                break;
        }
        if(i==70)return;

        LCD_SET_WIN(x,y,x+16,y+16);  //
        for(pos=0; pos<32; pos++)
        {
            temp=Hzk16x16[i].zimo[pos];
            for(t=0; t<8; t++)
            {
                if(temp&0x01)LCD_Write_DATA_16(color);
                else LCD_Write_DATA_16(b_color);
                temp>>=1;
            }
        }
        x+=16;
    }
}
//在x y位置显示n个汉字  dat为字符指针
void GUI_DispHZ_24x24(uint16_t x,uint16_t y,uint16_t color,uint16_t b_color,uint8_t *dat,uint8_t n)
{
    uint16_t j,pos,t,i;
    uint8_t temp;

    n=n<<1;
    for(j=0; j<n; j+=2)
    {
        for(i=0; i<70; i++)
        {
            if(dat[j]==Hzk24x24[i].index[0]&&dat[j+1]==Hzk24x24[i].index[1])
                break;
        }
        if(i==70)return;

        LCD_SET_WIN(x,y,x+24,y+24);  //
        for(pos=0; pos<72; pos++)
        {
            temp=Hzk24x24[i].zimo[pos];
            for(t=0; t<8; t++)
            {
                if(temp&0x01)LCD_Write_DATA_16(color);
                else LCD_Write_DATA_16(b_color);
                temp>>=1;
            }
        }
        x+=24;
    }
}
void DrawHLine(uint16_t x1,uint16_t x2,uint16_t y,uint16_t color)
{
    uint16_t t;
    LCD_SET_WIN(x1,y,x2,y+2);
    for(t=x1; t<x2; t++)
    {
        LCD_Write_DATA_16(color);
    }
}

void DrawVLine(uint16_t x,uint16_t y1,uint16_t y2,uint16_t color)
{
    uint16_t t;
    LCD_SET_WIN(x,y1,x+1,y2);
    for(t=y1; t<y2; t++)
    {
        LCD_Write_DATA_16(color);
    }
}


void GUI_DispDateTime(uint16_t x,uint16_t y,RTC_DateTypeDef Date,RTC_TimeTypeDef Time)
{
	uint8_t str[20];
	
	str[0] = '2';
	str[1] = '0';
	str[2] = (Date.Year/10)%10+0x30;
	str[3] = (Date.Year)%10+0x30;
	str[4] = '-';
	str[5] = (Date.Month/10)%10+0x30;
	str[6] = (Date.Month)%10+0x30;
	str[7] = '-';
	str[8] = (Date.Date/10)%10+0x30;
	str[9] = (Date.Date)%10+0x30;
	str[10] = ' ';
	str[11] = (Time.Hours/10)%10+0x30;
	str[12] = (Time.Hours)%10+0x30;
	str[13] = ':';
	str[14] = (Time.Minutes/10)%10+0x30;
	str[15] = (Time.Minutes)%10+0x30;
	str[16] = ':';
	str[17] = (Time.Seconds/10)%10+0x30;
	str[18] = (Time.Seconds)%10+0x30;
	GUI_Dispstr_8x16(x,y,WHITE,BLACK,str,19);//时间
}


void GUI_DispBattery(uint16_t x,uint16_t y,uint16_t Vbat)
{
	uint16_t t;
	uint8_t temp;
	LCD_SET_WIN(x,y,x+40,y+16);
	for(t=0; t<80; t++)
	{
			temp = batpic[t];
			for(int i=0;i<8;i++)
			{
				if(temp&0x01)LCD_Write_DATA_16(WHITE);
				else LCD_Write_DATA_16(BLACK);
				temp=temp>>1;
			}
	}
//	Vbat=387;
	if(Vbat>370)
	{
		x=x+29;
		LCD_SET_WIN(x,y+4,x+5,y+12);
		for(t=0; t<40; t++)
		{
				LCD_Write_DATA_16(WHITE);
		}
	}
	if(Vbat>380)
	{
		x-=6;
		LCD_SET_WIN(x,y+4,x+5,y+12);
		for(t=0; t<40; t++)
		{
				LCD_Write_DATA_16(WHITE);
		}
	}
	if(Vbat>390)
	{
		x-=6;
		LCD_SET_WIN(x,y+4,x+5,y+12);
		for(t=0; t<40; t++)
		{
				LCD_Write_DATA_16(WHITE);
		}
	}
	if(Vbat>400)
	{
		x-=6;
		LCD_SET_WIN(x,y+4,x+5,y+12);
		for(t=0; t<40; t++)
		{
				LCD_Write_DATA_16(WHITE);
		}
	}
	
}

const uint8_t arrow[]={0xFE,0x7C,0x38,0x10};
void GUI_Disp_Arrow(uint16_t x,uint16_t y)
{
	static uint16_t xtemp = 0;
	
	uint8_t temp;
	LCD_SET_WIN(xtemp-4,y,xtemp+4,y+4);
	for(uint8_t t=0; t<32; t++)
	{
			LCD_Write_DATA_16(BLACK);
	}
	
	LCD_SET_WIN(x-4,y,x+4,y+4);
	for(uint8_t t=0; t<4; t++)
	{
		temp = arrow[t];
		for(uint8_t i=0; i<8; i++)
		{
			if(temp&0x01)
				LCD_Write_DATA_16(WHITE);
			else
				LCD_Write_DATA_16(BLACK);
			temp>>=1;
		}
	}
	xtemp = x;
}

//void GUI_DispWeather()
//{
//    uint16_t pos,t;
//    uint8_t temp;
//		uint32_t dat;
//	
//		GUI_DispHZ_16x16(45,232,GREEN,BLACK,WEATHERCODE[Weather.Todaycode],4);//今天天气
//		//显示天气图标
//		dat = Weather.Todaycode*200;
//		LCD_SET_WIN(10,249,50,289);  //
//		for(pos=0; pos<200; pos++)
//		{
//				temp=Weather_pic[dat];
//				for(t=0; t<8; t++)
//				{
//						if(temp&0x01)LCD_Write_DATA_16(YELLOW);
//						else LCD_Write_DATA_16(BLACK);
//						temp>>=1;
//				}
//				dat++;
//		}
//		GUI_Dispstr_8x16(53,270,GREEN,BLACK,Weather.TodayT,8);//今天温度
//		
//		GUI_DispHZ_16x16(165,232,GREEN,BLACK,WEATHERCODE[Weather.Tomorrowcode],4);//明天天气
//		//显示天气图标
//		dat = Weather.Tomorrowcode*200;
//		LCD_SET_WIN(130,249,170,289);  //
//		for(pos=0; pos<200; pos++)
//		{
//				temp=Weather_pic[dat];
//				for(t=0; t<8; t++)
//				{
//						if(temp&0x01)LCD_Write_DATA_16(YELLOW);
//						else LCD_Write_DATA_16(BLACK);
//						temp>>=1;
//				}
//				dat++;
//		}
//		GUI_Dispstr_8x16(173,270,GREEN,BLACK,Weather.TomorrowT,8);//明天温度
//	
//		
//}

