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
  HAL_Init();                   	//初始化HAL库    
  Stm32_Clock_Init(336,8,2,7);  	//设置时钟,168Mhz
	TIM3_Init(1000-1,84-1);
	delay_init(168);               	//初始化延时函数
	uart_init(115200);             	//初始化USART
	usmart_dev.init(84); 		    //初始化USMART
	LED_Init();						//初始化LED	
	KEY_Init();						//初始化KEY
// 	LCD_Init();           			//初始化LCD
//	tp_dev.init();				    //触摸屏初始化 
	
	lv_init();//LVGL初始化
	lv_port_disp_init();//显示器初始化
	lv_port_indev_init();//输入设备初始化
	lv_demo_keypad_encoder();//运行Demo
	 
	while(1)
	{
		tp_dev.scan(0);//触摸扫描
		lv_task_handler();//LVGL任务处理器
	}
}

