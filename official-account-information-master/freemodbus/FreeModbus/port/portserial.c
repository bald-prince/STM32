/*
  * FreeModbus Libary: LPC214X Port
  * Copyright (C) 2007 Tiago Prado Lone <tiago@maxwellbohr.com.br>
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
 *
 * File: $Id: portserial.c,v 1.1 2007/04/24 23:15:18 wolti Exp $
 */

#include "port.h"

/* ----------------------- Modbus includes ----------------------------------*/
#include "mb.h"
#include "mbport.h"
/* ----------------------- Start implementation -----------------------------*/
void vMBPortSerialEnable( BOOL xRxEnable, BOOL xTxEnable )
{
	if(xRxEnable)
	{
		__HAL_UART_ENABLE_IT(&huart1,UART_IT_RXNE);
	}
	else
	{
		__HAL_UART_DISABLE_IT(&huart1, UART_IT_RXNE);
	}

	if(xTxEnable)
	{
		__HAL_UART_ENABLE_IT(&huart1,UART_IT_TC);
	}
	else
	{
		__HAL_UART_DISABLE_IT(&huart1, UART_IT_TC);
	}
}

void
vMBPortClose( void )
{
	__HAL_UART_DISABLE_IT(&huart1, UART_IT_TC|UART_IT_RXNE);
	__HAL_UART_DISABLE(&huart1);
}

BOOL
xMBPortSerialInit( UCHAR ucPORT, ULONG ulBaudRate, UCHAR ucDataBits, eMBParity eParity )
{	
	__HAL_UART_ENABLE_IT(&huart1,UART_IT_RXNE);
	__HAL_UART_ENABLE(&huart1);
  return TRUE;
}



BOOL
xMBPortSerialPutByte( CHAR ucByte )
{
  USART1->DR = (ucByte);
	while (__HAL_UART_GET_FLAG(&huart1,UART_FLAG_TC)==RESET){;}
  return TRUE;
}

BOOL
xMBPortSerialGetByte( CHAR * pucByte )
{
	*pucByte =(uint8_t)(USART1->DR & (uint16_t)0x01FF);
   return TRUE;
}

/* 
 * Create an interrupt handler for the transmit buffer empty interrupt
 * (or an equivalent) for your target processor. This function should then
 * call pxMBFrameCBTransmitterEmpty( ) which tells the protocol stack that
 * a new character can be sent. The protocol stack will then call 
 * xMBPortSerialPutByte( ) to send the character.
 */
void prvvUARTTxReadyISR(void)
{
    pxMBFrameCBTransmitterEmpty();
}

/* 
 * Create an interrupt handler for the receive interrupt for your target
 * processor. This function should then call pxMBFrameCBByteReceived( ). The
 * protocol stack will then call xMBPortSerialGetByte( ) to retrieve the
 * character.
 */
void prvvUARTRxISR(void)
{
    pxMBFrameCBByteReceived();
}
