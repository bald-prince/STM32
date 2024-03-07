#include "exti.h"

//////////////////////////////////////////////////////////////////////////////////	 
//本程序只供学习使用，未经作者许可，不得用于其它任何用途
//ALIENTEK STM32F429开发板
//外部中断驱动代码	   
//正点原子@ALIENTEK
//技术论坛:www.openedv.com
//创建日期:2016/1/5
//版本：V1.0
//版权所有，盗版必究。
//Copyright(C) 广州市星翼电子科技有限公司 2014-2024
//All rights reserved									  
////////////////////////////////////////////////////////////////////////////////// 	
//外部中断初始化
void EXTI_Init(void)
{
    GPIO_InitTypeDef GPIO_Initure;
    
    __HAL_RCC_GPIOA_CLK_ENABLE();               //开启GPIOA时钟
    __HAL_RCC_GPIOG_CLK_ENABLE();               //开启GPIOG时钟
    
    GPIO_Initure.Pin=GPIO_PIN_0;                //PA0
    GPIO_Initure.Mode=GPIO_MODE_IT_RISING;      //上升沿触发
    GPIO_Initure.Pull=GPIO_PULLDOWN;
    HAL_GPIO_Init(GPIOA,&GPIO_Initure);
    
    GPIO_Initure.Pin=GPIO_PIN_9;                //PG9
    GPIO_Initure.Mode=GPIO_MODE_IT_FALLING;     //下降沿触发
    GPIO_Initure.Pull=GPIO_PULLUP;
    HAL_GPIO_Init(GPIOG,&GPIO_Initure);
    
    GPIO_Initure.Pin=GPIO_PIN_10|GPIO_PIN_11|GPIO_PIN_13;     //PG13,11,10
    HAL_GPIO_Init(GPIOG,&GPIO_Initure);
    
    //中断线0-PA0
    HAL_NVIC_SetPriority(EXTI0_IRQn,2,0);       	  //抢占优先级为2，子优先级为0
    HAL_NVIC_EnableIRQ(EXTI0_IRQn);            	    //使能中断线0
    
    
	  //中断线2-PG9
    HAL_NVIC_SetPriority(EXTI9_5_IRQn,2,1);         //抢占优先级为2，子优先级为1
    HAL_NVIC_EnableIRQ(EXTI9_5_IRQn);               //使能中断线2
    
    //中断线3-PG10,11,13
    HAL_NVIC_SetPriority(EXTI15_10_IRQn,2,2);       //抢占优先级为2，子优先级为2
    HAL_NVIC_EnableIRQ(EXTI15_10_IRQn);             //使能中断线2
}


//中断服务函数
void EXTI0_IRQHandler(void)
{
	__HAL_GPIO_EXTI_CLEAR_IT(GPIO_PIN_0);	
}

void EXTI9_5_IRQHandler(void)
{
	__HAL_GPIO_EXTI_CLEAR_IT(GPIO_PIN_9);
}

void EXTI15_10_IRQHandler(void)
{
	__HAL_GPIO_EXTI_CLEAR_IT(GPIO_PIN_10|GPIO_PIN_11|GPIO_PIN_13);
}


