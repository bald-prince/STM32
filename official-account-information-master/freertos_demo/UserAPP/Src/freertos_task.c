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


//���������ź���
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
/* ����xQueueHandle��������������������ڴ�ӡ������ж����ػ���������Ϣ�� */
xQueueHandle xPrintQueue;
/*-----------------------------------------------------------*/

/* ����������жϽ���ͨ���ػ�����������ַ����� */
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
		adc_value[i]=(float)adc_value[i]/(10*4096)*3.3;//��ƽ��ֵ��ת���ɵ�ѹֵ
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
	/* ����Ψһ����ֱ�ӷ����ն�����������κ�����������Ҫ����ַ�����������ֱ�ӷ����նˣ����ǽ�Ҫ
	������ַ������͵������񡣲�����Ϊֻ�б�����ſ��Է��ʱ�׼��������Ա�������ʵ���ϲ���Ҫ���ǻ���
	�ʹ��л������⡣ */
	for( ;; )
	{
	/* �ȴ���Ϣ���ָ����һ�����޳�������ʱʱ�䣬���Բ���Ҫ��鷵��ֵ �C �˺���ֻ���ڳɹ��յ�
	��Ϣʱ�Ż᷵�ء� */
	xQueueReceive( xPrintQueue, &pcMessageToPrint, portMAX_DELAY );
	/* ����յ����ַ����� */
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
		//����һ�������ź���
		xMutex = xSemaphoreCreateMutex();

		/* �������У����Ϊ5�����ݵ�Ԫ����Ϊ�ַ�ָ�롣 */
		xPrintQueue = xQueueCreate( 5, sizeof( char * ) );

		/* Ϊα������������������ӡ� */
		srand( 567 );
		
		if( xPrintQueue != NULL )
		{
			/* �������������ʵ�����������ػ���������Ϣ��������ڲ���������Ҫ������ַ��������š�����
			��������в�ͬ�����ȼ������Ը����ȼ�������ʱ����ռ�����ȼ����� */
			xTaskCreate( prvPrintTask, "Print1", 1000, ( void * ) 0, 1, NULL );
			xTaskCreate( prvPrintTask, "Print2", 1000, ( void * ) 1, 2, NULL );

			/* �����ػ���������Ψһһ������ֱ�ӷ��ʱ�׼��������� */
			xTaskCreate( prvStdioGatekeeperTask, "Gatekeeper", 1000, NULL, 0, NULL );
			
			
//			//����һ������
//			if (pdTRUE != xTaskCreate((TaskFunction_t)UserAPP_Task01,
//																"UserAPP_Task01",
//																usStackDepth,
//																NULL,
//																1,
//																NULL))
//			{
//					printf("\nfreertos task01 create failed...\n");
//			}

//			//����һ������
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
