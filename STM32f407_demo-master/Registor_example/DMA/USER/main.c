#include "sys.h"
#include "delay.h"
#include "led.h"
#include "my_uart.h"
#include "my_dma.h"
#include "string.h"

/* extern */
void fill_caches(void);

int main(void)
{
  HAL_Init();                    	
  Stm32_Clock_Init(336,8,2,7);  
	delay_init(168);	
	led_reg_init();
	my_uart_init();
	DMA_Init((u32)Caches,(u32)&(USART1->DR),DATE_SIZE);
	fill_caches();
	DMA_TX();
	while(1)
	{
		led_flow();/* Á÷Ë®µÆ */
	}
}

void fill_caches(void)
{
	int i;
	for(i=0;i<720;i++)
		strcat((char*)Caches,"12345678\n");
}








