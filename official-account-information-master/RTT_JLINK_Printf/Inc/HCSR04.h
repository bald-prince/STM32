#ifndef __HCSR04_H
#define __HCSR04_H
#include "stm32f4xx.h"
#include "main.h"
#define HCSR_TRIG_HIGH() HAL_GPIO_WritePin(HC_SR04_Trig_GPIO_Port,HC_SR04_Trig_Pin,GPIO_PIN_SET)
#define HCSR_TRIG_LOW()  HAL_GPIO_WritePin(HC_SR04_Trig_GPIO_Port,HC_SR04_Trig_Pin,GPIO_PIN_RESET)

#define HCSR_ECHO()  HAL_GPIO_ReadPin(HC_SR04_ECHO_GPIO_Port,HC_SR04_ECHO_Pin)
float Distance(uint8_t cnt);

#endif
