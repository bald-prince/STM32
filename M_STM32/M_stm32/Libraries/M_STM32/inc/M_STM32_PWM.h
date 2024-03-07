#ifndef __M_STM32_PWM_H
#define __M_STM32_PWM_H

#include "stm32f10x.h"

////***************************TIM2 GPIO&Pin***********************************
//#define TIM2_PORT_1		GPIOA

//#define TIM2_CH2_Pin	GPIO_Pin_1			//PA1
//#define TIM2_CH3_Pin	GPIO_Pin_2			//PA2
//#define TIM2_CH4_Pin	GPIO_Pin_3			//PA3

////***************************TIM3 GPIO&Pin***********************************
//#define TIM3_PORT_1		GPIOA 

//#define TIM3_CH1_Pin	GPIO_Pin_6			//PA6
//#define TIM3_CH2_Pin	GPIO_Pin_7			//PA7

//#define TIM3_PORT_2		GPIOB

//#define TIM3_CH3_Pin	GPIO_Pin_0			//PB0
//#define TIM3_CH4_Pin	GPIO_Pin_1			//PB1

////***************************TIM4 GPIO&Pin***********************************
//#define TIM4_PORT_1		GPIOB

//#define TIM4_CH1_Pin	GPIO_Pin_6			//PB6
//#define TIM4_CH2_Pin	GPIO_Pin_7			//PB7
//#define TIM4_CH3_Pin	GPIO_Pin_8			//PB8
//#define TIM4_CH4_Pin	GPIO_Pin_9			//PB9

void M_PWM_Init(uint16_t PTx, uint32_t Freq, float Duty);                       //PWM初始化
void M_PWM_Duty(uint16_t PTx, uint32_t Freq, float Duty);//PWM占空比

#endif
