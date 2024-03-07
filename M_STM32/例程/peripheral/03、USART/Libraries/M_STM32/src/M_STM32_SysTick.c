#include "M_STM32_SysTick.h"

static __IO u32 TimingDelay;
/**
  * @brief  启动系统滴答定时器 SysTick
  * @param  无
  * @retval 无
  * example: M_SysTick_Init()
  */
void M_SysTick_Init(void)
{

	 
	if (SysTick_Config(SystemCoreClock / 1000000))	// 1us中断一次
	{ 
		/* Capture error */ 
		while (1);
	}
		// 关闭滴答定时器  
	SysTick->CTRL &= ~ SysTick_CTRL_ENABLE_Msk;
}

/**
  * @brief   us延时程序,10us为一个单位
  * @param   nTime————延时微秒
  * @retval  无
  */
void M_Delay_us(__IO u32 nTime)
{ 
	TimingDelay = nTime;	

	// 使能滴答定时器  
	SysTick->CTRL |=  SysTick_CTRL_ENABLE_Msk;

	while(TimingDelay != 0);
}

/**
  * @brief  获取节拍程序
  * @param  无
  * @retval 无
  * @attention  在 SysTick 中断函数 SysTick_Handler()调用
  */
void M_TimingDelay_Decrement(void)
{
	if (TimingDelay != 0x00)
	{ 
		TimingDelay--;
	}
}
