#include "common_interrupt.h"
#include "HLINK_voice.h"

/**
  * @brief  �����жϻص�����
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
	else if(huart->Instance==USART2)
	{
			Voice_RecUartCallBack();
	}
}

/**
  * @brief  ��ʱ���жϻص�����
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
	else if(htim->Instance==TIM3)
	{
		
	}
	else if(htim->Instance==TIM7)
	{
			Voice_RecTimCallBack(100);
	}
}
