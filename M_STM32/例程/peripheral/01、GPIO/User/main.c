#include "stm32f10x.h"

int main(void)
{	
	M_SysTick_Init();                   //Systic时钟初始化
	M_GPIO_Init(C13, GPIO_Mode_Out_PP); //C13,推挽输出
	
	while(1)
	{		
		M_GPIO_Set(C13, LOW);          //输出低电平
		M_Delay_ms(500);                //延时500ms
		M_GPIO_Set(C13, HIGH);         //输出高电平
		M_Delay_ms(500);                //延时500ms
	 } 
}

