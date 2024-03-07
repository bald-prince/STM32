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



#include "timer.h"
#include "includes.h"


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#if TIMx_Time_Init_Test==1  //1普通定时

//高级定时器TIM1,8  通用定时器TIM2,3,4,5   基本定时器TIM6,7
//下面以TIM1 TIM2 TIM6模板验证
void TIM1_Time_Init(u16 arr,u16 psc)
{
		//TIM1_Init(4999,7199);
	  //计数频率=Tclk/7200=72000000/7200=10000Hz  计一个数用时1/10000s  计数5000次=5000/10000s=500ms
	  //Tout(溢出时间)=(arr+1)*(psc+1)/Tclk =5000*7200/72000000s=500ms
		TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
		NVIC_InitTypeDef NVIC_InitStructure;

		RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1, ENABLE); 
		
		TIM_TimeBaseStructInit(&TIM_TimeBaseStructure);//设置缺省值,这一步最好加上
		TIM_TimeBaseStructure.TIM_Period = arr; //自动重装载寄存器周期的值，溢出值	
		TIM_TimeBaseStructure.TIM_Prescaler =psc; //时钟频率预分频值
		TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1; //设置时钟分割:输入捕获模式用来滤波
		TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIM向上计数模式
	  TIM_TimeBaseStructure.TIM_RepetitionCounter=0;//设置重复溢出次数，就是多少次溢出后进入中断，一般为0，只有高级定时器才有用
		TIM_TimeBaseInit(TIM1, &TIM_TimeBaseStructure); 

		TIM_ITConfig(TIM1,TIM_IT_Update,ENABLE ); //允许更新中断

		NVIC_InitStructure.NVIC_IRQChannel = TIM1_UP_IRQn; 
		NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 5;  
		NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;  
		NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; 
		NVIC_Init(&NVIC_InitStructure);  

		TIM_Cmd(TIM1, ENABLE);  
}

void TIM2_Time_Init(u16 arr,u16 psc)
{
		//TIM1_Init(4999,7199);
	  //计数频率=Tclk/7200=72000000/7200=10000Hz  计一个数用时1/10000s  计数5000次=5000/10000s=500ms
	  //Tout(溢出时间)=(arr+1)*(psc+1)/Tclk =5000*7200/72000000s=500ms
		TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
		NVIC_InitTypeDef NVIC_InitStructure;

		RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE); 
		
		TIM_TimeBaseStructInit(&TIM_TimeBaseStructure);//设置缺省值,这一步最好加上
		TIM_TimeBaseStructure.TIM_Period = arr; //自动重装载寄存器周期的值，溢出值	
		TIM_TimeBaseStructure.TIM_Prescaler =psc; //时钟频率预分频值
		TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1; //设置时钟分割:输入捕获模式用来滤波
		TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIM向上计数模式
		TIM_TimeBaseStructure.TIM_RepetitionCounter=0;//设置重复溢出次数，就是多少次溢出后进入中断，一般为0，只有高级定时器才有用
		TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure); 

		TIM_ITConfig(TIM2,TIM_IT_Update,ENABLE ); //允许更新中断

		NVIC_InitStructure.NVIC_IRQChannel = TIM2_IRQn; 
		NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;  
		NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;  
		NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; 
		NVIC_Init(&NVIC_InitStructure);  

		TIM_Cmd(TIM2, ENABLE);  
}
void TIM6_Time_Init(u16 arr,u16 psc)
{
		//TIM1_Init(4999,7199);
	  //计数频率=Tclk/7200=72000000/7200=10000Hz  计一个数用时1/10000s  计数5000次=5000/10000s=500ms
	  //Tout(溢出时间)=(arr+1)*(psc+1)/Tclk =5000*7200/72000000s=500ms
		TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
		NVIC_InitTypeDef NVIC_InitStructure;

		RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM6, ENABLE); 
		
		TIM_TimeBaseStructInit(&TIM_TimeBaseStructure);//设置缺省值,这一步最好加上
		TIM_TimeBaseStructure.TIM_Period = arr; //自动重装载寄存器周期的值，溢出值	
		TIM_TimeBaseStructure.TIM_Prescaler =psc; //时钟频率预分频值
		TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1; //设置时钟分割:输入捕获模式用来滤波
		TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIM向上计数模式
		TIM_TimeBaseStructure.TIM_RepetitionCounter=0;//设置重复溢出次数，就是多少次溢出后进入中断，一般为0，只有高级定时器才有用
		TIM_TimeBaseInit(TIM6, &TIM_TimeBaseStructure); 

		TIM_ITConfig(TIM6,TIM_IT_Update,ENABLE ); //允许更新中断

		NVIC_InitStructure.NVIC_IRQChannel = TIM6_IRQn; 
		NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;  
		NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;  
		NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; 
		NVIC_Init(&NVIC_InitStructure);  

		TIM_Cmd(TIM6, ENABLE);  
}
#endif
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#if TIMx_InputCapture_Init_Test==1  //2输入捕获

u16 TIM1CH1_CAPTURE_STA = 0;	//通道1输入捕获标志，15位做捕获标志，低15位做溢出标志		
u16 TIM1CH1_CAPTURE_UPVAL,TIM1CH1_CAPTURE_DOWNVAL;
//u16 TIM1CH2_CAPTURE_STA = 0;	//通道1输入捕获标志，15位做捕获标志，低15位做溢出标志			
//u16 TIM1CH2_CAPTURE_UPVAL,TIM1CH2_CAPTURE_DOWNVAL;
//u16 TIM1CH3_CAPTURE_STA = 0;	//通道1输入捕获标志，15位做捕获标志，低15位做溢出标志			
//u16 TIM1CH3_CAPTURE_UPVAL,TIM1CH3_CAPTURE_DOWNVAL;
u16 TIM1CH4_CAPTURE_STA = 0;	//通道1输入捕获标志，15位做捕获标志，低15位做溢出标志			
u16 TIM1CH4_CAPTURE_UPVAL,TIM1CH4_CAPTURE_DOWNVAL;

