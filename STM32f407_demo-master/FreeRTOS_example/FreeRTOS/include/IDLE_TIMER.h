#ifndef _IDLE_TIMER
#define _IDLE_TIMER

#include "FreeRTOS.h"
#include "task.h"
#include "timers.h"

#ifndef INC_FREERTOS_H
	#error "include FreeRTOS.h" must appear in source files before "include queue.h"
#endif

#ifdef __cplusplus
extern "C" {
#endif

//空闲任务
extern StackType_t IdleTaskStack[configMINIMAL_STACK_SIZE];
extern StaticTask_t IdleTaskTCB;

//定时器任务
extern StackType_t TimerTaskStack[configTIMER_TASK_STACK_DEPTH];
extern StaticTask_t TimerTaskTCB;
#ifdef __cplusplus
}
#endif
	
#endif


