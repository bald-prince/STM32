#include "sys.h"
#include "delay.h"
#include "my_uart.h"
#include "led.h"
#include "my_dac.h"


int main(void)
{
  HAL_Init();                    	
  Stm32_Clock_Init(336,8,2,7); 
	delay_init(168);	
	led_reg_init();
	my_uart_init();
	MY_DAC_Init();
	while(1)
	{
		led_flow();/* 流水灯检测系统运行 */
		DAC_OUT(1.3);
	}
}









