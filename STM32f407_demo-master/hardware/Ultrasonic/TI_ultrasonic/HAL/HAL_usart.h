/**
  ******************************************************************************
  * Copyright (c) 2018,北京中科浩电科技有限公司
  * All rights reserved.
  * 文件名称：UART.h
  * 摘    要：
  *
  * 当前版本：V1.0
  * 作    者：北京中科浩电科技有限公司研发部 
  * 完成日期：    
  * 修改说明：
  * 
  *
  * 历史版本：更新对MSP432的异步串口收发支持
  *
  *
  *******************************************************************************/
#ifndef _UART_H
#define _UART_H
//外部文件引用
#include "stdint.h"
#include "stdbool.h"
#include "queue.h"
#include "stdio.h"

#define MAX_RECEIVE_CNT     50
#define MAX_TRANSMIT_CNT    50

typedef struct
{
    /*接收部分数据变量*/
    uint32_t moduleInstance;
    bool RxStart;
    void (*RxHandle)(uint8_t *Ptr, uint8_t Length);
    uint8_t RxTimeout;
    uint8_t RxCnt;
    uint8_t RxBuff[MAX_RECEIVE_CNT];
    
    /*发送部分数据变量*/
    bool TxCommpleate;
    Queue_t qTx;
    uint8_t TxCnt;
    uint8_t TxLength;
    uint8_t TxBuff[MAX_TRANSMIT_CNT];
}Usart_t;

typedef enum
{
    UART_A0,
    UART_A2,
    UART_A3,
    
    Num_USART,
}emUSART_t;

//不可一次性输入超过32个字符
#define ZKHD_Printf(data)   {    char tmp[100];\
                                 uint8_t length;\
                                 length = sprintf(tmp,data);\
                                 USART_TX(&UsartGroup[UART_A0], (uint8_t*)tmp, length); \
                            }

extern Usart_t UsartGroup[Num_USART];

void USART_Init(void);
void USART_TX(Usart_t*, uint8_t* pTx, uint8_t len);

void PollingUSART(void);

#endif

/******************* (C) 版权所有 2018 北京中科浩电科技有限公司 *******************/

