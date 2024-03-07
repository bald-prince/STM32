#include "timer.h"
//////////////////////////////////////////////////////////////////////////////////	 
//本程序只供学习使用，未经作者许可，不得用于其它任何用途
//ALIENTEK STM32F407开发板
//定时器中断驱动代码	   
//正点原子@ALIENTEK
//技术论坛:www.openedv.com
//创建日期:2017/4/7
//版本：V1.0
//版权所有，盗版必究。
//Copyright(C) 广州市星翼电子科技有限公司 2014-2024
//All rights reserved									  
////////////////////////////////////////////////////////////////////////////////// 	
TIM_HandleTypeDef TIM2_Handler;      //定时器2句柄 
TIM_HandleTypeDef TIM3_Handler;      //定时器3句柄 
TIM_HandleTypeDef TIM4_Handler;      //定时器4句柄 
TIM_HandleTypeDef TIM5_Handler;      //定时器5句柄 
TIM_HandleTypeDef TIM7_Handler;      //定时器9句柄 
//通用定时器TIM3中断初始化
//arr：自动重装值。
//psc：时钟预分频数
//定时器溢出时间计算方法:Tout=((arr+1)*(psc+1))/Ft us.
//Ft=定时器工作频率,单位:Mhz
//这里使用的是定时器3!(定时器3挂在APB1上，时钟为APB1clk*2=42*2=84M)
void TIM2_Init(u16 arr,u16 psc)
{  
    TIM2_Handler.Instance=TIM2;                            //通用定时器2
    TIM2_Handler.Init.Prescaler=psc;                       //分频系数
    TIM2_Handler.Init.CounterMode=TIM_COUNTERMODE_UP;      //向上计数器
    TIM2_Handler.Init.Period=arr;                          //自动装载值
    TIM2_Handler.Init.ClockDivision=TIM_CLOCKDIVISION_DIV1;//时钟分频因子
    HAL_TIM_Base_Init(&TIM2_Handler);					   //初始化时基单元
                                                           //
    HAL_TIM_Base_Start_IT(&TIM2_Handler); 				   //使能定时器2和定时器2更新中断：TIM_IT_UPDATE   
}

void TIM3_Init(u16 arr,u16 psc)
{  
    TIM3_Handler.Instance=TIM3;                            //通用定时器3
    TIM3_Handler.Init.Prescaler=psc;                       //分频系数
    TIM3_Handler.Init.CounterMode=TIM_COUNTERMODE_UP;      //向上计数器
    TIM3_Handler.Init.Period=arr;                          //自动装载值
    TIM3_Handler.Init.ClockDivision=TIM_CLOCKDIVISION_DIV1;//时钟分频因子
    HAL_TIM_Base_Init(&TIM3_Handler);					   //初始化时基单元
														   //
    HAL_TIM_Base_Start_IT(&TIM3_Handler); 				   //使能定时器3和定时器3更新中断：TIM_IT_UPDATE   
}

void TIM4_Init(u16 arr,u16 psc)
{  
    TIM4_Handler.Instance=TIM4;                            //通用定时器4
    TIM4_Handler.Init.Prescaler=psc;                       //分频系数
    TIM4_Handler.Init.CounterMode=TIM_COUNTERMODE_UP;      //向上计数器
    TIM4_Handler.Init.Period=arr;                          //自动装载值
    TIM4_Handler.Init.ClockDivision=TIM_CLOCKDIVISION_DIV1;//时钟分频因子
    HAL_TIM_Base_Init(&TIM4_Handler);					   //初始化时基单元
														   //
    HAL_TIM_Base_Start_IT(&TIM4_Handler);				   //使能定时器4和定时器4更新中断：TIM_IT_UPDATE   
}

void TIM5_Init(u16 arr,u16 psc)
{  
    TIM5_Handler.Instance=TIM5;                            //通用定时器5
    TIM5_Handler.Init.Prescaler=psc;                       //分频系数
    TIM5_Handler.Init.CounterMode=TIM_COUNTERMODE_UP;      //向上计数器
    TIM5_Handler.Init.Period=arr;                          //自动装载值
    TIM5_Handler.Init.ClockDivision=TIM_CLOCKDIVISION_DIV1;//时钟分频因子
    HAL_TIM_Base_Init(&TIM5_Handler);					   //初始化时基单元
														   //
    HAL_TIM_Base_Start_IT(&TIM5_Handler); 				   //使能定时器5和定时器5更新中断：TIM_IT_UPDATE   
}

