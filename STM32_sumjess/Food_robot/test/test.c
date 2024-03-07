#include "sumjess_test.h" 

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
********************************************************************************/	



void test_Init(void)
{

 	  if(If==0)      //PWM部分的测试
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
		else if(If==1)      //循迹部分的测试
		{                                       
			if(right_rd)
			LED2=1; else  LED2=0;
		 }
		else if(If==2)      //RTC+OLED部分的测试
		{
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
	  }
 
}