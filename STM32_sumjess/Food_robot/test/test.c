#include "sumjess_test.h" 

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



void test_Init(void)
{

 	  if(If==0)      //PWM���ֵĲ���
		{
			for(b=0;b<100;b+=10){
			TIM_SetCompare1(TIM3,b);   delay_ms(100);}
			for(b=100;b>1;b-=10){
			TIM_SetCompare1(TIM3,b);   delay_ms(100);}
			TIM_SetCompare1(TIM3,0);   delay_ms(2000);
			for(b=0;b<100;b+=10){
			TIM_SetCompare2(TIM3,b);   delay_ms(100);}
			for(b=100;b>1;b-=10){
			TIM_SetCompare2(TIM3,b);   delay_ms(100);}
			for(b=0;b<100;b+=10){
			TIM_SetCompare3(TIM3,b);   delay_ms(100);}
			for(b=100;b>1;b-=10){
			TIM_SetCompare3(TIM3,b);   delay_ms(100);}
			TIM_SetCompare3(TIM3,0);   delay_ms(2000);
			for(b=0;b<100;b+=10){
			TIM_SetCompare4(TIM3,b);   delay_ms(100);}
			for(b=100;b>1;b-=10){
			TIM_SetCompare4(TIM3,b);   delay_ms(100);}
			TIM_SetCompare4(TIM3,0);   delay_ms(2000);		
	  }
		else if(If==1)      //ѭ�����ֵĲ���
		{                                       
			if(right_rd)
			LED2=1; else  LED2=0;
		 }
		else if(If==2)      //RTC+OLED���ֵĲ���
		{
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
	  }
 
}