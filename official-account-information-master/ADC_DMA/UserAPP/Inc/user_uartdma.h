#ifndef _USER_UARTDMA_H
#define _USER_UARTDMA_H

#include "stm32f1xx.h"
#include "main.h"

#define Max_RecLen 1024*3

typedef struct{
	uint8_t RxBuffer[Max_RecLen];		//DMA���ջ�����
	uint16_t RecDat_len;						//�������ݳ���
	uint32_t Cur_WriteAddr;					//APP��������ַ
	uint16_t BinLen;								//bin�ļ����ݳ���
	uint8_t rec_endFlag;						//�������ݽ��ս�����־
	uint8_t Binrec_endFlag;         //bin�ļ����ս�����־	
	uint16_t	DMA_TIMCNT;							//bin�ļ��·���ʱ������
	
}UserUartDMA_Typedef;

void User_uartdma_Init(void);
void User_uart_Transmit(const char *pData);
void User_uartdma_Transmit(const char *pData);
void User_uartdma_Receive(uint8_t *recData,uint16_t rec_len);

#endif
