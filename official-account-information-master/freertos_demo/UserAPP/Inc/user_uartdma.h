#ifndef _USER_UARTDMA_H
#define _USER_UARTDMA_H

#include "stm32f1xx.h"
#include "main.h"

#define Max_RecLen 1024*3

typedef struct{
	uint8_t RxBuffer[Max_RecLen];		//DMA接收缓冲区
	uint16_t RecDat_len;						//单包数据长度
	uint32_t Cur_WriteAddr;					//APP缓冲区地址
	uint16_t BinLen;								//bin文件数据长度
	uint8_t rec_endFlag;						//单包数据接收结束标志
	uint8_t Binrec_endFlag;         //bin文件接收结束标志	
	uint16_t	DMA_TIMCNT;							//bin文件下发超时计数器
	
}UserUartDMA_Typedef;

void User_uartdma_Init(void);
void User_uart_Transmit(const char *pData);
void User_uartdma_Transmit(const char *pData);
void User_uartdma_Receive(uint8_t *recData,uint16_t rec_len);

#endif
