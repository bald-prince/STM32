/*
 * @Author: your name
 * @Date: 2021-09-17 13:59:37
 * @LastEditTime: 2021-09-17 17:57:36
 * @LastEditors: Please set LastEditors
 * @Description: In User Settings Edit
 * @FilePath: \UART_CircleQueueTest\UserAPP\Src\freertos_task.c
 */
#include "freertos_task.h"
#include "stm32f1xx.h"

#include "semphr.h"
#include "stdio.h"

#include "FreeRTOS.h"
#include "task.h"
#include "stdlib.h"
#define usStackDepth 512


//声明互斥信号量
SemaphoreHandle_t xMutex;
//void debug_printf(const char *fmt, ...)
//{
//    if(xSemaphoreTake(xMutex, 100) == pdFALSE)
//        return;
//    printf(fmt);
//    xSemaphoreGive(xMutex);
//}


#define		DEBUG_INFO


#ifdef DEBUG_INFO
//#define debug_printf(format, args...)       do{     																						\
//																								 printf(format, ##args); \
//																								 }while(0)
//	
	
#define debug_printf(format, args...)       do{     																						\
																								 if(xSemaphoreTake(xMutex, 100) == pdFALSE)			\
																								 return; 																				\
																								 printf(format, ##args); \
																								 xSemaphoreGive(xMutex); }while(0)	

																								 

//	#define debug_printf(format, args...)       do{     																						\
//																								 taskENTER_CRITICAL(); 																				\
//																								 printf(format, ##args); \
//																								taskEXIT_CRITICAL(); }while(0)	

//																									 
//	#define debug_printf(format, args...)       do{     																						\
//																								 vTaskSuspendAll(); 																				\
//																								 printf(format, ##args); \
//																								 xTaskResumeAll(); }while(0)	

#else
#define debug_printf(format, args...)         do{ }while(0)
#endif

				
/*-----------------------------------------------------------*/
/* 声明xQueueHandle变量。这个变量将会用于打印任务和中断往守护任务发送消息。 */
xQueueHandle xPrintQueue;
/*-----------------------------------------------------------*/

/* 定义任务和中断将会通过守护任务输出的字符串。 */
static char *pcStringsToPrint[] =
{
	"freertos task01 is running...\r\n",
	"freertos task02 is running...\r\n",
	"Message printed from the tick hook interrupt ##############\r\n"
};


extern ADC_HandleTypeDef hadc1;
extern DMA_HandleTypeDef hdma_adc1;

uint16_t adc_buffer[10][4] = {0,0};
  
static void prvPrintTask( void *pvParameters )
{
	float adc_value[4] = {0};
	int i=0,j=0;
	HAL_ADCEx_Calibration_Start(&hadc1);
	HAL_ADC_Start_DMA(&hadc1,(uint32_t *)adc_buffer,40);
	int iIndexToString;
	/* Two instances of this task are created. The task parameter is used to pass
	an index into an array of strings into the task. Cast this to the required type. */
	iIndexToString = ( int ) pvParameters;
	for( ;; )
	{
		for(int i=0;i<4;i++)
		{
			for(int j=0;j<10;j++)
			{
				adc_value[i]+=adc_buffer[j][i];
			}
		adc_value[i]=(float)adc_value[i]/(10*4096)*3.3;//求平均值并转换成电压值
		//ADC_Value[i]=(float)sum/10;
		printf("ADC_Value[%d] = %.2f\n",i,adc_value[i]);
	}		
		vTaskDelay( ( rand() & 0x1FF ) );
		}
}

																								 
void vApplicationTickHook( void )
{
		static int iCount = 0;
		portBASE_TYPE xHigherPriorityTaskWoken = pdFALSE;
		/* Print out a message every 200 ticks. The message is not written out
		directly, but sent to the gatekeeper task. */
		iCount++;
		if( iCount >= 200 )
		{
		/* In this case the last parameter (xHigherPriorityTaskWoken) is not
		actually used but must still be supplied. */
//		xQueueSendToFrontFromISR( xPrintQueue,
//		&( pcStringsToPrint[ 2 ] ),
//		&xHigherPriorityTaskWoken );
		/* Reset the count ready to print out the string again in 200 ticks
		time. */
		iCount = 0;
		}
}		
																										 
																								 
static void prvStdioGatekeeperTask( void *pvParameters )
{
	char *pcMessageToPrint;
	/* 这是唯一允许直接访问终端输出的任务。任何其它任务想要输出字符串，都不能直接访问终端，而是将要
	输出的字符串发送到此任务。并且因为只有本任务才可以访问标准输出，所以本任务在实现上不需要考虑互斥
	和串行化等问题。 */
	for( ;; )
	{
	/* 等待信息到达。指定了一个无限长阻塞超时时间，所以不需要检查返回值 – 此函数只会在成功收到
	消息时才会返回。 */
	xQueueReceive( xPrintQueue, &pcMessageToPrint, portMAX_DELAY );
	/* 输出收到的字符串。 */
	printf( "%s", pcMessageToPrint );
	fflush( stdout );
	/* Now simply go back to wait for the next message. */
	}
}																					 
																								 


void UserAPP_Task01(void)
{

	for (;;)
	{

		//debug_printf("\nfreertos task01 is running...\n");
		vTaskDelay(500);
	}
}
void UserAPP_Task02(void)
{
    for (;;)
    {
        //debug_printf("\nfreertos task02 is running...\n");
        vTaskDelay(500);
    }
}

portBASE_TYPE UserAPP_TaskCreate(void)
{
		//创建一个互斥信号量
		xMutex = xSemaphoreCreateMutex();

		/* 创建队列，深度为5，数据单元类型为字符指针。 */
		xPrintQueue = xQueueCreate( 5, sizeof( char * ) );

		/* 为伪随机数发生器产生种子。 */
		srand( 567 );
		
		if( xPrintQueue != NULL )
		{
			/* 创建任务的两个实例，用于向守护任务发送信息。任务入口参数传入需要输出的字符串索引号。这两
			个任务具有不同的优先级，所以高优先级任务有时会抢占低优先级任务。 */
			xTaskCreate( prvPrintTask, "Print1", 1000, ( void * ) 0, 1, NULL );
			xTaskCreate( prvPrintTask, "Print2", 1000, ( void * ) 1, 2, NULL );

			/* 创建守护任务。这是唯一一个允许直接访问标准输出的任务。 */
			xTaskCreate( prvStdioGatekeeperTask, "Gatekeeper", 1000, NULL, 0, NULL );
			
			
//			//创建一个任务
//			if (pdTRUE != xTaskCreate((TaskFunction_t)UserAPP_Task01,
//																"UserAPP_Task01",
//																usStackDepth,
//																NULL,
//																1,
//																NULL))
//			{
//					printf("\nfreertos task01 create failed...\n");
//			}

//			//创建一个任务
//			if (pdTRUE != xTaskCreate((TaskFunction_t)UserAPP_Task02,
//																"UserAPP_Task02",
//																usStackDepth,
//																NULL,
//																1,
//																NULL))
//			{
//					printf("\nfreertos task02 create failed...\n");
//					return pdFALSE;
//			}
//			
			return pdTRUE;
	}
}
