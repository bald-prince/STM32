#include "stm32f10x.h"

int main(void)
{	
	M_SysTick_Init();
	M_PWM_Init(A1, 10000, 50);   //设置A1引脚PWM输出，频率为10000Hz，占空比为50%
	//其他可用PWM引脚在底层头文件中查询
	
	while(1)
	{ 
		
	}
}

