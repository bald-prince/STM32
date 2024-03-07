#include "sys.h"
#include "delay.h"
#include "usart.h"
#include "led.h"
#include "key.h"
#include "lcd.h"
#include "usmart.h"
#include "touch.h"
#include "timer.h"
#include "string.h"
#include "lv_port_disp.h"
#include "lv_port_indev.h"
#include "lv_demo_widgets.h"
#include "../../lv_examples.h"
#include "gui_guider.h"
#include "events_init.h"

lv_ui ui;
void analog(lv_obj_t *win);

int main(void)
{
	HAL_Init();												//��ʼ��HAL��
	Stm32_Clock_Init(336,8,2,7); 			//����ʱ��,168Mhz
	delay_init(168);									//��ʼ����ʱ����
	uart_init(115200);								//��ʼ��USART
	LED_Init();												//��ʼ��LED
	KEY_Init();												//��ʼ��KEY
	TIM3_Init(1000-1, 84-1); 		
	lv_init();			 									// ��ʼ��lvgl
	lv_port_disp_init(); 							// ��ʾ��ʼ��
	lv_port_indev_init();
	//lv_demo_widgets();	 						// ������ʾ
	lv_ex_slider_2();
  //lv_ex_calendar_1();
	//lv_demo_keypad_encoder();
	//lv_demo_printer();
	
  //setup_ui(&ui);
	//events_init(&ui);
	
	//analog(lv_scr_act());

	while(1)
	{
		tp_dev.scan(0);//����ɨ��
		lv_task_handler(); // ѭ�����ô���lvgl tasks
	}
}
