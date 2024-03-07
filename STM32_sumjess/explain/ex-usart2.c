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
http://blog.csdn.net/liukais/article/details/53926768
http://blog.csdn.net/ybhuangfugui/article/details/51308289
#include "led.h"
#include "delay.h"
#include "sys.h"
#include "sumjess_USART2.h"

 int main(void)
 {	
	u8 t;
	u8 len;	
	u16 times=0; 
 
	delay_init();	    	 //延时函数初始化	
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);// 设置中断优先级分组2
	USART2_Init(9600);	 //串口初始化为9600
	LED_Init();		  	 //初始化与LED连接的硬件接口 
 
	while(1)
	{
		if(USART2_RX_STA&0x8000)//一次接受完成
		{	
			len=USART2_RX_STA&0x3fff;//得到此次接收到的数据长度
			printf("\r\n您发送的消息为:\r\n");
			for(t=0;t<len;t++)
			{
				USART2->DR=USART2_RX_BUF[t];//向串口2发送数据
				while((USART2->SR&0X40)==0);//等待发送结束
			}
			printf("\r\n\r\n");//插入换行
			USART2_RX_STA=0;//清零
		}else
		{
			times++;
			if(times%1000==1)
			{
				printf("\r\nsumjess 开发板 串口实验\r\n");
				printf("博客：https://blog.csdn.net/qq_38351824\r\n\r\n\r\n");
			}
			if(times%200==0)printf("请输入数据,以回车键结束\r\n");  
			if(times%30==0)LED0=!LED0;//闪烁LED,提示系统正在运行.
			delay_ms(10);   
		}
	}	 
}


！！！串口发送数据！！！

sprintf(send,"value=%5.3f",value);
for (i = 0; send[i] != 0; i++) 
{
  USART_SendData(USART2,send[i]);
  delay_ms(5);			//该延时用来确保数据能够被发送出去
} 



！！！串口接收数据！！！

#include <math.h>


		if(USART2_RX_STA&0x8000)//一次接受完成
		{	
			len=USART2_RX_STA&0x3fff;//得到此次接收到的数据长度
			printf("\r\n您发送的消息为:\r\n");
			for(t=0;t<len;t++)
			{
				USART2->DR=USART2_RX_BUF[t];//向串口2发送数据
				while((USART2->SR&0X40)==0);//等待发送结束
				if(USART2_RX_BUF[t]==32) USART2_RX_BUF[t]=48;
				 x=x+(USART2_RX_BUF[t]-48)*pow(10,(len-t-1));printf("---%d++++",x);
			}
	  x=0;
    delay_ms(5);			//该延时用来确保数据能够被发送出去
		USART2_RX_STA=0;//清零
		}
















*/



