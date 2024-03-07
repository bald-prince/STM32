#include "my_uart.h"
#include "string.h"
#include "delay.h"
#include "stdlib.h"
#include "stdio.h"
/* Ex */
int fputc(int ch,FILE *stream)
{
	uart_Ts_Byte(ch);
	return ch;
}
/* Ts_buffer */
u8 Tx_buf[200]="������һ���ֽڵ��ַ���\n";
u8 Rx_buf[200]={0};
/* �������� */
/* ���ڳ�ʼ�� */
void my_uart_init(void)
{
	float tmp =(float)(84*1000000)/(115200*16);
	u16 int_nmu = tmp;
	u16 float_num = (tmp - int_nmu)*16;
	int_nmu <<= 4;
	int_nmu += float_num;
	/* ���ڸ���IO��ʼ�� */
	/* ʹ��ʱ��GPIOA */
	RCC->AHB1ENR |= (1<<0);
	/* ʹ�ܴ���ʱ��  */
	RCC->APB2ENR |= (1<<4);
	/* GPIO��ʼ�� */
	GPIOA->MODER &= ~(0x0F<<18);     /* ��ռĴ���GPIO9,10ģʽ����λ */
	GPIOA->MODER |=  (0x0A<<18);     /* ����PIN9,10Ϊ����ģʽ */
	GPIOA->AFR[1] &= ~(0xFF<<4);     /* ���AFRH-PIN9,10 */
	GPIOA->AFR[1] |=  (0x77<<4);     /* ����ΪAF7 */
	GPIOA->OTYPER &= ~(0x03<<9); 		 /* ����PIN9,10Ϊ������� */
	GPIOA->OSPEEDR &= ~(0x0F<<18);   /* ��ռĴ���GPIO9,10 */
	GPIOA->OSPEEDR |= (0x0A<<18);		 /* ����PIN0~7�ٶ�Ϊ50Mhz */
	GPIOA->PUPDR &= ~(0x0F<<18);		 /* �������� */
	GPIOA->PUPDR |= (0x05<<18);
	
	/* ���ڳ�ʼ�� */
	/* over8=0
		 disable usart
		 data 8bit
		 disable PCE
		 enable TS
		 enable Rs
	*/
	USART1->CR1 &= ~(1<<15); /* OVER8 = 0*/
	USART1->CR1 &= ~(1<<13); /* ʧ�ܴ���һ */
	USART1->CR1 &= ~(1<<12); /* ����λ8λ */
	USART1->CR1 &= ~(1<<10); /* ����żУ�� */
	USART1->CR1 |= 0x000C ;  /* ʹ�ܷ��ͽ��� */
	/* 1λֹͣλ */  
	USART1->CR2 &= ~(0x03<<12);/* ����12��13λ */
	/* ��Ӳ������ */
	USART1->CR3 &= ~(1<<8);
	/* ���ò�����115200 */
	USART1->BRR &= ~(1<<15);
	USART1->BRR = int_nmu;
/* ʹ�ܴ��ڽ����ж� */
#ifdef UART1_REC_IT
/* NVIC ʹ�� UART */
	NVIC_EnableIRQ(USART1_IRQn);
/* NVIC �����ж����ȼ� */
  HAL_NVIC_SetPriority(USART1_IRQn,3,1);
/* ���ڽ����ж�ʹ�� */
  USART1->CR1 |= (1<<5);
#endif
	/* ʹ�ܴ��� */
	USART1->CR1 |= (1<<13);
}

/* ���ڷ���һ���ֽڣ�8bit��*/
void uart_Ts_Byte(unsigned char ch)
{
	USART1->DR = ch;
	while(USART1->SR&(1<<6))
		USART1->SR &= ~(1<<6);
	/* ��ձ�־λ��Ҫ��������ʱ */
	delay_us(85);
}

void uart_print(unsigned char *ptr)
{
	u8 len;
	u8 s_len;
	len= strlen((char*)ptr);
	s_len = len;
	while(len--)
	{
		uart_Ts_Byte(ptr[s_len - len-1]);
	}
}

/* ���� */
/* ���ڽ���һ���ֽڣ�8bit��*/
void uart_Rs_Byte(void)
{
	u8 rec;
	while(1)
	{
		if( USART1->SR&(1<<5) )
		{
			uart_print("������һ�ֽڵ��ַ���\n");
			rec = USART1->DR;
			uart_Ts_Byte(rec);
		}
	}
}

/* Extern mode */
/* �жϷ����� */
void USART1_IRQHandler(void)
{
	u8 *rec=(u8*)malloc(sizeof(u8));
	if( USART1->SR&(1<<5) )
	{
		*rec = USART1->DR;
		//uart_Ts_Byte(*rec);
		strcat((char*)Rx_buf,(char*)rec);
		if( strlen( (char*)Rx_buf ) == 10)
		{
			uart_print(Rx_buf);
			memset( (char*)Rx_buf,0,strlen( (char*)Rx_buf ) );
		}
		free(rec);
	}
}







