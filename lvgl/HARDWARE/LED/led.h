#ifndef _LED_H
#define _LED_H
#include "sys.h"
//////////////////////////////////////////////////////////////////////////////////	 
//本程序只供学习使用，未经作者许可，不得用于其它任何用途
//ALIENTEK STM32F407开发板
//LED驱动代码	   
//正点原子@ALIENTEK
//技术论坛:www.openedv.com
//创建日期:2015/9/7
//版本：V1.0
//版权所有，盗版必究。
//Copyright(C) 广州市星翼电子科技有限公司 2014-2024
//All rights reserved									  
////////////////////////////////////////////////////////////////////////////////// 	

//LED端口定义
#define LED0 PCout(0)
#define LED1 PCout(1)
#define LED2 PCout(2)
#define LED3 PCout(3)
#define LED4 PCout(4)
#define LED5 PCout(5)
#define LED6 PCout(6)
#define LED7 PCout(7) 

void LED_Init(void);
#endif
