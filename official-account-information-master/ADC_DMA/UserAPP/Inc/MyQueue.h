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

#define QUEUESIZE 512 /*����˳��ѭ�����е��������*/


typedef uint8_t DataType; /*����˳��ѭ������Ԫ�ص�����Ϊu8��*/

typedef struct Squeue
{
	/*˳��ѭ�����е����Ͷ���*/
	DataType queue[QUEUESIZE];
	int front, rear; /*��ͷָ��Ͷ�βָ��*/
	int tag;		 /*���пա����ı�־*/
} SCQueue;

int EnQueue(SCQueue *SCQ, DataType e);
void InitQueue(SCQueue *SCQ);
int DeQueue(SCQueue *SCQ, DataType *e);
int QueueLength(SCQueue *SCQ);
int QueueEmpty(SCQueue SCQ);


#endif

