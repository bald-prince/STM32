#ifndef __M_SERVO_H
#define __M_SERVO_H

#include "stm32f10x.h"

//==========================舵机参数============================
static float DutyMin = 3.0;                               //0°对应占空比
static float DutyMax = 12.8;                              //180°对应占空比

static uint32_t Freq = 50;                                //舵机频率

void M_Servo_Init(uint16_t PTx, float Deg); //舵机初始化
void M_Servo_Ctl(uint16_t PTx, float Deg);                 //舵机控制

#endif
