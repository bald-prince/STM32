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
---------------------------------------------------------------------------------
没有完美的代码，只有不断的奉献，大家一起努力；
赠人玫瑰手留余香，欢迎大家反馈bug！
================================================================================
********************************************************************************/	
//OLED代码

#if (IF==0)
extern unsigned char temperature;     //温度变量 	    
extern unsigned char humidity;        //湿度变量
extern char pitch_mid[10];            //中介数组
extern float   pitch_md;              //中介数据
extern u8 t;                     //时钟中介变量
extern int track_media;        //决策中间变量

void sum_foodOLED(void)
{
	pitch_md=my_pitch();                                    //采集数值
	sprintf(pitch_mid,"%0.1f",pitch_md);                    //打印专用
	OLED_ShowString(80,0,(u8*)pitch_mid); delay_ms(50);    //动态俯仰角
	if(t!=calendar.sec)
	{
		t=calendar.sec;
		OLED_ShowNum(0,0,calendar.w_year,4,16);							//---------------显示年份		  
		OLED_ShowNum(40,0,calendar.w_month,2,16);						//---------------显示月份	  
		OLED_ShowNum(65,0,calendar.w_date,2,16);	          //---------------显示日期
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

		OLED_ShowNum(0,4,calendar.hour,2,16);							//显示小时		  
		OLED_ShowNum(25,4,calendar.min,2,16);							//显示分钟
		OLED_ShowNum(50,4,calendar.sec,2,16);             //显示秒钟
		DHT11_Read_Data(&temperature,&humidity);	        //读取温湿度值	
		OLED_ShowNum(90,2,temperature,2,16);              //显示温度
		OLED_ShowNum(90,4,humidity,2,16);                 //显示湿度
		  UltrasonicWave_StartMeasure2();                    //显示距离
       
			}	 
	  }
 #endif

