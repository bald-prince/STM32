#include "stm32f10x.h"
#include "M_STM32_USART.h"

int main(void)
{	
	
	M_USART_Init(USART1,9600); //USART初始化
	M_USARTx_NVIC_Configuration(USART1,NVIC_PriorityGroup_0,LEVEL_0,LEVEL_1);
	
	while(1)
	{
		

		if(USART_GetFlagStatus(USART1, 1) == RESET)
		USART_SendString(USART1,"进入调试模式!\n");
		
		
			
		}
}

