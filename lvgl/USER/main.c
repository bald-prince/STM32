#include "sys.h"
#include "delay.h"
#include "usart.h"
#include "led.h"
#include "key.h"
#include "lcd.h"
#include "usmart.h"
#include "touch.h"
#include "timer.h"
#include "lvgl.h" 
#include "lv_port_indev.h"
#include "lv_port_disp.h"
#include "lv_examples.h"


int main(void)
{ 
  HAL_Init();                   	//��ʼ��HAL��    
  Stm32_Clock_Init(336,8,2,7);  	//����ʱ��,168Mhz
	TIM3_Init(1000-1,84-1);
	delay_init(168);               	//��ʼ����ʱ����
	uart_init(115200);             	//��ʼ��USART
	usmart_dev.init(84); 		    //��ʼ��USMART
	LED_Init();						//��ʼ��LED	
	KEY_Init();						//��ʼ��KEY
// 	LCD_Init();           			//��ʼ��LCD
//	tp_dev.init();				    //��������ʼ�� 
	
	lv_init();//LVGL��ʼ��
	lv_port_disp_init();//��ʾ����ʼ��
	lv_port_indev_init();//�����豸��ʼ��
	lv_demo_keypad_encoder();//����Demo
	 
	while(1)
	{
		tp_dev.scan(0);//����ɨ��
		lv_task_handler();//LVGL��������
	}
}

