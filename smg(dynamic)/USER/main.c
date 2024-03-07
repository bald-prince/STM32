#include "sys.h"
#include "delay.h"
#include "SMG.h"
#include "usart.h"
#include "timer.h"
#include "led.h"
#include "beep.h"

int main(void)
{ 
	u32 counter_number=99999999;
	u16 i=0;
	HAL_Init();                    														//��ʼ��HAL��    
  Stm32_Clock_Init(336,8,2,7);  														//����ʱ��,168Mhz
	delay_init(168);																					//��ʼ����ʱ����
	SMG_Init();																								//��ʼ������ܺ���
	uart_init(115200);             														//��ʼ��USART
	TIM3_Init(10000-1,8400-1);       													//��ʱ��3��ʼ������ʱ��ʱ��Ϊ84M����Ƶϵ��Ϊ8400-1��
	LED_Init();																								//���Զ�ʱ��3��Ƶ��Ϊ84M/8400=10K���Զ���װ��Ϊ10000-1����ô��ʱ�����ھ���1s
	BEEP_Init();
	
	while(1)
	{
		DIV_number(counter_number);
		SMG_Disp(Disp_Code);
		i++;
		if(i==500)
		{
			counter_number--;
			i=0;
			if(counter_number==-1)
			{
				counter_number=999999999;
			}
		 }
		//SMG_Disp(Disp_Code);
	 }
		
}
