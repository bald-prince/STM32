#include "led.h"
#include "delay.h"

void LED_Init(void)
{
    GPIO_InitTypeDef GPIO_Initure;
    __HAL_RCC_GPIOC_CLK_ENABLE();           							 //开启GPIOF时钟
	
    GPIO_Initure.Pin=GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3|GPIO_PIN_4|GPIO_PIN_5|GPIO_PIN_6|GPIO_PIN_7;						  		//PC0
    GPIO_Initure.Mode=GPIO_MODE_OUTPUT_PP;  							//推挽输出
    GPIO_Initure.Pull=GPIO_PULLUP;          							//上拉
    GPIO_Initure.Speed=GPIO_SPEED_HIGH;     							//高速
    HAL_GPIO_Init(GPIOC,&GPIO_Initure);
	
    GPIOC->ODR=0xff;		
}

void LED_light(void)
{
	LED0=0;
	delay_ms(500);
	LED0=1;
}
