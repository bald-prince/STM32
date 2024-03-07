#include "sys.h"
#include "delay.h"
#include "usart.h"
#include "led.h"
#include "oled.h"
#include "key.h"
#include "bmp.h"

/**************************************/
//0.96寸OLED两种驱动方式
//1、u8g2方式
		//u8g2_t u8g2;
		//u8g2Init(&u8g2);
		//找到这两行并取消注释，然后调用u8g2的库即可

//2.常规方式
		//u8g2_t u8g2;
		//u8g2Init(&u8g2);
		//找到这两行并注释，然后调用oled.c里的显示函数即可	

//by YCL
//time:2022.07.02
/**************************************/

int main(void)
{
  	HAL_Init();                   	//初始化HAL库    
  	Stm32_Clock_Init(336,8,2,7);  	//设置时钟,168Mhz
	delay_init(168);               	//初始化延时函数
	uart_init(115200);             	//初始化USART
	LED_Init();											//初始化LED	
	OLED_Init();										//初始化OLED	
	KEY_Init();
	
	u8g2_t u8g2;
	u8g2Init(&u8g2);
	
  	while(1)
	{	
		//OLED_ShowPicture(0,0,128,64,BAR,1);
		//OLED_ShowPicture(0,13,128,64,STMMCU,1);		
		//OLED_DrawGIF(32,0,96,8,31,512,Pencil);
		//OLED_DrawQRCode("https://github.com/whik",1);     //只支持支付宝扫码
		//OLED_DrawQRCode("https://cli.im/",1);
		//OLED_Refresh_Gram();	 //更新显示到OLED
	
		u8g2_FirstPage(&u8g2);
		do{
			draw(&u8g2);
//			u8g2_DrawBox(&u8g2,0,0,20,20);
//			u8g2_DrawBox(&u8g2,20,20,20,20);
//			u8g2_DrawFrame(&u8g2,0,40,20,20);
			//u8g2_SetFont(&u8g2,u8g2_font_px437wyse700b_mr);
			//u8g2_DrawStr(&u8g2,50,15,"YCL");
//			u8g2_DrawStr(&u8g2,42,30,"OLED");
		}while(u8g2_NextPage(&u8g2));

	}
}
