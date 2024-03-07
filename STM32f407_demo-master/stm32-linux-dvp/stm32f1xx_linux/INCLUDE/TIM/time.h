#ifndef __TIME_H
#define __TIME_H
#include "../../USER/stm32f10x.h"
#include "../../USER/system_stm32f10x.h"

int Timx_Init(u8 swt_timx,u16 arr,u16 psc);
void Timx_Start(u8 swt_timx);
void TIM2_IRQHandler(void);

extern u32 pwm_compare;

#endif




