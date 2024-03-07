#include "sys.h"
#include "delay.h"
#include "usart.h"
#include "led.h"

int main(void)
{
  HAL_Init();                    	
  Stm32_Clock_Init(336,8,2,7);  	
	delay_init(168);	
	uart_init(115200);
	Led_Init();
	while(1)
	{
		
	}
		
}






