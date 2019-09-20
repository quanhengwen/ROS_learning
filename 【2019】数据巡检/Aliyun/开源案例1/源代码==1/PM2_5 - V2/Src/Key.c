#include "Key.h"
#include "stm32f0xx_hal.h"

__IO uint8_t key_tick=0;

void Key_IncTick()
{
	key_tick++;
}

unsigned char key_driver(void)  
{  
    static unsigned char key_state = key_state_0,key_temp = N_key;
    static int key_time = 0;  
    unsigned char key_press, key_return = N_key;  

    key_press = key_input;//HAL_GPIO_ReadPin(GPIO_KEY,GPIO_Pin_Key);                    // 读按键I/O电平  

    switch (key_state)  
    {  
      case key_state_0:                              // 按键初始态  
        if (key_press!=GPIO_Pin_Key) key_state = key_state_1;      // 有键被按下，状态转换到按键消抖和确认状态  
        break;  
        
      case key_state_1:                      // 按键消抖与确认态  
        if (key_press!=GPIO_Pin_Key)  
        {  
             key_time = 0;                   //   
             if((key_press & KEY1) == 0) key_temp = S_key1;
//             else if((key_press & KEY2) == 0) key_temp = S_key2;
//             else if((key_press & KEY3) == 0) key_temp = S_key3;
             key_state = key_state_2;   // 按键仍然处于按下，消抖完成，状态转换到按下键时间的计时状态，但返回的还是无键事件  
        }  
        else  
             key_state = key_state_0;   // 按键已抬起，转换到按键初始态。此处完成和实现软件消抖，其实按键的按下和释放都在此消抖的。  
        break;  
        
      case key_state_2:  
        if(key_press==GPIO_Pin_Key)  
        {  
             key_return = key_temp;        // 此时按键释放，说明是产生一次短操作，回送
             key_state = key_state_0;   // 转换到按键初始态  
        }  
        else if (++key_time >= 200)     // 继续按下，计时加10ms（10ms为本函数循环执行间隔）  
        {  
             key_return = key_temp+2;        // 按下时间>2000ms，此按键为长按操作，返回长键事件  
             key_state = key_state_3;   // 转换到等待按键释放状态  
        }  
        break;  

      case key_state_3:                 // 等待按键释放状态，此状态只返回无按键事件  
        if (key_press==GPIO_Pin_Key) key_state = key_state_0; //按键已释放，转换到按键初始态  
        break;  
    }  
    return key_return;  
} 

//10ms扫描一次
unsigned char key_read(void)  
{  
    static unsigned char key_m = key_state_0, key_time_1 = 0,key_temp=0;  
    unsigned char key_return = N_key,key_press;  
      
		if(key_tick<10) return 0;
		key_tick=0;
	
    key_press = key_driver();  
      
    switch(key_m)  
    {  
        case key_state_0:  
            if (key_press == S_key1 || key_press == S_key2 || key_press == S_key3)  
            {  
                 key_time_1 = 0;               // 第1次单击，不返回，到下个状态判断后面是否出现双击  
                 key_temp = key_press;
                 key_m = key_state_1;  
            }  
            else  
                 key_return = key_press;        // 对于无键、长键，返回原事件  
            break;  

        case key_state_1:  
            if (key_press == S_key1 || key_press == S_key2 || key_press == S_key3)             // 又一次单击（间隔肯定<500ms）  
            {  
                 key_return = key_temp+1;           // 返回双击键事件，回初始状态  
                 key_m = key_state_0;  
            }  
            else                                 
            {                                  // 这里300ms内肯定读到的都是无键事件，因为长键>1000ms，在1s前低层返回的都是无键  
                 if(++key_time_1 >= 30)  
                 {  
                      key_return = key_temp;      // 300ms内没有再次出现单键事件，返回上一次的单键事件  
                      key_m = key_state_0;     // 返回初始状态  
                 }  
             }  
             break;  
    } 
    return key_return;  
}      




