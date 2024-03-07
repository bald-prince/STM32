#include "exti.h"
#include "delay.h"
#include "led.h"
#include "key.h"


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
    HAL_NVIC_SetPriority(EXTI9_5_IRQn,2,1);       //抢占优先级为2，子优先级为1
    HAL_NVIC_EnableIRQ(EXTI9_5_IRQn);             //使能中断线2
    
    //中断线3-PG11
    HAL_NVIC_SetPriority(EXTI15_10_IRQn,2,2);       //抢占优先级为2，子优先级为2
    HAL_NVIC_EnableIRQ(EXTI15_10_IRQn);             //使能中断线2
}


//中断服务函数
void EXTI0_IRQHandler(void)
{
    HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_0);			//调用中断处理公用函数
		
}

void EXTI9_5_IRQHandler(void)
{
    HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_9);		//调用中断处理公用函数
	 
}

void EXTI15_10_IRQHandler(void)
{
    HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_13);		//调用中断处理公用函数
		HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_11);		//调用中断处理公用函数
		HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_10);		//调用中断处理公用函数
}


//中断服务程序中需要做的事情
//在HAL库中所有的外部中断服务函数都会调用此函数
//GPIO_Pin:中断引脚号
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
	delay_ms(10);      									//消抖
  switch(GPIO_Pin)
  {
		case GPIO_PIN_0:
			if(WEKEUP==1) 
      {
				L1=0;					//控制LED0,LED1互斥点亮
				L0=1;
      }
    break;
    case GPIO_PIN_10:
			if(KEY2==0)  						
      {
				L1=1; 
				L0=0;
      }
    break;
  }
}