u32 TIM1_CH1_Time;	//CH1测量方波1的高电平时间，用于计算占空比
//u32 TIM1_CH2_Time;	//CH2测量方波1的两个上升沿间隔时间，用于计算周期
//u32 TIM1_CH3_Time;	//CH3测量方波2的高电平时间，用于计算占空比
u32 TIM1_CH4_Time;	//CH4测量方波2的两个上升沿间隔时间，用于计算周期
void TIM1_InputCapture_Init(u16 arr,u16 psc)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
  TIM_ICInitTypeDef TIM_ICInitStructure;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1, ENABLE);
	//RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);  

	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8|GPIO_Pin_11;  
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD; 
	GPIO_Init(GPIOA, &GPIO_InitStructure);


	TIM_TimeBaseStructInit(&TIM_TimeBaseStructure);//设置缺省值,这一步最好加上
	TIM_TimeBaseStructure.TIM_Period = arr; //自动重装载寄存器周期的值，溢出值	
	TIM_TimeBaseStructure.TIM_Prescaler =psc; //时钟频率预分频值
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1; //设置时钟分割:输入捕获模式用来滤波
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIM向上计数模式
	TIM_TimeBaseStructure.TIM_RepetitionCounter=0;//设置重复溢出次数，就是多少次溢出后进入中断，一般为0，只有高级定时器才有用
	TIM_TimeBaseInit(TIM1, &TIM_TimeBaseStructure); 


	TIM_ICStructInit(&TIM_ICInitStructure);//设置缺省值,这一步最好加上
	TIM_ICInitStructure.TIM_ICPolarity = TIM_ICPolarity_Rising;	//上升沿捕获
	TIM_ICInitStructure.TIM_ICSelection = TIM_ICSelection_DirectTI; //映射到TI1上
	TIM_ICInitStructure.TIM_ICPrescaler = TIM_ICPSC_DIV1;	  //配置输入分频,不分频 
	TIM_ICInitStructure.TIM_ICFilter = 0x00;	  //IC1F=0000 配置输入滤波器 0不滤波
	
	//捕获通道1
	TIM_ICInitStructure.TIM_Channel = TIM_Channel_1; //IC1映射到TI1上，这四句不能合并
	TIM_ICInit(TIM1, &TIM_ICInitStructure);
	

	//捕获通道4
	TIM_ICInitStructure.TIM_Channel = TIM_Channel_4; //IC4映射到TI4上，这四句不能合并
	TIM_ICInit(TIM1, &TIM_ICInitStructure);
	
	//中断分组初始化
	NVIC_InitStructure.NVIC_IRQChannel = TIM1_CC_IRQn;  
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0; 
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0; 
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; 
	NVIC_Init(&NVIC_InitStructure);   

	TIM_ITConfig(TIM1,TIM_IT_Update|TIM_IT_CC1|TIM_IT_CC4,ENABLE);   //允许更新中断，允许CC1IE,CC2IE,CC3IE,CC4IE捕获中断	
	TIM_CtrlPWMOutputs(TIM1,ENABLE);	//主输出使能
	TIM_Cmd(TIM1, ENABLE); 		//使能定时器4
}



u16 TIM2CH1_CAPTURE_STA = 0;	//通道1输入捕获标志，15位做捕获标志，低15位做溢出标志		
u16 TIM2CH1_CAPTURE_UPVAL,TIM2CH1_CAPTURE_DOWNVAL;
u16 TIM2CH2_CAPTURE_STA = 0;	//通道1输入捕获标志，15位做捕获标志，低15位做溢出标志			
u16 TIM2CH2_CAPTURE_UPVAL,TIM2CH2_CAPTURE_DOWNVAL;
u16 TIM2CH3_CAPTURE_STA = 0;	//通道1输入捕获标志，15位做捕获标志，低15位做溢出标志			
u16 TIM2CH3_CAPTURE_UPVAL,TIM2CH3_CAPTURE_DOWNVAL;
u16 TIM2CH4_CAPTURE_STA = 0;	//通道1输入捕获标志，15位做捕获标志，低15位做溢出标志			
u16 TIM2CH4_CAPTURE_UPVAL,TIM2CH4_CAPTURE_DOWNVAL;

u32 TIM2_CH1_Time;	//CH1测量方波1的高电平时间，用于计算占空比
u32 TIM2_CH2_Time;	//CH2测量方波1的两个上升沿间隔时间，用于计算周期
u32 TIM2_CH3_Time;	//CH3测量方波2的高电平时间，用于计算占空比
u32 TIM2_CH4_Time;	//CH4测量方波2的两个上升沿间隔时间，用于计算周期
void TIM2_InputCapture_Init(u16 arr,u16 psc)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
  TIM_ICInitTypeDef TIM_ICInitStructure;
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);  

	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_2|GPIO_Pin_3;  
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD; 
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	GPIO_ResetBits(GPIOA, GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_2|GPIO_Pin_3);

	TIM_TimeBaseStructInit(&TIM_TimeBaseStructure);//设置缺省值,这一步最好加上
	TIM_TimeBaseStructure.TIM_Period = arr; //自动重装载寄存器周期的值，溢出值	
	TIM_TimeBaseStructure.TIM_Prescaler =psc; //时钟频率预分频值
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1; //设置时钟分割:输入捕获模式用来滤波
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIM向上计数模式
	TIM_TimeBaseStructure.TIM_RepetitionCounter=0;//设置重复溢出次数，就是多少次溢出后进入中断，一般为0，只有高级定时器才有用
	TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure); 


	TIM_ICStructInit(&TIM_ICInitStructure);//设置缺省值,这一步最好加上
	TIM_ICInitStructure.TIM_ICPolarity = TIM_ICPolarity_Rising;	//上升沿捕获
	TIM_ICInitStructure.TIM_ICSelection = TIM_ICSelection_DirectTI; //映射到TI1上
	TIM_ICInitStructure.TIM_ICPrescaler = TIM_ICPSC_DIV1;	  //配置输入分频,不分频 
	TIM_ICInitStructure.TIM_ICFilter = 0x00;	  //IC1F=0000 配置输入滤波器 0不滤波
	
	//捕获通道1
	TIM_ICInitStructure.TIM_Channel = TIM_Channel_1; //IC1映射到TI1上，这四句不能合并
	TIM_ICInit(TIM2, &TIM_ICInitStructure);
	
	//捕获通道2
	TIM_ICInitStructure.TIM_Channel = TIM_Channel_2; //IC2映射到TI2上，这四句不能合并
	TIM_ICInit(TIM2, &TIM_ICInitStructure);
	
	//捕获通道3
	TIM_ICInitStructure.TIM_Channel = TIM_Channel_3; //IC3映射到TI3上，这四句不能合并
	TIM_ICInit(TIM2, &TIM_ICInitStructure);

	//捕获通道4
	TIM_ICInitStructure.TIM_Channel = TIM_Channel_4; //IC4映射到TI4上，这四句不能合并
	TIM_ICInit(TIM2, &TIM_ICInitStructure);
	
	//中断分组初始化
	NVIC_InitStructure.NVIC_IRQChannel = TIM2_IRQn;  
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0; 
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0; 
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; 
	NVIC_Init(&NVIC_InitStructure);   

	TIM_ITConfig(TIM2,TIM_IT_Update|TIM_IT_CC1|TIM_IT_CC2|TIM_IT_CC3|TIM_IT_CC4,ENABLE);   //允许更新中断，允许CC1IE,CC2IE,CC3IE,CC4IE捕获中断	
	TIM_Cmd(TIM2, ENABLE); 		//使能定时器4
}
#endif
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#if TIMx_OutputCompare_Init_Test==1  //3输出比较 
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
u8 TIM1_CH1_Flag;	
u8 TIM1_CH2_Flag;	
u8 TIM1_CH3_Flag;	
u8 TIM1_CH4_Flag;	
void TIM1_OutputCompare_Init(u16 arr,u16 psc)
{
		GPIO_InitTypeDef GPIO_InitStructure;
		TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
		TIM_OCInitTypeDef  TIM_OCInitStructure;
	   NVIC_InitTypeDef NVIC_InitStructure;
	
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1, ENABLE); 
		//RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_AFIO, ENABLE);  
	
		TIM_TimeBaseStructInit(&TIM_TimeBaseStructure);//设置缺省值,这一步最好加上
		TIM_TimeBaseStructure.TIM_Period = arr; //自动重装载寄存器周期的值，溢出值
		TIM_TimeBaseStructure.TIM_Prescaler =psc; //时钟频率预分频值
	  TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1; //设置时钟分割:输入捕获模式用来滤波
		TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIM向上计数模式
		TIM_TimeBaseStructure.TIM_RepetitionCounter=0;//设置重复溢出次数，就是多少次溢出后进入中断，一般为0，只有高级定时器才有用
		TIM_TimeBaseInit(TIM1, &TIM_TimeBaseStructure); 
	
		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8|GPIO_Pin_11; 
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP; 
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
		GPIO_Init(GPIOA, &GPIO_InitStructure);

