#ifndef __M_STM32_USART_H
#define __M_STM32_USART_H

//***************************USART GPIO&Pin***********************************
//  USART1_TX PA9
//  USART1_RX PA10

//  USART2_TX PA2
//  USART2_RX PA3

//  USART3_TX PB10
//  USART3_RX PB11

#include "stm32f10x.h"
#include "stdio.h"
#include "sys.h"
void uart_init(u32 pclk2,u32 bound);
#endif	
void USART_SendString(USART_TypeDef* USARTx, char* str);                                   //USART����
void M_USART_Init(USART_TypeDef* USARTx, uint32_t USART_BautRate); //USART��ʼ��
void M_USARTx_NVIC_Configuration(USART_TypeDef* USARTx,                                    //USART�ж�����
								 uint32_t       NVIC_PriorityGroup_x, 
								 uint8_t        Pre_LEVEL_x, 
								 uint8_t        Sub_LEVEL_x);
