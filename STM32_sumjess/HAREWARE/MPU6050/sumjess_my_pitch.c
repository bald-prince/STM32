#include <stdio.h> 
#include "sumjess_my_pitch.h"

/*******************************************************************************
================================================================================
【平    台】stm32f103zet6_sumjess平台
【编    写】sumjess
【E-mail  】1371129880@qq.com
【软件版本】V2.0
【最后更新】2018年01月21日
【相关信息参考下列地址】
【网    站】http://www.openedv.com/
           http://www.stmcu.org/
					 http://www.firebbs.cn/forum.php
---------------------------------------------------------------------------------
【dev.env.】MDK5.14及以上版本
【Target  】stm32f103zet6
第一次修订：2017/11/09
第二次修订：2018/01/21
---------------------------------------------------------------------------------
没有完美的代码，只有不断的奉献，大家一起努力；
赠人玫瑰手留余香，欢迎大家反馈bug！
================================================================================
********************************************************************************/	
//mpu6050  驱动代码	 

  float my_pitch(void)
  {
		char pitch_x[10];//,roll_x[10],yaw_x[10];
	  float pitch,roll,yaw; 		//欧拉角
	  short aacx,aacy,aacz;		//加速度传感器原始数据
	  short gyrox,gyroy,gyroz;	//陀螺仪原始数据
	  short temp2;					//温度	
		mpu_dmp_get_data(&pitch,&roll,&yaw);
		//OLED_Clear();
		if(mpu_dmp_get_data(&pitch,&roll,& yaw)==0)
		{
			
			temp2=MPU_Get_Temperature();	//得到温度值
			temp2=temp2;//避免警告
		  //OLED_ShowNum(60,0,temp,3,16);
			
			MPU_Get_Accelerometer(&aacx,&aacy,&aacz);	//得到加速度传感器数据
			MPU_Get_Gyroscope(&gyrox,&gyroy,&gyroz);	//得到陀螺仪数据
			
			/*俯仰角*/
      sprintf(pitch_x,"%0.3f",pitch);//打印专用
			//OLED_ShowString(60,2,(u8*)pitch_x);//动态俯仰角
			//delay_ms(50);//适当延时使OLED不抖
			
			
		}
			return pitch;//返回俯仰角
	 }