// TIM_OCMode	           函数库描述	           解释 
// TIM_OCMode_Timing	   TIM输出比较时间模式	 冻结，输出比较不起作用
// TIM_OOCMode_Active	   TIM输出比较主动模式	 当比较发生时，强制输出高电平
// TIM_OCMode_Inactiive	 TIM输出比较非主动模式 当比较发生时，强制输出低电平
// TIM_OCMode_Toggle	   TIM输出比较触发模式	 当比较发生时，输出翻转
// TIM_OCMode_PWM1	     TIM脉冲宽度调制模式1	 PWM1
// TIM_OCMode_PWM2	     TIM脉冲宽度调制模式2	 PWM2

	  TIM_OCStructInit(&TIM_OCInitStructure);//设置缺省值,这一步最好加上
		TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_Toggle; //TIM输出比较触发模式	 当比较发生时，输出翻转，冻结模式可以翻转任意io生成pwm
		TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; //比较输出使能
		TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High; //输出极性:TIM输出比较极性高
	
    TIM_OCInitStructure.TIM_Pulse = 100; //设置待装入捕获比较寄存器的脉冲值
		TIM_OC1Init(TIM1, &TIM_OCInitStructure);           
		TIM_OC1PreloadConfig(TIM1, TIM_OCPreload_Disable);

    TIM_OCInitStructure.TIM_Pulse = 400;
		TIM_OC4Init(TIM1, &TIM_OCInitStructure);           
		TIM_OC4PreloadConfig(TIM1, TIM_OCPreload_Disable); 
		
	
		//中断分组初始化
	  NVIC_InitStructure.NVIC_IRQChannel = TIM1_CC_IRQn;  
	  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0; 
	  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0; 
	  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; 
	  NVIC_Init(&NVIC_InitStructure);   
  
    TIM_ITConfig(TIM1, TIM_IT_CC1|TIM_IT_CC2|TIM_IT_CC3|TIM_IT_CC4, ENABLE);
		TIM_CtrlPWMOutputs(TIM1,ENABLE);	//主输出使能
	  TIM_Cmd(TIM1,ENABLE); //启动定时器3 TIM3_CR1[0]=1;
}

u8 TIM2_CH1_Flag;	
u8 TIM2_CH2_Flag;	
u8 TIM2_CH3_Flag;	
u8 TIM2_CH4_Flag;	
void TIM2_OutputCompare_Init(u16 arr,u16 psc)
{
		GPIO_InitTypeDef GPIO_InitStructure;
		TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
		TIM_OCInitTypeDef  TIM_OCInitStructure;
	   NVIC_InitTypeDef NVIC_InitStructure;
	
		RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_AFIO, ENABLE);  
	
		TIM_TimeBaseStructInit(&TIM_TimeBaseStructure);//设置缺省值,这一步最好加上
		TIM_TimeBaseStructure.TIM_Period = arr; //自动重装载寄存器周期的值，溢出值
		TIM_TimeBaseStructure.TIM_Prescaler =psc; //时钟频率预分频值
	  TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1; //设置时钟分割:输入捕获模式用来滤波
		TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIM向上计数模式
		TIM_TimeBaseStructure.TIM_RepetitionCounter=0;//设置重复溢出次数，就是多少次溢出后进入中断，一般为0，只有高级定时器才有用
		TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure); 
	
		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_2|GPIO_Pin_3; 
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP; 
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
		GPIO_Init(GPIOA, &GPIO_InitStructure);

