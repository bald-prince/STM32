#include "timer.h"
#include "led.h"
#include "usart.h"	

#include "yinpin.h"   	 

//通用定时器3中断初始化
//这里时钟选择为APB1的2倍，而APB1为36M
//arr：自动重装值。
//psc：时钟预分频数
//这里使用的是定时器3!
u16 wavecount=0;
extern u8 num;
extern u8 i;
extern u8 j;
extern u8 k;
	
	
void TIM3_Int_Init(u16 arr,u16 psc)
{
  TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	NVIC_InitTypeDef NVIC_InitStructure;

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE); //时钟使能
	
	//定时器TIM3初始化
	TIM_TimeBaseStructure.TIM_Period = arr; //设置在下一个更新事件装入活动的自动重装载寄存器周期的值	
	TIM_TimeBaseStructure.TIM_Prescaler =psc; //设置用来作为TIMx时钟频率除数的预分频值
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1; //设置时钟分割:TDTS = Tck_tim
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIM向上计数模式
	TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure); //根据指定的参数初始化TIMx的时间基数单位
 
	TIM_ITConfig(TIM3,TIM_IT_Update,ENABLE ); //使能指定的TIM3中断,允许更新中断

	//中断优先级NVIC设置
	NVIC_InitStructure.NVIC_IRQChannel = TIM3_IRQn;  //TIM3中断
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;  //先占优先级0级
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;  //从优先级3级
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; //IRQ通道被使能
	NVIC_Init(&NVIC_InitStructure);  //初始化NVIC寄存器


	TIM_Cmd(TIM3, ENABLE);  //使能TIMx					 
}
//定时器3中断服务程序
void TIM3_IRQHandler(void)   //TIM3中断
{ 
	if (TIM_GetITStatus(TIM3, TIM_IT_Update) != RESET)  //检查TIM3更新中断发生与否
	{
		VoicePlayFunc();
	}
		TIM_ClearITPendingBit(TIM3, TIM_IT_Update  );  //清除TIMx更新中断标志 	
}

void VoicePlayFunc(void)
{
	uint16_t tmpCap=0;
	if(num==1){
		if( wavecount < SOUND_LENGTH )//根据对应音频代码长度定义此数
		{
			i=1;
			tmpCap = DATA[wavecount];
			wavecount++;
			/* Set DAC Channel1 DHR register */
			DAC_SetChannel1Data(DAC_Align_8b_R,tmpCap);                        
		}
		else
		{
			// 完成传输，关闭中断
			i=0;
			wavecount = 0;
			TIM_ITConfig(TIM3, TIM_IT_Update, DISABLE);
			TIM_Cmd(TIM3, DISABLE);
			 // 需要关闭DAC，不然在没有声音的时候会有杂音
			DAC_Cmd(DAC_Channel_1, DISABLE);
		}
	}
	else if(num==2){
		if( wavecount < SOUND_LENGTH_2)
		{
			j=1;
			tmpCap = DATA2[wavecount];
			wavecount++;
			/* Set DAC Channel1 DHR register */
			DAC_SetChannel1Data(DAC_Align_8b_R,tmpCap);                        
		}
		else
		{
			// 完成传输，关闭中断
			j=0;
			wavecount = 0;
			TIM_ITConfig(TIM3, TIM_IT_Update, DISABLE);
			TIM_Cmd(TIM3, DISABLE);
			// 需要关闭DAC，不然在没有声音的时候会有杂音
			DAC_Cmd(DAC_Channel_1, DISABLE);
		}
	}
	else if(num==3){
		if( wavecount < SOUND_LENGTH_2 )
		{
			k=1;
			tmpCap = DATA2[wavecount];
			wavecount++;
			/* Set DAC Channel1 DHR register */
			DAC_SetChannel1Data(DAC_Align_8b_R,tmpCap);                        
		}
		else
		{
			// 完成传输，关闭中断
			k=0;
			wavecount = 0;
			TIM_ITConfig(TIM3, TIM_IT_Update, DISABLE);
			TIM_Cmd(TIM3, DISABLE);
			// 需要关闭DAC，不然在没有声音的时候会有杂音
			DAC_Cmd(DAC_Channel_1, DISABLE);
		}
	}
	else	
	{
		// 完成传输，关闭中断
		wavecount = 0;
		TIM_ITConfig(TIM3, TIM_IT_Update, DISABLE);
		TIM_Cmd(TIM3, DISABLE);
		 // 需要关闭DAC，不然在没有声音的时候会有杂音
		DAC_Cmd(DAC_Channel_1, DISABLE);
	}
}











