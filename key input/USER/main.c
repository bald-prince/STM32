#include "sys.h"
#include "delay.h"
#include "usart.h"
#include "led.h"
#include "key.h"



int main(void)
{
		u8 key;
    HAL_Init();                    	//初始化HAL库    
    Stm32_Clock_Init(336,8,2,7);  	//设置时钟,168Mhz
		delay_init(168);               	//初始化延时函数
		LED_Init();											//初始化LED	
    KEY_Init();                     //初始化按键

	
    while(1)
    {
        key=KEY_Scan(0);            //按键扫描
				switch(key)
				{				 
					case KEY0_PRES:	
					while(1)
					{
						LED0=0;
						LED1=1;
					}
					case KEY1_PRES:	//同时控制LED0,LED1翻转		
				  while(1)
					{
						LED0=1;
						LED1=0;
					}
				}
        delay_ms(10);
//			key=KEY_Scan(0);            //按键扫描
//		switch(key)
//		{
//			case KEY0_PRES:	
//			//while(1)
//			//{	
//				LED0=1;
//				LED2=0;
//				delay_ms(10);	
//		}
	}
}