// TIM_OCMode	           函数库描述	           解释 
// TIM_OCMode_Timing	   TIM输出比较时间模式	 冻结，输出比较不起作用
// TIM_OOCMode_Active	   TIM输出比较主动模式	 当比较发生时，强制输出高电平
// TIM_OCMode_Inactiive	 TIM输出比较非主动模式 当比较发生时，强制输出低电平
// TIM_OCMode_Toggle	   TIM输出比较触发模式	 当比较发生时，输出翻转
// TIM_OCMode_PWM1	     TIM脉冲宽度调制模式1	 PWM1
// TIM_OCMode_PWM2	     TIM脉冲宽度调制模式2	 PWM2

	  TIM_OCStructInit(&TIM_OCInitStructure);//设置缺省值,这一步最好加上
		TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_Toggle; //TIM输出比较触发模式	 当比较发生时，输出翻转，冻结模式可以翻转任意io生成pwm
		TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; //比较输出使能
		TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High; //输出极性:TIM输出比较极性高
	
    TIM_OCInitStructure.TIM_Pulse = 100; //设置待装入捕获比较寄存器的脉冲值
		TIM_OC1Init(TIM2, &TIM_OCInitStructure);           
		TIM_OC1PreloadConfig(TIM2, TIM_OCPreload_Disable);
    
    TIM_OCInitStructure.TIM_Pulse = 200;		
		TIM_OC2Init(TIM2, &TIM_OCInitStructure);            
		TIM_OC2PreloadConfig(TIM2, TIM_OCPreload_Disable);
		 
		TIM_OCInitStructure.TIM_Pulse = 300;
		TIM_OC3Init(TIM2, &TIM_OCInitStructure);           
		TIM_OC3PreloadConfig(TIM2, TIM_OCPreload_Disable);

    TIM_OCInitStructure.TIM_Pulse = 400;
		TIM_OC4Init(TIM2, &TIM_OCInitStructure);           
		TIM_OC4PreloadConfig(TIM2, TIM_OCPreload_Disable); 
		
	
		//中断分组初始化
	NVIC_InitStructure.NVIC_IRQChannel = TIM2_IRQn;  
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0; 
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0; 
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; 
	NVIC_Init(&NVIC_InitStructure);   
  
    TIM_ITConfig(TIM2, TIM_IT_CC1|TIM_IT_CC2|TIM_IT_CC3|TIM_IT_CC4, ENABLE);
	  TIM_Cmd(TIM2,ENABLE); //启动定时器3 TIM3_CR1[0]=1;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


#endif
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#if TIMx_Pwm_Init_Test==1  //4PWM 
void TIM1_Pwm_Init(u16 arr,u16 psc)//TIM1_Pwm_Init(7200,0);PWM周期=(arr+1)*(psc+1)/Tclk=7200*1/72000000s=0.1ms
{  
	GPIO_InitTypeDef GPIO_InitStructure;
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	TIM_OCInitTypeDef  TIM_OCInitStructure;

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1, ENABLE); 
 	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA , ENABLE);  
	                                                                     	
	TIM_TimeBaseStructInit(&TIM_TimeBaseStructure);//设置缺省值,这一步最好加上
	TIM_TimeBaseStructure.TIM_Period = arr; //自动重装载寄存器周期的值，溢出值
	TIM_TimeBaseStructure.TIM_Prescaler =psc; //时钟频率预分频值
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1; //设置时钟分割:输入捕获模式用来滤波
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIM向上计数模式
	TIM_TimeBaseStructure.TIM_RepetitionCounter=0;//设置重复溢出次数，就是多少次溢出后进入中断，一般为0，只有高级定时器才有用
	TIM_TimeBaseInit(TIM1, &TIM_TimeBaseStructure); 
	
	
   //设置该引脚为复用输出功能,输出TIM1 CH1的PWM脉冲波形
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8|GPIO_Pin_11; 
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;  
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);

 	TIM_OCStructInit(&TIM_OCInitStructure);//设置缺省值,这一步最好加上
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM2; //选择定时器模式:TIM脉冲宽度调制模式2
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; //比较输出使能
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_Low; //输出极性:TIM输出比较极性高
	
	
	TIM_OC1Init(TIM1, &TIM_OCInitStructure);           
	TIM_OC1PreloadConfig(TIM1, TIM_OCPreload_Enable); 
	TIM_OC4Init(TIM1, &TIM_OCInitStructure);           
	TIM_OC4PreloadConfig(TIM1, TIM_OCPreload_Enable); 
	
  TIM_CtrlPWMOutputs(TIM1,ENABLE);	//主输出使能
	TIM_Cmd(TIM1, ENABLE);  //使能TIM1
}

void TIM2_Pwm_Init(u16 arr,u16 psc)//TIM2_Pwm_Init(7200,0);PWM周期=(arr+1)*(psc+1)/Tclk=7200*1/72000000s=0.1ms
{
		GPIO_InitTypeDef GPIO_InitStructure;
		TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
		TIM_OCInitTypeDef  TIM_OCInitStructure;

		RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_AFIO, ENABLE);  
	
		TIM_TimeBaseStructInit(&TIM_TimeBaseStructure);//设置缺省值,这一步最好加上
		TIM_TimeBaseStructure.TIM_Period = arr; //自动重装载寄存器周期的值，溢出值
		TIM_TimeBaseStructure.TIM_Prescaler =psc; //时钟频率预分频值
	  TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1; //设置时钟分割:输入捕获模式用来滤波
		TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIM向上计数模式
		TIM_TimeBaseStructure.TIM_RepetitionCounter=0;//设置重复溢出次数，就是多少次溢出后进入中断，一般为0，只有高级定时器才有用
		TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure); 
	
		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_2|GPIO_Pin_3; 
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP; 
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
		GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	  TIM_OCStructInit(&TIM_OCInitStructure);//设置缺省值,这一步最好加上
		TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1; //选择定时器模式:TIM脉冲宽度调制模式2
		TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; //比较输出使能
		TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High; //输出极性:TIM输出比较极性高
		
		TIM_OC1Init(TIM2, &TIM_OCInitStructure);           
		TIM_OC1PreloadConfig(TIM2, TIM_OCPreload_Enable); 
		TIM_OC2Init(TIM2, &TIM_OCInitStructure);            
		TIM_OC2PreloadConfig(TIM2, TIM_OCPreload_Enable);
		TIM_OC3Init(TIM2, &TIM_OCInitStructure);           
		TIM_OC3PreloadConfig(TIM2, TIM_OCPreload_Enable); 
		TIM_OC4Init(TIM2, &TIM_OCInitStructure);           
		TIM_OC4PreloadConfig(TIM2, TIM_OCPreload_Enable); 

		TIM_Cmd(TIM2, ENABLE);
}
#endif
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//将示波器(或逻辑分析仪)的探头连接到TIMx通道1对应的引脚，
//然后用杜邦线将TIMx通道2对应的引脚连接到GND接地引脚，然后马上在将杜邦线拔掉，这样来模拟一个上升沿
//在示波器(或逻辑分析仪)上就检测到延时设置延时时间后TIMx通道1输出一个设定宽度的脉冲

