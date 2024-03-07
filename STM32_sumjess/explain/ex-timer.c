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



定时器中断实现步骤

①-④在void TIM3_Int_Init(u16 arr,u16 psc)；中
⑤单独一步


①使能定时器时钟。
       RCC_APB1PeriphClockCmd();如下
			 ********RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);//时钟使能********
②初始化定时器，配置ARR,PSC。
      TIM_TimeBaseInit();如下
	***************************************************
	TIM_TimeBaseStructure.TIM_Period = arr; //设置在下一个更新事件装入活动的自动重装载寄存器周期的值	 计数到5000为500ms
	TIM_TimeBaseStructure.TIM_Prescaler =psc; //设置用来作为TIMx时钟频率除数的预分频值  10Khz的计数频率  
	TIM_TimeBaseStructure.TIM_ClockDivision =TIM_CKD_DIV1; //设置时钟分割:TDTS = Tck_tim*********这里任意选
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIM向上计数模式
	TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure); //根据TIM_TimeBaseInitStruct中指定的参数初始化TIMx的时间基数单位
	*******************************************************
			
③开启定时器中断，配置NVIC。
      void TIM_ITConfig();如下
			**********TIM_ITConfig(TIM3,TIM_IT_Update ,ENABLE);*********注意这里开启的是更新中断
      NVIC_Init();如下
	***************************************************************************************************************
	  NVIC_InitStruct.NVIC_IRQChannel = TIM3_IRQn;  //TIM3中断********在stm32f10x.c第190行左右
  	NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority =2;	//抢占优先级2 
  	NVIC_InitStruct.NVIC_IRQChannelSubPriority =1;					//子优先级1
  	NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;								//使能外部中断通道
  	NVIC_Init(&NVIC_InitStruct);  	  //根据NVIC_InitStruct中指定的参数初始化外设NVIC寄存器
		*************************************************************************************************************
④使能定时器。
      TIM_Cmd();如下
	******TIM_Cmd(TIM3, ENABLE);  //使能TIMx外设********
⑤编写中断服务函数。
      TIMx_IRQHandler();如下
			
	*******************************************************************************************************************
			void TIM3_IRQHandler(void)   //TIM3中断
{
	if (TIM_GetITStatus(TIM3, TIM_IT_Update) != RESET) //检查指定的TIM中断发生与否:TIM 中断源 ***RESET==0;SET==0***
		{
		TIM_ClearITPendingBit(TIM3, TIM_IT_Update  );  //清除TIMx的中断待处理位:TIM 中断源 
		LED1=!LED1;
		}
}

***********************************************************************************************************************


	*********************注意不要遗忘  NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);// 设置中断优先级分组2*********************
	
	*******注意计算定时器时间 TIM3_Int_Init(4999,7199);//10Khz的计数频率，计数到5000为500ms **************************************
***********************************算法见其对应的文件下的解释****************************

Tout（溢出时间）=（ARR+1)(PSC+1)/Tclk


#include "sys.h"
#include "led.h"
#include "delay.h"
#include "timer.h"

 int main(void)
 {		
	delay_init();	    	 //延时函数初始化	  
	TIM3_Int_Init(4999,7199);//10Khz的计数频率，计数到5000为500ms  
 	LED_Init();		  	 //初始化与LED连接的硬件接口	 
	delay_ms(500);   	 //让人看得到灭
	LED0=0;				 //点亮LED0
	while(1)
	{

	}
}
  




















































*/





