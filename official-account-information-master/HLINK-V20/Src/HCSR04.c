#include "HCSR04.h"
#include "user_delay.h"
extern TIM_HandleTypeDef htim2;

uint16_t msHcCount = 0;//ms

void HCSR04StartTrigStart(void)
{
	HCSR_TRIG_HIGH();
	for_delay_us(20);
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
		//HAL_TIM_Base_Start_IT(&htim2);
		msHcCount = 0;
	}
	else
	{
		HAL_TIM_Base_Stop(&htim2);
		//HAL_TIM_Base_Stop_IT(&htim2);
	}
}

//void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
//{
//	if(htim->Instance == TIM2)
//	{
//		msHcCount++;
//	}
//}
//单次获得测量距离
float	HCSR04_Get_Distant(void)
{
	HCSR04StartTrigStart();
	while(!HCSR_ECHO());
	HCSR04_TimerFunc(1);//开启定时器，开始测量
	while(HCSR_ECHO());
	HCSR04_TimerFunc(0);//关闭定时器，停止测量
	
	return (__HAL_TIM_GetCounter(&htim2))/58.0;
}

//均值滤波法减小误差
float Distance(uint8_t cnt)
{
	float sum = 0;
	for(int i =0;i<cnt;i++)
	{
		sum+=HCSR04_Get_Distant();
	}
	
	
	return sum/cnt;
}