#if TIMx_OnePulseOutput_Init_Test==1  //5单脉冲输出 
//检测到上升沿延时时间 （延时这么久开始输出单脉冲）= 1 / (72M/72/10000) = 10ms
//脉冲宽度                                         = 1 / (72M/72/(65535 - 10000)) = 55.535ms
void TIM1_OnePulseOutput_Init(u16 arr,u16 psc)
{
		GPIO_InitTypeDef GPIO_InitStructure;
		TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
		TIM_OCInitTypeDef  TIM_OCInitStructure;
	  TIM_ICInitTypeDef  TIM_ICInitStructure;
	  RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1, ENABLE); 
		//RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_AFIO, ENABLE);  
	
		TIM_TimeBaseStructInit(&TIM_TimeBaseStructure);//设置缺省值,这一步最好加上
		TIM_TimeBaseStructure.TIM_Period = arr; //自动重装载寄存器周期的值，溢出值
		TIM_TimeBaseStructure.TIM_Prescaler =psc; //时钟频率预分频值
	  TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1; //设置时钟分割:输入捕获模式用来滤波
		TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIM向上计数模式
		TIM_TimeBaseStructure.TIM_RepetitionCounter=0;//设置重复溢出次数，就是多少次溢出后进入中断，一般为0，只有高级定时器才有用
		TIM_TimeBaseInit(TIM1, &TIM_TimeBaseStructure); 
	
		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8; 
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP; 
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
		GPIO_Init(GPIOA, &GPIO_InitStructure);


		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9; 
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING ; 
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
		GPIO_Init(GPIOA, &GPIO_InitStructure);
		     
				 
	  TIM_OCStructInit(&TIM_OCInitStructure);//设置缺省值,这一步最好加上
		TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM2; //选择定时器模式:TIM脉冲宽度调制模式2
		TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; //比较输出使能
		TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High; //输出极性:TIM输出比较极性高	

    TIM_OCInitStructure.TIM_Pulse = 10000; //设置待装入捕获比较寄存器的脉冲值
		TIM_OC1Init(TIM1, &TIM_OCInitStructure);           
		TIM_OC1PreloadConfig(TIM1, TIM_OCPreload_Disable);
    
		
	TIM_ICStructInit(&TIM_ICInitStructure);//设置缺省值,这一步最好加上
	TIM_ICInitStructure.TIM_ICPolarity = TIM_ICPolarity_Rising;	//上升沿捕获
	TIM_ICInitStructure.TIM_ICSelection = TIM_ICSelection_DirectTI; //映射到TI1上
	TIM_ICInitStructure.TIM_ICPrescaler = TIM_ICPSC_DIV1;	  //配置输入分频,不分频 
	TIM_ICInitStructure.TIM_ICFilter = 0x00;	  //IC1F=0000 配置输入滤波器 0不滤波
	

	
	//捕获通道2
	TIM_ICInitStructure.TIM_Channel = TIM_Channel_2; //IC2映射到TI2上，这四句不能合并
	TIM_ICInit(TIM1, &TIM_ICInitStructure);
	

	TIM_SelectOnePulseMode(TIM1, TIM_OPMode_Single);//选择定时器为单脉冲模式
	TIM_SelectInputTrigger(TIM1, TIM_TS_TI2FP2);//选择触发源为IC2,没有TIM_TS_TI3FP3，TIM_TS_TI4FP4就是3,4不能用作单脉冲，网上有开启教程添加TIM_TS_TI3FP3，TIM_TS_TI4FP4，并改库函数，太过麻烦就算了
	TIM_SelectSlaveMode(TIM1, TIM_SlaveMode_Trigger);//选择定时器从模式为上升沿触发

	TIM_CtrlPWMOutputs(TIM1,ENABLE);	//主输出使能
	TIM_Cmd(TIM1, ENABLE);  //使能TIM1
}
//检测到上升沿延时时间 （延时这么久开始输出单脉冲）= 1 / (72M/72/10000) = 10ms
//脉冲宽度                                         = 1 / (72M/72/(65535 - 10000)) = 55.535ms
void TIM2_OnePulseOutput_Init(u16 arr,u16 psc)
{
		GPIO_InitTypeDef GPIO_InitStructure;
		TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
		TIM_OCInitTypeDef  TIM_OCInitStructure;
	  TIM_ICInitTypeDef  TIM_ICInitStructure;
	
		RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_AFIO, ENABLE);  
	
		TIM_TimeBaseStructInit(&TIM_TimeBaseStructure);//设置缺省值,这一步最好加上
		TIM_TimeBaseStructure.TIM_Period = arr; //自动重装载寄存器周期的值，溢出值
		TIM_TimeBaseStructure.TIM_Prescaler =psc; //时钟频率预分频值
	  TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1; //设置时钟分割:输入捕获模式用来滤波
		TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIM向上计数模式
		TIM_TimeBaseStructure.TIM_RepetitionCounter=0;//设置重复溢出次数，就是多少次溢出后进入中断，一般为0，只有高级定时器才有用
		TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure); 
	
		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0; 
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP; 
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
		GPIO_Init(GPIOA, &GPIO_InitStructure);


		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1; 
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING ; 
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
		GPIO_Init(GPIOA, &GPIO_InitStructure);
		     
				 
	  TIM_OCStructInit(&TIM_OCInitStructure);//设置缺省值,这一步最好加上
		TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM2; //选择定时器模式:TIM脉冲宽度调制模式2
		TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; //比较输出使能
		TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High; //输出极性:TIM输出比较极性高	

    TIM_OCInitStructure.TIM_Pulse = 10000; //设置待装入捕获比较寄存器的脉冲值
		TIM_OC1Init(TIM2, &TIM_OCInitStructure);           
		TIM_OC1PreloadConfig(TIM2, TIM_OCPreload_Disable);
    
		
	TIM_ICStructInit(&TIM_ICInitStructure);//设置缺省值,这一步最好加上
	TIM_ICInitStructure.TIM_ICPolarity = TIM_ICPolarity_Rising;	//上升沿捕获
	TIM_ICInitStructure.TIM_ICSelection = TIM_ICSelection_DirectTI; //映射到TI1上
	TIM_ICInitStructure.TIM_ICPrescaler = TIM_ICPSC_DIV1;	  //配置输入分频,不分频 
	TIM_ICInitStructure.TIM_ICFilter = 0x00;	  //IC1F=0000 配置输入滤波器 0不滤波
	

	
	//捕获通道2
	TIM_ICInitStructure.TIM_Channel = TIM_Channel_2; //IC2映射到TI2上，这四句不能合并
	TIM_ICInit(TIM2, &TIM_ICInitStructure);
	

	TIM_SelectOnePulseMode(TIM2, TIM_OPMode_Single);//选择定时器为单脉冲模式
	TIM_SelectInputTrigger(TIM2, TIM_TS_TI2FP2);//选择触发源为IC2,没有TIM_TS_TI3FP3，TIM_TS_TI4FP4就是3,4不能用作单脉冲，网上有开启教程添加TIM_TS_TI3FP3，TIM_TS_TI4FP4，并改库函数，太过麻烦就算了
	TIM_SelectSlaveMode(TIM2, TIM_SlaveMode_Trigger);//选择定时器从模式为上升沿触发
	TIM_Cmd(TIM2,ENABLE); //启动定时器3 TIM3_CR1[0]=1;
}
#endif
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


