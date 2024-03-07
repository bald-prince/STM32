#include "sys.h"
#include "delay.h"
#include "usart.h"
#include "led.h"
#include "oled.h"
#include "key.h"
#include "bmp.h"

//���㺯���ӿ�
void gfx_draw_pixel(int x, int y, unsigned int rgb)
{
    OLED_DrawPoint(x,y,rgb);
}
//���溯��(δʹ��)
void gfx_draw_fill(int x, int y,int w, int q, unsigned int rgb)
{ 
}
//����һ������ָ��ṹ��
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

  HAL_Init();                   	//��ʼ��HAL��    
  Stm32_Clock_Init(336,8,2,7);  	//����ʱ��,168Mhz
	delay_init(168);               	//��ʼ����ʱ����
	uart_init(115200);             	//��ʼ��USART
	LED_Init();						//��ʼ��LED	
	OLED_Init();					//��ʼ��OLED	
	KEY_Init();
	
	//���ݺ���ָ��
	my_gfx_op.draw_pixel = gfx_draw_pixel;
	my_gfx_op.fill_rect = NULL;//gfx_fill_rect;

 
	
  while(1)
	{			
		if(temp == 1)
		{
			//������Բ
			startHelloCircle(NULL, 128, 64, 1, &my_gfx_op);
		}
		else if(temp == 0)
		{
			OLED_ShowPicture(0,0,128,64,BAR,1);
			OLED_ShowPicture(0,13,128,64,STMMCU,1);
			OLED_Refresh_Gram();	 //������ʾ��OLED			
		}
			

		

	}
}
