#ifndef __M_STM32_SYSTICK_H
#define __M_STM32_SYSTICK_H

#include "stm32f10x.h"

void M_TimingDelay_Decrement(void);          //用于中断服务函数

void M_SysTick_Init(void);                   //Systick定时器初始化
void M_Delay_us(__IO u32 nTime);             //us定时
#define M_Delay_ms(x) M_Delay_us(1000*x)	 //单位ms      

#endif