#if TIMx_Time_Init_Test==1  //1普通定时
void TIM1_UP_IRQHandler(void)   
{
		if (TIM_GetITStatus(TIM1, TIM_IT_Update) != RESET)  //检查更新中断发生与否
		{
				TIM_ClearITPendingBit(TIM1, TIM_IT_Update);  //清除TIMx更新中断标志 
			  printf("TIM1 1s\r\n");
		}
}

void TIM2_IRQHandler(void)   
{
		if (TIM_GetITStatus(TIM2, TIM_IT_Update) != RESET)  //检查更新中断发生与否
		{
				TIM_ClearITPendingBit(TIM2, TIM_IT_Update);  //清除TIMx更新中断标志 
			  printf("TIM2 1s\r\n");
		}
}
void TIM6_IRQHandler(void)   
{
		if (TIM_GetITStatus(TIM6, TIM_IT_Update) != RESET)  //检查更新中断发生与否
		{
				TIM_ClearITPendingBit(TIM6, TIM_IT_Update);  //清除TIMx更新中断标志 
			  printf("TIM6 1s\r\n");
		}
}
#endif

#if TIMx_InputCapture_Init_Test==1  //2输入捕获
void TIM1_CC_IRQHandler(void)
{
		if (TIM_GetITStatus(TIM1, TIM_IT_Update) != RESET)
		{	
			  //通道1					
				if(TIM1CH1_CAPTURE_STA&0X8000)//已经捕获到高电平了
				{
						if((TIM1CH1_CAPTURE_STA&0X7FFF)==0X7FFF)//高电平太长了
                TIM1CH1_CAPTURE_STA = 0;		//捕获标志位清零
						else 
								TIM1CH1_CAPTURE_STA++;
				}
			
			  //通道4			
				if(TIM1CH4_CAPTURE_STA&0X8000)//已经捕获到高电平了
				{
						if((TIM1CH4_CAPTURE_STA&0X7FFF)==0X7FFF)//高电平太长了
                TIM1CH4_CAPTURE_STA = 0;		//捕获标志位清零
						else 
								TIM1CH4_CAPTURE_STA++;
				}	
		}
		
		//通道1
		if (TIM_GetITStatus(TIM1, TIM_IT_CC1) != RESET) 		//捕获1发生捕获事件
		{
				
				if (TIM1CH1_CAPTURE_STA & 0X8000)		//捕获到一个下降沿
				{
						TIM1CH1_CAPTURE_DOWNVAL = TIM_GetCapture1(TIM1);//记录下此时的定时器计数值
						TIM_OC1PolarityConfig(TIM1, TIM_ICPolarity_Rising); //设置为上升沿捕获
						TIM1_CH1_Time = TIM1CH1_CAPTURE_DOWNVAL - TIM1CH1_CAPTURE_UPVAL+ 65536*(TIM1CH1_CAPTURE_STA&0X7FFF);		//得到总的高电平的时间
						TIM1CH1_CAPTURE_STA = 0;		//捕获标志位清零					
				}
				else //发生捕获时间但不是下降沿，第一次捕获到上升沿，记录此时的定时器计数值
				{
						TIM1CH1_CAPTURE_UPVAL = TIM_GetCapture1(TIM1);		//获取上升沿数据
						TIM_OC1PolarityConfig(TIM1, TIM_ICPolarity_Falling);//设置为下降沿捕获
						TIM1CH1_CAPTURE_STA |= 0X8000;		//标记已捕获到上升沿
				}
		}
	
		//通道4
		if (TIM_GetITStatus(TIM1, TIM_IT_CC4) != RESET) 		//捕获4发生捕获事件
		{
				if (TIM1CH4_CAPTURE_STA & 0X8000)		//捕获到一个下降沿
				{
						TIM1CH4_CAPTURE_DOWNVAL = TIM_GetCapture4(TIM1);//记录下此时的定时器计数值
						//TIM_OC4PolarityConfig(TIM1, TIM_ICPolarity_Rising); //设置为上升沿捕获
						TIM1_CH4_Time = TIM1CH4_CAPTURE_DOWNVAL - TIM1CH4_CAPTURE_UPVAL+ 65536*(TIM1CH4_CAPTURE_STA&0X7FFF);		//得到总的高电平的时间
						TIM1CH4_CAPTURE_STA = 0;		//捕获标志位清零					
				}
				else //发生捕获时间但不是下降沿，第一次捕获到上升沿，记录此时的定时器计数值
				{
						TIM1CH4_CAPTURE_UPVAL = TIM_GetCapture4(TIM1);		//获取上升沿数据
						//TIM_OC4PolarityConfig(TIM1, TIM_ICPolarity_Falling);//设置为下降沿捕获
						TIM1CH4_CAPTURE_STA |= 0X8000;		//标记已捕获到上升沿
				}
		}
    TIM_ClearITPendingBit(TIM1, TIM_IT_CC1|TIM_IT_CC4|TIM_IT_Update); 		//清除中断标志位		
} 

