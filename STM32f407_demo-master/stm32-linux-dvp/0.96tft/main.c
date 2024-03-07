#include "stdio.h"
#include "stdlib.h"
#include "./User/led.h"
#include "./User/delay.h"
#include "./User/uart.h"
#include "./User/ipsspi.h"

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
    Lcd_Init();

    while(1)
    {
        static u8 ch = 48;
        Gui_DrawFont_char(20,20,ch++);
        Led_Flow();
    }
    
    return 0;
}
