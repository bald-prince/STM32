#include "uart.h"
#include "delay.h"
#include "string.h"
/* uart init */

void Uart_Init(u32 boundrate)
{
	/* 初始化Uart_X */
	//1.0--[IO时钟初始化]
	RCC->AHB1ENR |= (0x1<<0);//使能GPIOA
	RCC->APB2ENR |= (0x1<<4);//使能Uart_X
	//1.1--[GPIO初始化]
  	GPIOA->MODER  &= (~(0xf<<18));  // [ 清零 ]
	GPIOA->MODER  |=   (0xa<<18);	// [ 复用模式 ]
	GPIOA->OTYPER &= (~(0x3<<9));	// [ 推挽输出 ]
	GPIOA->PUPDR  &= (~(0xf<<18));	// [ 上拉 ]
	GPIOA->PUPDR  |=   (0x5<<18);  	// [ 上拉 ]
	GPIOA->AFR[1]   &= (~(0xff<<4));	// [ 清零 ]
	GPIOA->AFR[1]   |=   (0x77<<4);	// [ PA9,10 --> AF7 ]
       	//1.2--[Uart配置初始化]
	USART1->CR1 &= (~(0x1<<10)); // [ 无奇偶校验 ]
	USART1->CR1 &= (~(0x1<<12)); // [ 8位数据位  ]
	USART1->CR1 &= (~(0x1<<15)); // [ 16倍过采样 ]
	//USART1->USART_CR1 |= (1<<2);	   // [ 接收使能 ]
	//USART1->USART_CR1 |= (1<<3);	   // [ 发送使能 ]
	//USART1->USART_CR1 |= (1<<13);    // [ 串口使能 ]
	USART1->CR2 &= (~(0x3<<12));  // [ 1h个停止位 ]
	
	//1.3--[配置波特率]
	//[ 已知boundrate --> 115200 ]
	//[ FCK = 8M ]
	//[ boundrate = FCK / 8x(2-OVER8)*USARTDIV ]
	//[ Need 8.625 --> 0x8a ]
	float tmp = (float)(84*1000000) / (boundrate*16);
	u16 intn = tmp;
	u16 flon = (tmp - intn)*16;
	intn <<= 4;
	intn += flon;
	USART1->BRR &= (~(0xffff<<0));
	USART1->BRR |= intn;
	
	USART1->CR1 |= (1<<2);	   // [ 接收使能 ]
	USART1->CR1 |= (1<<3);	   // [ 发送使能 ]
	USART1->CR1 |= (1<<13);      // [ 串口使能 ]
	

}

u8 USART_Tx_Byte(u8 ch)
{
	USART1->DR |= ch;
	while( !(USART1->SR&(0x1<<6)) );// [ 发送完毕 ]
	return 0;	
}

void USART_Tx_String(char* str)
{
	unsigned int len = strlen(str);
	for(int i=0;i<len;i++)
		USART_Tx_Byte(str[i]);
	delay_us(10);
}

