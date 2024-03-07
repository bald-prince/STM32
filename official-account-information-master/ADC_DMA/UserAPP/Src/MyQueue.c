#include <math.h>
#include "myqueue.h"
#include <stdio.h> /*����ͷ�ļ�����Ҫ���������������*/
#include "UserUart.h"

#define Queue_printf_debug

#ifdef Queue_printf_debug

#define Queue_printf(format, args...) \
	do                                \
	{                                 \
		printf(format, ##args);       \
	} while (0)
#else
#define Queue_printf(format, args...) \
	do                                \
	{                                 \
	} while (0)
#endif

////����1  ���ӱ�־��

//	
///*��˳��ѭ�����г�ʼ��Ϊ�ն��У���Ҫ�Ѷ�ͷָ��Ͷ�βָ��ͬʱ��Ϊ0���ұ�־λ��Ϊ0*/
//void InitQueue(SCQueue *SCQ)
//{
//	SCQ->front = SCQ->rear = 0; /*��ͷָ��Ͷ�βָ�붼��Ϊ0*/
//	SCQ->tag = 0;				/*��־λ��Ϊ0*/
//}

//// //��ȡ���г���
// int QueueLength(SCQueue *scq)
//{
//	return (scq->rear - scq->front + QUEUESIZE) % QUEUESIZE;
// }
///*�ж�˳��ѭ�������Ƿ�Ϊ�գ�����Ϊ�շ���1�����򷵻�0*/
//int QueueEmpty(SCQueue SCQ)
//{
//	if (SCQ.front == SCQ.rear && SCQ.tag == 0) /*��ͷָ��Ͷ�βָ�붼Ϊ0�ұ�־λΪ0��ʾ�����ѿ�*/
//		return 1;
//	else
//		return 0;
//}
///*��Ԫ��e���뵽˳��ѭ������SQ�У�����ɹ�����1�����򷵻�0*/
//int EnQueue(SCQueue *SCQ, DataType e)
//{
//	if (SCQ->front == SCQ->rear && SCQ->tag == 1)
//	/*�ڲ����µ�Ԫ��֮ǰ���ж��Ƿ��βָ�뵽����������ֵ�����Ƿ�����*/
//	{
//		Queue_printf("\r\nthe circle queue is full!\r\n");
//	}
//	else
//	{
//		SCQ->queue[SCQ->rear] = e; /*�ڶ�β����Ԫ��e */
//		SCQ->rear = (SCQ->rear + 1) % QUEUESIZE;
////		Queue_printf("\r\ndata has been inserted!\r\n");
//	}
//	if (SCQ->rear == SCQ->front)
//	{
//		SCQ->tag = 1; /*������������־λ��Ϊ1 */
//		Queue_printf("\r\nSCQ->tag is: %d\r\n",SCQ->tag);
//		
//	}

//	return SCQ->tag;
//}
///*ɾ��˳��ѭ�������еĶ�ͷԪ�أ�������Ԫ�ظ�ֵ��e��ɾ���ɹ�����1�����򷵻�0*/
//int DeQueue(SCQueue *SCQ, DataType *e)
//{
//	if (QueueEmpty(*SCQ)) /*��ɾ��Ԫ��֮ǰ���ж϶����Ƿ�Ϊ��*/
//	{
//		//Queue_printf("˳��ѭ�������Ѿ��ǿն��У������ٽ��г����в�����");
//		return 0;
//	}
//	else
//	{
//		*e = SCQ->queue[SCQ->front];			   /*Ҫ�����е�Ԫ��ֵ��ֵ��e */
//		SCQ->front = (SCQ->front + 1) % QUEUESIZE; /*��ͷָ������ƶ�һ��λ�ã�ָ���µĶ�ͷԪ��*/
//		SCQ->tag = 0;							   /*ɾ���ɹ�����־λ��Ϊ0 */
//		
//		return 1;
//	}
//	if (SCQ->rear == SCQ->front)
//	{
//		SCQ->tag = 0; /*�����ѿգ���־λ��Ϊ0 */
//		Queue_printf("\r\nSCQ->tag is: %d\r\n",SCQ->tag);
//	}

//	return SCQ->tag;
//}

 //����2 Ԥ���ռ�ʵ��

 /*��˳��ѭ�����г�ʼ��Ϊ�ն��У���Ҫ�Ѷ�ͷָ��Ͷ�βָ��ͬʱ��Ϊ0���ұ�־λ��Ϊ0*/
 void InitQueue(SCQueue *SCQ)
 {
 	SCQ->front = SCQ->rear = 0; /*��ͷָ��Ͷ�βָ�붼��Ϊ0*/
 	SCQ->tag = 0;				/*��־λ��Ϊ0*/
 }
 //��ȡ���г���
 int QueueLength(SCQueue *SCQ)
 {
 	return (SCQ->rear - SCQ->front + QUEUESIZE) % QUEUESIZE;
 }

 /*�ж�˳��ѭ�������Ƿ�Ϊ�գ�����Ϊ�շ���1�����򷵻�0*/
 int QueueEmpty(SCQueue SCQ)
 {
 	if (SCQ.front == SCQ.rear) /*��ͷָ��Ͷ�βָ�붼Ϊ0�ұ�־λΪ0��ʾ�����ѿ�*/
 		return 1;
 	else
 		return 0;
 }

 /*��Ԫ��e���뵽˳��ѭ������SQ�У�����ɹ�����1�����򷵻�0*/
 int EnQueue(SCQueue *SCQ, DataType e)
 {
 	/*�ڲ����µ�Ԫ��֮ǰ���ж��Ƿ��βָ�뵽����������ֵ�����Ƿ�����*/
 	if ((SCQ->rear + 1) % QUEUESIZE == SCQ->front)
 	{
 		Queue_printf("\r\nthe circle queue is full!\r\n");
 		return 0;
 	}

 	SCQ->queue[SCQ->rear] = e;				 /*�ڶ�β����Ԫ��e */
 	SCQ->rear = (SCQ->rear + 1) % QUEUESIZE; /*��βָ������ƶ�һ��λ�ã�ָ���µĶ�β*/
 	//Queue_printf("\r\ndata has been inserted!\r\n");
 	return 1;
 }
 /*ɾ��˳��ѭ�������еĶ�ͷԪ�أ�������Ԫ�ظ�ֵ��e��ɾ���ɹ�����1�����򷵻�0*/
 int DeQueue(SCQueue *SCQ, DataType *e)
 {
 	if (QueueEmpty(*SCQ)) /*��ɾ��Ԫ��֮ǰ���ж϶����Ƿ�Ϊ��*/
 	{
 //	Queue_printf("˳��ѭ�������Ѿ��ǿն��У������ٽ��г����в�����\r\n");
 		return 0;
 	}
 	else
 	{
 		*e = SCQ->queue[SCQ->front];			   /*Ҫ�����е�Ԫ��ֵ��ֵ��e */
 		SCQ->front = (SCQ->front + 1) % QUEUESIZE; /*��ͷָ������ƶ�һ��λ�ã�ָ���µĶ�ͷԪ��*/
		
 		return 1;
 	}
 }
