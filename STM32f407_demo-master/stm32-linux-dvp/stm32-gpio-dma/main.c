#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "./User/led.h"
#include "./User/delay.h"
#include "./User/uart.h"
#include "./User/dma.h"

//[ DMA ]
//[日期 ：] ---- [ 2020.9.28 ] ----  [ 19.39 ]
//[作者 ：] ---- [ 熊诺晔 ] ---- [ Xiong Nuoye ]
//[版本 ：] ---- [ V1.0  ]
//[License :] ---- [GPL]

u32 BUF_CT;
unsigned char dma_buf[1] = {0};
const unsigned char str[] = "DMA Test --- [Creator:XNY].";

int main(void)
{
    int len;
    Sys_Clock_Set(336,8,2,7);
    delay_init(168);
    Led_Init();
    Uart_Init(115200);	
    My_DMA_Init();		
    while(1)
    {
        //Led_Flow();
	static u8 flow = 0x1;
	dma_buf[0] |= ~flow;
        USART_Tx_String("dma buf:");
	USART_Tx_Byte(dma_buf[0]);
        USART_Tx_String("\r\n");
	My_DMA_Start();
        USART_Tx_String("DMA START!\r\n");
	delay_ms(100);
	while(DMA2_Stream1->CR & 0x1);
	flow <<= 1;
	if(flow == 0)
		flow = 0x1;
	if(DMA2_Stream1->NDTR > 0)
        	USART_Tx_String("ReMin Data > 1!\r\n");
	else
        	USART_Tx_String("DMA COMPLETE!\r\n");
   	
        USART_Tx_String("dma buf:");
	USART_Tx_Byte(dma_buf[0]);
        USART_Tx_String("\r\n");
    }
    
    return 0;
}
