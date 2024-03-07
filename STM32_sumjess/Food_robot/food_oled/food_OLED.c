#include "food_OLED.h"
#include "delay.h"
#include "inv_mpu.h"
#include "inv_mpu_dmp_motion_driver.h" 
#include "sumjess_mpu6050.h"
#include "sumjess_my_pitch.h"
#include "timer.h"
#include "sumjess_UltrasonicWave.h"
#include "dht11.h"
#include "sumjess_oled.h"
#include <stdio.h> 
#include "rtc.h"

/*******************************************************************************
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
---------------------------------------------------------------------------------
û�������Ĵ��룬ֻ�в��ϵķ��ף����һ��Ŭ����
����õ���������㣬��ӭ��ҷ���bug��
================================================================================
********************************************************************************/	
//OLED����

#if (IF==0)
extern unsigned char temperature;     //�¶ȱ��� 	    
extern unsigned char humidity;        //ʪ�ȱ���
extern char pitch_mid[10];            //�н�����
extern float   pitch_md;              //�н�����
extern u8 t;                     //ʱ���н����
extern int track_media;        //�����м����

void sum_foodOLED(void)
{
	pitch_md=my_pitch();                                    //�ɼ���ֵ
	sprintf(pitch_mid,"%0.1f",pitch_md);                    //��ӡר��
	OLED_ShowString(80,0,(u8*)pitch_mid); delay_ms(50);    //��̬������
	if(t!=calendar.sec)
	{
		t=calendar.sec;
		OLED_ShowNum(0,0,calendar.w_year,4,16);							//---------------��ʾ���		  
		OLED_ShowNum(40,0,calendar.w_month,2,16);						//---------------��ʾ�·�	  
		OLED_ShowNum(65,0,calendar.w_date,2,16);	          //---------------��ʾ����
		switch(calendar.week)
		{
			case 0:
				OLED_ShowString(0,2,"Sunday   ");
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
		DHT11_Read_Data(&temperature,&humidity);	        //��ȡ��ʪ��ֵ	
		OLED_ShowNum(90,2,temperature,2,16);              //��ʾ�¶�
		OLED_ShowNum(90,4,humidity,2,16);                 //��ʾʪ��
		  UltrasonicWave_StartMeasure2();                    //��ʾ����
       
			}	 
	  }
 #endif

