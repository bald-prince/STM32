/******************** (C) 1209 Lab **************************
 * 文件名  : UltrasonicWave.c
 * 描述    ：超声波测距模块，UltrasonicWave_Configuration（）函数
             初始化超声模块，UltrasonicWave_StartMeasure（）函数
			 启动测距，并将测得的数据通过串口1打印出来         
 * 实验平台：Mini STM32开发板  STM32F103RBT6
 * 硬件连接：------------------
 *          | PC8  - TRIG      |
 *          | PC7  - ECHO      |
 *           ------------------
 * 库版本  ：ST3.5.0
 *
 * 作者    ：sumjess 
*********************************************************************************/
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
//超声波驱动 代码	  

#include "sumjess_UltrasonicWave.h"
#include "usart.h"
#include "timer.h"
#include "delay.h"
#include "sumjess_oled.h"
//#define	TRIG_PORT      GPIOC		//TRIG       
//#define	ECHO_PORT      GPIOC		//ECHO 
//#define	TRIG_PIN       GPIO_Pin_8   //TRIG       
//#define	ECHO_PIN       GPIO_Pin_7	//ECHO   

//float UltrasonicWave_Distance;      //计算出的距离    


///*
// * 函数名：UltrasonicWave_Configuration
// * 描述  ：超声波模块的初始化
// * 输入  ：无
// * 输出  ：无	
// */
//void UltrasonicWave_Configuration(void)
//{
//  GPIO_InitTypeDef GPIO_InitStructure;	
//	EXTI_InitTypeDef EXTI_InitStructure;
// 	NVIC_InitTypeDef NVIC_InitStructure;
//	
//	GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable , ENABLE);	//关闭jtag
//  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC|RCC_APB2Periph_AFIO, ENABLE);
//    
//  GPIO_InitStructure.GPIO_Pin = TRIG_PIN;					 //PC8接TRIG
//  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;		     //设为推挽输出模式
//  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;	         
//  GPIO_Init(TRIG_PORT, &GPIO_InitStructure);	                 //初始化外设GPIO 

//  GPIO_InitStructure.GPIO_Pin = ECHO_PIN;				     //PC7接ECH0
//  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD;		 //设为输入
//  GPIO_Init(ECHO_PORT,&GPIO_InitStructure);						 //初始化GPIOA
//	
//	 //GPIOC.7	  中断线以及中断初始化配置
// 	GPIO_EXTILineConfig(GPIO_PortSourceGPIOC,GPIO_PinSource7);

// 	  EXTI_InitStructure.EXTI_Line=EXTI_Line7;
//  	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;	
//  	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising;
//  	EXTI_InitStructure.EXTI_LineCmd = ENABLE;
//  	EXTI_Init(&EXTI_InitStructure);		//根据EXTI_InitStruct中指定的参数初始化外设EXTI寄存器
//		
//			
//	  NVIC_InitStructure.NVIC_IRQChannel = EXTI9_5_IRQn;			//使能按键所在的外部中断通道
//  	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;	//抢占优先级2 
//  	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;					//子优先级2 
//  	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;								//使能外部中断通道
//  	NVIC_Init(&NVIC_InitStructure);  	  //根据NVIC_InitStruct中指定的参数初始化外设NVIC寄存器
//}


//void EXTI9_5_IRQHandler(void)
//{
//	delay_us(10);		                      //延时10us
//     if(EXTI_GetITStatus(EXTI_Line7) != RESET)
//	{
//			TIM_SetCounter(TIM2,0);
//			TIM_Cmd(TIM2, ENABLE);                                             //开启时钟
//		
//			while(GPIO_ReadInputDataBit(ECHO_PORT,ECHO_PIN));	                 //等待低电平

//			TIM_Cmd(TIM2, DISABLE);			                                 //定时器2失能
//			UltrasonicWave_Distance=TIM_GetCounter(TIM2)*5*34/200.0;									 //计算距离&&UltrasonicWave_Distance<150
//		
//	if(UltrasonicWave_Distance>0)
//	{
//		printf("distance:%f cm",UltrasonicWave_Distance);
//	}
//		
//	
//	
//	EXTI_ClearITPendingBit(EXTI_Line7);  //清除EXTI7线路挂起位
//}

//}

///*
// * 函数名：UltrasonicWave_StartMeasure
// * 描述  ：开始测距，发送一个>10us的脉冲，然后测量返回的高电平时间
// * 输入  ：无
// * 输出  ：无	
// */
//void UltrasonicWave_StartMeasure(void)
//{
//  GPIO_SetBits(TRIG_PORT,TRIG_PIN); 		  //送>10US的高电平RIG_PORT,TRIG_PIN这两个在define中有?
//  delay_us(20);		                      //延时20US
//  GPIO_ResetBits(TRIG_PORT,TRIG_PIN);
//	
//}


