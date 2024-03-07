#include "sys.h"
#include "delay.h"
#include "usart.h"
#include "led.h"

int main(void)
{ 
    HAL_Init();                    														//��ʼ��HAL��    
    Stm32_Clock_Init(336,8,2,7);  														//����ʱ��,168Mhz
		delay_init(168);              													 	//��ʼ����ʱ����
		LED_Init();																								//��ʼ��LED	
	
	while(1)
	{
        HAL_GPIO_WritePin(GPIOC,GPIO_PIN_0,GPIO_PIN_RESET); 	//LED0��Ӧ����PC0���ͣ�������ͬ��LED0(0)
        delay_ms(1000);																				//��ʱ1000ms
        HAL_GPIO_WritePin(GPIOC,GPIO_PIN_0,GPIO_PIN_SET);   	//LED0��Ӧ����PC0���ߣ��𣬵�ͬ��LED0(1)
        delay_ms(1000);                                      	//��ʱ1000ms 
	}
}





