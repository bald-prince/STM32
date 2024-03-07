#include "sys.h"
#include "delay.h"
#include "usart.h"
#include "led.h"

int main(void)
{ 
    HAL_Init();                    														//初始化HAL库    
    Stm32_Clock_Init(336,8,2,7);  														//设置时钟,168Mhz
		delay_init(168);              													 	//初始化延时函数
		LED_Init();																								//初始化LED	
	
	while(1)
	{
        HAL_GPIO_WritePin(GPIOC,GPIO_PIN_0,GPIO_PIN_RESET); 	//LED0对应引脚PC0拉低，亮，等同于LED0(0)
        delay_ms(1000);																				//延时1000ms
        HAL_GPIO_WritePin(GPIOC,GPIO_PIN_0,GPIO_PIN_SET);   	//LED0对应引脚PC0拉高，灭，等同于LED0(1)
        delay_ms(1000);                                      	//延时1000ms 
	}
}





