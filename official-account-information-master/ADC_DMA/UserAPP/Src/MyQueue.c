#include <math.h>
#include "myqueue.h"
#include <stdio.h> /*包含头文件，主要包含输入输出函数*/
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

////方法1  附加标志法

//	
///*将顺序循环队列初始化为空队列，需要把队头指针和队尾指针同时置为0，且标志位置为0*/
//void InitQueue(SCQueue *SCQ)
//{
//	SCQ->front = SCQ->rear = 0; /*队头指针和队尾指针都置为0*/
//	SCQ->tag = 0;				/*标志位置为0*/
//}

//// //获取队列长度
// int QueueLength(SCQueue *scq)
//{
//	return (scq->rear - scq->front + QUEUESIZE) % QUEUESIZE;
// }
///*判断顺序循环队列是否为空，队列为空返回1，否则返回0*/
//int QueueEmpty(SCQueue SCQ)
//{
//	if (SCQ.front == SCQ.rear && SCQ.tag == 0) /*队头指针和队尾指针都为0且标志位为0表示队列已空*/
//		return 1;
//	else
//		return 0;
//}
///*将元素e插入到顺序循环队列SQ中，插入成功返回1，否则返回0*/
//int EnQueue(SCQueue *SCQ, DataType e)
//{
//	if (SCQ->front == SCQ->rear && SCQ->tag == 1)
//	/*在插入新的元素之前，判断是否队尾指针到达数组的最大值，即是否上溢*/
//	{
//		Queue_printf("\r\nthe circle queue is full!\r\n");
//	}
//	else
//	{
//		SCQ->queue[SCQ->rear] = e; /*在队尾插入元素e */
//		SCQ->rear = (SCQ->rear + 1) % QUEUESIZE;
////		Queue_printf("\r\ndata has been inserted!\r\n");
//	}
//	if (SCQ->rear == SCQ->front)
//	{
//		SCQ->tag = 1; /*队列已满，标志位置为1 */
//		Queue_printf("\r\nSCQ->tag is: %d\r\n",SCQ->tag);
//		
//	}

//	return SCQ->tag;
//}
///*删除顺序循环队列中的队头元素，并将该元素赋值给e，删除成功返回1，否则返回0*/
//int DeQueue(SCQueue *SCQ, DataType *e)
//{
//	if (QueueEmpty(*SCQ)) /*在删除元素之前，判断队列是否为空*/
//	{
//		//Queue_printf("顺序循环队列已经是空队列，不能再进行出队列操作！");
//		return 0;
//	}
//	else
//	{
//		*e = SCQ->queue[SCQ->front];			   /*要出队列的元素值赋值给e */
//		SCQ->front = (SCQ->front + 1) % QUEUESIZE; /*队头指针向后移动一个位置，指向新的队头元素*/
//		SCQ->tag = 0;							   /*删除成功，标志位置为0 */
//		
//		return 1;
//	}
//	if (SCQ->rear == SCQ->front)
//	{
//		SCQ->tag = 0; /*队列已空，标志位置为0 */
//		Queue_printf("\r\nSCQ->tag is: %d\r\n",SCQ->tag);
//	}

//	return SCQ->tag;
//}

 //方法2 预留空间实现

 /*将顺序循环队列初始化为空队列，需要把队头指针和队尾指针同时置为0，且标志位置为0*/
 void InitQueue(SCQueue *SCQ)
 {
 	SCQ->front = SCQ->rear = 0; /*队头指针和队尾指针都置为0*/
 	SCQ->tag = 0;				/*标志位置为0*/
 }
 //获取队列长度
 int QueueLength(SCQueue *SCQ)
 {
 	return (SCQ->rear - SCQ->front + QUEUESIZE) % QUEUESIZE;
 }

 /*判断顺序循环队列是否为空，队列为空返回1，否则返回0*/
 int QueueEmpty(SCQueue SCQ)
 {
 	if (SCQ.front == SCQ.rear) /*队头指针和队尾指针都为0且标志位为0表示队列已空*/
 		return 1;
 	else
 		return 0;
 }

 /*将元素e插入到顺序循环队列SQ中，插入成功返回1，否则返回0*/
 int EnQueue(SCQueue *SCQ, DataType e)
 {
 	/*在插入新的元素之前，判断是否队尾指针到达数组的最大值，即是否上溢*/
 	if ((SCQ->rear + 1) % QUEUESIZE == SCQ->front)
 	{
 		Queue_printf("\r\nthe circle queue is full!\r\n");
 		return 0;
 	}

 	SCQ->queue[SCQ->rear] = e;				 /*在队尾插入元素e */
 	SCQ->rear = (SCQ->rear + 1) % QUEUESIZE; /*队尾指针向后移动一个位置，指向新的队尾*/
 	//Queue_printf("\r\ndata has been inserted!\r\n");
 	return 1;
 }
 /*删除顺序循环队列中的队头元素，并将该元素赋值给e，删除成功返回1，否则返回0*/
 int DeQueue(SCQueue *SCQ, DataType *e)
 {
 	if (QueueEmpty(*SCQ)) /*在删除元素之前，判断队列是否为空*/
 	{
 //	Queue_printf("顺序循环队列已经是空队列，不能再进行出队列操作！\r\n");
 		return 0;
 	}
 	else
 	{
 		*e = SCQ->queue[SCQ->front];			   /*要出队列的元素值赋值给e */
 		SCQ->front = (SCQ->front + 1) % QUEUESIZE; /*队头指针向后移动一个位置，指向新的队头元素*/
		
 		return 1;
 	}
 }
