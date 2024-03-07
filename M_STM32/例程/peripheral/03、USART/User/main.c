#include "stm32f10x.h"

int main(void)
{	
	M_SysTick_Init();
	M_USART_Init(USART1, 115200);          //初始化串口1，设置波特率为115200
	M_USARTx_NVIC_Configuration(USART1, NVIC_PriorityGroup_0, LEVEL_0, LEVEL_0);  //配置串口中断
	printf("This is Sender\n");
	printf("Please Input any characters");
	printf("Waiting answer..........\n");
	//中断处理语句在“stm32f10x_it.c”文件中
	while(1)
	{		
		//等待中断
	} 
}

