#include "stm32f10x.h"

int main(void)
{	
	M_SysTick_Init();
	M_USART_Init(USART1, 115200);          //��ʼ������1�����ò�����Ϊ115200
	M_USARTx_NVIC_Configuration(USART1, NVIC_PriorityGroup_0, LEVEL_0, LEVEL_0);  //���ô����ж�
	printf("This is Sender\n");
	printf("Please Input any characters");
	printf("Waiting answer..........\n");
	//�жϴ�������ڡ�stm32f10x_it.c���ļ���
	while(1)
	{		
		//�ȴ��ж�
	} 
}

