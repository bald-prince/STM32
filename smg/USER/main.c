#include "sys.h"
#include "delay.h"
#include "SMG.h"
#include "timer.h"
#include "usart.h"

int main(void)
{ 
	u16 j=0;
	u8 counter_number=12;
	u8 number=0;
	u8 counter=0;
	//u32 number=20163546;
  HAL_Init();                    														//��ʼ��HAL��    
  Stm32_Clock_Init(336,8,2,7);  														//����ʱ��,168Mhz
	delay_init(168);																					//��ʼ����ʱ����
	SMG_Init();																								//��ʼ������ܺ���
	uart_init(115200);             													//��ʼ��USART
	TIM3_Init(10000-1,8400-1);       												//��ʱ��3��ʼ������ʱ��ʱ��Ϊ84M����Ƶϵ��Ϊ8400-1��

	while(1)
	{
		//DIV(counter);
		//div_number(number);
		//DIV_Number(counter_number);
		SMG_Disp(Disp_Code);
		/*j++;
		if(j==50)
		{
			counter++;
			j=0;
		}
		if(counter==60)
		{
			number=number+1;
			counter=0;
		}
		
		if(number==60)
		{
			counter_number=counter_number+1;
			number=0;
			if(counter_number==24)
				counter_number=0;
		}*/

	}

}

		
			
		

