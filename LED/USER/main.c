#include "sys.h"
#include "delay.h"
#include "led.h"

int main(void)
{ 
	HAL_Init();                    														//��ʼ��HAL��    
  Stm32_Clock_Init(336,8,2,7);  														//����ʱ��,168Mhz
	delay_init(168);              													 	//��ʼ����ʱ����
	LED_Init();																								//��ʼ��LED	
	
	while(1)
	{
    LED0=0;
		LED1=1;
		//delay_ms(100);
		//LED0=1;	
	}
}


