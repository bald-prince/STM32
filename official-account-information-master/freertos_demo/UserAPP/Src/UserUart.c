#include "UserUart.h"
#include "MyQueue.h"
#include "string.h"
#include "stdio.h"
#include "bsp_iap.h"
#include "bsp_flash.h"
#define useruart_printf_debug

#ifdef useruart_printf_debug

#define uart_printf(format, args...) \
    do                               \
    {                                \
        printf(format, ##args);      \
    } while (0)
#else
#define uart_printf(format, args...) \
    do                               \
    {                                \
    } while (0)
#endif

extern UART_HandleTypeDef huart1;
UART_TXRX_HandleTypeDef UART_TXRX_Para;

SCQueue Q; /*定义一个顺序循环队列*/

void UserUartInit(void)
{
    HAL_UART_Receive_IT(&huart1, &UART_TXRX_Para.RxData, 1);
    InitQueue(&Q); /*初始化顺序循环队列*/
}

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
//    if (huart->Instance == USART1)
//    {
//      EnQueue(&Q, (DataType)UART_TXRX_Para.RxData);
//			
//			if(strAppBin.usLength<APP_FLASH_LEN)
//			{
//				strAppBin.ucDataBuf[strAppBin.usLength++]=UART_TXRX_Para.RxData;
//			}
//    }
//    HAL_UART_Receive_IT(&huart1, &UART_TXRX_Para.RxData, 1);
}

void SCQueue_MessageRecive(void)
{
    uint8_t data_temp1,data_temp2;
		uint16_t data_flash;
		uint32_t app_addr_offset =0;

		app_addr_offset=APP_START_ADDR;
		if(!QueueEmpty(Q))
    {	
			DeQueue(&Q, &data_temp1);
		  //BSP_FLASH_Write(FLASHSIZE_BASE+0x3000,data_temp,1);
      HAL_UART_Transmit(&huart1, &data_temp1, 1, 100);
			
			DeQueue(&Q, &data_temp2);
			//BSP_FLASH_Write(FLASHSIZE_BASE+0x3000,data_temp,1);
      HAL_UART_Transmit(&huart1, &data_temp2, 1, 100);			
			data_flash=data_temp2<<8|data_temp1;
			BSP_FLASH_Write(app_addr_offset,&data_flash,1);
			app_addr_offset++;
    }
}
