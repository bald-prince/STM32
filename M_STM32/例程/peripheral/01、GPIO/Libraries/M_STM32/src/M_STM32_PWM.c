#include "M_STM32_PWM.h"

/**
  * @brief  辨别PWM定时器
  * @param  PTx: 引脚
  * @retval None
  */
TIM_TypeDef* M_TIMx_ID(uint16_t PTx)
{	
	if((PTx == A1) || (PTx == A2) || (PTx == A3)){
		return TIM2;
	}
	else if((PTx == A6) || (PTx == A7) || (PTx == B0) || (PTx == B1)){
		return TIM3;
	}
	else if((PTx == B6) || (PTx == B7) || (PTx == B8) || (PTx == B9)){
		return TIM4;
	}
	else{
		return 0;
	}
}

/**
  * @brief  辨别PWM定时器
  * @param  PTx: 引脚
  * @retval None
  */
  uint16_t M_TIM_Channel_ID(uint16_t PTx)
  {
	  if((PTx == A6) || (PTx == B6)){
		  return TIM_Channel_1;
	  }
	  else if((PTx == A1) || (PTx == A7) || (PTx == B7)){
		  return TIM_Channel_2;
	  }
	  else if((PTx == A2) || (PTx == B0) || (PTx == B8)){
		  return TIM_Channel_3;
	  }
	  else if((PTx == A3) || (PTx == B1) || (PTx == B9)){
		  return TIM_Channel_4;
	  }
	  else{
		  return 0;
	  }
  }
  
/**
  * @brief  设置PWM输出占空比
  * @param  TIMx: TIMx通道
  * @param  Channel_x: 端口
  * @param  Duty: 占空比(0~999)
  * @retval None
  * example: M_PWM_Duty();
  */
void M_PWM_Duty(uint16_t PTx, uint32_t Freq, float Duty)
{
	TIM_TypeDef* TIMx;
	u8           TIM_Channel_x;
	TIMx          = M_TIMx_ID(PTx);        //获取TIMx定时器
	TIM_Channel_x = M_TIM_Channel_ID(PTx); //获取TIMx通道
	
	if(TIM_Channel_x == TIM_Channel_1){
		TIMx->CCR1 = (uint16_t)((1.0/Freq)*1000000*(Duty/100.0));
	}
	else if(TIM_Channel_x == TIM_Channel_2){
		TIMx->CCR2 = (uint16_t)((1.0/Freq)*1000000*(Duty/100.0));
	}
	else if(TIM_Channel_x == TIM_Channel_3){
		TIMx->CCR3 = (uint16_t)((1.0/Freq)*1000000*(Duty/100.0));
	}
	else if(TIM_Channel_x == TIM_Channel_4){
		TIMx->CCR4 = (uint16_t)((1.0/Freq)*1000000*(Duty/100.0));
	}
}

/**
  * @brief  PWM工作方式配置
  * @param  TIMx: TIMx通道
  * @param  Channel_x: 端口
  * @param  Duty: 占空比(0~100)
  * @retval None
  */
void M_PWM_Config(TIM_TypeDef* TIMx, u8 TIM_Channel_x, uint32_t Freq, float Duty)
{
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	TIM_OCInitTypeDef        TIM_OCInitStructure;
	
	/* 设置TIMxCLK 为 72MHZ */
	if(TIMx == TIM2)			RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);
	else if(TIMx == TIM3)		RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);
	else if(TIMx == TIM4)		RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE);

	/* Time base configuration */
	TIM_TimeBaseStructure.TIM_Period = (uint16_t)((1.0/Freq)*1000000-1);   //周期计算
  	TIM_TimeBaseStructure.TIM_Prescaler = 71;	    //设置预分频,公式72MHz/prescaler+1MHz
  	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1 ;	//设置时钟分频系数：不分频(这里用不到)
  	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //向上计数模式
	TIM_TimeBaseInit(TIMx, &TIM_TimeBaseStructure);

	/* PWM1 Mode configuration: TIM_Channel_x */
  	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;	    //配置为PWM模式1
  	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;	
  	TIM_OCInitStructure.TIM_Pulse = (uint16_t)((1.0/Freq)*1000000*(Duty/100.0));	   //设置跳变值，当计数器计数到这个值时，电平发生跳变
  	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;  //当定时器计数值小于CCR1_Val时为高电平
	if(TIM_Channel_x == TIM_Channel_1){
		TIM_OC1Init(TIMx, &TIM_OCInitStructure);	 //使能通道1
  		TIM_OC1PreloadConfig(TIMx, TIM_OCPreload_Enable);
	}
	else if(TIM_Channel_x == TIM_Channel_2){
		TIM_OC2Init(TIMx, &TIM_OCInitStructure);	 //使能通道2
  		TIM_OC2PreloadConfig(TIMx, TIM_OCPreload_Enable);
	}
	else if(TIM_Channel_x == TIM_Channel_3){
		TIM_OC3Init(TIMx, &TIM_OCInitStructure);	 //使能通道3
  		TIM_OC3PreloadConfig(TIMx, TIM_OCPreload_Enable);
	}
	else if(TIM_Channel_x == TIM_Channel_4){
		TIM_OC4Init(TIMx, &TIM_OCInitStructure);	 //使能通道4
  		TIM_OC4PreloadConfig(TIMx, TIM_OCPreload_Enable);
	}

	TIM_ARRPreloadConfig(TIMx, ENABLE);			 // 使能TIMx重载寄存器ARR

  	/* TIMx enable counter */
  	TIM_Cmd(TIMx, ENABLE);                   //使能定时器x	
}

/**
  * @brief  PWM输出初始化
  * @param  Px: GPIO口
  * @param  TIMx: TIMx通道
  * @param  TIM_Channel_x: 端口
  * @param  Freq  频率
  * @param  Duty: 占空比
  * @retval None
  */
void M_PWM_Init(uint16_t PTx,  uint32_t Freq, float Duty)
{	
	TIM_TypeDef* TIMx;
	u8           TIM_Channel_x;
	TIMx          = M_TIMx_ID(PTx);        //获取TIMx定时器
	TIM_Channel_x = M_TIM_Channel_ID(PTx); //获取TIMx通道

	M_GPIO_Init(PTx, GPIO_Mode_AF_PP);
	M_PWM_Config(TIMx, TIM_Channel_x, Freq, Duty);
}
