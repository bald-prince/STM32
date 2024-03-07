#include "sys.h"
#include "delay.h"
#include "usart.h"
#include "led.h"
#include "key.h"



int main(void)
{
		u8 key;
    HAL_Init();                    	//��ʼ��HAL��    
    Stm32_Clock_Init(336,8,2,7);  	//����ʱ��,168Mhz
		delay_init(168);               	//��ʼ����ʱ����
		LED_Init();											//��ʼ��LED	
    KEY_Init();                     //��ʼ������

	
    while(1)
    {
        key=KEY_Scan(0);            //����ɨ��
				switch(key)
				{				 
					case KEY0_PRES:	
					while(1)
					{
						LED0=0;
						LED1=1;
					}
					case KEY1_PRES:	//ͬʱ����LED0,LED1��ת		
				  while(1)
					{
						LED0=1;
						LED1=0;
					}
				}
        delay_ms(10);
//			key=KEY_Scan(0);            //����ɨ��
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


