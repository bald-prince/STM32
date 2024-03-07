/*
*******************************************************************************
================================================================================
【平    台】stm32f103zet6_sumjess平台
【编    写】sumjess
【E-mail  】1371129880@qq.com
【软件版本】V2.0
【最后更新】2018年09月06日
【相关信息参考下列地址】
【网    站】
           https://blog.csdn.net/qq_38351824
           http://www.openedv.com/
           http://www.stmcu.org/
					 http://www.firebbs.cn/forum.php
---------------------------------------------------------------------------------
【dev.env.】MDK5.14及以上版本
【Target  】stm32f103zet6
第一次修订：2017/11/09
第二次修订：2018/01/21
第三次修订：2018/09/06
【problem 】
    （1）库内补充的不全面；
    （2）库内解释部分不全面；
    （3）库内还存在一定的bug；
【direction】
      下一步的目标就是把库继续集成！
【explain 】
      本库是根据正点原子、中景园电子、优信电子等商家改编而成，
      同时为了方便使用，我也自己写了很多的库，和优化了算法和表示方式！
【warning】
      目前程序中暂无警告 ！   
---------------------------------------------------------------------------------
没有完美的代码，只有不断的奉献，大家一起努力；
赠人玫瑰手留余香，欢迎大家反馈bug！
================================================================================
********************************************************************************





#include "led.h"
#include "delay.h"
#include "key.h"
#include "sys.h"
#include "lcd.h"
#include "usart.h"	
#include "usmart.h"	 
#include "rtc.h" 

 int main(void)
 {	 
 	u8 t=0;	
	delay_init();	    	 //延时函数初始化	  
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//设置中断优先级分组为组2：2位抢占优先级，2位响应优先级
	uart_init(115200);	 	//串口初始化为115200
 	LED_Init();			     //LED端口初始化
	LCD_Init();			 	
	usmart_dev.init(SystemCoreClock/1000000);	//初始化USMART	-----------------可设置时间
	RTC_Init();	  			//RTC初始化
	POINT_COLOR=RED;//设置字体为红色 
	LCD_ShowString(60,50,200,16,16,"WarShip STM32");	
	LCD_ShowString(60,70,200,16,16,"RTC TEST");	
	LCD_ShowString(60,90,200,16,16,"ATOM@ALIENTEK");
	LCD_ShowString(60,110,200,16,16,"2018/9/12");		
	//显示时间
	//RTC_Set(2018,9,12,07,35,01); // ----------------------------------可设置时间
	POINT_COLOR=BLUE;//设置字体为蓝色
	LCD_ShowString(60,130,200,16,16,"    -  -  ");	   
	LCD_ShowString(60,162,200,16,16,"  :  :  ");		    
	while(1)
	{								    
		if(t!=calendar.sec)
		{
			t=calendar.sec;
			LCD_ShowNum(60,130,calendar.w_year,4,16);							//---------------显示年份		  
			LCD_ShowNum(100,130,calendar.w_month,2,16);						//---------------显示月份	  
			LCD_ShowNum(124,130,calendar.w_date,2,16);	          //---------------显示日期
			switch(calendar.week)
			{
				case 0:
					LCD_ShowString(60,148,200,16,16,"Sunday   ");
					break;
				case 1:
					LCD_ShowString(60,148,200,16,16,"Monday   ");
					break;
				case 2:
					LCD_ShowString(60,148,200,16,16,"Tuesday  ");
					break;
				case 3:
					LCD_ShowString(60,148,200,16,16,"Wednesday");
					break;
				case 4:
					LCD_ShowString(60,148,200,16,16,"Thursday ");
					break;
				case 5:
					LCD_ShowString(60,148,200,16,16,"Friday   ");
					break;
				case 6:
					LCD_ShowString(60,148,200,16,16,"Saturday ");
					break;  
			}
			LCD_ShowNum(60,162,calendar.hour,2,16);							//显示小时		  
			LCD_ShowNum(84,162,calendar.min,2,16);							//显示分钟
			LCD_ShowNum(108,162,calendar.sec,2,16);             //显示秒钟
			LED0=!LED0;
		}	
		delay_ms(10);								  
	};  
 }
 
 
 
 		if(t!=calendar.sec)
		{
			t=calendar.sec;
			OLED_ShowNum(0,0,calendar.w_year,4,16);							//---------------显示年份		  
			OLED_ShowNum(40,0,calendar.w_month,2,16);						//---------------显示月份	  
			OLED_ShowNum(65,0,calendar.w_date,2,16);	          //---------------显示日期
			switch(calendar.week)
			{
				case 0:
					OLED_ShowString(0,6,"Sunday   ");
					break;                                   
				case 1:
					OLED_ShowString(0,2,"Monday   ");
					break;
				case 2:
					OLED_ShowString(0,2,"Tuesday  ");
					break;
				case 3:
					OLED_ShowString(0,2,"Wednesday");
					break;                                        
				case 4:
					OLED_ShowString(0,2,"Thursday ");
					break;
				case 5:
					OLED_ShowString(0,2,"Friday   ");
					break;
				case 6:
					OLED_ShowString(0,2,"Saturday ");
					break;  
			}
			OLED_ShowNum(0,4,calendar.hour,2,16);							//显示小时		  
			OLED_ShowNum(25,4,calendar.min,2,16);							//显示分钟
			OLED_ShowNum(50,4,calendar.sec,2,16);             //显示秒钟
	
		}
 
 
 
 */
 
 



