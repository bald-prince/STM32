#include "sys.h"
#include "delay.h"
#include "SMG.h"

int main(void)
{ 
	u16 j=0;
	//u32 counter_number=12345678;
	//u32 number=20163546;
  HAL_Init();                    														//��ʼ��HAL��    
  Stm32_Clock_Init(336,8,2,7);  														//����ʱ��,168Mhz
	delay_init(168);																					//��ʼ����ʱ����
	SMG_Init();																								//��ʼ������ܺ���

	while(1)
	{
		//DIV_number(counter_number);
		SMG_Disp(Disp_Code);
		j++;
		if(j==3000)
		{
			//DIV_number(counter_number);
		  SMG(Disp_Code);
			//DIV_number(number);
			while(1)
			{
				SMG_Disp(Code);
				j=0;
			}
		}
	}
}