void TIM2_IRQHandler(void)
{
		if (TIM_GetITStatus(TIM2, TIM_IT_Update) != RESET)
		{	
			  //通道1					
				if(TIM2CH1_CAPTURE_STA&0X8000)//已经捕获到高电平了
				{
						if((TIM2CH1_CAPTURE_STA&0X7FFF)==0X7FFF)//高电平太长了
                TIM2CH1_CAPTURE_STA = 0;		//捕获标志位清零
						else 
								TIM2CH1_CAPTURE_STA++;
				}
			  //通道2				
				if(TIM2CH2_CAPTURE_STA&0X8000)//已经捕获到高电平了
				{
						if((TIM2CH2_CAPTURE_STA&0X7FFF)==0X7FFF)//高电平太长了
                TIM2CH2_CAPTURE_STA = 0;		//捕获标志位清零
						else 
								TIM2CH2_CAPTURE_STA++;
				}	
			  //通道3				
				if(TIM2CH3_CAPTURE_STA&0X8000)//已经捕获到高电平了
				{
						if((TIM2CH3_CAPTURE_STA&0X7FFF)==0X7FFF)//高电平太长了
                TIM2CH3_CAPTURE_STA = 0;		//捕获标志位清零
						else 
								TIM2CH3_CAPTURE_STA++;
				}
			  //通道4			
				if(TIM2CH4_CAPTURE_STA&0X8000)//已经捕获到高电平了
				{
						if((TIM2CH4_CAPTURE_STA&0X7FFF)==0X7FFF)//高电平太长了
                TIM2CH4_CAPTURE_STA = 0;		//捕获标志位清零
						else 
								TIM2CH4_CAPTURE_STA++;
				}	
		}
		
		//通道1
		if (TIM_GetITStatus(TIM2, TIM_IT_CC1) != RESET) 		//捕获1发生捕获事件
		{
				
				if (TIM2CH1_CAPTURE_STA & 0X8000)		//捕获到一个下降沿
				{
						TIM2CH1_CAPTURE_DOWNVAL = TIM_GetCapture1(TIM2);//记录下此时的定时器计数值
						TIM_OC1PolarityConfig(TIM2, TIM_ICPolarity_Rising); //设置为上升沿捕获
						TIM2_CH1_Time = TIM2CH1_CAPTURE_DOWNVAL - TIM2CH1_CAPTURE_UPVAL+ 65536*(TIM2CH1_CAPTURE_STA&0X7FFF);		//得到总的高电平的时间
						TIM2CH1_CAPTURE_STA = 0;		//捕获标志位清零					
				}
				else //发生捕获时间但不是下降沿，第一次捕获到上升沿，记录此时的定时器计数值
				{
						TIM2CH1_CAPTURE_UPVAL = TIM_GetCapture1(TIM2);		//获取上升沿数据
						TIM_OC1PolarityConfig(TIM2, TIM_ICPolarity_Falling);//设置为下降沿捕获
						TIM2CH1_CAPTURE_STA |= 0X8000;		//标记已捕获到上升沿
				}
		}
		//通道2
		if (TIM_GetITStatus(TIM2, TIM_IT_CC2) != RESET) 		//捕获2发生捕获事件
		{
				if (TIM2CH2_CAPTURE_STA & 0X8000)		//捕获到一个下降沿
				{
						TIM2CH2_CAPTURE_DOWNVAL = TIM_GetCapture2(TIM2);//记录下此时的定时器计数值
						//TIM_OC2PolarityConfig(TIM2, TIM_ICPolarity_Rising); //设置为上升沿捕获
						TIM2_CH2_Time = TIM2CH2_CAPTURE_DOWNVAL - TIM2CH2_CAPTURE_UPVAL+ 65536*(TIM2CH2_CAPTURE_STA&0X7FFF);		//得到总的高电平的时间
						TIM2CH2_CAPTURE_STA = 0;		//捕获标志位清零					
				}
				else //发生捕获时间但不是下降沿，第一次捕获到上升沿，记录此时的定时器计数值
				{
						TIM2CH2_CAPTURE_UPVAL = TIM_GetCapture2(TIM2);		//获取上升沿数据
						//TIM_OC2PolarityConfig(TIM2, TIM_ICPolarity_Falling);//设置为下降沿捕获
						TIM2CH2_CAPTURE_STA |= 0X8000;		//标记已捕获到上升沿
				}
		}
		//通道3
		if (TIM_GetITStatus(TIM2, TIM_IT_CC3) != RESET) 		//捕获3发生捕获事件
		{
				if (TIM2CH3_CAPTURE_STA & 0X8000)		//捕获到一个下降沿
				{
						TIM2CH3_CAPTURE_DOWNVAL = TIM_GetCapture3(TIM2);//记录下此时的定时器计数值
						TIM_OC3PolarityConfig(TIM2, TIM_ICPolarity_Rising); //设置为上升沿捕获
						TIM2_CH3_Time = TIM2CH3_CAPTURE_DOWNVAL - TIM2CH3_CAPTURE_UPVAL+ 65536*(TIM2CH3_CAPTURE_STA&0X7FFF);		//得到总的高电平的时间
						TIM2CH3_CAPTURE_STA = 0;		//捕获标志位清零					
				}
				else //发生捕获时间但不是下降沿，第一次捕获到上升沿，记录此时的定时器计数值
				{
						TIM2CH3_CAPTURE_UPVAL = TIM_GetCapture3(TIM2);		//获取上升沿数据
						TIM_OC3PolarityConfig(TIM2, TIM_ICPolarity_Falling);//设置为下降沿捕获
						TIM2CH3_CAPTURE_STA |= 0X8000;		//标记已捕获到上升沿
				}
		}
		//通道4
		if (TIM_GetITStatus(TIM2, TIM_IT_CC4) != RESET) 		//捕获4发生捕获事件
		{
				if (TIM2CH4_CAPTURE_STA & 0X8000)		//捕获到一个下降沿
				{
						TIM2CH4_CAPTURE_DOWNVAL = TIM_GetCapture4(TIM2);//记录下此时的定时器计数值
						//TIM_OC4PolarityConfig(TIM2, TIM_ICPolarity_Rising); //设置为上升沿捕获
						TIM2_CH4_Time = TIM2CH4_CAPTURE_DOWNVAL - TIM2CH4_CAPTURE_UPVAL+ 65536*(TIM2CH4_CAPTURE_STA&0X7FFF);		//得到总的高电平的时间
						TIM2CH4_CAPTURE_STA = 0;		//捕获标志位清零					
				}
				else //发生捕获时间但不是下降沿，第一次捕获到上升沿，记录此时的定时器计数值
				{
						TIM2CH4_CAPTURE_UPVAL = TIM_GetCapture4(TIM2);		//获取上升沿数据
						//TIM_OC4PolarityConfig(TIM2, TIM_ICPolarity_Falling);//设置为下降沿捕获
						TIM2CH4_CAPTURE_STA |= 0X8000;		//标记已捕获到上升沿
				}
		}
    TIM_ClearITPendingBit(TIM2, TIM_IT_CC1|TIM_IT_CC2|TIM_IT_CC3|TIM_IT_CC4|TIM_IT_Update); 		//清除中断标志位		
} 
#endif

