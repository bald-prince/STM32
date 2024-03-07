#ifndef _EXTI_H
#define _EXTI_H
#include "sys.h"


void EXTI_Init(void);
void EXTI0_IRQHandler(void);
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin);
#endif
