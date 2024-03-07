#include "HCSR04.h"
#include "user_delay.h"
extern TIM_HandleTypeDef htim2;

uint16_t msHcCount = 0;//ms

void HCSR04StartTrigStart(void)
{
	HCSR_TRIG_HIGH();
	//delay_us(20);
	HAL_Delay(2);
	HCSR_TRIG_LOW();
}

//mode=1-->open timer 
//mode=0-->close timer
void HCSR04_TimerFunc(uint8_t mode)
{
	if(mode)
	{
		__HAL_TIM_SetCounter(&htim2,0);
		HAL_TIM_Base_Start(&htim2);
		HAL_TIM_Base_Start_IT(&htim2);
		msHcCount = 0;
	}
	else
	{
		HAL_TIM_Base_Stop(&htim2);
		HAL_TIM_Base_Stop_IT(&htim2);
	}
}

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
	if(htim->Instance == TIM2)
	{
		msHcCount++;
	}
}

float	HCSR04_Get_Time(void)
{
	HCSR04StartTrigStart();
	while(!HCSR_ECHO());
	HCSR04_TimerFunc(1);//开启定时器，开始测量
	while(HCSR_ECHO());
	HCSR04_TimerFunc(0);//关闭定时器，停止测量
	
	return (__HAL_TIM_GetCounter(&htim2))*340/2*100;
}
