#include "exti.h"
#include "delay.h"
#include "led.h"
#include "key.h"
//#include "oled.h"
#include "usart.h"
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
    __HAL_RCC_GPIOG_CLK_ENABLE();               //开启GPIOH时钟
    
    GPIO_Initure.Pin=GPIO_PIN_0;                //PA0
    GPIO_Initure.Mode=GPIO_MODE_IT_RISING;      //上升沿触发
    GPIO_Initure.Pull=GPIO_PULLDOWN;
    HAL_GPIO_Init(GPIOA,&GPIO_Initure);
    
    GPIO_Initure.Pin=GPIO_PIN_9;               //PG9
    GPIO_Initure.Mode=GPIO_MODE_IT_FALLING;     //下降沿触发
    GPIO_Initure.Pull=GPIO_PULLUP;
    HAL_GPIO_Init(GPIOG,&GPIO_Initure);
    
    GPIO_Initure.Pin=GPIO_PIN_10|GPIO_PIN_11|GPIO_PIN_13;     //PG11,10
    HAL_GPIO_Init(GPIOG,&GPIO_Initure);
    
    //中断线0-PA0
    HAL_NVIC_SetPriority(EXTI0_IRQn,2,0);       //抢占优先级为2，子优先级为0
    HAL_NVIC_EnableIRQ(EXTI0_IRQn);             //使能中断线0
    
    //中断线2-PG9
    HAL_NVIC_SetPriority(EXTI9_5_IRQn,2,1);       //抢占优先级为2，子优先级为1
    HAL_NVIC_EnableIRQ(EXTI9_5_IRQn);             //使能中断线2
    
    //中断线3-PG10
    HAL_NVIC_SetPriority(EXTI15_10_IRQn,2,2);       //抢占优先级为2，子优先级为2
    HAL_NVIC_EnableIRQ(EXTI15_10_IRQn);             //使能中断线2*/
    
  //中断线13-PG11
  HAL_NVIC_SetPriority(EXTI15_10_IRQn,2,3);   //抢占优先级为2，子优先级为3
  HAL_NVIC_EnableIRQ(EXTI15_10_IRQn);         //使能中断线13  
}


//中断服务函数
void EXTI0_IRQHandler(void)
{
	
	delay_ms(3);
	__HAL_GPIO_EXTI_CLEAR_IT(GPIO_PIN_0);
  key_buf = 1;
	
		
}

void EXTI9_5_IRQHandler(void)
{
	delay_ms(3);
	__HAL_GPIO_EXTI_CLEAR_IT(GPIO_PIN_9);
	if(KEY0==0)
		{
           key_buf = 2;        
            }
}

void EXTI15_10_IRQHandler(void)
{
	__HAL_GPIO_EXTI_CLEAR_IT(GPIO_PIN_10|GPIO_PIN_11);
	delay_ms(3);
	if(KEY1 == 0)
		{
        key_buf = 3;    
            }
	if(KEY2 == 0)
		{
				key_buf = 4; 
            }
}
/*
void EXTI15_10_IRQHandler(void)
{
    HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_11);//调用中断处理公用函数
}
*/
//中断服务程序中需要做的事情
//在HAL库中所有的外部中断服务函数都会调用此函数
//GPIO_Pin:中断引脚号
/*void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
    delay_ms(100);      //消抖
    switch(GPIO_Pin)
    {
        case GPIO_PIN_0:
            //if(WK_UP==1) 
            {
				LED1=!LED1;//控制LED0,LED1互斥点亮
				LED0=!LED1;
            }
            break;
        case GPIO_PIN_9:
            if(Key1==0)  //LED1翻转
            {
                LED1=!LED1;    
            }
            break;
        case GPIO_PIN_10:
            if(Key2==0)  //同时控制LED0,LED1翻转 
            {
                LED0=!LED0;
				        LED1=!LED1;
            }
            break;

        case GPIO_PIN_11:
            if(Key3==0)  
            {
				LED0=!LED0;//控制LED0翻转
            }
            break;
    }
}*/
