#include "stm32f10x.h"

int main(void)
{	
	M_SysTick_Init();                   //Systicʱ�ӳ�ʼ��
	M_GPIO_Init(C13, GPIO_Mode_Out_PP); //C13,�������
	
	while(1)
	{		
		M_GPIO_Set(C13, LOW);          //����͵�ƽ
		M_Delay_ms(500);                //��ʱ500ms
		M_GPIO_Set(C13, HIGH);         //����ߵ�ƽ
		M_Delay_ms(500);                //��ʱ500ms
	 } 
}

