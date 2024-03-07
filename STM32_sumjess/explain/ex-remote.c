/*

*******************************************************************************
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
********************************************************************************




#include "led.h"
#include "delay.h"
#include "sys.h"
#include "usart.h"
#include "remote.h"   


 int main(void)
 { 
	u8 key;
	u8 t=0;	
	u8 *str=0; 	
	delay_init();	    	 //延时函数初始?
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);// 设置中断优先级分组2	  
	uart_init(9600);	 	//串口初始化为9600
	LED_Init();		  		//初始化与LED连接的硬件接口
	Remote_Init();			//红外接收初始化	 
 		 	  		    							  
	while(1)
	{
		key=Remote_Scan();	
		if(key)
		{	 
      printf("%d",key);		//显示键值
      printf("%d",RmtCnt);	//显示按键次数		  
			switch(key)
			{
				case 0:str="ERROR";break;			   //ERROR
				case 162:str="POWER";break;	    //POWER
				case 98:str="UP";break;	    //UP
				case 2:str="PLAY";break;		 //PLAY
				case 226:str="ALIENTEK";break;		 // ALIENTEK    *****************str="ALIENTEK"这部分可以随意更改********************
				case 194:str="RIGHT";break;	   //RIGHT
				case 34:str="LEFT";break;		  //LEFT
				case 224:str="VOL-";break;		  //VOL-
				case 168:str="DOWN";break;		   //DOWN
				case 144:str="VOL+";break;		    //VOL
				case 104:str="1";break;		  //1
				case 152:str="2";break;	   //2
				case 176:str="3";break;	    //3
				case 48:str="4";break;		    //4
				case 24:str="5";break;		    //5
				case 122:str="6";break;		  //6
				case 16:str="7";break;			//7	
				case 56:str="8";break;	 //8
				case 90:str="9";break;//9
				case 66:str="0";break;//0
				case 82:str="DELETE";break;		 //DELETE
			}
		}else delay_ms(10);	  
		t++;
		if(t==20)
		{
			t=0;
			LED0=!LED0;
		}
	}
}










*/









