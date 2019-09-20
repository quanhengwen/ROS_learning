#ifndef __RELAY_H__
#define __RELAY_H__


#include "stm32f0xx_hal.h"


typedef struct {
unsigned char index[2];
unsigned char zimo[128];
}HZK32;

typedef struct {
unsigned char index[2];
unsigned char zimo[72];
}HZK24;

typedef struct {
unsigned char index[2];
unsigned char zimo[32];
}HZK16;

extern const HZK16 Hzk16x16[];
extern const HZK24 Hzk24x24[];
extern const HZK32 Hzk32x32[];
extern const uint8_t Str_8x16[];
extern const uint8_t Str_12x24[];
extern const uint8_t Str_16x32[];
extern const uint8_t Digital_Num_16x32[];
extern const uint8_t Digital_Num_48x76[];
extern const uint8_t batpic[];
extern const uint8_t Weather_pic[];
#endif

