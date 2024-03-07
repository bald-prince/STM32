#include "sys.h"
#include "delay.h"
#include "usart.h"
#include "FreeRTOS.h"
#include "task.h"
#include "misc.h"
#include "led.h"
#include "IDLE_TIMER.h"
//声明
UBaseType_t uxTaskGetStackHighWaterMark( TaskHandle_t xTask ) PRIVILEGED_FUNCTION;
//任务函数定义
//开始函数
TaskHandle_t start_task_handler; 
void start_init(void *pvParameters);
//任务函数
TaskHandle_t Task_1_Handler; 
void Task_1(void *pvParameters);

TaskHandle_t Task_2_Handler; 
void Task_2(void *pvParameters);

TaskHandle_t Task_3_Handler; 
void Task_3(void *vpParameter);

TaskHandle_t Task_4_Handler; 
void Task_4(void *vpParameter);

//全局变量
	
//函数入口
int main()
{
	Stm32_Clock_Init(480,8,2,10);                   				//HAL系统时钟初始化
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_4);					//设置系统中断优先级分组4
	delay_init(240);															 					//初始化延时函数
	uart_init(115200);  													 		  		//初始化串口
	
	 xTaskCreate((TaskFunction_t  )start_init,            	 //任务函数
                (const char*    )"start_init",          	 //任务名称
                (uint16_t       )256,        	 						 //任务堆栈大小
                (void*          )NULL,                  	 //传递给任务函数的参数
                (UBaseType_t    )1,       	      				 //任务优先级
                (TaskHandle_t*  )&start_task_handler);  	 //任务句柄    
								
    vTaskStartScheduler();          //开启任务调度
		while(1)
		{
		}
}



void start_init(void *pvParameters)
{
	 taskENTER_CRITICAL();
	 xTaskCreate((TaskFunction_t  )Task_1,             			 //任务函数
                (const char*    )"Task_1",          			 //任务名称
                (uint16_t       )256,         						 //任务堆栈大小
                (void*          )NULL,                     //传递给任务函数的参数
                (UBaseType_t    )2,       								 //任务优先级
                (TaskHandle_t*  )&Task_1_Handler);   			 //任务句柄    
 
   xTaskCreate((TaskFunction_t  )Task_2,             			 //任务函数
                (const char*    )"Task_2",        		  	 //任务名称
                (uint16_t       )256,                			 //任务堆栈大小
                (void*          )NULL,               			 //传递给任务函数的参数
                (UBaseType_t    )3,                    		 //任务优先级
                (TaskHandle_t*  )&Task_2_Handler);   			 //任务句柄  
								
	 xTaskCreate((TaskFunction_t  )Task_3,             			 //任务函数
                (const char*    )"Task_3",        		  	 //任务名称
                (uint16_t       )256,                			 //任务堆栈大小
                (void*          )NULL,               			 //传递给任务函数的参数
                (UBaseType_t    )4,                    		 //任务优先级
                (TaskHandle_t*  )&Task_3_Handler);   			 //任务句柄   
								
	 xTaskCreate((TaskFunction_t  )Task_4,             			 //任务函数
                (const char*    )"Task_4",        		  	 //任务名称
                (uint16_t       )256,                			 //任务堆栈大小
                (void*          )NULL,               			 //传递给任务函数的参数
                (UBaseType_t    )6,                    		 //任务优先级
                (TaskHandle_t*  )&Task_4_Handler);   			 //任务句柄   
	
	vTaskDelete(start_task_handler);												 //传入NULL删除自身
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
//开关总中断
taskDISABLE_INTERRUPTS();  
delay_xms(5000);
taskENABLE_INTERRUPTS();

//挂起任务
vTaskSuspend(oled_task_handler);
delay_xms(5000);
vTaskResume(oled_task_handler);

//软定时器定义和使用
void Auto_Tim_Callback(TimerHandle_t xTim);
TimerHandle_t auto_timer_Handle;

auto_timer_Handle = xTimerCreate((const char*            )"auto_timer",
	                               (TickType_t             )500,
	                               (UBaseType_t            )pdTRUE,
                                 (void*                  )1,
	                              (TimerCallbackFunction_t)Auto_Tim_Callback);
xTimerStart(auto_timer_Handle,0);
//定时器中断服务
void Auto_Tim_Callback(TimerHandle_t xTim)
{
	PCout(2) =! PCout(2);
}
***********************/


