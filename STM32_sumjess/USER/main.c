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

#define IF  1               //测试函数---1
                            //工作函数---0
#define If  2               //测试函数选择
                            //PWM部分的测试      --- 0
                            //循迹部分的测试     --- 1
                            //RTC+OLED部分的测试 --- 2
														
extern u32 temp;						//超声波距离								
														
int track_media = 0;        //决策中间变量
int b = 0;                  //PWM循环变量
u8 t=0;                     //时钟中介变量

unsigned char temperature = 0; //温度变量 	    
unsigned char humidity = 0;    //湿度变量
char pitch_mid[10];            //中介数组
float   pitch_md;              //中介数据


void test_Init(void);         //测试函数



 int main(void)
 {
	 delay_init();	       	                        //延时初始化  
	 NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//设置中断优先级分组为组2：2位抢占优先级，2位响应优先级
   uart_init(115200);	 	                          //串口初始化为115200
//	 mpu_dmp_init();                                //mpu6050初始化
//   KEY_Init();                                    //按键初始化
//	 LED_Init();	                                  //LED初始化
//	 relay_Init();                                  //继电器初始化
//	 light_Init();                                  //光照初始化
	 RTC_Init();	  			                          //RTC初始化
	 //RTC_Set(2018,9,23,15,52,35);                 //可设置时间
//   speed_Init();                                  //电机PWM初始化                
//	 BEEP_Init();                                   //蜂鸣器初始化
	 OLED_Init();			                              //初始化OLED  
	 OLED_Clear();                                  //清屏 
	 OLED_DrawBMP(32,0,96,8,BMP1);                  //校徽
	 delay_ms(1000);                                //延时
	 OLED_Clear();                                  //清屏
	 OLED_ShowString(0,0,"    -  -  ");	            //时钟框架
	 OLED_ShowString(0,4,"  :  :  ");	              //时钟框架
//	 OLED_ShowString(110,2,"T");                    //温度框架
//   OLED_ShowString(110,4,"%");                    //湿度框架	 
//	 delay_ms(50);
//   TIM5_Cap_Init(0XFFFF,72-1);	                  //以1Mhz的频率计数 	 
//	 while(DHT11_Init());	                          //DHT11初始化	
	 
	// IWDG_Init(4,1250);                              //看门狗初始化
	                                                //与分频数为64,重载值为625,溢出时间为1s		 
	while(1) 
	{	
   #if IF                          //各部分的测试
		   test_Init();                //各部分的测试
	 #else                           //主程序
	 {
//		  track_data();                //数据采集
//		  track_media=track_decide();  //数据处理
//		  track_motor();               //电机执行
//		  sum_foodOLED();              //基础显示
//	 	  if(temp<10) {stop();BEEP=1;delay_ms(500);BEEP=0;delay_ms(500);} //超声波停车、报警
//		  while(temp<10) UltrasonicWave_StartMeasure2();  //直到无障碍物
	 }
	#endif
//  if(LIGHT)  Relay=1; else Relay=0;
	//IWDG_Feed();                     //喂狗
	}
}
 


 void test_Init(void)
{

 	  if(If==0)           //PWM部分的测试
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
		else if(If==1)      //循迹部分的测试
		{                                       
//			if(right_rd)
//			LED2=1; else  LED2=0;
		 }
		else if(If==2)      //RTC+超声波+MPU6050+OLED部分的测试
		{ 
//			pitch_md=my_pitch();                                    //采集数值
//      sprintf(pitch_mid,"%0.1f",pitch_md);                    //打印专用
//			OLED_ShowString(80,0,(u8*)pitch_mid); delay_ms(150);    //动态俯仰角

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
        //Relay=0;delay_ms(700);Relay=0;                  //继电器
				//BEEP=1;delay_ms(500);BEEP=0;                    //蜂鸣器
				OLED_ShowNum(0,4,calendar.hour,2,16);							//显示小时		  
				OLED_ShowNum(25,4,calendar.min,2,16);							//显示分钟
				OLED_ShowNum(50,4,calendar.sec,2,16);             //显示秒钟
// 		 		DHT11_Read_Data(&temperature,&humidity);	        //读取温湿度值	
//			  OLED_ShowNum(90,2,temperature,2,16);              //显示温度
//			  OLED_ShowNum(90,4,humidity,2,16);                 //显示湿度
//				UltrasonicWave_StartMeasure2();                    //显示距离
       
			}	 
	  }
}


