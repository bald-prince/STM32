#ifndef __USER_DELAY_H
#define	__USER_DELAY_H

#include "stm32f4xx.h"
void user_delaynus_tim(uint32_t nus);
void delay_ms_tim(uint16_t nms);
void HAL_Delay_us_init(uint8_t SYSCLK);
void HAL_Delay_us(uint32_t nus);
void for_delay_us(uint32_t nus);



#endif
