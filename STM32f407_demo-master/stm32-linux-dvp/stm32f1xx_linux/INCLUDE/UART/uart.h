#ifndef __UART_H
#define __UART_H
#include "../../USER/stm32f10x.h"
#include "../../USER/system_stm32f10x.h"

#define EN_USART1_RX 
#define MAX_BUF_SIZE 200

extern u8 recbuf[MAX_BUF_SIZE];
extern u8 rec_count;

void uart_init(u32 pclk2,u32 bound);
void USART1_Write_Byte(u8 dat);
void USART1_Printf(char *buf);
#endif


