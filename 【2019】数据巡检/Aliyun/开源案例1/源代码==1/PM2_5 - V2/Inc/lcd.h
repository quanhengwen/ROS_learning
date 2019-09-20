#ifndef __LCD_H
#define __LCD_H


#include "stm32f0xx_hal.h"



#define GPIO_TFT_CTRL  				GPIOB
#define GPIO_Pin_TFT_CS   		GPIO_PIN_7
#define GPIO_Pin_TFT_RS   		GPIO_PIN_6
#define GPIO_Pin_TFT_WR   		GPIO_PIN_5
#define GPIO_Pin_TFT_RD   		GPIO_PIN_4
#define GPIO_Pin_TFT_RESET   	GPIO_PIN_3

#define GPIO_TFT_DATA 				GPIOB->ODR
#define GPIO_TFT_DATA_IN 			(GPIOB->IDR&0x00FF)

#define SET_TFT_CS 			GPIO_TFT_CTRL->BSRR = GPIO_Pin_TFT_CS  // GPIOx->BSRR = GPIO_Pin;
#define SET_TFT_RS 			GPIO_TFT_CTRL->BSRR = GPIO_Pin_TFT_RS
#define SET_TFT_WR 			GPIO_TFT_CTRL->BSRR = GPIO_Pin_TFT_WR
#define SET_TFT_RD 			GPIO_TFT_CTRL->BSRR = GPIO_Pin_TFT_RD
#define SET_TFT_RESET 	GPIO_TFT_CTRL->BSRR = GPIO_Pin_TFT_RESET

#define CLR_TFT_CS 			GPIO_TFT_CTRL->BRR = GPIO_Pin_TFT_CS
#define CLR_TFT_RS 			GPIO_TFT_CTRL->BRR = GPIO_Pin_TFT_RS
#define CLR_TFT_WR 			GPIO_TFT_CTRL->BRR = GPIO_Pin_TFT_WR
#define CLR_TFT_RD 			GPIO_TFT_CTRL->BRR = GPIO_Pin_TFT_RD
#define CLR_TFT_RESET 	GPIO_TFT_CTRL->BRR = GPIO_Pin_TFT_RESET



#define WHITE           0xFFFF
#define BLACK           0x0000          
#define BLUE            0x001F  
#define BRED            0XF81F
#define GRED            0XFFE0
#define GBLUE           0X07FF
#define RED             0xF800
#define MAGENTA         0xF81F
#define ORANGE          0xFF00
#define GREEN           0x07E0
#define CYAN            0x7FFF
#define YELLOW          0xFFE0
#define BROWN           0XBC40 //??
#define BRRED           0XFC07 //???
#define GRAY            0X8430 //??

extern void LCD_INIT(void);
extern void LCD_BRUSH(unsigned int color);
extern void LCD_Draw_Point(unsigned int x,unsigned int y,unsigned int color);
extern void GUI_Rectangle(unsigned int Xstart,unsigned int Ystart,unsigned int Xend, unsigned int Yend,unsigned int color);
extern void TFT_BK(uint8_t status);

extern void GUI_DispNumber_16x32(uint16_t x,uint16_t y,uint16_t color,uint16_t b_color,uint8_t *dat,uint8_t n);
extern void GUI_DispNumber_48x76(uint16_t x,uint16_t y,uint16_t color,uint16_t b_color,uint8_t *dat,uint8_t n);
extern void GUI_DispHZ_32x32(uint16_t x,uint16_t y,uint16_t color,uint16_t b_color,uint8_t *dat,uint8_t n);
extern void GUI_DispHZ_24x24(uint16_t x,uint16_t y,uint16_t color,uint16_t b_color,uint8_t *dat,uint8_t n);
extern void GUI_DispHZ_16x16(uint16_t x,uint16_t y,uint16_t color,uint16_t b_color,const uint8_t *dat,uint8_t n);
extern void GUI_Dispstr_8x16(uint16_t x,uint16_t y,uint16_t color,uint16_t b_color,uint8_t *dat,uint8_t n);
extern void GUI_Dispstr_12x24(uint16_t x,uint16_t y,uint16_t color,uint16_t b_color,uint8_t *dat,uint8_t n);
extern void GUI_Dispstr_16x32(uint16_t x,uint16_t y,uint16_t color,uint16_t b_color,uint8_t *dat,uint8_t n);
extern void DrawVLine(uint16_t x,uint16_t y1,uint16_t y2,uint16_t color);
extern void DrawHLine(uint16_t x1,uint16_t x2,uint16_t y,uint16_t color);
extern void GUI_DispDateTime(uint16_t x,uint16_t y,RTC_DateTypeDef Date,RTC_TimeTypeDef Time);
extern void GUI_DispBattery(uint16_t x,uint16_t y,uint16_t Vbat);
extern void GUI_Disp_Arrow(uint16_t x,uint16_t y);
extern void GUI_DispWeather(void);


#endif

