#include "my_adc.h"

/* function defination */
void MY_ADC_Init()
{
	/* ��ʼ��GPIOʱ�� */
	RCC->AHB1ENR |= (1<<0);/* ʹ��GPIOA_CLK */
	/* ��ʼ��ADCʱ�� */
	RCC->APB2ENR |= (1<<8);/* ʹ��ADC1_CLK */
	
	/* GPIO��ʼ�� */
	/* GPIO��ʼ�� */
	GPIOA->MODER &= ~(0x03<<10);     /* ���GPIOA_PIN_5 */
	GPIOA->MODER |= (0x03<<10);      /* ����GPIOA_PIN_5Ϊģ��ģʽ */
	GPIOA->OTYPER &= ~(1<<5);  		   /* OTTYPE��λ */
	GPIOA->OSPEEDR &= ~(0x03<<10); 	 /* ���GPIOA_PIN_5 */
	GPIOA->OSPEEDR |= (0x03<<10);		 /* ����GPIOA_PIN_5�ٶ�Ϊ100Mhz */
	GPIOA->PUPDR &= ~(0x01<<10);     /* ���� */     

	/* ADC��ʼ�� */
	ADC1->CR2 &= ~(1<<0);            /* disable adc1 */
	ADC->CCR  |= (0x1<<16);          /* 84/4 = 21Mhz */
  ADC1->CR1  =  0;                 /* Reset CR1 */
	ADC1->CR2  =  0;
	ADC1->CR1 &= ~(0x3<<24);         /* 12bit */
	ADC1->SMPR2 |= (0x07<<15);        /* 480 �������� */
	ADC1->SQR1 &= ~(0xF<<20);        /* ֻת����������һ */
	ADC1->SQR3 |= (0x5<<0);          /* ͨ����Ĳ���ֵ�ŵ���������һ�� */
	ADC1->CR1 |=  (0x1<<11);         /* enable rul channel acquire */
	ADC1->CR2 |=  (1<<0);            /* enable adc1 */
}

float Get_Adc_Val(void)
{
	  u16 tmp;
		ADC1->CR2 |=  (1<<30);           /* open rul channel */
		while( ( ADC1->SR & (0x1<<1) ) == 0 );
		tmp = ADC1->DR;
		return (float)(tmp/4095.00)*3.3;
}

float Get_Average_Adc(u16 times)
{
	u16 ii;
	float ave_tmp = 0;
  for(ii=0;ii<times;ii++)
	{
		ave_tmp += Get_Adc_Val();
	}
	return ave_tmp/ii;
}

