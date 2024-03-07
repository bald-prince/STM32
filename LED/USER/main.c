#include "sys.h"
#include "delay.h"
#include "led.h"

int main(void)
{ 
	HAL_Init();                    														//初始化HAL库    
  Stm32_Clock_Init(336,8,2,7);  														//设置时钟,168Mhz
	delay_init(168);              													 	//初始化延时函数
	LED_Init();																								//初始化LED	
	
	while(1)
	{
    LED0=0;
		LED1=1;
		//delay_ms(100);
		//LED0=1;	
	}
}


