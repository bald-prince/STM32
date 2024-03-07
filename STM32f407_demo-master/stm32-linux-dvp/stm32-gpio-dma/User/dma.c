#include "dma.h"

//unsigned char dma_buf[1];

void My_DMA_Init()
{
	/* DMA2时钟使能 */
	RCC->AHB1ENR |= (0x1<<22);  	        //使能DMA2时钟
	DMA2_Stream1->CR &= (~(0x1<<0)); 	//禁止数据流
	/* [ 开始配置 ] */
	//DMA2_Stream7->CR |= (0x1<<4);  		//传输完成中断使能
	//DMA2_Stream1->CR &= (~(0x1<<5));	//DMA是流控制器	
	DMA2_Stream1->CR &= (~(0x3<<6));	//存储器到外设
	DMA2_Stream1->CR |= (0x2<<6);
	DMA2_Stream1->CR &= (~(0x1<<8));	//禁止循环模式
	DMA2_Stream1->CR &= (~(0x1<<9));	//外设非递增
	DMA2_Stream1->CR &= (~(0x1<<10));	//存储器递增
	DMA2_Stream1->CR &= (~(0x3<<11));	//外设数据单字节
	DMA2_Stream1->CR &= (~(0x3<<13));	//存储器数据单字节
	DMA2_Stream1->CR &= (~(0x1<<15));	//外设增量取决于PSIZE位(11~12)
	DMA2_Stream1->CR &= (~(0x3<<16));	//优先级‘中’
	DMA2_Stream1->CR |= (0x01<<16);		
	DMA2_Stream1->CR &= (~(0x1<<18));	//单缓冲
	DMA2_Stream1->CR &= (~(0x3<<21));	//单次传输
	DMA2_Stream1->CR &= (~(0x3<<23));	//单次传输
	DMA2_Stream1->CR &= (~(0x7<<25));
	DMA2_Stream1->CR |= (0x3<<25);		//DMA2 Stream1 channel3
	DMA2_Stream1->M0AR = (u32)&GPIOC->ODR;		//外设地址
	DMA2_Stream1->PAR = (u32)dma_buf;		//内存地址
	DMA2_Stream1->NDTR |= 1;		//data size
	//DMA2_Stream1->FCR  &= (~(0x1<<2));	//prohibit fifo
	/* 中断使能 */
//	MY_NVIC_Init(1,1,70,2);
}
/* TCIE 中断服务 */
//void DMA2_Stream7_IRQHandler()
//{
//	/* 中断服务 */
//
//	/* 中断服务 */
//	
//	/* 中断复位 */
//	DMA2->HISR &= (~(0x1<<27));
//
//}


void My_DMA_Start()
{
	//DMA2_Stream1->NDTR |= 1;
	DMA2_Stream1->CR |= (0x1<<0);		//使能数据流
}


void My_DMA_Stop()
{
	DMA2_Stream1->CR &= (~(0x1<<0));	//失能数据流
	while(DMA2_Stream1->CR & 0x1);
}

