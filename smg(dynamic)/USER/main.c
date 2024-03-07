#include "sys.h"
#include "delay.h"
#include "SMG.h"
#include "usart.h"
#include "timer.h"
#include "led.h"
#include "beep.h"

int main(void)
{ 
	u32 counter_number=99999999;
	u16 i=0;
	HAL_Init();                    														//初始化HAL库    
  Stm32_Clock_Init(336,8,2,7);  														//设置时钟,168Mhz
	delay_init(168);																					//初始化延时函数
	SMG_Init();																								//初始化数码管函数
	uart_init(115200);             														//初始化USART
	TIM3_Init(10000-1,8400-1);       													//定时器3初始化，定时器时钟为84M，分频系数为8400-1，
	LED_Init();																								//所以定时器3的频率为84M/8400=10K，自动重装载为10000-1，那么定时器周期就是1s
	BEEP_Init();
	
	while(1)
	{
		DIV_number(counter_number);
		SMG_Disp(Disp_Code);
		i++;
		if(i==500)
		{
			counter_number--;
			i=0;
			if(counter_number==-1)
			{
				counter_number=999999999;
			}
		 }
		//SMG_Disp(Disp_Code);
	 }
		
}
