#include "stdio.h"
#include "./User/led.h"
//[第一个Linux下的STM32项目] -------- [Light LED]
//[日期 ：] ---- [ 2020.9.16 ] ----  [ 16:34 ]
//[作者 ：] ---- [ 熊诺晔 ] ---- [ Xiong Nuoye ]
//[版本 ：] ---- [ V1.0  ]
//[License :] ---- [GPL]
int main(void)
{
    Led_Init();
    mydelay(1000);
    while(1)
    {
        Led_Flash(500);
        //Led_Flow();
    }
    
    return 0;
}
