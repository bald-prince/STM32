/*

*******************************************************************************
================================================================================
��ƽ    ̨��stm32f103zet6_sumjessƽ̨
����    д��sumjess
��E-mail  ��1371129880@qq.com
������汾��V2.0
�������¡�2018��01��21��
�������Ϣ�ο����е�ַ��
����    վ��http://www.openedv.com/
           http://www.stmcu.org/
					 http://www.firebbs.cn/forum.php
---------------------------------------------------------------------------------
��dev.env.��MDK5.14�����ϰ汾
��Target  ��stm32f103zet6
��һ���޶���2017/11/09
�ڶ����޶���2018/01/21
---------------------------------------------------------------------------------
û�������Ĵ��룬ֻ�в��ϵķ��ף����һ��Ŭ����
����õ���������㣬��ӭ��ҷ���bug��
================================================================================
********************************************************************************



#include "timer.h"
#include "includes.h"


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#if TIMx_Time_Init_Test==1  //1��ͨ��ʱ

//�߼���ʱ��TIM1,8  ͨ�ö�ʱ��TIM2,3,4,5   ������ʱ��TIM6,7
//������TIM1 TIM2 TIM6ģ����֤
void TIM1_Time_Init(u16 arr,u16 psc)
{
		//TIM1_Init(4999,7199);
	  //����Ƶ��=Tclk/7200=72000000/7200=10000Hz  ��һ������ʱ1/10000s  ����5000��=5000/10000s=500ms
	  //Tout(���ʱ��)=(arr+1)*(psc+1)/Tclk =5000*7200/72000000s=500ms
		TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
		NVIC_InitTypeDef NVIC_InitStructure;

		RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1, ENABLE); 
		
		TIM_TimeBaseStructInit(&TIM_TimeBaseStructure);//����ȱʡֵ,��һ����ü���
		TIM_TimeBaseStructure.TIM_Period = arr; //�Զ���װ�ؼĴ������ڵ�ֵ�����ֵ	
		TIM_TimeBaseStructure.TIM_Prescaler =psc; //ʱ��Ƶ��Ԥ��Ƶֵ
		TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1; //����ʱ�ӷָ�:���벶��ģʽ�����˲�
		TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIM���ϼ���ģʽ
	  TIM_TimeBaseStructure.TIM_RepetitionCounter=0;//�����ظ�������������Ƕ��ٴ����������жϣ�һ��Ϊ0��ֻ�и߼���ʱ��������
		TIM_TimeBaseInit(TIM1, &TIM_TimeBaseStructure); 

		TIM_ITConfig(TIM1,TIM_IT_Update,ENABLE ); //��������ж�

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
	  //����Ƶ��=Tclk/7200=72000000/7200=10000Hz  ��һ������ʱ1/10000s  ����5000��=5000/10000s=500ms
	  //Tout(���ʱ��)=(arr+1)*(psc+1)/Tclk =5000*7200/72000000s=500ms
		TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
		NVIC_InitTypeDef NVIC_InitStructure;

		RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE); 
		
		TIM_TimeBaseStructInit(&TIM_TimeBaseStructure);//����ȱʡֵ,��һ����ü���
		TIM_TimeBaseStructure.TIM_Period = arr; //�Զ���װ�ؼĴ������ڵ�ֵ�����ֵ	
		TIM_TimeBaseStructure.TIM_Prescaler =psc; //ʱ��Ƶ��Ԥ��Ƶֵ
		TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1; //����ʱ�ӷָ�:���벶��ģʽ�����˲�
		TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIM���ϼ���ģʽ
		TIM_TimeBaseStructure.TIM_RepetitionCounter=0;//�����ظ�������������Ƕ��ٴ����������жϣ�һ��Ϊ0��ֻ�и߼���ʱ��������
		TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure); 

		TIM_ITConfig(TIM2,TIM_IT_Update,ENABLE ); //��������ж�

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
	  //����Ƶ��=Tclk/7200=72000000/7200=10000Hz  ��һ������ʱ1/10000s  ����5000��=5000/10000s=500ms
	  //Tout(���ʱ��)=(arr+1)*(psc+1)/Tclk =5000*7200/72000000s=500ms
		TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
		NVIC_InitTypeDef NVIC_InitStructure;

		RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM6, ENABLE); 
		
		TIM_TimeBaseStructInit(&TIM_TimeBaseStructure);//����ȱʡֵ,��һ����ü���
		TIM_TimeBaseStructure.TIM_Period = arr; //�Զ���װ�ؼĴ������ڵ�ֵ�����ֵ	
		TIM_TimeBaseStructure.TIM_Prescaler =psc; //ʱ��Ƶ��Ԥ��Ƶֵ
		TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1; //����ʱ�ӷָ�:���벶��ģʽ�����˲�
		TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIM���ϼ���ģʽ
		TIM_TimeBaseStructure.TIM_RepetitionCounter=0;//�����ظ�������������Ƕ��ٴ����������жϣ�һ��Ϊ0��ֻ�и߼���ʱ��������
		TIM_TimeBaseInit(TIM6, &TIM_TimeBaseStructure); 

		TIM_ITConfig(TIM6,TIM_IT_Update,ENABLE ); //��������ж�

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
#if TIMx_InputCapture_Init_Test==1  //2���벶��

u16 TIM1CH1_CAPTURE_STA = 0;	//ͨ��1���벶���־��15λ�������־����15λ�������־		
u16 TIM1CH1_CAPTURE_UPVAL,TIM1CH1_CAPTURE_DOWNVAL;
//u16 TIM1CH2_CAPTURE_STA = 0;	//ͨ��1���벶���־��15λ�������־����15λ�������־			
//u16 TIM1CH2_CAPTURE_UPVAL,TIM1CH2_CAPTURE_DOWNVAL;
//u16 TIM1CH3_CAPTURE_STA = 0;	//ͨ��1���벶���־��15λ�������־����15λ�������־			
//u16 TIM1CH3_CAPTURE_UPVAL,TIM1CH3_CAPTURE_DOWNVAL;
u16 TIM1CH4_CAPTURE_STA = 0;	//ͨ��1���벶���־��15λ�������־����15λ�������־			
u16 TIM1CH4_CAPTURE_UPVAL,TIM1CH4_CAPTURE_DOWNVAL;

u32 TIM1_CH1_Time;	//CH1��������1�ĸߵ�ƽʱ�䣬���ڼ���ռ�ձ�
//u32 TIM1_CH2_Time;	//CH2��������1�����������ؼ��ʱ�䣬���ڼ�������
//u32 TIM1_CH3_Time;	//CH3��������2�ĸߵ�ƽʱ�䣬���ڼ���ռ�ձ�
u32 TIM1_CH4_Time;	//CH4��������2�����������ؼ��ʱ�䣬���ڼ�������
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


	TIM_TimeBaseStructInit(&TIM_TimeBaseStructure);//����ȱʡֵ,��һ����ü���
	TIM_TimeBaseStructure.TIM_Period = arr; //�Զ���װ�ؼĴ������ڵ�ֵ�����ֵ	
	TIM_TimeBaseStructure.TIM_Prescaler =psc; //ʱ��Ƶ��Ԥ��Ƶֵ
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1; //����ʱ�ӷָ�:���벶��ģʽ�����˲�
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIM���ϼ���ģʽ
	TIM_TimeBaseStructure.TIM_RepetitionCounter=0;//�����ظ�������������Ƕ��ٴ����������жϣ�һ��Ϊ0��ֻ�и߼���ʱ��������
	TIM_TimeBaseInit(TIM1, &TIM_TimeBaseStructure); 


	TIM_ICStructInit(&TIM_ICInitStructure);//����ȱʡֵ,��һ����ü���
	TIM_ICInitStructure.TIM_ICPolarity = TIM_ICPolarity_Rising;	//�����ز���
	TIM_ICInitStructure.TIM_ICSelection = TIM_ICSelection_DirectTI; //ӳ�䵽TI1��
	TIM_ICInitStructure.TIM_ICPrescaler = TIM_ICPSC_DIV1;	  //���������Ƶ,����Ƶ 
	TIM_ICInitStructure.TIM_ICFilter = 0x00;	  //IC1F=0000 ���������˲��� 0���˲�
	
	//����ͨ��1
	TIM_ICInitStructure.TIM_Channel = TIM_Channel_1; //IC1ӳ�䵽TI1�ϣ����ľ䲻�ܺϲ�
	TIM_ICInit(TIM1, &TIM_ICInitStructure);
	

	//����ͨ��4
	TIM_ICInitStructure.TIM_Channel = TIM_Channel_4; //IC4ӳ�䵽TI4�ϣ����ľ䲻�ܺϲ�
	TIM_ICInit(TIM1, &TIM_ICInitStructure);
	
	//�жϷ����ʼ��
	NVIC_InitStructure.NVIC_IRQChannel = TIM1_CC_IRQn;  
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0; 
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0; 
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; 
	NVIC_Init(&NVIC_InitStructure);   

	TIM_ITConfig(TIM1,TIM_IT_Update|TIM_IT_CC1|TIM_IT_CC4,ENABLE);   //��������жϣ�����CC1IE,CC2IE,CC3IE,CC4IE�����ж�	
	TIM_CtrlPWMOutputs(TIM1,ENABLE);	//�����ʹ��
	TIM_Cmd(TIM1, ENABLE); 		//ʹ�ܶ�ʱ��4
}



u16 TIM2CH1_CAPTURE_STA = 0;	//ͨ��1���벶���־��15λ�������־����15λ�������־		
u16 TIM2CH1_CAPTURE_UPVAL,TIM2CH1_CAPTURE_DOWNVAL;
u16 TIM2CH2_CAPTURE_STA = 0;	//ͨ��1���벶���־��15λ�������־����15λ�������־			
u16 TIM2CH2_CAPTURE_UPVAL,TIM2CH2_CAPTURE_DOWNVAL;
u16 TIM2CH3_CAPTURE_STA = 0;	//ͨ��1���벶���־��15λ�������־����15λ�������־			
u16 TIM2CH3_CAPTURE_UPVAL,TIM2CH3_CAPTURE_DOWNVAL;
u16 TIM2CH4_CAPTURE_STA = 0;	//ͨ��1���벶���־��15λ�������־����15λ�������־			
u16 TIM2CH4_CAPTURE_UPVAL,TIM2CH4_CAPTURE_DOWNVAL;

u32 TIM2_CH1_Time;	//CH1��������1�ĸߵ�ƽʱ�䣬���ڼ���ռ�ձ�
u32 TIM2_CH2_Time;	//CH2��������1�����������ؼ��ʱ�䣬���ڼ�������
u32 TIM2_CH3_Time;	//CH3��������2�ĸߵ�ƽʱ�䣬���ڼ���ռ�ձ�
u32 TIM2_CH4_Time;	//CH4��������2�����������ؼ��ʱ�䣬���ڼ�������
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

	TIM_TimeBaseStructInit(&TIM_TimeBaseStructure);//����ȱʡֵ,��һ����ü���
	TIM_TimeBaseStructure.TIM_Period = arr; //�Զ���װ�ؼĴ������ڵ�ֵ�����ֵ	
	TIM_TimeBaseStructure.TIM_Prescaler =psc; //ʱ��Ƶ��Ԥ��Ƶֵ
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1; //����ʱ�ӷָ�:���벶��ģʽ�����˲�
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIM���ϼ���ģʽ
	TIM_TimeBaseStructure.TIM_RepetitionCounter=0;//�����ظ�������������Ƕ��ٴ����������жϣ�һ��Ϊ0��ֻ�и߼���ʱ��������
	TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure); 


	TIM_ICStructInit(&TIM_ICInitStructure);//����ȱʡֵ,��һ����ü���
	TIM_ICInitStructure.TIM_ICPolarity = TIM_ICPolarity_Rising;	//�����ز���
	TIM_ICInitStructure.TIM_ICSelection = TIM_ICSelection_DirectTI; //ӳ�䵽TI1��
	TIM_ICInitStructure.TIM_ICPrescaler = TIM_ICPSC_DIV1;	  //���������Ƶ,����Ƶ 
	TIM_ICInitStructure.TIM_ICFilter = 0x00;	  //IC1F=0000 ���������˲��� 0���˲�
	
	//����ͨ��1
	TIM_ICInitStructure.TIM_Channel = TIM_Channel_1; //IC1ӳ�䵽TI1�ϣ����ľ䲻�ܺϲ�
	TIM_ICInit(TIM2, &TIM_ICInitStructure);
	
	//����ͨ��2
	TIM_ICInitStructure.TIM_Channel = TIM_Channel_2; //IC2ӳ�䵽TI2�ϣ����ľ䲻�ܺϲ�
	TIM_ICInit(TIM2, &TIM_ICInitStructure);
	
	//����ͨ��3
	TIM_ICInitStructure.TIM_Channel = TIM_Channel_3; //IC3ӳ�䵽TI3�ϣ����ľ䲻�ܺϲ�
	TIM_ICInit(TIM2, &TIM_ICInitStructure);

	//����ͨ��4
	TIM_ICInitStructure.TIM_Channel = TIM_Channel_4; //IC4ӳ�䵽TI4�ϣ����ľ䲻�ܺϲ�
	TIM_ICInit(TIM2, &TIM_ICInitStructure);
	
	//�жϷ����ʼ��
	NVIC_InitStructure.NVIC_IRQChannel = TIM2_IRQn;  
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0; 
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0; 
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; 
	NVIC_Init(&NVIC_InitStructure);   

	TIM_ITConfig(TIM2,TIM_IT_Update|TIM_IT_CC1|TIM_IT_CC2|TIM_IT_CC3|TIM_IT_CC4,ENABLE);   //��������жϣ�����CC1IE,CC2IE,CC3IE,CC4IE�����ж�	
	TIM_Cmd(TIM2, ENABLE); 		//ʹ�ܶ�ʱ��4
}
#endif
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#if TIMx_OutputCompare_Init_Test==1  //3����Ƚ� 
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
	
		TIM_TimeBaseStructInit(&TIM_TimeBaseStructure);//����ȱʡֵ,��һ����ü���
		TIM_TimeBaseStructure.TIM_Period = arr; //�Զ���װ�ؼĴ������ڵ�ֵ�����ֵ
		TIM_TimeBaseStructure.TIM_Prescaler =psc; //ʱ��Ƶ��Ԥ��Ƶֵ
	  TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1; //����ʱ�ӷָ�:���벶��ģʽ�����˲�
		TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIM���ϼ���ģʽ
		TIM_TimeBaseStructure.TIM_RepetitionCounter=0;//�����ظ�������������Ƕ��ٴ����������жϣ�һ��Ϊ0��ֻ�и߼���ʱ��������
		TIM_TimeBaseInit(TIM1, &TIM_TimeBaseStructure); 
	
		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8|GPIO_Pin_11; 
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP; 
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
		GPIO_Init(GPIOA, &GPIO_InitStructure);

// TIM_OCMode	           ����������	           ���� 
// TIM_OCMode_Timing	   TIM����Ƚ�ʱ��ģʽ	 ���ᣬ����Ƚϲ�������
// TIM_OOCMode_Active	   TIM����Ƚ�����ģʽ	 ���ȽϷ���ʱ��ǿ������ߵ�ƽ
// TIM_OCMode_Inactiive	 TIM����ȽϷ�����ģʽ ���ȽϷ���ʱ��ǿ������͵�ƽ
// TIM_OCMode_Toggle	   TIM����Ƚϴ���ģʽ	 ���ȽϷ���ʱ�������ת
// TIM_OCMode_PWM1	     TIM�����ȵ���ģʽ1	 PWM1
// TIM_OCMode_PWM2	     TIM�����ȵ���ģʽ2	 PWM2

	  TIM_OCStructInit(&TIM_OCInitStructure);//����ȱʡֵ,��һ����ü���
		TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_Toggle; //TIM����Ƚϴ���ģʽ	 ���ȽϷ���ʱ�������ת������ģʽ���Է�ת����io����pwm
		TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; //�Ƚ����ʹ��
		TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High; //�������:TIM����Ƚϼ��Ը�
	
    TIM_OCInitStructure.TIM_Pulse = 100; //���ô�װ�벶��ȽϼĴ���������ֵ
		TIM_OC1Init(TIM1, &TIM_OCInitStructure);           
		TIM_OC1PreloadConfig(TIM1, TIM_OCPreload_Disable);

    TIM_OCInitStructure.TIM_Pulse = 400;
		TIM_OC4Init(TIM1, &TIM_OCInitStructure);           
		TIM_OC4PreloadConfig(TIM1, TIM_OCPreload_Disable); 
		
	
		//�жϷ����ʼ��
	  NVIC_InitStructure.NVIC_IRQChannel = TIM1_CC_IRQn;  
	  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0; 
	  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0; 
	  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; 
	  NVIC_Init(&NVIC_InitStructure);   
  
    TIM_ITConfig(TIM1, TIM_IT_CC1|TIM_IT_CC2|TIM_IT_CC3|TIM_IT_CC4, ENABLE);
		TIM_CtrlPWMOutputs(TIM1,ENABLE);	//�����ʹ��
	  TIM_Cmd(TIM1,ENABLE); //������ʱ��3 TIM3_CR1[0]=1;
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
	
		TIM_TimeBaseStructInit(&TIM_TimeBaseStructure);//����ȱʡֵ,��һ����ü���
		TIM_TimeBaseStructure.TIM_Period = arr; //�Զ���װ�ؼĴ������ڵ�ֵ�����ֵ
		TIM_TimeBaseStructure.TIM_Prescaler =psc; //ʱ��Ƶ��Ԥ��Ƶֵ
	  TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1; //����ʱ�ӷָ�:���벶��ģʽ�����˲�
		TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIM���ϼ���ģʽ
		TIM_TimeBaseStructure.TIM_RepetitionCounter=0;//�����ظ�������������Ƕ��ٴ����������жϣ�һ��Ϊ0��ֻ�и߼���ʱ��������
		TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure); 
	
		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_2|GPIO_Pin_3; 
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP; 
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
		GPIO_Init(GPIOA, &GPIO_InitStructure);

// TIM_OCMode	           ����������	           ���� 
// TIM_OCMode_Timing	   TIM����Ƚ�ʱ��ģʽ	 ���ᣬ����Ƚϲ�������
// TIM_OOCMode_Active	   TIM����Ƚ�����ģʽ	 ���ȽϷ���ʱ��ǿ������ߵ�ƽ
// TIM_OCMode_Inactiive	 TIM����ȽϷ�����ģʽ ���ȽϷ���ʱ��ǿ������͵�ƽ
// TIM_OCMode_Toggle	   TIM����Ƚϴ���ģʽ	 ���ȽϷ���ʱ�������ת
// TIM_OCMode_PWM1	     TIM�����ȵ���ģʽ1	 PWM1
// TIM_OCMode_PWM2	     TIM�����ȵ���ģʽ2	 PWM2

	  TIM_OCStructInit(&TIM_OCInitStructure);//����ȱʡֵ,��һ����ü���
		TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_Toggle; //TIM����Ƚϴ���ģʽ	 ���ȽϷ���ʱ�������ת������ģʽ���Է�ת����io����pwm
		TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; //�Ƚ����ʹ��
		TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High; //�������:TIM����Ƚϼ��Ը�
	
    TIM_OCInitStructure.TIM_Pulse = 100; //���ô�װ�벶��ȽϼĴ���������ֵ
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
		
	
		//�жϷ����ʼ��
	NVIC_InitStructure.NVIC_IRQChannel = TIM2_IRQn;  
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0; 
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0; 
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; 
	NVIC_Init(&NVIC_InitStructure);   
  
    TIM_ITConfig(TIM2, TIM_IT_CC1|TIM_IT_CC2|TIM_IT_CC3|TIM_IT_CC4, ENABLE);
	  TIM_Cmd(TIM2,ENABLE); //������ʱ��3 TIM3_CR1[0]=1;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


#endif
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#if TIMx_Pwm_Init_Test==1  //4PWM 
void TIM1_Pwm_Init(u16 arr,u16 psc)//TIM1_Pwm_Init(7200,0);PWM����=(arr+1)*(psc+1)/Tclk=7200*1/72000000s=0.1ms
{  
	GPIO_InitTypeDef GPIO_InitStructure;
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	TIM_OCInitTypeDef  TIM_OCInitStructure;

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1, ENABLE); 
 	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA , ENABLE);  
	                                                                     	
	TIM_TimeBaseStructInit(&TIM_TimeBaseStructure);//����ȱʡֵ,��һ����ü���
	TIM_TimeBaseStructure.TIM_Period = arr; //�Զ���װ�ؼĴ������ڵ�ֵ�����ֵ
	TIM_TimeBaseStructure.TIM_Prescaler =psc; //ʱ��Ƶ��Ԥ��Ƶֵ
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1; //����ʱ�ӷָ�:���벶��ģʽ�����˲�
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIM���ϼ���ģʽ
	TIM_TimeBaseStructure.TIM_RepetitionCounter=0;//�����ظ�������������Ƕ��ٴ����������жϣ�һ��Ϊ0��ֻ�и߼���ʱ��������
	TIM_TimeBaseInit(TIM1, &TIM_TimeBaseStructure); 
	
	
   //���ø�����Ϊ�����������,���TIM1 CH1��PWM���岨��
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8|GPIO_Pin_11; 
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;  
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);

 	TIM_OCStructInit(&TIM_OCInitStructure);//����ȱʡֵ,��һ����ü���
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM2; //ѡ��ʱ��ģʽ:TIM�����ȵ���ģʽ2
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; //�Ƚ����ʹ��
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_Low; //�������:TIM����Ƚϼ��Ը�
	
	
	TIM_OC1Init(TIM1, &TIM_OCInitStructure);           
	TIM_OC1PreloadConfig(TIM1, TIM_OCPreload_Enable); 
	TIM_OC4Init(TIM1, &TIM_OCInitStructure);           
	TIM_OC4PreloadConfig(TIM1, TIM_OCPreload_Enable); 
	
  TIM_CtrlPWMOutputs(TIM1,ENABLE);	//�����ʹ��
	TIM_Cmd(TIM1, ENABLE);  //ʹ��TIM1
}

void TIM2_Pwm_Init(u16 arr,u16 psc)//TIM2_Pwm_Init(7200,0);PWM����=(arr+1)*(psc+1)/Tclk=7200*1/72000000s=0.1ms
{
		GPIO_InitTypeDef GPIO_InitStructure;
		TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
		TIM_OCInitTypeDef  TIM_OCInitStructure;

		RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_AFIO, ENABLE);  
	
		TIM_TimeBaseStructInit(&TIM_TimeBaseStructure);//����ȱʡֵ,��һ����ü���
		TIM_TimeBaseStructure.TIM_Period = arr; //�Զ���װ�ؼĴ������ڵ�ֵ�����ֵ
		TIM_TimeBaseStructure.TIM_Prescaler =psc; //ʱ��Ƶ��Ԥ��Ƶֵ
	  TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1; //����ʱ�ӷָ�:���벶��ģʽ�����˲�
		TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIM���ϼ���ģʽ
		TIM_TimeBaseStructure.TIM_RepetitionCounter=0;//�����ظ�������������Ƕ��ٴ����������жϣ�һ��Ϊ0��ֻ�и߼���ʱ��������
		TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure); 
	
		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_2|GPIO_Pin_3; 
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP; 
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
		GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	  TIM_OCStructInit(&TIM_OCInitStructure);//����ȱʡֵ,��һ����ü���
		TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1; //ѡ��ʱ��ģʽ:TIM�����ȵ���ģʽ2
		TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; //�Ƚ����ʹ��
		TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High; //�������:TIM����Ƚϼ��Ը�
		
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
//��ʾ����(���߼�������)��̽ͷ���ӵ�TIMxͨ��1��Ӧ�����ţ�
//Ȼ���öŰ��߽�TIMxͨ��2��Ӧ���������ӵ�GND�ӵ����ţ�Ȼ�������ڽ��Ű��߰ε���������ģ��һ��������
//��ʾ����(���߼�������)�Ͼͼ�⵽��ʱ������ʱʱ���TIMxͨ��1���һ���趨��ȵ�����

#if TIMx_OnePulseOutput_Init_Test==1  //5��������� 
//��⵽��������ʱʱ�� ����ʱ��ô�ÿ�ʼ��������壩= 1 / (72M/72/10000) = 10ms
//������                                         = 1 / (72M/72/(65535 - 10000)) = 55.535ms
void TIM1_OnePulseOutput_Init(u16 arr,u16 psc)
{
		GPIO_InitTypeDef GPIO_InitStructure;
		TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
		TIM_OCInitTypeDef  TIM_OCInitStructure;
	  TIM_ICInitTypeDef  TIM_ICInitStructure;
	  RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1, ENABLE); 
		//RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_AFIO, ENABLE);  
	
		TIM_TimeBaseStructInit(&TIM_TimeBaseStructure);//����ȱʡֵ,��һ����ü���
		TIM_TimeBaseStructure.TIM_Period = arr; //�Զ���װ�ؼĴ������ڵ�ֵ�����ֵ
		TIM_TimeBaseStructure.TIM_Prescaler =psc; //ʱ��Ƶ��Ԥ��Ƶֵ
	  TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1; //����ʱ�ӷָ�:���벶��ģʽ�����˲�
		TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIM���ϼ���ģʽ
		TIM_TimeBaseStructure.TIM_RepetitionCounter=0;//�����ظ�������������Ƕ��ٴ����������жϣ�һ��Ϊ0��ֻ�и߼���ʱ��������
		TIM_TimeBaseInit(TIM1, &TIM_TimeBaseStructure); 
	
		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8; 
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP; 
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
		GPIO_Init(GPIOA, &GPIO_InitStructure);


		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9; 
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING ; 
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
		GPIO_Init(GPIOA, &GPIO_InitStructure);
		     
				 
	  TIM_OCStructInit(&TIM_OCInitStructure);//����ȱʡֵ,��һ����ü���
		TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM2; //ѡ��ʱ��ģʽ:TIM�����ȵ���ģʽ2
		TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; //�Ƚ����ʹ��
		TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High; //�������:TIM����Ƚϼ��Ը�	

    TIM_OCInitStructure.TIM_Pulse = 10000; //���ô�װ�벶��ȽϼĴ���������ֵ
		TIM_OC1Init(TIM1, &TIM_OCInitStructure);           
		TIM_OC1PreloadConfig(TIM1, TIM_OCPreload_Disable);
    
		
	TIM_ICStructInit(&TIM_ICInitStructure);//����ȱʡֵ,��һ����ü���
	TIM_ICInitStructure.TIM_ICPolarity = TIM_ICPolarity_Rising;	//�����ز���
	TIM_ICInitStructure.TIM_ICSelection = TIM_ICSelection_DirectTI; //ӳ�䵽TI1��
	TIM_ICInitStructure.TIM_ICPrescaler = TIM_ICPSC_DIV1;	  //���������Ƶ,����Ƶ 
	TIM_ICInitStructure.TIM_ICFilter = 0x00;	  //IC1F=0000 ���������˲��� 0���˲�
	

	
	//����ͨ��2
	TIM_ICInitStructure.TIM_Channel = TIM_Channel_2; //IC2ӳ�䵽TI2�ϣ����ľ䲻�ܺϲ�
	TIM_ICInit(TIM1, &TIM_ICInitStructure);
	

	TIM_SelectOnePulseMode(TIM1, TIM_OPMode_Single);//ѡ��ʱ��Ϊ������ģʽ
	TIM_SelectInputTrigger(TIM1, TIM_TS_TI2FP2);//ѡ�񴥷�ԴΪIC2,û��TIM_TS_TI3FP3��TIM_TS_TI4FP4����3,4�������������壬�����п����̳����TIM_TS_TI3FP3��TIM_TS_TI4FP4�����Ŀ⺯����̫���鷳������
	TIM_SelectSlaveMode(TIM1, TIM_SlaveMode_Trigger);//ѡ��ʱ����ģʽΪ�����ش���

	TIM_CtrlPWMOutputs(TIM1,ENABLE);	//�����ʹ��
	TIM_Cmd(TIM1, ENABLE);  //ʹ��TIM1
}
//��⵽��������ʱʱ�� ����ʱ��ô�ÿ�ʼ��������壩= 1 / (72M/72/10000) = 10ms
//������                                         = 1 / (72M/72/(65535 - 10000)) = 55.535ms
void TIM2_OnePulseOutput_Init(u16 arr,u16 psc)
{
		GPIO_InitTypeDef GPIO_InitStructure;
		TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
		TIM_OCInitTypeDef  TIM_OCInitStructure;
	  TIM_ICInitTypeDef  TIM_ICInitStructure;
	
		RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_AFIO, ENABLE);  
	
		TIM_TimeBaseStructInit(&TIM_TimeBaseStructure);//����ȱʡֵ,��һ����ü���
		TIM_TimeBaseStructure.TIM_Period = arr; //�Զ���װ�ؼĴ������ڵ�ֵ�����ֵ
		TIM_TimeBaseStructure.TIM_Prescaler =psc; //ʱ��Ƶ��Ԥ��Ƶֵ
	  TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1; //����ʱ�ӷָ�:���벶��ģʽ�����˲�
		TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIM���ϼ���ģʽ
		TIM_TimeBaseStructure.TIM_RepetitionCounter=0;//�����ظ�������������Ƕ��ٴ����������жϣ�һ��Ϊ0��ֻ�и߼���ʱ��������
		TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure); 
	
		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0; 
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP; 
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
		GPIO_Init(GPIOA, &GPIO_InitStructure);


		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1; 
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING ; 
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
		GPIO_Init(GPIOA, &GPIO_InitStructure);
		     
				 
	  TIM_OCStructInit(&TIM_OCInitStructure);//����ȱʡֵ,��һ����ü���
		TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM2; //ѡ��ʱ��ģʽ:TIM�����ȵ���ģʽ2
		TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; //�Ƚ����ʹ��
		TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High; //�������:TIM����Ƚϼ��Ը�	

    TIM_OCInitStructure.TIM_Pulse = 10000; //���ô�װ�벶��ȽϼĴ���������ֵ
		TIM_OC1Init(TIM2, &TIM_OCInitStructure);           
		TIM_OC1PreloadConfig(TIM2, TIM_OCPreload_Disable);
    
		
	TIM_ICStructInit(&TIM_ICInitStructure);//����ȱʡֵ,��һ����ü���
	TIM_ICInitStructure.TIM_ICPolarity = TIM_ICPolarity_Rising;	//�����ز���
	TIM_ICInitStructure.TIM_ICSelection = TIM_ICSelection_DirectTI; //ӳ�䵽TI1��
	TIM_ICInitStructure.TIM_ICPrescaler = TIM_ICPSC_DIV1;	  //���������Ƶ,����Ƶ 
	TIM_ICInitStructure.TIM_ICFilter = 0x00;	  //IC1F=0000 ���������˲��� 0���˲�
	

	
	//����ͨ��2
	TIM_ICInitStructure.TIM_Channel = TIM_Channel_2; //IC2ӳ�䵽TI2�ϣ����ľ䲻�ܺϲ�
	TIM_ICInit(TIM2, &TIM_ICInitStructure);
	

	TIM_SelectOnePulseMode(TIM2, TIM_OPMode_Single);//ѡ��ʱ��Ϊ������ģʽ
	TIM_SelectInputTrigger(TIM2, TIM_TS_TI2FP2);//ѡ�񴥷�ԴΪIC2,û��TIM_TS_TI3FP3��TIM_TS_TI4FP4����3,4�������������壬�����п����̳����TIM_TS_TI3FP3��TIM_TS_TI4FP4�����Ŀ⺯����̫���鷳������
	TIM_SelectSlaveMode(TIM2, TIM_SlaveMode_Trigger);//ѡ��ʱ����ģʽΪ�����ش���
	TIM_Cmd(TIM2,ENABLE); //������ʱ��3 TIM3_CR1[0]=1;
}
#endif
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


#if TIMx_Time_Init_Test==1  //1��ͨ��ʱ
void TIM1_UP_IRQHandler(void)   
{
		if (TIM_GetITStatus(TIM1, TIM_IT_Update) != RESET)  //�������жϷ������
		{
				TIM_ClearITPendingBit(TIM1, TIM_IT_Update);  //���TIMx�����жϱ�־ 
			  printf("TIM1 1s\r\n");
		}
}

void TIM2_IRQHandler(void)   
{
		if (TIM_GetITStatus(TIM2, TIM_IT_Update) != RESET)  //�������жϷ������
		{
				TIM_ClearITPendingBit(TIM2, TIM_IT_Update);  //���TIMx�����жϱ�־ 
			  printf("TIM2 1s\r\n");
		}
}
void TIM6_IRQHandler(void)   
{
		if (TIM_GetITStatus(TIM6, TIM_IT_Update) != RESET)  //�������жϷ������
		{
				TIM_ClearITPendingBit(TIM6, TIM_IT_Update);  //���TIMx�����жϱ�־ 
			  printf("TIM6 1s\r\n");
		}
}
#endif

#if TIMx_InputCapture_Init_Test==1  //2���벶��
void TIM1_CC_IRQHandler(void)
{
		if (TIM_GetITStatus(TIM1, TIM_IT_Update) != RESET)
		{	
			  //ͨ��1					
				if(TIM1CH1_CAPTURE_STA&0X8000)//�Ѿ����񵽸ߵ�ƽ��
				{
						if((TIM1CH1_CAPTURE_STA&0X7FFF)==0X7FFF)//�ߵ�ƽ̫����
                TIM1CH1_CAPTURE_STA = 0;		//�����־λ����
						else 
								TIM1CH1_CAPTURE_STA++;
				}
			
			  //ͨ��4			
				if(TIM1CH4_CAPTURE_STA&0X8000)//�Ѿ����񵽸ߵ�ƽ��
				{
						if((TIM1CH4_CAPTURE_STA&0X7FFF)==0X7FFF)//�ߵ�ƽ̫����
                TIM1CH4_CAPTURE_STA = 0;		//�����־λ����
						else 
								TIM1CH4_CAPTURE_STA++;
				}	
		}
		
		//ͨ��1
		if (TIM_GetITStatus(TIM1, TIM_IT_CC1) != RESET) 		//����1���������¼�
		{
				
				if (TIM1CH1_CAPTURE_STA & 0X8000)		//����һ���½���
				{
						TIM1CH1_CAPTURE_DOWNVAL = TIM_GetCapture1(TIM1);//��¼�´�ʱ�Ķ�ʱ������ֵ
						TIM_OC1PolarityConfig(TIM1, TIM_ICPolarity_Rising); //����Ϊ�����ز���
						TIM1_CH1_Time = TIM1CH1_CAPTURE_DOWNVAL - TIM1CH1_CAPTURE_UPVAL+ 65536*(TIM1CH1_CAPTURE_STA&0X7FFF);		//�õ��ܵĸߵ�ƽ��ʱ��
						TIM1CH1_CAPTURE_STA = 0;		//�����־λ����					
				}
				else //��������ʱ�䵫�����½��أ���һ�β��������أ���¼��ʱ�Ķ�ʱ������ֵ
				{
						TIM1CH1_CAPTURE_UPVAL = TIM_GetCapture1(TIM1);		//��ȡ����������
						TIM_OC1PolarityConfig(TIM1, TIM_ICPolarity_Falling);//����Ϊ�½��ز���
						TIM1CH1_CAPTURE_STA |= 0X8000;		//����Ѳ���������
				}
		}
	
		//ͨ��4
		if (TIM_GetITStatus(TIM1, TIM_IT_CC4) != RESET) 		//����4���������¼�
		{
				if (TIM1CH4_CAPTURE_STA & 0X8000)		//����һ���½���
				{
						TIM1CH4_CAPTURE_DOWNVAL = TIM_GetCapture4(TIM1);//��¼�´�ʱ�Ķ�ʱ������ֵ
						//TIM_OC4PolarityConfig(TIM1, TIM_ICPolarity_Rising); //����Ϊ�����ز���
						TIM1_CH4_Time = TIM1CH4_CAPTURE_DOWNVAL - TIM1CH4_CAPTURE_UPVAL+ 65536*(TIM1CH4_CAPTURE_STA&0X7FFF);		//�õ��ܵĸߵ�ƽ��ʱ��
						TIM1CH4_CAPTURE_STA = 0;		//�����־λ����					
				}
				else //��������ʱ�䵫�����½��أ���һ�β��������أ���¼��ʱ�Ķ�ʱ������ֵ
				{
						TIM1CH4_CAPTURE_UPVAL = TIM_GetCapture4(TIM1);		//��ȡ����������
						//TIM_OC4PolarityConfig(TIM1, TIM_ICPolarity_Falling);//����Ϊ�½��ز���
						TIM1CH4_CAPTURE_STA |= 0X8000;		//����Ѳ���������
				}
		}
    TIM_ClearITPendingBit(TIM1, TIM_IT_CC1|TIM_IT_CC4|TIM_IT_Update); 		//����жϱ�־λ		
} 

void TIM2_IRQHandler(void)
{
		if (TIM_GetITStatus(TIM2, TIM_IT_Update) != RESET)
		{	
			  //ͨ��1					
				if(TIM2CH1_CAPTURE_STA&0X8000)//�Ѿ����񵽸ߵ�ƽ��
				{
						if((TIM2CH1_CAPTURE_STA&0X7FFF)==0X7FFF)//�ߵ�ƽ̫����
                TIM2CH1_CAPTURE_STA = 0;		//�����־λ����
						else 
								TIM2CH1_CAPTURE_STA++;
				}
			  //ͨ��2				
				if(TIM2CH2_CAPTURE_STA&0X8000)//�Ѿ����񵽸ߵ�ƽ��
				{
						if((TIM2CH2_CAPTURE_STA&0X7FFF)==0X7FFF)//�ߵ�ƽ̫����
                TIM2CH2_CAPTURE_STA = 0;		//�����־λ����
						else 
								TIM2CH2_CAPTURE_STA++;
				}	
			  //ͨ��3				
				if(TIM2CH3_CAPTURE_STA&0X8000)//�Ѿ����񵽸ߵ�ƽ��
				{
						if((TIM2CH3_CAPTURE_STA&0X7FFF)==0X7FFF)//�ߵ�ƽ̫����
                TIM2CH3_CAPTURE_STA = 0;		//�����־λ����
						else 
								TIM2CH3_CAPTURE_STA++;
				}
			  //ͨ��4			
				if(TIM2CH4_CAPTURE_STA&0X8000)//�Ѿ����񵽸ߵ�ƽ��
				{
						if((TIM2CH4_CAPTURE_STA&0X7FFF)==0X7FFF)//�ߵ�ƽ̫����
                TIM2CH4_CAPTURE_STA = 0;		//�����־λ����
						else 
								TIM2CH4_CAPTURE_STA++;
				}	
		}
		
		//ͨ��1
		if (TIM_GetITStatus(TIM2, TIM_IT_CC1) != RESET) 		//����1���������¼�
		{
				
				if (TIM2CH1_CAPTURE_STA & 0X8000)		//����һ���½���
				{
						TIM2CH1_CAPTURE_DOWNVAL = TIM_GetCapture1(TIM2);//��¼�´�ʱ�Ķ�ʱ������ֵ
						TIM_OC1PolarityConfig(TIM2, TIM_ICPolarity_Rising); //����Ϊ�����ز���
						TIM2_CH1_Time = TIM2CH1_CAPTURE_DOWNVAL - TIM2CH1_CAPTURE_UPVAL+ 65536*(TIM2CH1_CAPTURE_STA&0X7FFF);		//�õ��ܵĸߵ�ƽ��ʱ��
						TIM2CH1_CAPTURE_STA = 0;		//�����־λ����					
				}
				else //��������ʱ�䵫�����½��أ���һ�β��������أ���¼��ʱ�Ķ�ʱ������ֵ
				{
						TIM2CH1_CAPTURE_UPVAL = TIM_GetCapture1(TIM2);		//��ȡ����������
						TIM_OC1PolarityConfig(TIM2, TIM_ICPolarity_Falling);//����Ϊ�½��ز���
						TIM2CH1_CAPTURE_STA |= 0X8000;		//����Ѳ���������
				}
		}
		//ͨ��2
		if (TIM_GetITStatus(TIM2, TIM_IT_CC2) != RESET) 		//����2���������¼�
		{
				if (TIM2CH2_CAPTURE_STA & 0X8000)		//����һ���½���
				{
						TIM2CH2_CAPTURE_DOWNVAL = TIM_GetCapture2(TIM2);//��¼�´�ʱ�Ķ�ʱ������ֵ
						//TIM_OC2PolarityConfig(TIM2, TIM_ICPolarity_Rising); //����Ϊ�����ز���
						TIM2_CH2_Time = TIM2CH2_CAPTURE_DOWNVAL - TIM2CH2_CAPTURE_UPVAL+ 65536*(TIM2CH2_CAPTURE_STA&0X7FFF);		//�õ��ܵĸߵ�ƽ��ʱ��
						TIM2CH2_CAPTURE_STA = 0;		//�����־λ����					
				}
				else //��������ʱ�䵫�����½��أ���һ�β��������أ���¼��ʱ�Ķ�ʱ������ֵ
				{
						TIM2CH2_CAPTURE_UPVAL = TIM_GetCapture2(TIM2);		//��ȡ����������
						//TIM_OC2PolarityConfig(TIM2, TIM_ICPolarity_Falling);//����Ϊ�½��ز���
						TIM2CH2_CAPTURE_STA |= 0X8000;		//����Ѳ���������
				}
		}
		//ͨ��3
		if (TIM_GetITStatus(TIM2, TIM_IT_CC3) != RESET) 		//����3���������¼�
		{
				if (TIM2CH3_CAPTURE_STA & 0X8000)		//����һ���½���
				{
						TIM2CH3_CAPTURE_DOWNVAL = TIM_GetCapture3(TIM2);//��¼�´�ʱ�Ķ�ʱ������ֵ
						TIM_OC3PolarityConfig(TIM2, TIM_ICPolarity_Rising); //����Ϊ�����ز���
						TIM2_CH3_Time = TIM2CH3_CAPTURE_DOWNVAL - TIM2CH3_CAPTURE_UPVAL+ 65536*(TIM2CH3_CAPTURE_STA&0X7FFF);		//�õ��ܵĸߵ�ƽ��ʱ��
						TIM2CH3_CAPTURE_STA = 0;		//�����־λ����					
				}
				else //��������ʱ�䵫�����½��أ���һ�β��������أ���¼��ʱ�Ķ�ʱ������ֵ
				{
						TIM2CH3_CAPTURE_UPVAL = TIM_GetCapture3(TIM2);		//��ȡ����������
						TIM_OC3PolarityConfig(TIM2, TIM_ICPolarity_Falling);//����Ϊ�½��ز���
						TIM2CH3_CAPTURE_STA |= 0X8000;		//����Ѳ���������
				}
		}
		//ͨ��4
		if (TIM_GetITStatus(TIM2, TIM_IT_CC4) != RESET) 		//����4���������¼�
		{
				if (TIM2CH4_CAPTURE_STA & 0X8000)		//����һ���½���
				{
						TIM2CH4_CAPTURE_DOWNVAL = TIM_GetCapture4(TIM2);//��¼�´�ʱ�Ķ�ʱ������ֵ
						//TIM_OC4PolarityConfig(TIM2, TIM_ICPolarity_Rising); //����Ϊ�����ز���
						TIM2_CH4_Time = TIM2CH4_CAPTURE_DOWNVAL - TIM2CH4_CAPTURE_UPVAL+ 65536*(TIM2CH4_CAPTURE_STA&0X7FFF);		//�õ��ܵĸߵ�ƽ��ʱ��
						TIM2CH4_CAPTURE_STA = 0;		//�����־λ����					
				}
				else //��������ʱ�䵫�����½��أ���һ�β��������أ���¼��ʱ�Ķ�ʱ������ֵ
				{
						TIM2CH4_CAPTURE_UPVAL = TIM_GetCapture4(TIM2);		//��ȡ����������
						//TIM_OC4PolarityConfig(TIM2, TIM_ICPolarity_Falling);//����Ϊ�½��ز���
						TIM2CH4_CAPTURE_STA |= 0X8000;		//����Ѳ���������
				}
		}
    TIM_ClearITPendingBit(TIM2, TIM_IT_CC1|TIM_IT_CC2|TIM_IT_CC3|TIM_IT_CC4|TIM_IT_Update); 		//����жϱ�־λ		
} 
#endif

#if TIMx_OutputCompare_Init_Test==1  //3����Ƚ� 
void TIM1_CC_IRQHandler(void)
{
		u16 capture;
		if (TIM_GetITStatus(TIM1, TIM_IT_CC1) != RESET)
		{
			TIM_ClearITPendingBit(TIM1,TIM_IT_CC1);
			//��ʼ�����ö���ģʽ������������������������Ų���pwm TIM_OCMode_Timing	   TIM����Ƚ�ʱ��ģʽ	 ���ᣬ����Ƚϲ�������
			//GPIO_WriteBit(GPIOC,GPIO_Pin_6,(BitAction)(1-GPIO_ReadOutputDataBit(GPIOC,GPIO_Pin_6)));
			TIM1_CH1_Flag=!TIM1_CH1_Flag;
			if(TIM1_CH1_Flag==1)
			{
					capture = TIM_GetCapture1(TIM1);
					TIM_SetCompare1(TIM1, capture+5); //�ߵ�ƽ500ms
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
			//��ʼ�����ö���ģʽ������������������������Ų���pwm TIM_OCMode_Timing	   TIM����Ƚ�ʱ��ģʽ	 ���ᣬ����Ƚϲ�������
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
			//��ʼ�����ö���ģʽ������������������������Ų���pwm TIM_OCMode_Timing	   TIM����Ƚ�ʱ��ģʽ	 ���ᣬ����Ƚϲ�������
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
			//��ʼ�����ö���ģʽ������������������������Ų���pwm TIM_OCMode_Timing	   TIM����Ƚ�ʱ��ģʽ	 ���ᣬ����Ƚϲ�������
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
			//��ʼ�����ö���ģʽ������������������������Ų���pwm TIM_OCMode_Timing	   TIM����Ƚ�ʱ��ģʽ	 ���ᣬ����Ƚϲ�������
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
			//��ʼ�����ö���ģʽ������������������������Ų���pwm TIM_OCMode_Timing	   TIM����Ƚ�ʱ��ģʽ	 ���ᣬ����Ƚϲ�������
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




