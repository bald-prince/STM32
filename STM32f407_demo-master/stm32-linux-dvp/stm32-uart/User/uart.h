#ifndef __UART_H
#define __UART_H
#include "sys.h"

/* extern */
void Uart_Init(u32 boundrate);
u8 USART_Tx_Byte(u8 ch);
void USART_Tx_String(char* str);

#endif
