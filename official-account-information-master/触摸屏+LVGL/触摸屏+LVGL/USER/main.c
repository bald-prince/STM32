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
	HAL_Init();												//初始化HAL库
	Stm32_Clock_Init(336,8,2,7); 			//设置时钟,168Mhz
	delay_init(168);									//初始化延时函数
	uart_init(115200);								//初始化USART
	LED_Init();												//初始化LED
	KEY_Init();												//初始化KEY
	TIM3_Init(1000-1, 84-1); 		
	lv_init();			 									// 初始化lvgl
	lv_port_disp_init(); 							// 显示初始化
	lv_port_indev_init();
	//lv_demo_widgets();	 						// 例子演示
	lv_ex_slider_2();
  //lv_ex_calendar_1();
	//lv_demo_keypad_encoder();
	//lv_demo_printer();
	
  //setup_ui(&ui);
	//events_init(&ui);
	
	//analog(lv_scr_act());

	while(1)
	{
		tp_dev.scan(0);//触摸扫描
		lv_task_handler(); // 循环调用处理lvgl tasks
	}
}
