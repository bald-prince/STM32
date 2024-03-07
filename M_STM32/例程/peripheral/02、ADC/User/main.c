#include "stm32f10x.h"

//ADC1�������(DMA��ʽ���ռ��С5000,һ�βɼ�5000������)
extern __IO uint16_t ADC1_ConvertedValue[5000];

int main(void)
{	
	M_SysTick_Init(); 
	M_USART_Init(USART1, 115200);     //���ڳ�ʼ��

	//��ʼ��ADC
	//ADC1ģ���
	//ADC_CH0_Pin���ײ�ͷ�ļ������Ŷ���
	//ADC_ExternalTrigConv_None����Դ���ò���
	//1 ��ͨ���ɼ�
	//Rank_1����˳��1
	M_ADC_Init(ADC1, ADC_CH0_Pin, ADC_ExternalTrigConv_None, 1, Rank_1);

	printf("This is a test\n");

	while(1)
	{		
		//ADC1_ConvertedValue[0]Ϊ�ɼ���ѹ12λֵ���辭������
		//��AD�ɼ�Ϊ12λ�����Գ���4096
		//��ѹΪ3.3��
		printf("��ǰ��ѹ��%.3f\n", ADC1_ConvertedValue[0]/4096.0*3.3);
	} 
}

