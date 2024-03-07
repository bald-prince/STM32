#include "M_STM32_Timer.h"


/**
  * @brief  配置TIM中断
  * @param  TIMx: TIMx通道
  * @param  NVIC_PriorityGroup_x: 终端组别
  * @param  Pre_LEVEL_x：抢占优先级
  * @param  Sub_LEVEL_x：响应优先级
  * @retval None
  * example:M_TIMx_NVIC_Configuration(TIM1, NVIC_PriorityGroup_0, LEVEL_0, LEVEL_0);
  */
void M_TIMx_NVIC_Configuration(TIM_TypeDef* TIMx, uint32_t NVIC_PriorityGroup_x, uint8_t Pre_LEVEL_x, uint8_t Sub_LEVEL_x)
{
	NVIC_InitTypeDef NVIC_InitStructure;

	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_x);
    //选用TIMx通道
    if(TIMx == TIM1)        NVIC_InitStructure.NVIC_IRQChannel = TIM1_UP_IRQn;
    else if(TIMx == TIM2)   NVIC_InitStructure.NVIC_IRQChannel = TIM2_IRQn;
    else if(TIMx == TIM3)   NVIC_InitStructure.NVIC_IRQChannel = TIM3_IRQn;
    else if(TIMx == TIM4)   NVIC_InitStructure.NVIC_IRQChannel = TIM4_IRQn;
	
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = Pre_LEVEL_x;			//选择抢占优先级
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = Sub_LEVEL_x;				//先择响应优先级
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;								//使能中断
	NVIC_Init(&NVIC_InitStructure);
}

/**
  * @brief  TIMx通道初始化
  * @param  TIMx:   TIMx通道x[1,2,3,4]
  * @param  CK_time:定时器进入中断时间间隔(0~65535)
  * @retval None
  * example: M_TIMx_Init(TIM1, 1000); 
  */
void M_TIMx_Init(TIM_TypeDef* TIMx, u16 CK_time)
{
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	
	// 开启TIMx_CLK,x[1,2,3,4],即内部时钟CK_INT=72M
	if(TIMx == TIM1)			RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1, ENABLE);
	else if(TIMx == TIM2)		RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);
	else if(TIMx == TIM3)		RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);
    else if(TIMx == TIM4)       RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE);
	
	// 自动重装载寄存器周的值(计数值)
    TIM_TimeBaseStructure.TIM_Period=CK_time;
    // 时钟预分频数为71，则驱动计数器的时钟CK_CNT = CK_INT / (71+1)=1M
    TIM_TimeBaseStructure.TIM_Prescaler= 71;
    // 计数器计数模式，设置为向上计数
    TIM_TimeBaseStructure.TIM_CounterMode=TIM_CounterMode_Up;
    // 初始化定时器TIMx, x[1,2,3,4]
    TIM_TimeBaseInit(TIMx, &TIM_TimeBaseStructure);
    // 清除计数器中断标志位
    TIM_ClearFlag(TIMx, TIM_FLAG_Update);
	  
	// 开启计数器中断
    TIM_ITConfig(TIMx,TIM_IT_Update,ENABLE);
		
	// 使能计数器
    TIM_Cmd(TIMx, ENABLE);

    // 暂时关闭TIMx,x[1,2,3,4]的时钟，等待使用
    if(TIMx == TIM1)			RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1, DISABLE);
  	else if(TIMx == TIM2)		RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, DISABLE);
  	else if(TIMx == TIM3)		RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, DISABLE);
    else if(TIMx == TIM4)       RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, DISABLE);
}

/**
  * @brief  TIMx中断开关
  * @param  TIMx:     TIMx通道
  * @param  NewState: 开启或关闭(ENABLE、DISABLE)
  * @retval None
  * example: M_TIMx_Switch(TIM1, ENABLE);
  */
void M_TIMx_Switch(TIM_TypeDef* TIMx, FunctionalState NewState)
{
	if(TIMx == TIM1)				RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1, NewState);
	else if(TIMx == TIM2)			RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, NewState);
	else if(TIMx == TIM3)			RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, NewState);
    else if(TIMx == TIM4)           RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, NewState);
}