#if TIMx_OutputCompare_Init_Test==1  //3输出比较 
void TIM1_CC_IRQHandler(void)
{
		u16 capture;
		if (TIM_GetITStatus(TIM1, TIM_IT_CC1) != RESET)
		{
			TIM_ClearITPendingBit(TIM1,TIM_IT_CC1);
			//初始化设置冻结模式可以用来用下面这句任意引脚产生pwm TIM_OCMode_Timing	   TIM输出比较时间模式	 冻结，输出比较不起作用
			//GPIO_WriteBit(GPIOC,GPIO_Pin_6,(BitAction)(1-GPIO_ReadOutputDataBit(GPIOC,GPIO_Pin_6)));
			TIM1_CH1_Flag=!TIM1_CH1_Flag;
			if(TIM1_CH1_Flag==1)
			{
					capture = TIM_GetCapture1(TIM1);
					TIM_SetCompare1(TIM1, capture+5); //高电平500ms
			}	
			else
			{
				  capture= TIM_GetCapture1(TIM1);
					TIM_SetCompare1(TIM1, capture+300); 
			}	
			
		}
		if (TIM_GetITStatus(TIM1, TIM_IT_CC4) != RESET)
		{
			TIM_ClearITPendingBit(TIM1,TIM_IT_CC4);
			//初始化设置冻结模式可以用来用下面这句任意引脚产生pwm TIM_OCMode_Timing	   TIM输出比较时间模式	 冻结，输出比较不起作用
			//GPIO_WriteBit(GPIOC,GPIO_Pin_7,(BitAction)(1-GPIO_ReadOutputDataBit(GPIOC,GPIO_Pin_7)));
			TIM1_CH4_Flag=!TIM1_CH4_Flag;
			if(TIM1_CH4_Flag==1)
			{
					capture = TIM_GetCapture4(TIM1);
					TIM_SetCompare4(TIM1, capture + 90);  
			}	
			else
			{
					capture = TIM_GetCapture4(TIM1);
					TIM_SetCompare4(TIM1, capture + 500);  
			}	           
		}
}
void TIM2_IRQHandler(void)
{
		 u16 capture;
		if (TIM_GetITStatus(TIM2, TIM_IT_CC1) != RESET)
		{
			TIM_ClearITPendingBit(TIM2,TIM_IT_CC1);
			//初始化设置冻结模式可以用下面这句来用任意引脚产生pwm TIM_OCMode_Timing	   TIM输出比较时间模式	 冻结，输出比较不起作用
			//GPIO_WriteBit(GPIOC,GPIO_Pin_1,(BitAction)(1-GPIO_ReadOutputDataBit(GPIOC,GPIO_Pin_1)));
			TIM2_CH1_Flag=!TIM2_CH1_Flag;
			if(TIM2_CH1_Flag==1)
			{
					capture = TIM_GetCapture1(TIM2);
					TIM_SetCompare1(TIM2, capture+5); 
			}	
			else
			{
				  capture= TIM_GetCapture1(TIM2);
					TIM_SetCompare1(TIM2, capture+300); 
			}	
			
		}
		if (TIM_GetITStatus(TIM2, TIM_IT_CC2) != RESET)
		{
			TIM_ClearITPendingBit(TIM2,TIM_IT_CC2);
			//初始化设置冻结模式可以用下面这句来用任意引脚产生pwm TIM_OCMode_Timing	   TIM输出比较时间模式	 冻结，输出比较不起作用
			//GPIO_WriteBit(GPIOC,GPIO_Pin_2,(BitAction)(1-GPIO_ReadOutputDataBit(GPIOC,GPIO_Pin_2)));
			TIM2_CH2_Flag=!TIM2_CH2_Flag;
			if(TIM2_CH2_Flag==1)
			{
					capture = TIM_GetCapture2(TIM2);
					TIM_SetCompare2(TIM2, capture + 80);  
			}	
			else
			{
					capture = TIM_GetCapture2(TIM2);
					TIM_SetCompare2(TIM2, capture + 100);  
			}	      
		}
		if (TIM_GetITStatus(TIM2, TIM_IT_CC3) != RESET)
		{
			TIM_ClearITPendingBit(TIM2,TIM_IT_CC3);
			//初始化设置冻结模式可以用下面这句来用任意引脚产生pwm TIM_OCMode_Timing	   TIM输出比较时间模式	 冻结，输出比较不起作用
			//GPIO_WriteBit(GPIOC,GPIO_Pin_3,(BitAction)(1-GPIO_ReadOutputDataBit(GPIOC,GPIO_Pin_3)));
			TIM2_CH3_Flag=!TIM2_CH3_Flag;
			if(TIM2_CH3_Flag==1)
			{
					capture = TIM_GetCapture3(TIM2);
					TIM_SetCompare3(TIM2, capture + 20);  
			}	
			else
			{
					capture = TIM_GetCapture3(TIM2);
					TIM_SetCompare3(TIM2, capture + 400);  
			}	           
		}
		if (TIM_GetITStatus(TIM2, TIM_IT_CC4) != RESET)
		{
			TIM_ClearITPendingBit(TIM2,TIM_IT_CC4);
			//初始化设置冻结模式可以用下面这句来用任意引脚产生pwm TIM_OCMode_Timing	   TIM输出比较时间模式	 冻结，输出比较不起作用
			//GPIO_WriteBit(GPIOC,GPIO_Pin_4,(BitAction)(1-GPIO_ReadOutputDataBit(GPIOC,GPIO_Pin_4)));
			TIM2_CH4_Flag=!TIM2_CH4_Flag;
			if(TIM2_CH4_Flag==1)
			{
					capture = TIM_GetCapture4(TIM2);
					TIM_SetCompare4(TIM2, capture + 9);  
			}	
			else
			{
					capture = TIM_GetCapture4(TIM2);
					TIM_SetCompare4(TIM2, capture + 500);  
			}	           
		}
}
#endif


*/




