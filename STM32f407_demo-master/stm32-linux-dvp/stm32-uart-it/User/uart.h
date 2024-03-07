#ifndef __UART_H
#define __UART_H
#include "sys.h"

/* buf */
#define BUF_LEN 128
extern u32 BUF_CT;
extern u8 USART_Rx_Buf[BUF_LEN];

/* extern */
void Uart_Init(u32 boundrate);
u8 USART_Tx_Byte(u8 ch);
void USART_Tx_String(char* str);
u8 USART_Rx();

#endif
