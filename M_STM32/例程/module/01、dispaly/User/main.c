#include "stm32f10x.h"

//引脚定义在库文件中修改
//Max7219_pinDIN	    B9
//Max7219_pinCS			B8
//Max7219_pinCLK	    B7

int main(void)
{	
	M_SysTick_Init();                   //Systic时钟初始化
   
    Init_MAX7219();   //初始化屏幕
	Clear_Display();  //清空屏幕显示
	
	while(1)
	{		
		Number_Display(35);   //滚动显示数字35
	}
}

