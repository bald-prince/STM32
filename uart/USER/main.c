#include "sys.h"
#include "delay.h"
#include "my_uart.h"
#include "led.h"

int main(void)
{
  HAL_Init();                    	
  Stm32_Clock_Init(336,8,2,7); 
	delay_init(168);	
	led_reg_init();
	my_uart_init();
	
	while(1)
	{
		//if(USART1->SR&(1<<5))
		uart_Rs_Byte();
		//else
		//led_flow();/* 流水灯检测系统运行 */
	}
	
}









