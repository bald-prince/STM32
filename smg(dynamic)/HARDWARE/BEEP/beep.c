#include "beep.h"
#include "delay.h"

void BEEP_Init(void)
{
    GPIO_InitTypeDef GPIO_Initure;
    __HAL_RCC_GPIOF_CLK_ENABLE();           //开启GPIOF时钟
	
    GPIO_Initure.Pin=GPIO_PIN_2; 						//PF2
    GPIO_Initure.Mode=GPIO_MODE_OUTPUT_PP;  //推挽输出
    GPIO_Initure.Pull=GPIO_PULLUP;          //上拉
    GPIO_Initure.Speed=GPIO_SPEED_HIGH;     //高速
    HAL_GPIO_Init(GPIOF,&GPIO_Initure);
	
    HAL_GPIO_WritePin(GPIOF,GPIO_PIN_2,GPIO_PIN_RESET);	//蜂鸣器对应引脚GPIOF2拉低，
}

void BEEP_Sound(void)
{
	BEEP=1;
	delay_ms(400);
	BEEP=0;
}
