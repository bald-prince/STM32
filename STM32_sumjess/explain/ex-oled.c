/*

*******************************************************************************
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
********************************************************************************




//////////////////////////////////////////////////////////////////////////////////	 
//              说明: 
//              ----------------------------------------------------------------
//              GND    电源地
//              VCC  接5V或3.3v电源
//              D0   接PB13（SCL）
//              D1   接PB15（SDA）
//              RES  接PB11
//              DC   接PB10
//              CS   接P12               
//              ----------------------------------------------------------------
// ******************************************************************************
#include "delay.h"
#include "sys.h"
#include "sumjess_oled.h"
#include "bmp.h"
 int main(void)
 {	u8 t;
		delay_init();	    	 //延时函数初始化	  
		NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2); //设置NVIC中断分组2:2位抢占优先级，2位响应优先级 	LED_Init();			     //LED端口初始化
		OLED_Init();			//初始化OLED  
		OLED_Clear(); 
		
	while(1) 
	{		
		
		OLED_Clear();
		LED_ON;
   	OLED_ShowCHinese(63,3,90);//
		OLED_ShowCHinese(18,0,1);//
		OLED_ShowCHinese(36,0,2);//
		OLED_ShowCHinese(54,0,3);***************显示汉字,需要的汉字在OLEDFONT.H中添加
		OLED_ShowCHinese(72,0,4);//
		OLED_ShowCHinese(90,0,5);//
		OLED_ShowCHinese(108,0,6);//
		
		
	  OLED_ShowString(0,3,"1.3' OLED TEST");********
		OLED_ShowString(8,2,"sumjess");********(x,y,字符号串）
		
	  OLED_ShowString(20,4,"2014/05/01"); *******
		
		OLED_ShowString(0,6,"ASCII:");  **********
		OLED_ShowString(63,6,"CODE:");  ***********
		
		
		OLED_ShowChar(48,6,t);//显示ASCII字符	 ******** 指定位置显示一个字符,包括部分字符//x:0~127//y:0~63

		t++;
	if(t>'~')t=' ';
		OLED_ShowNum(103,6,t,3,16);//显示ASCII字符的码值(x,y,数值，数字位数，字体大小） 
			
		delay_ms(8000);
		
		
		
		
*******************************************************************************************************************		
****************图片显示(图片显示慎用，生成的字表较大，会占用较多空间，FLASH空间8K以下慎用)****************************
********************************************************图片*******************************************************
	************************************************************************************************************	
	  OLED_Clear();
		delay_ms(8000);
		LED_OFF;	
		OLED_DrawBMP(0,0,128,8,BMP1);  //
		delay_ms(8000);
		OLED_DrawBMP(0,0,128,8,BMP2);  //
		delay_ms(8000);

BMP1和BMP2在BMP.H中修改
************功能描述：显示显示BMP图片128×64起始点坐标(x,y),x的范围0～127，y为页的范围0～7****************

********************************************************************************************************************
_______________________________________________________________________________________________________________________
***************************************
**************OLED.c中调节**************
***************************************
#define OLED_MODE 0     //0,反白显示;1,正常显示
#define SIZE 16         //字体大小
#define XLevelL		0x00
#define XLevelH		0x10
#define Max_Column	128  //128列
#define Max_Row		64     //64行
#define	Brightness	0xFF //亮度
#define X_WIDTH 	128    //x宽度
#define Y_WIDTH 	64	    //y宽度








陀螺仪源码





#include "delay.h"
#include "sys.h"
#include "oled.h"
#include "bmp.h"
 int main(void)
 {	u8 t;
		delay_init();	    	 //延时函数初始化	  
		NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2); //设置NVIC中断分组2:2位抢占优先级，2位响应优先级 	LED_Init();			     //LED端口初始化
		OLED_Init();			//初始化OLED  
		OLED_Clear()  	; 
		
	  OLED_ShowString(30,0,"OLED TEST");
		OLED_ShowString(8,2,"ZHONGJINGYUAN");  
		OLED_ShowString(20,4,"2014/05/01");  
		OLED_ShowString(0,6,"ASCII:");  
		OLED_ShowString(63,6,"CODE:");  
		t=' '; 
		OLED_ShowCHinese(0,0,0);//显
		OLED_ShowCHinese(18,0,1);//示
		OLED_ShowCHinese(36,0,2);//中
		OLED_ShowCHinese(54,0,3);//文
		OLED_ShowCHinese(72,0,4);//
		OLED_ShowCHinese(90,0,5);//
		OLED_ShowCHinese(108,0,6);//
		
		t=' ';
	while(1) 
	{		
		
		OLED_Clear();
		LED_ON;
   	OLED_ShowCHinese(0,0,0);//
		OLED_ShowCHinese(18,0,1);//
		OLED_ShowCHinese(36,0,2);//
		OLED_ShowCHinese(54,0,3);//显
		OLED_ShowCHinese(72,0,4);//示
		OLED_ShowCHinese(90,0,5);//中
		OLED_ShowCHinese(108,0,6);//文
	  OLED_ShowString(0,3,"1.3' OLED TEST");
		OLED_ShowString(8,2,"sumjess");  
	  OLED_ShowString(20,4,"2014/05/01");  
		OLED_ShowString(0,6,"ASCII:");  
		OLED_ShowString(63,6,"CODE:");  
		OLED_ShowChar(48,6,t);//显示ASCII字符	   
		t++;
	if(t>'~')t=' ';
		OLED_ShowNum(103,6,t,3,16);//显示ASCII字符的码值 	
			
		delay_ms(8000);
	OLED_Clear();
		delay_ms(8000);
		LED_OFF;	
		OLED_DrawBMP(0,0,128,8,BMP1);  //图片显示(图片显示慎用，生成的字表较大，会占用较多空间，FLASH空间8K以下慎用)
		delay_ms(8000);
		OLED_DrawBMP(0,0,128,8,BMP2);
		delay_ms(8000);

	}	  
	
}




#include "delay.h"
#include "sys.h"
#include "sumjess_oled.h"


 int main(void)
 {	
  int t=99;
	float pitch=5.56;
	char pitch_x[20];
	delay_init();	    	 //延时函数初始化	  
  OLED_Init();
   	while(1)
	{
    OLED_Clear();//清屏
    //-***************显示汉字,需要的汉字在OLEDFONT.H中添加
		OLED_ShowCHinese(90,0,5);//文字
		OLED_ShowCHinese(108,0,6);//文字		

	  OLED_ShowString(0,3,"1.3' OLED TEST");//-********
		OLED_ShowString(8,5,"sumjess");//-********(x,y,字符号串）
		
		sprintf(pitch_x,"value=%0.3f",pitch);//打印专用
	  OLED_ShowString(0,0,(u8*)pitch_x);//动态俯仰角

		OLED_ShowChar(90,7,t);//显示ASCII字符	 ******** 指定位置显示一个字符,包括部分字符//x:0~127//y:0~63
    delay_ms(50);//适当延时使OLED不抖
	} 
}
  




while(1)
					{
		mpu_dmp_get_data(&pitch,&roll,&yaw);
		OLED_Clear();			
		if(mpu_dmp_get_data(&pitch,&roll,& yaw)==0)
		{
			
			temp=MPU_Get_Temperature();	//得到温度值
		  OLED_ShowNum(60,0,temp,3,16);		
			MPU_Get_Accelerometer(&aacx,&aacy,&aacz);	//得到加速度传感器数据
			MPU_Get_Gyroscope(&gyrox,&gyroy,&gyroz);	//得到陀螺仪数据
			//俯仰角
			pitch_oled();
      sprintf(pitch_x,"%0.3f",pitch);
		  OLED_ShowString(60,2,(u8*)pitch_x);				
			printf("%0.3f",pitch);
			printf("\n");
		  //偏航角
			yaw_oled();
      sprintf(roll_x,"%0.3f",roll);
		  OLED_ShowString(60,4,(u8*)roll_x);				
			printf("%0.3f",roll);		
			printf("\n");
			//翻滚角
			roll_oled();
      sprintf(yaw_x,"%0.3f",yaw);
		  OLED_ShowString(60,6,(u8*)yaw_x);
			printf("%0.3f",yaw);
			printf("\n");		
			
			delay_ms(80);
			OLED_Clear();
					}
		  	}


*/





