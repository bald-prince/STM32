#include "sys.h"
#include "delay.h"
#include "usart.h"
#include "led.h"
#include "key.h"
#include "timer.h"


int main(void)
{
    HAL_Init();                   	//��ʼ��HAL��    
    Stm32_Clock_Init(336,8,2,7);  	//����ʱ��,168Mhz
		delay_init(168);               	//��ʼ����ʱ����
		uart_init(115200);             	//��ʼ��USART
		LED_Init();											//��ʼ��LED	
    KEY_Init();                    	//��ʼ������
    TIM3_Init(10000-1,8400-1);      //��ʱ��3��ʼ������ʱ��ʱ��Ϊ84M����Ƶϵ��Ϊ8400-1��
                                    //���Զ�ʱ��3��Ƶ��Ϊ84M/8400=10K���Զ���װ��Ϊ10000-1����ô��ʱ�����ھ���1s
    while(1)
    {
        LED0=!LED0;                 //LED0��ת
				delay_ms(500);
    }
}

