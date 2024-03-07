#include "exti.h"
#include "delay.h"
#include "key.h"
#include "SMG.h"


//外部中断初始化
void EXTI_Init(void)
{
    GPIO_InitTypeDef GPIO_Initure;
    
    __HAL_RCC_GPIOG_CLK_ENABLE();              														 //开启GPIOG时钟
		__HAL_RCC_GPIOA_CLK_ENABLE();
   
		GPIO_Initure.Pin=GPIO_PIN_0; 
		GPIO_Initure.Mode=GPIO_MODE_IT_RISING;
		GPIO_Initure.Pull=GPIO_PULLDOWN; 
		HAL_GPIO_Init(GPIOA,&GPIO_Initure);
	
    GPIO_Initure.Pin=GPIO_PIN_9|GPIO_PIN_10|GPIO_PIN_11|GPIO_PIN_13; 			//PG9,10,11,13
    GPIO_Initure.Mode=GPIO_MODE_IT_FALLING;    						 								//下降沿触发
    GPIO_Initure.Pull=GPIO_PULLUP;    																		//下拉
    HAL_GPIO_Init(GPIOG,&GPIO_Initure);
    
    //中断线0-PG9
    HAL_NVIC_SetPriority(EXTI0_IRQn,2,0);       //抢占优先级为2，子优先级为0
    HAL_NVIC_EnableIRQ(EXTI0_IRQn);             //使能中断线0
    
    //中断线2-PG10
    HAL_NVIC_SetPriority(EXTI2_IRQn,2,1);       //抢占优先级为2，子优先级为1
    HAL_NVIC_EnableIRQ(EXTI2_IRQn);             //使能中断线2
    
    //中断线3-PG11
    HAL_NVIC_SetPriority(EXTI3_IRQn,2,2);       //抢占优先级为2，子优先级为2
    HAL_NVIC_EnableIRQ(EXTI3_IRQn);             //使能中断线2
    
    //中断线4-PG13
    HAL_NVIC_SetPriority(EXTI4_IRQn,2,3);   		//抢占优先级为2，子优先级为3
    HAL_NVIC_EnableIRQ(EXTI4_IRQn);         		//使能中断线4
}


//中断服务函数
void EXTI0_IRQHandler(void)
{
    HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_0);			//调用中断处理公用函数
		
}

void EXTI2_IRQHandler(void)
{
    HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_10);		//调用中断处理公用函数
	 
}

void EXTI3_IRQHandler(void)
{
    HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_11);		//调用中断处理公用函数
	  
}

void EXTI4_IRQHandler(void)
{
    HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_13);		//调用中断处理公用函数
		
}


//中断服务程序中需要做的事情
//在HAL库中所有的外部中断服务函数都会调用此函数
//GPIO_Pin:中断引脚号
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{   
		u32 counter=99999999;
    delay_ms(10);      									//消抖
    switch(GPIO_Pin)
    {
        case GPIO_PIN_13:
        if(KEY0==0)  
        {
					DIV_number(counter);
					SMG_Disp(Disp_Code);						//控制LED0翻转
        }
        break;
    }
}