void TIM9_Init(u16 arr,u16 psc)
{  
    TIM7_Handler.Instance=TIM7;                            //通用定时器9
    TIM7_Handler.Init.Prescaler=psc;                       //分频系数
    TIM7_Handler.Init.CounterMode=TIM_COUNTERMODE_UP;      //向上计数器
    TIM7_Handler.Init.Period=arr;                          //自动装载值
    TIM7_Handler.Init.ClockDivision=TIM_CLOCKDIVISION_DIV1;//时钟分频因子
    HAL_TIM_Base_Init(&TIM7_Handler);					   //初始化时基单元
														   //
    HAL_TIM_Base_Start_IT(&TIM7_Handler); 				   //使能定时器9和定时器9更新中断：TIM_IT_UPDATE   
}

//定时器底册驱动，开启时钟，设置中断优先级
//此函数会被HAL_TIM_Base_Init()函数调用
void HAL_TIM_Base_MspInit(TIM_HandleTypeDef *htim)
{
	if(htim->Instance==TIM2)
	{
		__HAL_RCC_TIM2_CLK_ENABLE();            //使能TIM2时钟
		HAL_NVIC_SetPriority(TIM2_IRQn,1,0);    //设置中断优先级，抢占优先级1，子优先级0
		HAL_NVIC_EnableIRQ(TIM2_IRQn);          //开启ITM2中断   
	}
    if(htim->Instance==TIM3)
	{
		__HAL_RCC_TIM3_CLK_ENABLE();            //使能TIM3时钟
		HAL_NVIC_SetPriority(TIM3_IRQn,1,1);    //设置中断优先级，抢占优先级1，子优先级1
		HAL_NVIC_EnableIRQ(TIM3_IRQn);          //开启ITM3中断   
	}
	if(htim->Instance==TIM4)
	{
		__HAL_RCC_TIM4_CLK_ENABLE();            //使能TIM4时钟
		HAL_NVIC_SetPriority(TIM4_IRQn,1,2);    //设置中断优先级，抢占优先级1，子优先级2
		HAL_NVIC_EnableIRQ(TIM4_IRQn);          //开启ITM4中断   
	}
	if(htim->Instance==TIM5)
	{
		__HAL_RCC_TIM5_CLK_ENABLE();            //使能TIM5时钟
		HAL_NVIC_SetPriority(TIM5_IRQn,1,3);    //设置中断优先级，抢占优先级1，子优先级3
		HAL_NVIC_EnableIRQ(TIM5_IRQn);          //开启ITM5中断   
	}
	if(htim->Instance==TIM7)
	{
		__HAL_RCC_TIM9_CLK_ENABLE();            //使能TIM7时钟
		HAL_NVIC_SetPriority(TIM7_IRQn,1,4);    //设置中断优先级，抢占优先级1，子优先级4
		HAL_NVIC_EnableIRQ(TIM7_IRQn);          //开启ITM7中断   
	}
}

void TIM2_IRQHandler(void)
{
	 __HAL_TIM_CLEAR_IT(&TIM2_Handler,TIM_IT_UPDATE);
}

void TIM3_IRQHandler(void)
{
	 __HAL_TIM_CLEAR_IT(&TIM3_Handler,TIM_IT_UPDATE);
}

void TIM4_IRQHandler(void)
{
     __HAL_TIM_CLEAR_IT(&TIM4_Handler,TIM_IT_UPDATE);
}
void TIM5_IRQHandler(void)
{
	 __HAL_TIM_CLEAR_IT(&TIM5_Handler,TIM_IT_UPDATE);
}
void TIM7_IRQHandler(void)
{
	 __HAL_TIM_CLEAR_IT(&TIM9_Handler,TIM_IT_UPDATE);
}
