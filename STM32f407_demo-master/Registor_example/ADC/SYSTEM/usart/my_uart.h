#ifndef __MY_UART_H
#define __MY_UART_H
#include "sys.h"

/* ºê */
#define UART1_REC_IT 1
typedef unsigned char u8;
extern u8 Tx_buf[200];
extern u8 Rx_buf[200];

/* º¯ÊýÉêÃ÷ */
void my_uart_init(void);
void uart_Ts_Byte(unsigned char ch);
void uart_print(unsigned char ptr[]);
void uart_Rs_Byte(void);

/* Extern */
int fputc(int ch,FILE *stream);

#endif



