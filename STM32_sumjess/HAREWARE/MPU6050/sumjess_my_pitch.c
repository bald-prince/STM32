#include <stdio.h> 
#include "sumjess_my_pitch.h"

/*******************************************************************************
================================================================================
��ƽ    ̨��stm32f103zet6_sumjessƽ̨
����    д��sumjess
��E-mail  ��1371129880@qq.com
������汾��V2.0
�������¡�2018��01��21��
�������Ϣ�ο����е�ַ��
����    վ��http://www.openedv.com/
           http://www.stmcu.org/
					 http://www.firebbs.cn/forum.php
---------------------------------------------------------------------------------
��dev.env.��MDK5.14�����ϰ汾
��Target  ��stm32f103zet6
��һ���޶���2017/11/09
�ڶ����޶���2018/01/21
---------------------------------------------------------------------------------
û�������Ĵ��룬ֻ�в��ϵķ��ף����һ��Ŭ����
����õ���������㣬��ӭ��ҷ���bug��
================================================================================
********************************************************************************/	
//mpu6050  ��������	 

  float my_pitch(void)
  {
		char pitch_x[10];//,roll_x[10],yaw_x[10];
	  float pitch,roll,yaw; 		//ŷ����
	  short aacx,aacy,aacz;		//���ٶȴ�����ԭʼ����
	  short gyrox,gyroy,gyroz;	//������ԭʼ����
	  short temp2;					//�¶�	
		mpu_dmp_get_data(&pitch,&roll,&yaw);
		//OLED_Clear();
		if(mpu_dmp_get_data(&pitch,&roll,& yaw)==0)
		{
			
			temp2=MPU_Get_Temperature();	//�õ��¶�ֵ
			temp2=temp2;//���⾯��
		  //OLED_ShowNum(60,0,temp,3,16);
			
			MPU_Get_Accelerometer(&aacx,&aacy,&aacz);	//�õ����ٶȴ���������
			MPU_Get_Gyroscope(&gyrox,&gyroy,&gyroz);	//�õ�����������
			
			/*������*/
      sprintf(pitch_x,"%0.3f",pitch);//��ӡר��
			//OLED_ShowString(60,2,(u8*)pitch_x);//��̬������
			//delay_ms(50);//�ʵ���ʱʹOLED����
			
			
		}
			return pitch;//���ظ�����
	 }



