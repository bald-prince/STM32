#include "IDLE_TIMER.h"

 //空闲任务 
 StackType_t IdleTaskStack[configMINIMAL_STACK_SIZE];
 StaticTask_t IdleTaskTCB;
 
 //定时器任务
 StackType_t TimerTaskStack[configTIMER_TASK_STACK_DEPTH];
 StaticTask_t TimerTaskTCB;

//空闲任务所需内存
void vApplicationGetIdleTaskMemory( StaticTask_t **ppxIdleTaskTCBBuffer, 
									StackType_t **ppxIdleTaskStackBuffer, 
									uint32_t *pulIdleTaskStackSize )
{
	*ppxIdleTaskTCBBuffer=&IdleTaskTCB;
	*ppxIdleTaskStackBuffer=IdleTaskStack;
	*pulIdleTaskStackSize=configMINIMAL_STACK_SIZE;
}

//定时器任务所需内存
void vApplicationGetTimerTaskMemory( StaticTask_t **ppxTimerTaskTCBBuffer, 
									 StackType_t **ppxTimerTaskStackBuffer, 
									 uint32_t *pulTimerTaskStackSize )
{
	*ppxTimerTaskTCBBuffer=&TimerTaskTCB;
	*ppxTimerTaskStackBuffer=TimerTaskStack;
	*pulTimerTaskStackSize=configMINIMAL_STACK_SIZE;
}

