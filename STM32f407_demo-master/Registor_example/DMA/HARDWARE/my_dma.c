#include "my_dma.h"
/* Caches */
u8 Caches[DATE_SIZE]={0};
/* function defination */
void DMA_Init(u32 reg_addr ,u32 par_addr ,u16 date_size)
{
	RCC->AHB1ENR|=1<<22;//DMA2 ʱ��ʹ��
	/* ͨ��ѡ�� */
	DMA2_Stream7->CR &= ~(1<<0);	  /* ʧ��DMA */
	DMA2_Stream7->CR &= ~(0x07<<25);/* cls */
	DMA2_Stream7->CR |=  (0x04<<25);/* ѡ��ͨ��4->USART1_Tx */
	DMA2_Stream7->CR &= ~(0x0F<<21);/* ���δ��� */
	DMA2_Stream7->CR &= ~(0x03<<16);/* cls */
	DMA2_Stream7->CR |=  (0x01<<16);/* priority �� */
	DMA2_Stream7->CR &= ~(0x03<<13);/* cls */
	DMA2_Stream7->CR |=  (0x00<<13);/* �洢�ռ䰴�ֽڻ���8bit */
	DMA2_Stream7->CR &= ~(0x03<<11);/* cls */
	DMA2_Stream7->CR |=  (0x00<<11);/* �����ֳ�8bit */
	DMA2_Stream7->CR |=  (0x01<<10);/* �洢����ַ���� */
	DMA2_Stream7->CR &= ~(0x01<<9); /* �����ַ�̶� */
	DMA2_Stream7->CR &= ~(0x01<<8); /* ��ֹѭ��ģʽ */
	DMA2_Stream7->CR &= ~(0x03<<6); /* cls */
	DMA2_Stream7->CR |=  (0x01<<6); /* �洢�������� */
	DMA2_Stream7->NDTR |= date_size;/* ���ݴ�С */
	DMA2_Stream7->PAR = par_addr;
	DMA2_Stream7->M0AR = reg_addr;
}
/* DMA���Ϳ�ʼ */
void DMA_TX(void)
{
	DMA2_Stream7->NDTR |= DATE_SIZE;/* �������� */
	DMA2_Stream7->CR |= (1<<0);
}


