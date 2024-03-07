#include "user_delay.h"
#include "main.h"

extern TIM_HandleTypeDef htim2;
/*
	ʹ����ͨ��ʱ����ʽʵ��
*/
void user_delaynus_tim(uint32_t nus)
{
	//������ʱ��
	uint16_t  differ = 0xffff-nus-5;
	
  __HAL_TIM_SetCounter(&htim2,differ);       	// ���ϴ���ʱ�����ļ�������
  HAL_TIM_Base_Start(&htim2);

  while( differ<0xffff-5) 
	{
		differ = __HAL_TIM_GetCounter(&htim2);
	};		
 
  HAL_TIM_Base_Stop(&htim2);
	
}

void delay_ms_tim(uint16_t nms)
{
	uint32_t i;
	for(i=0;i<nms;i++) user_delaynus_tim(1000);
}



/*
ʹ��systickʵ��
*/
uint32_t fac_us;

void HAL_Delay_us_init(uint8_t SYSCLK)
{
     fac_us=SYSCLK; 
}

void HAL_Delay_us(uint32_t nus)
{
    uint32_t ticks;
    uint32_t told,tnow,tcnt=0;
    uint32_t reload=SysTick->LOAD;
    ticks=nus*fac_us; 
    told=SysTick->VAL; 
    while(1)
    {
        tnow=SysTick->VAL;
        if(tnow!=told)
        {
            if(tnow<told)tcnt+=told-tnow;
            else tcnt+=reload-tnow+told;
            told=tnow;
            if(tcnt>=ticks)break; 
        }
    };
}

/*
ʹ��forѭ��ʵ��
*/
void for_delay_us(uint32_t nus)
{
	uint32_t Delay = nus * 168/4;
	do
	{
		__NOP();
	}
	while (Delay --);
}



