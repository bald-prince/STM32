#include "../INCLUDE/LED/led.h"
#include "../INCLUDE/TIM/time.h"
#include "../INCLUDE/UART/uart.h"
#include "stdio.h"
#include "../INCLUDE/SEG/seg.h"
//ALIENTEK战舰STM32开发板 实验1
//跑马灯 实验  
//技术支持：www.openedv.com
//广州市星翼电子科技有限公司
void delay_uncertain(unsigned int times);
int System_Clock_Init(u8 plldiv);

u32 pwm_compare = 256;
u8 array[] = {2,0,1,7,4,0,3,9};

int main(void)
{				  
	NVIC_SetPriorityGrouping(2);
	System_Clock_Init(16);
	LED_Init();		  	//初始化与LED连接的硬件接口
	// Timx_Init(2,32,10);     // TIM2 DEP APB1 : 32MHz 32_000_000 / 32 : 1_000_000 / 10 : 100_000Hz : 100KHz
	// Timx_Start(2);
	/* 10Hz 中断LED跳变一次 闪烁频率为 : 5Hz : 200ms为一周期 */
	HC595_IO_Init();
	uart_init(64,9600);
	while(1)
	{
		// LED_FLASH();
		// delay_uncertain(0x7ff);
		// USART1_Printf("hellow");
		// printf ("{pwm_duty:[%d] pwm_cmp:[%d]}\r\n",(int)((pwm_compare/256.0)*100),pwm_compare);
		// delay_uncertain(500);
		SEG_DISPLAY(array);
	}	 
}

void delay_uncertain(unsigned int times)
{
	for (int i=0;i<times;i++)
	{
		;
	}
}
/*
* @parm : HSI 8MHz
* @parm : PLL INPUT SWITCH HSI/2 : 4MHz
* @parm : PLL CLK : 4*16 : 64MHz
* @parm : SWITCH SYSCLK AS PLLCLK (MAX : 72MHZ)
* @parm : AHB DIV 1 : 64MHz (MAX : 72MHZ)
* @parm : PLLOUT - SYSCLK : 64MHz
* @parm : APB1 DIV 2 : 32MHz
* @parm : APB2 DIV 1 : 64MHz
*/
int System_Clock_Init(u8 plldiv)
{
	u8 temp = 0x0;
	/* 系统复位 && 未设置HSE时钟，系统默认使用HSI且不能停止 */
	if ( !( RCC->CR & (0x1<<1) ) ) /* 检测HSI是否稳定 */
		return -1;
	RCC->CFGR &= (~(0x1<<16));     /* 设置pll输入时钟源为HSI:4MHz */
	RCC->CFGR |= ((plldiv-2)<<16);		 /* 设置pllmul倍频系数 pllout: 4Mhz*plldiv */
	RCC->CFGR &= (~(0x1<<7));      /* AHB DIV 1 */
	RCC->CFGR &= (~(0x7<<8));
	RCC->CFGR |= (0x4<<8);				 /* APB1 DIV 2 */
	RCC->CFGR &= (~(0x1<<13));     /* APB2 DIV 1 */
	FLASH->ACR|=0x32; 						 //FLASH 2 个延时周期
	RCC->CR |= 0x01000000; 				 /* pll on */
	while(!(RCC->CR>>25)); 				 //等待 PLL 锁定
	RCC->CFGR|=0x00000002; 				 //PLL 作为系统时钟
	while(temp!=0x02) 						 //等待 PLL 作为系统时钟设置成功
	{ 
		temp=RCC->CFGR>>2;
		temp&=0x03;
	} 
	return 0;
}
