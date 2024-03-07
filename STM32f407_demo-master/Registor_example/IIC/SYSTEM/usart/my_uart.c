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
u8 Tx_buf[200]="请输入一个字节的字符！\n";
u8 Rx_buf[200]={0};
/* 函数定义 */
/* 串口初始化 */
void my_uart_init(void)
{
	float tmp =(float)(84*1000000)/(115200*16);
	u16 int_nmu = tmp;
	u16 float_num = (tmp - int_nmu)*16;
	int_nmu <<= 4;
	int_nmu += float_num;
	/* 串口复用IO初始化 */
	/* 使能时钟GPIOA */
	RCC->AHB1ENR |= (1<<0);
	/* 使能串口时钟  */
	RCC->APB2ENR |= (1<<4);
	/* GPIO初始化 */
	GPIOA->MODER &= ~(0x0F<<18);     /* 清空寄存器GPIO9,10模式配置位 */
	GPIOA->MODER |=  (0x0A<<18);     /* 配置PIN9,10为复用模式 */
	GPIOA->AFR[1] &= ~(0xFF<<4);     /* 清空AFRH-PIN9,10 */
	GPIOA->AFR[1] |=  (0x77<<4);     /* 复用为AF7 */
	GPIOA->OTYPER &= ~(0x03<<9); 		 /* 配置PIN9,10为推挽输出 */
	GPIOA->OSPEEDR &= ~(0x0F<<18);   /* 清空寄存器GPIO9,10 */
	GPIOA->OSPEEDR |= (0x0A<<18);		 /* 设置PIN0~7速度为50Mhz */
	GPIOA->PUPDR &= ~(0x0F<<18);		 /* 设置上拉 */
	GPIOA->PUPDR |= (0x05<<18);
	
	/* 串口初始化 */
	/* over8=0
		 disable usart
		 data 8bit
		 disable PCE
		 enable TS
		 enable Rs
	*/
	USART1->CR1 &= ~(1<<15); /* OVER8 = 0*/
	USART1->CR1 &= ~(1<<13); /* 失能串口一 */
	USART1->CR1 &= ~(1<<12); /* 数据位8位 */
	USART1->CR1 &= ~(1<<10); /* 无奇偶校验 */
	USART1->CR1 |= 0x000C ;  /* 使能发送接收 */
	/* 1位停止位 */  
	USART1->CR2 &= ~(0x03<<12);/* 清零12，13位 */
	/* 无硬件流控 */
	USART1->CR3 &= ~(1<<8);
	/* 设置波特率115200 */
	USART1->BRR &= ~(1<<15);
	USART1->BRR = int_nmu;
/* 使能串口接收中断 */
#ifdef UART1_REC_IT
/* NVIC 使能 UART */
	NVIC_EnableIRQ(USART1_IRQn);
/* NVIC 设置中断优先级 */
  HAL_NVIC_SetPriority(USART1_IRQn,3,1);
/* 串口接收中断使能 */
  USART1->CR1 |= (1<<5);
#endif
	/* 使能串口 */
	USART1->CR1 |= (1<<13);
}

/* 串口发送一个字节（8bit）*/
void uart_Ts_Byte(unsigned char ch)
{
	USART1->DR = ch;
	while(USART1->SR&(1<<6))
		USART1->SR &= ~(1<<6);
	/* 清空标志位需要加物理延时 */
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

/* 阻塞 */
/* 串口接收一个字节（8bit）*/
void uart_Rs_Byte(void)
{
	u8 rec;
	while(1)
	{
		if( USART1->SR&(1<<5) )
		{
			uart_print("请输入一字节的字符：\n");
			rec = USART1->DR;
			uart_Ts_Byte(rec);
		}
	}
}

/* Extern mode */
/* 中断服务函数 */
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







