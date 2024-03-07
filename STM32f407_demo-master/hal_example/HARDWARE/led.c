#include "led.h"


void Led_Init(void)
{
	GPIO_InitTypeDef  GPIO_Initure;
	__HAL_RCC_GPIOF_CLK_ENABLE();    
  __HAL_RCC_GPIOE_CLK_ENABLE();  	
	
	GPIO_Initure.Pin=GPIO_PIN_9|GPIO_PIN_10;
	GPIO_Initure.Mode=GPIO_MODE_OUTPUT_PP;
	GPIO_Initure.Pull=GPIO_PULLUP;
	GPIO_Initure.Speed=GPIO_SPEED_FREQ_HIGH;
	HAL_GPIO_Init(GPIOF,&GPIO_Initure);
	
	GPIO_Initure.Pin=GPIO_PIN_13|GPIO_PIN_14;
	GPIO_Initure.Mode=GPIO_MODE_OUTPUT_PP;
	GPIO_Initure.Pull=GPIO_PULLUP;
	GPIO_Initure.Speed=GPIO_SPEED_FREQ_HIGH;
	HAL_GPIO_Init(GPIOE,&GPIO_Initure);
	
	PFout(9) = 0;
	PFout(10) = 0;
	
	PFout(13) = 0;
	PFout(14) = 0;
}

