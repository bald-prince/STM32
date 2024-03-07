#include "M_Servo.h"

/**
  * @brief  舵机角度变换
  * @param  deg 角度，单位度
  * @retval 占空比
  */
float M_DegToDuty(float deg)
{
	return ((DutyMax-DutyMin)/180)*deg+DutyMin;
}

/**
  * @brief  舵机角度控制
  * @param  PTx            控制引脚
  * @param  Deg            角度，单位度
  * @retval None
  */
void M_Servo_Ctl(uint16_t PTx, float Deg)
{
	M_PWM_Duty(PTx, Freq, M_DegToDuty(Deg));
}

/**
  * @brief  舵机初始化
  * @param  PTx           控制引脚
  * @param  Deg           初始角度，单位度  
  * @retval None
  */
void M_Servo_Init(uint16_t PTx, float Deg)
{
	M_PWM_Init(PTx, Freq, M_DegToDuty(Deg));
}



