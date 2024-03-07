/**
  ******************************************************************************
  * Copyright (c) 2018,北京中科浩电科技有限公司
  * All rights reserved.
  * 文件名称：UART.c
  * 摘    要：
  *
  * 当前版本：V1.0
  * 作    者：北京中科浩电科技有限公司研发部 
  * 完成日期：    
  * 修改说明：
  * 
  *
  * 历史版本：
  *
  *
  *******************************************************************************/

/*==============================================================================
                         ##### How to use this driver #####
==============================================================================
处理串口的相关事情

*/
//外部文件引用
#include "HAL_usart.h"
#include "driverlib.h"
#include "stdio.h"

#define USART_RX_TIMEOUT_MAX    5



bool lbUsartRx = false;
int TimeoutUSART = 0;
uint8_t SBusRxBuff[30] = {0};

Usart_t UsartGroup[Num_USART];

void UART_A0_ReceiveHandle(uint8_t *ptr, uint8_t length);
void UART_A2_ReceiveHandle(uint8_t *ptr, uint8_t length);
void UART_A3_ReceiveHandle(uint8_t *ptr, uint8_t length);

/******************************************************************************
  * 函数名称：USART_Init
  * 函数描述：串口初始化
  * 输    入：void
  * 输    出：void
  * 返    回：void
  * 备    注：TI公司通过以下网址提供给用户波特率配置信息
  * http://software-dl.ti.com/msp430/msp430_public_sw/mcu/msp430/MSP430BaudRateConverter/index.html
  * A2连接S.BUS总线，波特率为100K    
  * A0连接ANO光流，波特率为115200
  * A3连接ANO数传，波特率为500K
******************************************************************************/
void USART_Init()
{
    eUSCI_UART_Config uartConfigA2 =
    {
            EUSCI_A_UART_CLOCKSOURCE_SMCLK,          // SMCLK Clock Source
            30,                                      // BRDIV = 78
            0,                                       // UCxBRF = 2
            0,                                       // UCxBRS = 0
            EUSCI_A_UART_EVEN_PARITY,                  // No Parity-
            EUSCI_A_UART_LSB_FIRST,                  // LSB First
            EUSCI_A_UART_TWO_STOP_BITS,               // One stop bit
            EUSCI_A_UART_MODE,                       // UART mode
            EUSCI_A_UART_OVERSAMPLING_BAUDRATE_GENERATION  // Oversampling
    };
    
    eUSCI_UART_Config uartConfigA0 =
    {
            EUSCI_A_UART_CLOCKSOURCE_SMCLK,          // SMCLK Clock Source
            26,                                      // BRDIV = 78
            0,                                       // UCxBRF = 2
            111,                                       // UCxBRS = 0
            EUSCI_A_UART_NO_PARITY,                  // No Parity-
            EUSCI_A_UART_LSB_FIRST,                  // LSB First
            EUSCI_A_UART_ONE_STOP_BIT,               // One stop bit
            EUSCI_A_UART_MODE,                       // UART mode
            EUSCI_A_UART_OVERSAMPLING_BAUDRATE_GENERATION  // Oversampling
    };

    //连接数传到上位机  baud:500k
    eUSCI_UART_Config uartConfigA3 =
    {
            EUSCI_A_UART_CLOCKSOURCE_SMCLK,          // SMCLK Clock Source
            26,                                      // BRDIV = 78
            0,                                       // UCxBRF = 2
            111,                                       // UCxBRS = 0
            EUSCI_A_UART_NO_PARITY,                  // No Parity-
            EUSCI_A_UART_LSB_FIRST,                  // LSB First
            EUSCI_A_UART_ONE_STOP_BIT,               // One stop bit
            EUSCI_A_UART_MODE,                       // UART mode
            EUSCI_A_UART_OVERSAMPLING_BAUDRATE_GENERATION  // Oversampling
    };
		
    //
    MAP_GPIO_setAsPeripheralModuleFunctionInputPin(GPIO_PORT_P3,
            GPIO_PIN3 | GPIO_PIN2, GPIO_PRIMARY_MODULE_FUNCTION);
    
    MAP_UART_initModule(EUSCI_A2_BASE, &uartConfigA2);
    /* Enable UART module */
    MAP_UART_enableModule(EUSCI_A2_BASE);
    /* Enabling interrupts */
    MAP_UART_enableInterrupt(EUSCI_A2_BASE, EUSCI_A_UART_RECEIVE_INTERRUPT);
    MAP_UART_enableInterrupt(EUSCI_A2_BASE, EUSCI_A_UART_TRANSMIT_INTERRUPT);

    //
    MAP_GPIO_setAsPeripheralModuleFunctionInputPin(GPIO_PORT_P1,
            GPIO_PIN2 | GPIO_PIN3, GPIO_PRIMARY_MODULE_FUNCTION);    
    MAP_UART_initModule(EUSCI_A0_BASE, &uartConfigA0);
    /* Enable UART module */
    MAP_UART_enableModule(EUSCI_A0_BASE);
    /* Enabling interrupts */
    MAP_UART_enableInterrupt(EUSCI_A0_BASE, EUSCI_A_UART_RECEIVE_INTERRUPT);
    MAP_UART_enableInterrupt(EUSCI_A0_BASE, EUSCI_A_UART_TRANSMIT_INTERRUPT);

    //初始化A3串口引脚、初始化模块、使能模块、使能中断
    MAP_GPIO_setAsPeripheralModuleFunctionInputPin(GPIO_PORT_P9,
            GPIO_PIN6 | GPIO_PIN7, GPIO_PRIMARY_MODULE_FUNCTION);
    MAP_UART_initModule(EUSCI_A3_BASE, &uartConfigA3);
    MAP_UART_enableModule(EUSCI_A3_BASE);
    MAP_UART_enableInterrupt(EUSCI_A3_BASE, EUSCI_A_UART_RECEIVE_INTERRUPT);
    MAP_UART_enableInterrupt(EUSCI_A3_BASE, EUSCI_A_UART_TRANSMIT_INTERRUPT);
		
    //初始化串口后再使能中断
    MAP_Interrupt_enableInterrupt(INT_EUSCIA0);
    MAP_Interrupt_enableInterrupt(INT_EUSCIA2);
    MAP_Interrupt_enableInterrupt(INT_EUSCIA3);
    
    UsartGroup[UART_A0].RxHandle = UART_A0_ReceiveHandle;
    UsartGroup[UART_A2].RxHandle = UART_A2_ReceiveHandle;
    UsartGroup[UART_A3].RxHandle = UART_A3_ReceiveHandle;
    UsartGroup[UART_A0].TxCommpleate = true;
    UsartGroup[UART_A2].TxCommpleate = true;
    UsartGroup[UART_A3].TxCommpleate = true;
    UsartGroup[UART_A0].moduleInstance = EUSCI_A0_BASE;
    UsartGroup[UART_A2].moduleInstance = EUSCI_A2_BASE;
    UsartGroup[UART_A3].moduleInstance = EUSCI_A3_BASE;
}

