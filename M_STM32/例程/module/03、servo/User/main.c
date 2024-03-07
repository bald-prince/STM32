#include "stm32f10x.h"

int main(void)
{
	float Deg = 90;
	
	M_SysTick_Init();
	//A1 --只能用能产生硬件PWM的引脚，引脚定义查询在PWM底层头文件查询
	//Deg--初始角度，单位度
	M_Servo_Init(A1, Deg);  
	
	while(1)
	{ 
		M_Servo_Ctl(A1, Deg);  //控制舵机转向，Deg为转向角度
		M_Delay_ms(100);
		Deg +=1;
		if(Deg == 180)	Deg = 0;
	}
}

