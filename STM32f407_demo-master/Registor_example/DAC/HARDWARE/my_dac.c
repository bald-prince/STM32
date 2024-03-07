#include "my_dac.h"

/* function defination */\
void MY_DAC_Init(void)
{
	/* 时钟使能 */
	RCC->APB1ENR |= (1<<29);/* DAC_CLK_ENABLE */
	RCC->AHB1ENR |= (1<<0); /* GPIOA_CLK_ENABLE */
	
	/* GPIO 初始化 */
	GPIOA->MODER |= (0x3F<<6);  /* 配置PIN3 4 5为模拟模式 */
	GPIOA->OTYPER &= ~(0x7<<3);  /* 配置PIN3 4 5为推挽输出 */
	GPIOA->OSPEEDR |= (0x3F<<6);/* 设置PIN4速度为100Mhz */
	GPIOA->PUPDR &= ~(0x3F<<6);
	GPIOA->PUPDR |= (0x15<<6);   /* 上拉 */
	
	/* DAC 初始化 */
	DAC->CR &= ~(1<<0);/* disable dac */
	DAC->CR |= (1<<1); /* disable cache of output */
	DAC->CR &= ~(1<<2);/* disable channel tri */
	DAC->CR |= (0x07<<3);/* software tri */
	DAC->CR &= ~(0x03<<6);/* disable wave */
	DAC->CR &= ~(1<<12);/* disable dma */

	DAC->CR |=  (1<<0);/* enable dac */
}
/* DAC_DHR 写入12bit 0~4095 to 0~3.3 => DAC_OUT = (val/3.3)*4095*/
void DAC_OUT(float val)
{
	DAC->DHR12R1 = (u16)((val/3.3)*4095);
}







