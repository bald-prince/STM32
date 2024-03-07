#ifndef __FREERTOS_TASK_H
#define __FREERTOS_TASK_H

#include "FREERTOSConfig.h"
#include "FreeRTOS.h"
#include "task.h"

portBASE_TYPE UserAPP_TaskCreate(void);
void vApplicationTickHook( void );


#endif