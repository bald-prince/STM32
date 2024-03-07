/*
 * @Author: your name
 * @Date: 2021-05-24 15:57:28
 * @LastEditTime: 2021-05-26 15:48:30
 * @LastEditors: Please set LastEditors
 * @Description: 
 */
#ifndef __MYQUEUE_H
#define __MYQUEUE_H

#include "stm32f1xx.h"

#define QUEUESIZE 512 /*定义顺序循环队列的最大容量*/


typedef uint8_t DataType; /*定义顺序循环队列元素的类型为u8型*/

typedef struct Squeue
{
	/*顺序循环队列的类型定义*/
	DataType queue[QUEUESIZE];
	int front, rear; /*队头指针和队尾指针*/
	int tag;		 /*队列空、满的标志*/
} SCQueue;

int EnQueue(SCQueue *SCQ, DataType e);
void InitQueue(SCQueue *SCQ);
int DeQueue(SCQueue *SCQ, DataType *e);
int QueueLength(SCQueue *SCQ);
int QueueEmpty(SCQueue SCQ);


#endif

