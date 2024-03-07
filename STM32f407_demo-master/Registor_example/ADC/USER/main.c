#include "sys.h"
#include "delay.h"
#include "my_uart.h"
#include "led.h"
#include "my_adc.h"
#include "my_dac.h"

#define ABS(num) (num>0? num:(-num)) 
/* globle val */
float get_val = 0;
/**************/
int main(void)
{
  HAL_Init();                    	
  Stm32_Clock_Init(336,8,2,7); 
	delay_init(168);	
	led_reg_init();
	my_uart_init();
	MY_ADC_Init();
	MY_DAC_Init();
	while(1)
	{
		led_flow();/* 流水灯检测系统运行 */
		DAC_OUT(1.5);
		get_val = Get_Average_Adc(2500);
		printf("采样值:%0.3f  DAC输出值:%0.3f  误差：%0.3f\n",get_val,1.50,ABS((get_val-1.50)));
	}
}









