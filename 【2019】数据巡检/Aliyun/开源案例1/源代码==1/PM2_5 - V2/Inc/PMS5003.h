#ifndef __PMS5003_H
#define __PMS5003_H


#ifdef __cplusplus
 extern "C" {
#endif


#include "stm32f0xx_hal.h"

//#define PMS5003_ST	 

typedef struct
{
	uint16_t PM1_0;
	uint16_t PM2_5;
	uint16_t PM10;
#ifdef PMS5003_ST	
	uint16_t Temperature;
	uint16_t Humidity;
	uint16_t HCHO;
#endif	
}PMS5003_t;	


extern PMS5003_t PMS5003_Data;

void PMS_RevData(void);	 
	 
	 

	 
#endif
