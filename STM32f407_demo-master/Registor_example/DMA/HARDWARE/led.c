#include "led.h"
#include "delay.h"

void Led_Init(void)
{
	GPIO_InitTypeDef  GPIO_Initure;
	__HAL_RCC_GPIOC_CLK_ENABLE();      	
	
	GPIO_Initure.Pin=GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3|GPIO_PIN_4|GPIO_PIN_5|GPIO_PIN_6|GPIO_PIN_7;
	GPIO_Initure.Mode=GPIO_MODE_OUTPUT_PP;
	GPIO_Initure.Pull=GPIO_PULLUP;
	GPIO_Initure.Speed=GPIO_SPEED_FREQ_HIGH;
	HAL_GPIO_Init(GPIOC,&GPIO_Initure);
	
	GPIOC->ODR = 0xFFU;
}

void led_reg_init(void)
{
	/* 使能时钟GPIOC */
	RCC->AHB1ENR |= (1<<2);
	/* GPIO初始化 */
	GPIOC->MODER &= (1<<17);   /* 清空寄存器低16位 */
	GPIOC->MODER |= (0x5555);  /* 配置PIN0~7为输出模式 */
	GPIOC->OTYPER &= (1<<17);  /* 配置PIN0~7为推挽输出 */
	GPIOC->OSPEEDR &= (1<<17); /* 清空低16位 */
	GPIOC->OSPEEDR |= (0xAAAA);/* 设置PIN0~7速度为50Mhz */
	GPIOC->PUPDR &= (1<<17);
	GPIOC->PUPDR |= (0x5555);
	
	/* 初始状态led全灭 */
	GPIOC->ODR = 0x00;
}

void led_flow(void)
{
	static u8 led_flow = 0x01;
	GPIOC->ODR = ~led_flow;
	led_flow <<= 1;
	if(led_flow == 0)
	{
		led_flow = 0x01;
	}
	delay_ms(200);
}

