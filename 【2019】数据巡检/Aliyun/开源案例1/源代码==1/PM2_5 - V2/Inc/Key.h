#ifndef __KEY_H__
#define __KEY_H__

#define key_state_0 0  // 按键初始态
#define key_state_1 1  // 按键消抖与确认态 
#define key_state_2 2  
#define key_state_3 3  		

#define N_key     0             //无键  

#define S_key1    1             //key1单键  
#define D_key1    2             //key1双键  
#define L_key1    3             //key1长键  

#define S_key2    4             //key2单键  
#define D_key2    5             //key2双键  
#define L_key2    6             //key2长键  

#define S_key3    7             //key3单键  
#define D_key3    8             //key3双键  
#define L_key3    9             //key3长键  



#define KEY1       (GPIO_PIN_1)
//#define KEY2       (GPIO_PIN_4)
//#define KEY3       (GPIO_PIN_5)


//按键引脚
#define GPIO_KEY 				GPIOB
#define GPIO_Pin_Key 		GPIO_PIN_1
#define key_input    GPIO_KEY->IDR & GPIO_Pin_Key   // 按键输入口  


extern void Key_IncTick(void);                 
extern unsigned char key_read(void);			// 10ms调用1次，返回按键值

#endif

