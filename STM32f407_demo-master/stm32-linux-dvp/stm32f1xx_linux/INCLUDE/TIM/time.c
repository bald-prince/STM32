#include "time.h"
#include "../LED/led.h"

static u32 pwm_judge = 0;
/* TIM : 100KHz F(led) : 100_000/256 ~= 390Hz => T(led_flash) : 3ms */
static u32 keep_stat = 0;
/*
* @parm : TIMx for x in range(2 , 7)
*
*/
int Timx_Init(u8 swt_timx,u16 arr,u16 psc)
{
	u32 priority = 0;
	if ( swt_timx == 1 || swt_timx>7 )
		return -1;
	else
		RCC->APB1ENR |= (0x1<<(swt_timx-2)); /* TIMX 时钟使能 */
	switch (swt_timx)
	{
		case 2:TIM2->CR1 &= (~(0x3<<5));     /* TIM2 边沿计数 */
					 TIM2->CR1 |= (0x1<<4);        /* 向下计数 */
					 TIM2->CR1 |= (0x1<<7);        /* 自动重装 */
					 TIM2->CR1 &= (~(0x1<<3));     /* 单脉冲 */
					 // TIM2->CR1 |= (0x1<<2);		 /* 只更新计数器中断 */
					 TIM2->CR1 &= (~(0x1<<1));     /* 允许更新中断 */
					 TIM2->DIER |= (0x1<<0);       /* 打开更新中断*/
					 TIM2->ARR = arr-1;
					 TIM2->PSC = psc-1;
					 NVIC_EnableIRQ(TIM2_IRQn);
					 priority = NVIC_EncodePriority(2,1,0);
					 NVIC_SetPriority(TIM2_IRQn,priority);
					 break;
		default:break;
	}
	return 0;
}

void Timx_Start(u8 swt_timx)
{
	switch (swt_timx)
	{
		case 2:TIM2->CR1 |= (0x1<<0);         /* 开始计数 */
					 break;
		default:break;
	}
}

void Timx_Clear_IT(u8 swt_timx)
{
	switch (swt_timx)
	{
		case 2:TIM2->SR &= (~(0x1<<0));         /* UIF置位 */
					 while (TIM2->SR & 0x1);
					 break;
		default:break;
	}
}

void TIM2_IRQHandler(void)
{
	/* 必须先读SR的更新中断位 */
	static int count_dir = -1;
	static u32 compare_lmt = 0;
	if (TIM2->SR & 0x1)
	{
		/* IRQ SERVER */
		// LED_FLASH();
		if (pwm_judge + 1 == 256)
		{
			if (keep_stat + 1 == 1)
			{
				pwm_compare += count_dir;
				if (pwm_compare == compare_lmt)
				{
					// pwm_compare = 256;
					if (!compare_lmt)
						compare_lmt = 256;
					else
						compare_lmt = 0;
					if (count_dir == -1)
						count_dir = 1;
					else
						count_dir = -1;
				}
			}
			keep_stat = (keep_stat+1)%1; /* 1*3ms = 3ms 保持3ms的该占空比状态 */
		}
		pwm_judge = (pwm_judge+1)%256;   /* acute : 0.0001 */
		if (pwm_judge < pwm_compare)
			GPIOA->ODR |= 0x1<<1;					 /* led on */
		else
			GPIOA->ODR &= ~(0x1<<1);			 /* led off */
	}
	Timx_Clear_IT(2);
}
