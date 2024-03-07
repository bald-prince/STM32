#include "led.h"

void LED_Init(void)
{
    GPIO_InitTypeDef GPIO_Initure;
    __HAL_RCC_GPIOC_CLK_ENABLE();           							 //开启GPIOF时钟
	
    GPIO_Initure.Pin=GPIO_PIN_0;						  						//PC0
    GPIO_Initure.Mode=GPIO_MODE_OUTPUT_PP;  							//推挽输出
    GPIO_Initure.Pull=GPIO_PULLUP;          							//上拉
    GPIO_Initure.Speed=GPIO_SPEED_HIGH;     							//高速
    HAL_GPIO_Init(GPIOC,&GPIO_Initure);
	
    HAL_GPIO_WritePin(GPIOC,GPIO_PIN_0,GPIO_PIN_SET);			//PC0置1，默认初始化后灯灭
   
}
