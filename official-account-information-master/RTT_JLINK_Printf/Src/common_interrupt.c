#include "common_interrupt.h"
#include "HLINK_voice.h"
#include "HW_Remote.h"
/**
  * @brief  串口中断回调函数
  *         
  * @param  
  * @param  
  * @retval none
  */
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
	if(huart->Instance==USART1)
	{
			Voice_RecUartCallBack();
	}
	if(huart->Instance==USART2)
	{
			Voice_RecUartCallBack();
	}
}

/**
  * @brief  定时器中断回调函数
  *         
  * @param  
  * @param  
  * @retval none
  */
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
	if(htim->Instance==TIM2)
	{
		
	}
	if(htim->Instance==TIM3)
	{
		
	}
	if(htim->Instance==TIM7)
	{
			Voice_RecTimCallBack(100);
	}
	if(htim->Instance==TIM4)
	{
		RemoteDataTimerCallBack();
	}
}
