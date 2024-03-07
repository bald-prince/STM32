#include "my_adc.h"

/* function defination */
void MY_ADC_Init()
{
	/* 初始化GPIO时钟 */
	RCC->AHB1ENR |= (1<<0);/* 使能GPIOA_CLK */
	/* 初始化ADC时钟 */
	RCC->APB2ENR |= (1<<8);/* 使能ADC1_CLK */
	
	/* GPIO初始化 */
	/* GPIO初始化 */
	GPIOA->MODER &= ~(0x03<<10);     /* 清空GPIOA_PIN_5 */
	GPIOA->MODER |= (0x03<<10);      /* 配置GPIOA_PIN_5为模拟模式 */
	GPIOA->OTYPER &= ~(1<<5);  		   /* OTTYPE复位 */
	GPIOA->OSPEEDR &= ~(0x03<<10); 	 /* 清空GPIOA_PIN_5 */
	GPIOA->OSPEEDR |= (0x03<<10);		 /* 设置GPIOA_PIN_5速度为100Mhz */
	GPIOA->PUPDR &= ~(0x01<<10);     /* 上拉 */     

	/* ADC初始化 */
	ADC1->CR2 &= ~(1<<0);            /* disable adc1 */
	ADC->CCR  |= (0x1<<16);          /* 84/4 = 21Mhz */
  ADC1->CR1  =  0;                 /* Reset CR1 */
	ADC1->CR2  =  0;
	ADC1->CR1 &= ~(0x3<<24);         /* 12bit */
	ADC1->SMPR2 |= (0x07<<15);        /* 480 采样周期 */
	ADC1->SQR1 &= ~(0xF<<20);        /* 只转换规则序列一 */
	ADC1->SQR3 |= (0x5<<0);          /* 通道五的采样值放到规则序列一中 */
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

