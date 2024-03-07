#include "led.h"
//////////////////////////////////////////////////////////////////////////////////	 
//本程序只供学习使用，未经作者许可，不得用于其它任何用途
//ALIENTEK战舰STM32开发板V3
//LED驱动代码	   
//正点原子@ALIENTEK
//技术论坛:www.openedv.com
//创建日期:2015/1/9
//版本：V1.0
//版权所有，盗版必究。
//Copyright(C) 广州市星翼电子科技有限公司 2009-2019
//All rights reserved									  
////////////////////////////////////////////////////////////////////////////////// 

//初始化PB5和PE5为输出口.并使能这两个口的时钟		    
//LED IO初始化
void LED_Init(void)
{
	RCC->APB2ENR |= (0x1<<2); // GPIOA 时钟使能
	
	GPIOA->CRL |= (0x3<<4);   // GPIOA_IO1 OUT MODE
	GPIOA->CRL &= (~(0x3<<6));  // GPIOA_IO1 PULL OUT
	
	GPIOA->ODR |= (~(0x1<<1));   // led on
}

void LED_FLASH(void)
{
	if (GPIOA->ODR & (0x1<<1))
		GPIOA->ODR &= (~(0x1<<1));
	else
		GPIOA->ODR |=  (0x1<<1);
}






