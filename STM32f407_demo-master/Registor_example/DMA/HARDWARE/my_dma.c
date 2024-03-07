#include "my_dma.h"
/* Caches */
u8 Caches[DATE_SIZE]={0};
/* function defination */
void DMA_Init(u32 reg_addr ,u32 par_addr ,u16 date_size)
{
	RCC->AHB1ENR|=1<<22;//DMA2 时钟使能
	/* 通道选择 */
	DMA2_Stream7->CR &= ~(1<<0);	  /* 失能DMA */
	DMA2_Stream7->CR &= ~(0x07<<25);/* cls */
	DMA2_Stream7->CR |=  (0x04<<25);/* 选择通道4->USART1_Tx */
	DMA2_Stream7->CR &= ~(0x0F<<21);/* 单次传输 */
	DMA2_Stream7->CR &= ~(0x03<<16);/* cls */
	DMA2_Stream7->CR |=  (0x01<<16);/* priority 中 */
	DMA2_Stream7->CR &= ~(0x03<<13);/* cls */
	DMA2_Stream7->CR |=  (0x00<<13);/* 存储空间按字节划分8bit */
	DMA2_Stream7->CR &= ~(0x03<<11);/* cls */
	DMA2_Stream7->CR |=  (0x00<<11);/* 外设字长8bit */
	DMA2_Stream7->CR |=  (0x01<<10);/* 存储器地址递增 */
	DMA2_Stream7->CR &= ~(0x01<<9); /* 外设地址固定 */
	DMA2_Stream7->CR &= ~(0x01<<8); /* 禁止循环模式 */
	DMA2_Stream7->CR &= ~(0x03<<6); /* cls */
	DMA2_Stream7->CR |=  (0x01<<6); /* 存储器到外设 */
	DMA2_Stream7->NDTR |= date_size;/* 数据大小 */
	DMA2_Stream7->PAR = par_addr;
	DMA2_Stream7->M0AR = reg_addr;
}
/* DMA传送开始 */
void DMA_TX(void)
{
	DMA2_Stream7->NDTR |= DATE_SIZE;/* 减到零了 */
	DMA2_Stream7->CR |= (1<<0);
}


