/*
*******************************************************************************
================================================================================
��ƽ    ̨��stm32f103zet6_sumjessƽ̨
����    д��sumjess
��E-mail  ��1371129880@qq.com
������汾��V2.0
�������¡�2018��09��06��
�������Ϣ�ο����е�ַ��
����    վ��
           https://blog.csdn.net/qq_38351824
           http://www.openedv.com/
           http://www.stmcu.org/
					 http://www.firebbs.cn/forum.php
---------------------------------------------------------------------------------
��dev.env.��MDK5.14�����ϰ汾
��Target  ��stm32f103zet6
��һ���޶���2017/11/09
�ڶ����޶���2018/01/21
�������޶���2018/09/06
��problem ��
    ��1�����ڲ���Ĳ�ȫ�棻
    ��2�����ڽ��Ͳ��ֲ�ȫ�棻
    ��3�����ڻ�����һ����bug��
��direction��
      ��һ����Ŀ����ǰѿ�������ɣ�
��explain ��
      �����Ǹ�������ԭ�ӡ��о�԰���ӡ����ŵ��ӵ��̼Ҹı���ɣ�
      ͬʱΪ�˷���ʹ�ã���Ҳ�Լ�д�˺ܶ�Ŀ⣬���Ż����㷨�ͱ�ʾ��ʽ��
��warning��
      Ŀǰ���������޾��� ��   
---------------------------------------------------------------------------------
û�������Ĵ��룬ֻ�в��ϵķ��ף����һ��Ŭ����
����õ���������㣬��ӭ��ҷ���bug��
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
	delay_init();	    	 //��ʱ������ʼ��	  
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//�����ж����ȼ�����Ϊ��2��2λ��ռ���ȼ���2λ��Ӧ���ȼ�
	uart_init(115200);	 	//���ڳ�ʼ��Ϊ115200
 	LED_Init();			     //LED�˿ڳ�ʼ��
	LCD_Init();			 	
	usmart_dev.init(SystemCoreClock/1000000);	//��ʼ��USMART	-----------------������ʱ��
	RTC_Init();	  			//RTC��ʼ��
	POINT_COLOR=RED;//��������Ϊ��ɫ 
	LCD_ShowString(60,50,200,16,16,"WarShip STM32");	
	LCD_ShowString(60,70,200,16,16,"RTC TEST");	
	LCD_ShowString(60,90,200,16,16,"ATOM@ALIENTEK");
	LCD_ShowString(60,110,200,16,16,"2018/9/12");		
	//��ʾʱ��
	//RTC_Set(2018,9,12,07,35,01); // ----------------------------------������ʱ��
	POINT_COLOR=BLUE;//��������Ϊ��ɫ
	LCD_ShowString(60,130,200,16,16,"    -  -  ");	   
	LCD_ShowString(60,162,200,16,16,"  :  :  ");		    
	while(1)
	{								    
		if(t!=calendar.sec)
		{
			t=calendar.sec;
			LCD_ShowNum(60,130,calendar.w_year,4,16);							//---------------��ʾ���		  
			LCD_ShowNum(100,130,calendar.w_month,2,16);						//---------------��ʾ�·�	  
			LCD_ShowNum(124,130,calendar.w_date,2,16);	          //---------------��ʾ����
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
			LCD_ShowNum(60,162,calendar.hour,2,16);							//��ʾСʱ		  
			LCD_ShowNum(84,162,calendar.min,2,16);							//��ʾ����
			LCD_ShowNum(108,162,calendar.sec,2,16);             //��ʾ����
			LED0=!LED0;
		}	
		delay_ms(10);								  
	};  
 }
 
 
 
 		if(t!=calendar.sec)
		{
			t=calendar.sec;
			OLED_ShowNum(0,0,calendar.w_year,4,16);							//---------------��ʾ���		  
			OLED_ShowNum(40,0,calendar.w_month,2,16);						//---------------��ʾ�·�	  
			OLED_ShowNum(65,0,calendar.w_date,2,16);	          //---------------��ʾ����
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
			OLED_ShowNum(0,4,calendar.hour,2,16);							//��ʾСʱ		  
			OLED_ShowNum(25,4,calendar.min,2,16);							//��ʾ����
			OLED_ShowNum(50,4,calendar.sec,2,16);             //��ʾ����
	
		}
 
 
 
 */
 
 



