#include "beep.h"
void BEEP_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
    __HAL_RCC_GPIOF_CLK_ENABLE();

    GPIO_InitStructure.Pin=GPIO_PIN_2;            
    GPIO_InitStructure.Mode=GPIO_MODE_OUTPUT_PP;      
    GPIO_InitStructure.Pull=GPIO_PULLDOWN;        
    GPIO_InitStructure.Speed=GPIO_SPEED_FREQ_HIGH;     
    HAL_GPIO_Init(GPIOF,&GPIO_InitStructure);	
    HAL_GPIO_WritePin(GPIOF,GPIO_PIN_2,GPIO_PIN_RESET);
	
}



