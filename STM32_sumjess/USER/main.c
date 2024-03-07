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
********************************************************************************/	


#include "delay.h"                    
#include "sys.h"
#include "sumjess_pwm.h"
#include "key.h"
#include "led.h"
#include "rtc.h" 
#include "usart.h"	
#include "sumjess_oled.h"
#include "bmp.h"
#include "wdg.h"
#include "sumjess_track.h" 
#include "sumjess_track_motor.h" 
#include "timer.h"
#include "sumjess_UltrasonicWave.h"
#include "dht11.h"
#include "beep.h"
#include "inv_mpu.h"
#include "inv_mpu_dmp_motion_driver.h" 
#include "sumjess_mpu6050.h"
#include "sumjess_my_pitch.h"
#include "food_OLED.h"

#define IF  1               //���Ժ���---1
                            //��������---0
#define If  2               //���Ժ���ѡ��
                            //PWM���ֵĲ���      --- 0
                            //ѭ�����ֵĲ���     --- 1
                            //RTC+OLED���ֵĲ��� --- 2
														
extern u32 temp;						//����������								
														
int track_media = 0;        //�����м����
int b = 0;                  //PWMѭ������
u8 t=0;                     //ʱ���н����

unsigned char temperature = 0; //�¶ȱ��� 	    
unsigned char humidity = 0;    //ʪ�ȱ���
char pitch_mid[10];            //�н�����
float   pitch_md;              //�н�����


void test_Init(void);         //���Ժ���



 int main(void)
 {
	 delay_init();	       	                        //��ʱ��ʼ��  
	 NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//�����ж����ȼ�����Ϊ��2��2λ��ռ���ȼ���2λ��Ӧ���ȼ�
   uart_init(115200);	 	                          //���ڳ�ʼ��Ϊ115200
//	 mpu_dmp_init();                                //mpu6050��ʼ��
//   KEY_Init();                                    //������ʼ��
//	 LED_Init();	                                  //LED��ʼ��
//	 relay_Init();                                  //�̵�����ʼ��
//	 light_Init();                                  //���ճ�ʼ��
	 RTC_Init();	  			                          //RTC��ʼ��
	 //RTC_Set(2018,9,23,15,52,35);                 //������ʱ��
//   speed_Init();                                  //���PWM��ʼ��                
//	 BEEP_Init();                                   //��������ʼ��
	 OLED_Init();			                              //��ʼ��OLED  
	 OLED_Clear();                                  //���� 
	 OLED_DrawBMP(32,0,96,8,BMP1);                  //У��
	 delay_ms(1000);                                //��ʱ
	 OLED_Clear();                                  //����
	 OLED_ShowString(0,0,"    -  -  ");	            //ʱ�ӿ��
	 OLED_ShowString(0,4,"  :  :  ");	              //ʱ�ӿ��
//	 OLED_ShowString(110,2,"T");                    //�¶ȿ��
//   OLED_ShowString(110,4,"%");                    //ʪ�ȿ��	 
//	 delay_ms(50);
//   TIM5_Cap_Init(0XFFFF,72-1);	                  //��1Mhz��Ƶ�ʼ��� 	 
//	 while(DHT11_Init());	                          //DHT11��ʼ��	
	 
	// IWDG_Init(4,1250);                              //���Ź���ʼ��
	                                                //���Ƶ��Ϊ64,����ֵΪ625,���ʱ��Ϊ1s		 
	while(1) 
	{	
   #if IF                          //�����ֵĲ���
		   test_Init();                //�����ֵĲ���
	 #else                           //������
	 {
//		  track_data();                //���ݲɼ�
//		  track_media=track_decide();  //���ݴ���
//		  track_motor();               //���ִ��
//		  sum_foodOLED();              //������ʾ
//	 	  if(temp<10) {stop();BEEP=1;delay_ms(500);BEEP=0;delay_ms(500);} //������ͣ��������
//		  while(temp<10) UltrasonicWave_StartMeasure2();  //ֱ�����ϰ���
	 }
	#endif
//  if(LIGHT)  Relay=1; else Relay=0;
	//IWDG_Feed();                     //ι��
	}
}
 


 void test_Init(void)
{

 	  if(If==0)           //PWM���ֵĲ���
		{
//			for(b=0;b<100;b+=10){
//			TIM_SetCompare1(TIM3,b);   delay_ms(100);}
//			for(b=100;b>1;b-=10){
//			TIM_SetCompare1(TIM3,b);   delay_ms(100);}
//			TIM_SetCompare1(TIM3,0);   delay_ms(2000);
//			for(b=0;b<100;b+=10){
//			TIM_SetCompare2(TIM3,b);   delay_ms(100);}
//			for(b=100;b>1;b-=10){
//			TIM_SetCompare2(TIM3,b);   delay_ms(100);}
//			for(b=0;b<100;b+=10){
//			TIM_SetCompare3(TIM3,b);   delay_ms(100);}
//			for(b=100;b>1;b-=10){
//			TIM_SetCompare3(TIM3,b);   delay_ms(100);}
//			TIM_SetCompare3(TIM3,0);   delay_ms(2000);
//			for(b=0;b<100;b+=10){
//			TIM_SetCompare4(TIM3,b);   delay_ms(100);}
//			for(b=100;b>1;b-=10){
//			TIM_SetCompare4(TIM3,b);   delay_ms(100);}
//			TIM_SetCompare4(TIM3,0);   delay_ms(2000);		
	  }
		else if(If==1)      //ѭ�����ֵĲ���
		{                                       
//			if(right_rd)
//			LED2=1; else  LED2=0;
		 }
		else if(If==2)      //RTC+������+MPU6050+OLED���ֵĲ���
		{ 
//			pitch_md=my_pitch();                                    //�ɼ���ֵ
//      sprintf(pitch_mid,"%0.1f",pitch_md);                    //��ӡר��
//			OLED_ShowString(80,0,(u8*)pitch_mid); delay_ms(150);    //��̬������

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
        //Relay=0;delay_ms(700);Relay=0;                  //�̵���
				//BEEP=1;delay_ms(500);BEEP=0;                    //������
				OLED_ShowNum(0,4,calendar.hour,2,16);							//��ʾСʱ		  
				OLED_ShowNum(25,4,calendar.min,2,16);							//��ʾ����
				OLED_ShowNum(50,4,calendar.sec,2,16);             //��ʾ����
// 		 		DHT11_Read_Data(&temperature,&humidity);	        //��ȡ��ʪ��ֵ	
//			  OLED_ShowNum(90,2,temperature,2,16);              //��ʾ�¶�
//			  OLED_ShowNum(90,4,humidity,2,16);                 //��ʾʪ��
//				UltrasonicWave_StartMeasure2();                    //��ʾ����
       
			}	 
	  }
}