/******************************************************************************
  * 函数名称：PollingUSART
  * 函数描述：轮询串口接收信息
  * 输    入：void
  * 输    出：void
  * 返    回：void
  * 备    注：整个系统与上位机通信，此处为入口
  *
  *
******************************************************************************/
void PollingUSART()
{    
    for(int i = 0;i < Num_USART; i++)
    {
        if(UsartGroup[i].RxStart)
        {
            UsartGroup[i].RxTimeout++;
            
            if(UsartGroup[i].RxTimeout > USART_RX_TIMEOUT_MAX)
            {
                //UsartGroup[i].RxCnt = UsartGroup[i].RxCnt > MAX_RECEIVE_CNT ? MAX_RECEIVE_CNT : UsartGroup[i].RxCnt;
                if(UsartGroup[i].RxCnt > MAX_RECEIVE_CNT)
                {
                   UsartGroup[i].RxCnt = MAX_RECEIVE_CNT;
                }
                
                UsartGroup[i].RxHandle(UsartGroup[i].RxBuff, UsartGroup[i].RxCnt);
                UsartGroup[i].RxTimeout = 0;
                UsartGroup[i].RxStart = false;               
                UsartGroup[i].RxCnt = 0;
            }
        }
        
        if(UsartGroup[i].TxCommpleate)
        {
            if(deQueue(&UsartGroup[i].qTx,UsartGroup[i].TxBuff,&UsartGroup[i].TxLength))
            {
                UsartGroup[i].TxCommpleate = false;
                
                UART_transmitData(UsartGroup[i].moduleInstance, UsartGroup[i].TxBuff[0]);
            }
        }
    }
}

/******************************************************************************
  * 函数名称：USART_TX
  * 函数描述：以中断的方式发送数据
  * 输    入：
  * Usart_t usart:选择要发送数据的模块
  * uint8_t *ptx:要发送的数据地址
  * uint8_t len:要发送的数据长度
  * 输    出：void
  * 返    回：void
  * 备    注：null
  *
  *
******************************************************************************/
void USART_TX(Usart_t *usart, uint8_t* pTx, uint8_t len)
{
    for(int i = 0; i < Num_USART; i++)
    {
        if(usart == &UsartGroup[i])
        {
            enQueue(&UsartGroup[i].qTx, pTx, len);
            break;
        }
    }
}

