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
unsigned char dma_buf[4096] = {0};
const unsigned char str[] = "DMA Test --- [Creator:XNY].";

int main(void)
{
    int len;
    Sys_Clock_Set(336,8,2,7);
    delay_init(168);
    Led_Init();
    Uart_Init(115200);	
    My_DMA_Init();		
	
    /* pack buf */
    len = strlen(str);
    for(int i=0;i<4096/len;i++)
    {
	sprintf(&dma_buf[i*len],"%s",str);
    }
    delay_ms(5000);
    My_DMA_Start();

    while(1)
    {
        Led_Flow();
    }
    
    return 0;
}
