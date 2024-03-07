#include "stm32f10x.h"

int main(void)
{
	M_GPIO_Init(C13, GPIO_Mode_Out_PP);    //设置C13引脚为推挽输出
	
	M_TIMx_Init(TIM2, 1000);    //设置TIM2定时器，1000us中断 一次
	M_TIMx_NVIC_Configuration(TIM2, NVIC_PriorityGroup_0, LEVEL_0, LEVEL_0);  //设置中断等级
	M_TIMx_Switch(TIM2, ENABLE);   //使能中断
	
	//中断处理语句在“stm32f10x_it.c”文件中
	while(1)
	{
	
	}
}