/******************************************************************************
  * 函数名称：EUSCIA2_IRQHandler
  * 函数描述：EUSCIA2断服务函数
  * 输    入：void
  * 输    出：void
  * 返    回：void
  * 备    注：SBUS处理函数
  *
  *
******************************************************************************/
void EUSCIA2_IRQHandler(void)
{
    uint32_t status = MAP_UART_getEnabledInterruptStatus(EUSCI_A2_BASE);
    
    UART_clearInterruptFlag(EUSCI_A2_BASE, status);
    
    if(status & EUSCI_A_UART_RECEIVE_INTERRUPT_FLAG)
    {
        UsartGroup[UART_A2].RxBuff[UsartGroup[UART_A2].RxCnt] = MAP_UART_receiveData(EUSCI_A2_BASE);
        UsartGroup[UART_A2].RxCnt++;
        UsartGroup[UART_A2].RxStart = true;
        UsartGroup[UART_A2].RxTimeout = 0;
        
        if(UsartGroup[UART_A2].RxBuff[0] != 0x0F)
        {
            UsartGroup[UART_A2].RxCnt = 0;
        }
        
        if(UsartGroup[UART_A2].RxCnt == 25)
        {
            UART_A2_ReceiveHandle(UsartGroup[UART_A2].RxBuff, UsartGroup[UART_A2].RxCnt);
            UsartGroup[UART_A2].RxCnt = 0;
        }else if(UsartGroup[UART_A2].RxCnt > 25)
        {
            UsartGroup[UART_A2].RxCnt = 0;
        }
    }
}


void EUSCIA0_IRQHandler(void)
{
    uint32_t status = MAP_UART_getEnabledInterruptStatus(EUSCI_A0_BASE);
    UART_clearInterruptFlag(EUSCI_A0_BASE,status);
    if(status & EUSCI_A_UART_RECEIVE_INTERRUPT_FLAG)
    {
            UsartGroup[UART_A0].RxBuff[UsartGroup[UART_A0].RxCnt] = MAP_UART_receiveData(EUSCI_A0_BASE);
            UsartGroup[UART_A0].RxCnt++;
            UsartGroup[UART_A0].RxStart = true;
            UsartGroup[UART_A0].RxTimeout = 0;
    }
    
    if(status & EUSCI_A_UART_TRANSMIT_INTERRUPT_FLAG)
    {
        if(!UsartGroup[UART_A0].TxCommpleate)
        {
            UsartGroup[UART_A0].TxCnt++;
            
            if(UsartGroup[UART_A0].TxCnt >= UsartGroup[UART_A0].TxLength)
            {
                UsartGroup[UART_A0].TxCommpleate = true;
                UsartGroup[UART_A0].TxCnt = 0;
            }else
            {
                UART_transmitData(UsartGroup[UART_A0].moduleInstance, 
                                  UsartGroup[UART_A0].TxBuff[UsartGroup[UART_A0].TxCnt]);
            }
        }
    }
}

void EUSCIA3_IRQHandler(void)
{
    uint32_t status = MAP_UART_getEnabledInterruptStatus(EUSCI_A3_BASE);
    UART_clearInterruptFlag(EUSCI_A3_BASE, status);
    
    if(status & EUSCI_A_UART_RECEIVE_INTERRUPT_FLAG)
    {
            UsartGroup[UART_A3].RxBuff[UsartGroup[UART_A3].RxCnt] = MAP_UART_receiveData(EUSCI_A3_BASE);
            UsartGroup[UART_A3].RxCnt++;
            UsartGroup[UART_A3].RxStart = true;
            UsartGroup[UART_A3].RxTimeout = 0;
    }
    
    if(status & EUSCI_A_UART_TRANSMIT_INTERRUPT_FLAG)
    {
        if(!UsartGroup[UART_A3].TxCommpleate)
        {
            UsartGroup[UART_A3].TxCnt++;
            
            if(UsartGroup[UART_A3].TxCnt >= UsartGroup[UART_A3].TxLength)
            {
                UsartGroup[UART_A3].TxCommpleate = true;
                UsartGroup[UART_A3].TxCnt = 0;
            }else
            {
                UART_transmitData(UsartGroup[UART_A3].moduleInstance, 
                                  UsartGroup[UART_A3].TxBuff[UsartGroup[UART_A3].TxCnt]);
            }
        }
    }
}

void UART_A0_ReceiveHandle(uint8_t *ptr, uint8_t length)
{

}

void UART_A2_ReceiveHandle(uint8_t *ptr, uint8_t length)
{

}

void UART_A3_ReceiveHandle(uint8_t *ptr, uint8_t length)
{

}




/******************* (C) 版权所有 2018 北京中科浩电科技有限公司 *******************/
