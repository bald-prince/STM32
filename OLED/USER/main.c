#include "sys.h"
#include "delay.h"
#include "usart.h"
#include "led.h"
#include "oled.h"
#include "key.h"
#include "bmp.h"

int main(void)
{
	//u8 t=0; 
	//u8 temp=0;

  HAL_Init();                   	//��ʼ��HAL��    
  Stm32_Clock_Init(336,8,2,7);  	//����ʱ��,168Mhz
	delay_init(168);               	//��ʼ����ʱ����
	uart_init(115200);             	//��ʼ��USART
	LED_Init();						//��ʼ��LED	
	OLED_Init();					//��ʼ��OLED	
	KEY_Init();
 
	
  while(1)
	{			
		OLED_ShowPicture(0,0,128,64,BAR,1);
		OLED_ShowPicture(0,13,128,64,STMMCU,1);		

		//OLED_DrawGIF(32,0,96,8,31,512,Pencil);
		//OLED_DrawQRCode("https://github.com/whik",1);     //ֻ֧��֧����ɨ��
		//OLED_DrawQRCode("https://cli.im/",1);


		OLED_Refresh_Gram();	 //������ʾ��OLED

	}
}
