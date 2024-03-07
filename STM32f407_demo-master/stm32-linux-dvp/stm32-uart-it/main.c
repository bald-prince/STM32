#include "stdio.h"
#include "stdlib.h"
#include "./User/led.h"
#include "./User/delay.h"
#include "./User/uart.h"

//[ DCMI --- DMA ]
//[日期 ：] ---- [ 2020.9.28 ] ----  [ 19.39 ]
//[作者 ：] ---- [ 熊诺晔 ] ---- [ Xiong Nuoye ]
//[版本 ：] ---- [ V1.0  ]
//[License :] ---- [GPL]

u32 BUF_CT;

int main(void)
{
    Sys_Clock_Set(336,8,2,7);
    delay_init(168);
    Led_Init();
    Uart_Init(115200);	

    while(1)
    {
        Led_Flow();
    }
    
    return 0;
}
