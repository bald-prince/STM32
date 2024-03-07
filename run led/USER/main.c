#include "sys.h"
#include "delay.h"
#include "led.h"

int main(void)
{  
		u8 flow_dat=0xfe;
    HAL_Init();                    														//初始化HAL库    
    Stm32_Clock_Init(336,8,2,7);  														//设置时钟,168Mhz
		delay_init(168);              													 	//初始化延时函数
		LED_Init();																								//初始化LED	
	
	while(1)
	{
    //shuzu_Led();
		/*int j;
		for(j=0;j<14;j++)
		{
				LED_light(j);
				delay_ms(1000);
		}*/
		kekong_Led(flow_dat,1);
//		kekong_Led(0x7f,0);
//		Flow_Led(flow_dat);
//		kekong_Led_led(0xfc);
		
	}
}





