#include "sys.h"
#include "delay.h"
#include "SMG.h"
#include "timer.h"
#include "usart.h"

int main(void)
{ 
	u16 j=0;
	u8 counter_number=12;
	u8 number=0;
	u8 counter=0;
	//u32 number=20163546;
  HAL_Init();                    														//初始化HAL库    
  Stm32_Clock_Init(336,8,2,7);  														//设置时钟,168Mhz
	delay_init(168);																					//初始化延时函数
	SMG_Init();																								//初始化数码管函数
	uart_init(115200);             													//初始化USART
	TIM3_Init(10000-1,8400-1);       												//定时器3初始化，定时器时钟为84M，分频系数为8400-1，

	while(1)
	{
		//DIV(counter);
		//div_number(number);
		//DIV_Number(counter_number);
		SMG_Disp(Disp_Code);
		/*j++;
		if(j==50)
		{
			counter++;
			j=0;
		}
		if(counter==60)
		{
			number=number+1;
			counter=0;
		}
		
		if(number==60)
		{
			counter_number=counter_number+1;
			number=0;
			if(counter_number==24)
				counter_number=0;
		}*/

	}

}

		
			
		