u32 temp=0;
TIM_ICInitTypeDef  TIM5_ICInitStructure;
void TIM5_Cap_Init(unsigned short arr,unsigned short psc)
{	 
	GPIO_InitTypeDef GPIO_InitStructure;
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
   	NVIC_InitTypeDef NVIC_InitStructure;

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM5, ENABLE);	//使能TIM5时钟
 	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);  //使能GPIOA时钟
	
	GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_0;  //PA0 清除之前设置  
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD; //PA0 输入  
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	GPIO_ResetBits(GPIOA,GPIO_Pin_0);						 //PA0 下拉
	
	//初始化定时器5 TIM5	 
	TIM_TimeBaseStructure.TIM_Period = arr; //设定计数器自动重装值 
	TIM_TimeBaseStructure.TIM_Prescaler =psc; 	//预分频器   
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1; //设置时钟分割:TDTS = Tck_tim
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIM向上计数模式
	TIM_TimeBaseInit(TIM5, &TIM_TimeBaseStructure); //根据TIM_TimeBaseInitStruct中指定的参数初始化TIMx的时间基数单位
  
	//初始化TIM5输入捕获参数
	TIM5_ICInitStructure.TIM_Channel = TIM_Channel_1; //CC1S=01 	选择输入端 IC1映射到TI1上
  	TIM5_ICInitStructure.TIM_ICPolarity = TIM_ICPolarity_Rising;	//上升沿捕获
  	TIM5_ICInitStructure.TIM_ICSelection = TIM_ICSelection_DirectTI; //映射到TI1上
  	TIM5_ICInitStructure.TIM_ICPrescaler = TIM_ICPSC_DIV1;	 //配置输入分频,不分频 
  	TIM5_ICInitStructure.TIM_ICFilter = 0x00;//IC1F=0000 配置输入滤波器 不滤波
  	TIM_ICInit(TIM5, &TIM5_ICInitStructure);
	
	//中断分组初始化
	NVIC_InitStructure.NVIC_IRQChannel = TIM5_IRQn;  //TIM3中断
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;  //先占优先级2级
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;  //从优先级0级
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; //IRQ通道被使能
	NVIC_Init(&NVIC_InitStructure);  //根据NVIC_InitStruct中指定的参数初始化外设NVIC寄存器 
	
	TIM_ITConfig(TIM5,TIM_IT_Update|TIM_IT_CC1,ENABLE);//允许更新中断 ,允许CC1IE捕获中断	
	
  TIM_Cmd(TIM5,ENABLE ); 	//使能定时器5
 	
 RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);	 //使能PA,PD端口时钟
	
 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;				 //LED0-->PA.8 端口配置
 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //推挽输出
 GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 //IO口速度为50MHz
 GPIO_Init(GPIOA, &GPIO_InitStructure);					 //根据设定参数初始化GPIOA.8
 GPIO_SetBits(GPIOA,GPIO_Pin_2);						 //PA.8 输出高
}

u8  TIM5CH1_CAPTURE_STA=0;	//输入捕获状态		    				
u16	TIM5CH1_CAPTURE_VAL;	//输入捕获值
 
//定时器5中断服务程序	 
void TIM5_IRQHandler(void)
{ 

 	if((TIM5CH1_CAPTURE_STA&0X80)==0)//还未成功捕获	
	{	  
		if (TIM_GetITStatus(TIM5, TIM_IT_Update) != RESET)
		 
		{	    
			if(TIM5CH1_CAPTURE_STA&0X40)//已经捕获到高电平了
			{
				if((TIM5CH1_CAPTURE_STA&0X3F)==0X3F)//高电平太长了
				{
					TIM5CH1_CAPTURE_STA|=0X80;//标记成功捕获了一次
					TIM5CH1_CAPTURE_VAL=0XFFFF;
				}else TIM5CH1_CAPTURE_STA++;
			}	 
		}
	if (TIM_GetITStatus(TIM5, TIM_IT_CC1) != RESET)//捕获1发生捕获事件
		{	
			if(TIM5CH1_CAPTURE_STA&0X40)		//捕获到一个下降沿 		
			{	  			
				TIM5CH1_CAPTURE_STA|=0X80;		//标记成功捕获到一次高电平脉宽
				TIM5CH1_CAPTURE_VAL=TIM_GetCapture1(TIM5);
		   		TIM_OC1PolarityConfig(TIM5,TIM_ICPolarity_Rising); //CC1P=0 设置为上升沿捕获
			}else  								//还未开始,第一次捕获上升沿
			{
				TIM5CH1_CAPTURE_STA=0;			//清空
				TIM5CH1_CAPTURE_VAL=0;
	 			TIM_SetCounter(TIM5,0);
				TIM5CH1_CAPTURE_STA|=0X40;		//标记捕获到了上升沿
		   		TIM_OC1PolarityConfig(TIM5,TIM_ICPolarity_Falling);		//CC1P=1 设置为下降沿捕获
			}		    
		}			     	    					   
 	}
 
    TIM_ClearITPendingBit(TIM5, TIM_IT_CC1|TIM_IT_Update); //清除中断标志位
 
}




	void UltrasonicWave_StartMeasure2(void)
	{
	tri=1;
	delay_us(20);
	tri=0;
	delay_us(20);		 		 
	if(TIM5CH1_CAPTURE_STA&0X80)//成功捕获到了一次上升沿
	{
	temp=TIM5CH1_CAPTURE_STA&0X3F;
	temp*=65536;//溢出时间总和
	temp+=TIM5CH1_CAPTURE_VAL;//得到总的高电平时间
	if((temp*170/10000)>0)
	{
		OLED_ShowString(0,6,"distance:    cm");
		OLED_ShowNum(80,6,temp*170/10000,3,12);							//显示小时		
	}
	TIM5CH1_CAPTURE_STA=0;//开启下一次捕获
	}
	}

