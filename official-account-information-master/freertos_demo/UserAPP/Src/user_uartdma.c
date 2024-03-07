#include "user_uartdma.h"
#include "string.h"

extern UART_HandleTypeDef huart1;

UserUartDMA_Typedef UserUartDma;

/******************************************************
* Brief     : ����DMA ��ʼ������ʼ������cubemx����֮��Ĳ���
* Parameter : 
*           : 
* Return    : None.
*******************************************************/
void User_uartdma_Init(void)
{
	//ʧ�ܴ���DMA����
	HAL_UART_DMAStop(&huart1);
	//ʹ�ܴ���1�����ж�
	__HAL_UART_ENABLE_IT(&huart1,UART_IT_RXNE);
	//ʹ�ܴ���1�����ж�
	__HAL_UART_ENABLE_IT(&huart1,UART_IT_IDLE);
	//ʹ�ܴ���DMA����
	HAL_UART_Receive_DMA(&huart1,UserUartDma.RxBuffer,Max_RecLen);
}

/******************************************************
* Brief     : DMA���亯��
* Parameter : 
*           *pData: Ҫ���������
* Return    : None.
*******************************************************/
void User_uartdma_Transmit(const char *pData)
{	
	HAL_UART_Transmit_DMA(&huart1,(uint8_t *)pData,strlen(pData));
}

/******************************************************
* Brief     : ���ڷ��ʹ��亯��
* Parameter : 
*           *pData: Ҫ���������
* Return    : None.
*******************************************************/
void User_uart_Transmit(const char *pData)
{	
	HAL_UART_Transmit(&huart1,(uint8_t *)pData,strlen(pData),1000);
}

/**
  * @brief  DMA���պ���
  * @param  htim TIM Base handle
  * @retval HAL status
  */
void User_uartdma_Receive(uint8_t *recData,uint16_t rec_len)
{
	HAL_UART_Receive_DMA(&huart1,recData,rec_len);
}




