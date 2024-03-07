#include "stm32f10x.h"

//ADC1采样结果(DMA方式，空间大小5000,一次采集5000个数据)
extern __IO uint16_t ADC1_ConvertedValue[5000];

int main(void)
{	
	M_SysTick_Init(); 
	M_USART_Init(USART1, 115200);     //串口初始化

	//初始化ADC
	//ADC1模块号
	//ADC_CH0_Pin见底层头文件中引脚定义
	//ADC_ExternalTrigConv_None触发源常用参数
	//1 单通道采集
	//Rank_1采样顺序1
	M_ADC_Init(ADC1, ADC_CH0_Pin, ADC_ExternalTrigConv_None, 1, Rank_1);

	printf("This is a test\n");

	while(1)
	{		
		//ADC1_ConvertedValue[0]为采集电压12位值，需经过换算
		//因AD采集为12位，所以除以4096
		//电压为3.3伏
		printf("当前电压：%.3f\n", ADC1_ConvertedValue[0]/4096.0*3.3);
	} 
}

