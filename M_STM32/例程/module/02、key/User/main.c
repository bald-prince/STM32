#include "stm32f10x.h"

extern KEY_Event key_val;

int main(void)
{
	M_SysTick_Init();
	M_USART_Init(USART1, 115200);    //初始化串口
	
	key_event_init();     //定义按键对应的引脚A0, A1, A2, A3
	
	M_TIMx_Init(TIM1, 10);    
	M_TIMx_NVIC_Configuration(TIM1, NVIC_PriorityGroup_0, LEVEL_0, LEVEL_0);
	M_TIMx_Switch(TIM1, ENABLE);
	
	printf("This is a test\n");
	
	while(1)
	{
		deal_key_enent();    //按键状态处理
		
		printf("UP = %d,  DOWN = %d,  L = %d,  R = %d\n", key_val.up, key_val.down, key_val.dec, key_val.add);
	}
}

