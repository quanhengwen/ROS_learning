#ifndef _FILE_H
#define _FILE_H

#include "stm32f0xx_hal.h"




#define  WRITE_FILE_TIME  60 //写文件时间间隔 单位秒

void File_IncTick(void);
void WriteData(void);
void ReadParam(void);


#endif

