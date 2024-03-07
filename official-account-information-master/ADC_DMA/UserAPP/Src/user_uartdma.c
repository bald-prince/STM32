#include "user_uartdma.h"
#include "string.h"

extern UART_HandleTypeDef huart1;

UserUartDMA_Typedef UserUartDma;

/******************************************************
* Brief     : 串口DMA 初始化，初始化除了cubemx配置之外的部分
* Parameter : 
*           : 
* Return    : None.
*******************************************************/
void User_uartdma_Init(void)
{
	//失能串口DMA传输
	HAL_UART_DMAStop(&huart1);
	//使能串口1接收中断
	__HAL_UART_ENABLE_IT(&huart1,UART_IT_RXNE);
	//使能串口1空闲中断
	__HAL_UART_ENABLE_IT(&huart1,UART_IT_IDLE);
	//使能串口DMA接收
	HAL_UART_Receive_DMA(&huart1,UserUartDma.RxBuffer,Max_RecLen);
}

/******************************************************
* Brief     : DMA传输函数
* Parameter : 
*           *pData: 要传输的数据
* Return    : None.
*******************************************************/
void User_uartdma_Transmit(const char *pData)
{	
	HAL_UART_Transmit_DMA(&huart1,(uint8_t *)pData,strlen(pData));
}

/******************************************************
* Brief     : 串口发送传输函数
* Parameter : 
*           *pData: 要传输的数据
* Return    : None.
*******************************************************/
void User_uart_Transmit(const char *pData)
{	
	HAL_UART_Transmit(&huart1,(uint8_t *)pData,strlen(pData),1000);
}

/**
  * @brief  DMA接收函数
  * @param  htim TIM Base handle
  * @retval HAL status
  */
void User_uartdma_Receive(uint8_t *recData,uint16_t rec_len)
{
	HAL_UART_Receive_DMA(&huart1,recData,rec_len);
}




