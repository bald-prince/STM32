/*
 * @Author: your name
 * @Date: 2021-05-24 16:54:39
 * @LastEditTime: 2021-05-24 17:52:23
 * @LastEditors: Please set LastEditors
 * @Description: In User Settings Edit;
 * @FilePath: \MDK-ARMf:\STM32_Display\UART\UART_TEST\UserAPP\Inc\UserUart.h
 */
#ifndef __USERUART_H
#define __USERUART_H
#include "stm32f1xx.h"

typedef struct{

		uint8_t RxData;
}UART_TXRX_HandleTypeDef;

void UserUartInit(void);
void SCQueue_MessageRecive(void);

#endif
