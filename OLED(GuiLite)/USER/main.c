#include "sys.h"
#include "delay.h"
#include "usart.h"
#include "led.h"
#include "oled.h"
#include "key.h"
#include "bmp.h"

//画点函数接口
void gfx_draw_pixel(int x, int y, unsigned int rgb)
{
    OLED_DrawPoint(x,y,rgb);
}
//画面函数(未使用)
void gfx_draw_fill(int x, int y,int w, int q, unsigned int rgb)
{ 
}
//创建一个函数指针结构体
struct EXTERNAL_GFX_OP
{
 void (*draw_pixel)(int x, int y, unsigned int rgb);
 void (*fill_rect)(int x0, int y0, int x1, int y1, unsigned int rgb);
} my_gfx_op;

extern void startHelloCircle(void* phy_fb, int width, int height, int color_bytes, struct EXTERNAL_GFX_OP* gfx_op);

int main(void)
{
	//u8 t=0; 
	u8 temp = 1;

  HAL_Init();                   	//初始化HAL库    
  Stm32_Clock_Init(336,8,2,7);  	//设置时钟,168Mhz
	delay_init(168);               	//初始化延时函数
	uart_init(115200);             	//初始化USART
	LED_Init();						//初始化LED	
	OLED_Init();					//初始化OLED	
	KEY_Init();
	
	//传递函数指针
	my_gfx_op.draw_pixel = gfx_draw_pixel;
	my_gfx_op.fill_rect = NULL;//gfx_fill_rect;

 
	
  while(1)
	{			
		if(temp == 1)
		{
			//启动画圆
			startHelloCircle(NULL, 128, 64, 1, &my_gfx_op);
		}
		else if(temp == 0)
		{
			OLED_ShowPicture(0,0,128,64,BAR,1);
			OLED_ShowPicture(0,13,128,64,STMMCU,1);
			OLED_Refresh_Gram();	 //更新显示到OLED			
		}
			

		

	}
}
