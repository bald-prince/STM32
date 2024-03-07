#include "my_dac.h"

/* function defination */\
void MY_DAC_Init(void)
{
	/* ʱ��ʹ�� */
	RCC->APB1ENR |= (1<<29);/* DAC_CLK_ENABLE */
	RCC->AHB1ENR |= (1<<0); /* GPIOA_CLK_ENABLE */
	
	/* GPIO ��ʼ�� */
	GPIOA->MODER |= (0x3F<<6);  /* ����PIN3 4 5Ϊģ��ģʽ */
	GPIOA->OTYPER &= ~(0x7<<3);  /* ����PIN3 4 5Ϊ������� */
	GPIOA->OSPEEDR |= (0x3F<<6);/* ����PIN4�ٶ�Ϊ100Mhz */
	GPIOA->PUPDR &= ~(0x3F<<6);
	GPIOA->PUPDR |= (0x15<<6);   /* ���� */
	
	/* DAC ��ʼ�� */
	DAC->CR &= ~(1<<0);/* disable dac */
	DAC->CR |= (1<<1); /* disable cache of output */
	DAC->CR &= ~(1<<2);/* disable channel tri */
	DAC->CR |= (0x07<<3);/* software tri */
	DAC->CR &= ~(0x03<<6);/* disable wave */
	DAC->CR &= ~(1<<12);/* disable dma */

	DAC->CR |=  (1<<0);/* enable dac */
}
/* DAC_DHR д��12bit 0~4095 to 0~3.3 => DAC_OUT = (val/3.3)*4095*/
void DAC_OUT(float val)
{
	DAC->DHR12R1 = (u16)((val/3.3)*4095);
}







