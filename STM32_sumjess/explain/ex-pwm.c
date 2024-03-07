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



///////////////////////未映射的内容与下列类似，直接看pwm.c就好////////////////////
/////////////////////////////////映射的内容/////////////////////////////////////
PWM输出配置步骤：
***********************************************************
所有步骤都在void TIM3_PWM_Init(u16 arr,u16 psc)中
//arr：自动重装值
//psc：时钟预分频数
//PWM输出初始化
************************************************************
①使能定时器3和相关IO口时钟。使能GPIO外设时钟使能
         使能定时器3时钟：RCC_APB1PeriphClockCmd();
         使能GPIOB时钟：RCC_APB2PeriphClockCmd();如下
				 **********************************************************
					RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);	//使能定时器3时钟
					RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB  | RCC_APB2Periph_AFIO, ENABLE);  //使能GPIO外设和AFIO复用功能模块时钟
				 *********************************************************
②初始化IO口为复用功能输出。函数：GPIO_Init();
*********************************************************************
       注意： GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;   
*********************************************************************
③这里我们是要把PB5用作定时器的PWM输出引脚，所以要重映射配置，所以需要开启AFIO时钟。同时设置重映射。如下
        RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);
        GPIO_PinRemapConfig(GPIO_PartialRemap_TIM3, ENABLE); ****根据该文件下的解释选用是什么类型的映射***
				
	  //设置该引脚为复用输出功能,输出TIM3 CH2的PWM脉冲波形	GPIOB.5
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_5; //TIM_CH2
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF_PP;  //复用推挽输出
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIO_InitStruct);//初始化GPIO
④初始化定时器：ARR,PSC等：TIM_TimeBaseInit();
*****************************************************************************************************
	TIM_TimeBaseStructure.TIM_Period = arr; //设置在下一个更新事件装入活动的自动重装载寄存器周期的值	 计数到5000为500ms
	TIM_TimeBaseStructure.TIM_Prescaler =psc; //设置用来作为TIMx时钟频率除数的预分频值  10Khz的计数频率  
	TIM_TimeBaseStructure.TIM_ClockDivision =TIM_CKD_DIV1; //设置时钟分割:TDTS = Tck_tim*********这里任意选
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIM向上计数模式
	TIM_TimeBaseInit(TIM1, &TIM_TimeBaseStructure); //根据TIM_TimeBaseInitStruct中指定的参数初始化TIMx的时间基数单位
******************************************************************************************************
⑤初始化输出比较参数:TIM_OC2Init();通道2的初始化程序。如下
*****************************************************************************************
	//初始化TIM3 Channel2 PWM模式	 
	TIM_OCInitStruct.TIM_OCMode = TIM_OCMode_PWM2; //选择定时器模式:TIM脉冲宽度调制模式2(板载呼吸灯)模式1（外插呼吸灯）
 	TIM_OCInitStruct.TIM_OutputState = TIM_OutputState_Enable; //比较输出使能
	TIM_OCInitStruct.TIM_OCPolarity = TIM_OCPolarity_High; //输出极性:TIM输出比较极性高
	TIM_OC2Init(TIM3, &TIM_OCInitStruct);  //根据T指定的参数初始化外设TIM3 OC2
******************************************************************************************
⑥使能预装载寄存器： TIM_OC2PreloadConfig(TIM3, TIM_OCPreload_Enable); 如下
*******************************************************************************************
****TIM_OC2PreloadConfig(TIM3, TIM_OCPreload_Enable);  //使能TIM3在CCR2上的预装载寄存器****当通道不是2是需要更改
*****************************************************************************************
⑦使能定时器。TIM_Cmd();如下
*******************************************************************************************
	TIM_Cmd(TIM3, ENABLE);  //使能TIM3
*******************************************************************************************
——————————————————————————————————————————————————
⑧不断改变比较值CCRx，达到不同的占空比效果:TIM_SetCompare2();如下《￥￥在主函数中写￥￥￥》

		TIM_SetCompare1(TIM1,led0pwmval);	//通改变led0pwmval改变占空比

//TIM_SetCompare1这个函数名中的数字1代表的是TIMx的通道1,TIMx中的x可以取1到17且除了6、7的数，
函数TIM_SetCompare1(TIM_TypeDef* TIMx, uint16_t Compare1)的调用时，
前一项参数为TIMx,TIMx中的x可以取1到17且除了6、7的数,Compare1是用于与TIMx比较的数，
相当于用TIMx的一个周期的时间减去这个Compare1，使得TIMx的周期从后面开始的Compare1的时间为TIMx的前部分时间的反向。
即若前部分时间为高电平，则Compare1段所在时间为低电平。若前部分时间为低电平，则Compare1段所在时间为高电平


u8 dir=1;	

TIM1_PWM_Init(899,0);//不分频。PWM频率=72000/(899+1)=80Khz 


#include "led.h"
#include "delay.h"
#include "sys.h"
#include "sumjess_pwm.h"


 int main(void)
 {	
	u16 led0pwmval=0;    
	u8 dir=1;	
	delay_init();	    	 //延时函数初始化	  
	LED_Init();		  	//初始化与LED连接的硬件接口
	TIM1_PWM_Init(899,0);//不分频。PWM频率=72000/(899+1)=80Khz 
   	while(1)
	{
 		delay_ms(10);	 
		if(dir)led0pwmval++;
		else led0pwmval--;	 
 		if(led0pwmval>300)dir=0;
		if(led0pwmval==0)dir=1;	   					 
		TIM_SetCompare1(TIM1,led0pwmval);	   
	} 
}
  
#include "delay.h"
#include "sys.h"
#include "sumjess_pwm.h"
 int main(void)
 {	  
	 int b = 0;
	 delay_init();	
   speed_Configuration();

	while(1) 
	{		
		for(b=0;b<100;b+=10){
		TIM_SetCompare1(TIM3,b);   delay_ms(100);}
		for(b=100;b>1;b-=10){
		TIM_SetCompare1(TIM3,b);   delay_ms(100);}
    TIM_SetCompare1(TIM3,0);  delay_ms(2000);
		for(b=0;b<100;b+=10){
		TIM_SetCompare2(TIM3,b);   delay_ms(100);}
		for(b=100;b>1;b-=10){
		TIM_SetCompare2(TIM3,b);   delay_ms(100);}		
		TIM_SetCompare2(TIM3,0);  delay_ms(2000);
		for(b=0;b<100;b+=10){
		TIM_SetCompare3(TIM3,b);   delay_ms(100);}
		for(b=100;b>1;b-=10){
		TIM_SetCompare3(TIM3,b);   delay_ms(100);}
    TIM_SetCompare3(TIM3,0);  delay_ms(2000);
		for(b=0;b<100;b+=10){
		TIM_SetCompare4(TIM3,b);   delay_ms(100);}
		for(b=100;b>1;b-=10){
		TIM_SetCompare4(TIM3,b);   delay_ms(100);}
    TIM_SetCompare4(TIM3,0);  delay_ms(2000);		
	}
}
*/




