#include "uart.h"
#include "string.h"
#include "stdio.h"
#include "stdlib.h"
#include "../LED/led.h"
 
//重映射fputc函数，此函数为多个输出函数的基础函数
int fputc(int ch, FILE *f)
{
	USART1_Write_Byte((u8)ch);
	return ch;
}

u8 recbuf[MAX_BUF_SIZE] = {0};
u8 rec_count = 0;

void uart_init(u32 pclk2,u32 bound)
{ 
	u32 priority;
	float temp;
	u16 mantissa;
	u16 fraction; 
	temp=(float)(pclk2*1000000)/(bound*16);//得到 USARTDIV
	mantissa=temp; //得到整数部分
	fraction=(temp-mantissa)*16; //得到小数部分
	 mantissa<<=4;
	mantissa+=fraction; 
	
	RCC->APB2ENR|=1<<2; //使能 PORTA 口时钟 
	RCC->APB2ENR|=1<<14; //使能串口时钟
	GPIOA->CRH&=0XFFFFF00F;//IO 状态设置
	GPIOA->CRH|=0X000008B0;//IO 状态设置
	RCC->APB2RSTR|=1<<14; //复位串口 1
	RCC->APB2RSTR&=~(1<<14);//停止复位 
	//波特率设置
	USART1->BRR=mantissa; // 波特率设置
	USART1->CR1|=0X200C; //1 位停止,无校验位
	#ifdef EN_USART1_RX //如果使能了接收
	//使能接收中断
	USART1->CR1|=1<<5; //接收缓冲区非空中断使能 
	NVIC_EnableIRQ(USART1_IRQn);
	priority = NVIC_EncodePriority(2,3,2);
	NVIC_SetPriority(USART1_IRQn,priority);
	#endif 
}

void USART1_Write_Byte(u8 dat)
{
	while ( (USART1->SR & (0x1<<6))==0 );
	USART1->DR = dat;
}

void USART1_Printf(char *buf)
{
	for (int len=0;len<strlen(buf);len++)
		USART1_Write_Byte((u8)buf[len]);
}

void USART1_IRQHandler(void)
{
	if (USART1->SR & (0x1<<5) )
	{
		recbuf[rec_count] = USART1->DR;
		rec_count = (rec_count+1)%MAX_BUF_SIZE;
		// USART1_Write_Byte(recbuf[rec_count-1]);
		if (recbuf[rec_count-1] == '\n')
		{
			char *str = (char*)malloc(sizeof(char)*rec_count);
			strncpy(str,(char*)recbuf,rec_count-1);
			printf ("%s",str);
			rec_count = 0;
		}
	}
}



