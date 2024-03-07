#include "sys.h"
#include "delay.h"
#include "usart.h"
#include "FreeRTOS.h"
#include "task.h"
#include "misc.h"
#include "led.h"
#include "IDLE_TIMER.h"
//����
UBaseType_t uxTaskGetStackHighWaterMark( TaskHandle_t xTask ) PRIVILEGED_FUNCTION;
//����������
//��ʼ����
TaskHandle_t start_task_handler; 
void start_init(void *pvParameters);
//������
TaskHandle_t Task_1_Handler; 
void Task_1(void *pvParameters);

TaskHandle_t Task_2_Handler; 
void Task_2(void *pvParameters);

TaskHandle_t Task_3_Handler; 
void Task_3(void *vpParameter);

TaskHandle_t Task_4_Handler; 
void Task_4(void *vpParameter);

//ȫ�ֱ���
	
//�������
int main()
{
	Stm32_Clock_Init(480,8,2,10);                   				//HALϵͳʱ�ӳ�ʼ��
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_4);					//����ϵͳ�ж����ȼ�����4
	delay_init(240);															 					//��ʼ����ʱ����
	uart_init(115200);  													 		  		//��ʼ������
	
	 xTaskCreate((TaskFunction_t  )start_init,            	 //������
                (const char*    )"start_init",          	 //��������
                (uint16_t       )256,        	 						 //�����ջ��С
                (void*          )NULL,                  	 //���ݸ��������Ĳ���
                (UBaseType_t    )1,       	      				 //�������ȼ�
                (TaskHandle_t*  )&start_task_handler);  	 //������    
								
    vTaskStartScheduler();          //�����������
		while(1)
		{
		}
}



void start_init(void *pvParameters)
{
	 taskENTER_CRITICAL();
	 xTaskCreate((TaskFunction_t  )Task_1,             			 //������
                (const char*    )"Task_1",          			 //��������
                (uint16_t       )256,         						 //�����ջ��С
                (void*          )NULL,                     //���ݸ��������Ĳ���
                (UBaseType_t    )2,       								 //�������ȼ�
                (TaskHandle_t*  )&Task_1_Handler);   			 //������    
 
   xTaskCreate((TaskFunction_t  )Task_2,             			 //������
                (const char*    )"Task_2",        		  	 //��������
                (uint16_t       )256,                			 //�����ջ��С
                (void*          )NULL,               			 //���ݸ��������Ĳ���
                (UBaseType_t    )3,                    		 //�������ȼ�
                (TaskHandle_t*  )&Task_2_Handler);   			 //������  
								
	 xTaskCreate((TaskFunction_t  )Task_3,             			 //������
                (const char*    )"Task_3",        		  	 //��������
                (uint16_t       )256,                			 //�����ջ��С
                (void*          )NULL,               			 //���ݸ��������Ĳ���
                (UBaseType_t    )4,                    		 //�������ȼ�
                (TaskHandle_t*  )&Task_3_Handler);   			 //������   
								
	 xTaskCreate((TaskFunction_t  )Task_4,             			 //������
                (const char*    )"Task_4",        		  	 //��������
                (uint16_t       )256,                			 //�����ջ��С
                (void*          )NULL,               			 //���ݸ��������Ĳ���
                (UBaseType_t    )6,                    		 //�������ȼ�
                (TaskHandle_t*  )&Task_4_Handler);   			 //������   
	
	vTaskDelete(start_task_handler);												 //����NULLɾ������
	taskEXIT_CRITICAL();
}

void Task_1(void *pvParameters)
{
	while(1)
	{
		vTaskDelay(1);
	}
	
}

void Task_2(void *pvParameter)
{
	while(1)
	{ 
		vTaskDelay(100);
	}
}

void Task_3(void *vpParameter)
{
	while(1)
	{
		vTaskDelay(150);
  }
}

void Task_4(void *vpParameter)
{
	while(1)
	{
		vTaskDelay(1000);
	}
}



/***********************
//�������ж�
taskDISABLE_INTERRUPTS();  
delay_xms(5000);
taskENABLE_INTERRUPTS();

//��������
vTaskSuspend(oled_task_handler);
delay_xms(5000);
vTaskResume(oled_task_handler);

//��ʱ�������ʹ��
void Auto_Tim_Callback(TimerHandle_t xTim);
TimerHandle_t auto_timer_Handle;

auto_timer_Handle = xTimerCreate((const char*            )"auto_timer",
	                               (TickType_t             )500,
	                               (UBaseType_t            )pdTRUE,
                                 (void*                  )1,
	                              (TimerCallbackFunction_t)Auto_Tim_Callback);
xTimerStart(auto_timer_Handle,0);
//��ʱ���жϷ���
void Auto_Tim_Callback(TimerHandle_t xTim)
{
	PCout(2) =! PCout(2);
}
***********************/


