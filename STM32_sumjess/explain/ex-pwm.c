/*

*******************************************************************************
================================================================================
��ƽ    ̨��stm32f103zet6_sumjessƽ̨
����    д��sumjess
��E-mail  ��1371129880@qq.com
������汾��V2.0
�������¡�2018��09��06��
�������Ϣ�ο����е�ַ��
����    վ��
           https://blog.csdn.net/qq_38351824
           http://www.openedv.com/
           http://www.stmcu.org/
					 http://www.firebbs.cn/forum.php
---------------------------------------------------------------------------------
��dev.env.��MDK5.14�����ϰ汾
��Target  ��stm32f103zet6
��һ���޶���2017/11/09
�ڶ����޶���2018/01/21
�������޶���2018/09/06
��problem ��
    ��1�����ڲ���Ĳ�ȫ�棻
    ��2�����ڽ��Ͳ��ֲ�ȫ�棻
    ��3�����ڻ�����һ����bug��
��direction��
      ��һ����Ŀ����ǰѿ�������ɣ�
��explain ��
      �����Ǹ�������ԭ�ӡ��о�԰���ӡ����ŵ��ӵ��̼Ҹı���ɣ�
      ͬʱΪ�˷���ʹ�ã���Ҳ�Լ�д�˺ܶ�Ŀ⣬���Ż����㷨�ͱ�ʾ��ʽ��
��warning��
      Ŀǰ���������޾��� ��   
---------------------------------------------------------------------------------
û�������Ĵ��룬ֻ�в��ϵķ��ף����һ��Ŭ����
����õ���������㣬��ӭ��ҷ���bug��
================================================================================
********************************************************************************



///////////////////////δӳ����������������ƣ�ֱ�ӿ�pwm.c�ͺ�////////////////////
/////////////////////////////////ӳ�������/////////////////////////////////////
PWM������ò��裺
***********************************************************
���в��趼��void TIM3_PWM_Init(u16 arr,u16 psc)��
//arr���Զ���װֵ
//psc��ʱ��Ԥ��Ƶ��
//PWM�����ʼ��
************************************************************
��ʹ�ܶ�ʱ��3�����IO��ʱ�ӡ�ʹ��GPIO����ʱ��ʹ��
         ʹ�ܶ�ʱ��3ʱ�ӣ�RCC_APB1PeriphClockCmd();
         ʹ��GPIOBʱ�ӣ�RCC_APB2PeriphClockCmd();����
				 **********************************************************
					RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);	//ʹ�ܶ�ʱ��3ʱ��
					RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB  | RCC_APB2Periph_AFIO, ENABLE);  //ʹ��GPIO�����AFIO���ù���ģ��ʱ��
				 *********************************************************
�ڳ�ʼ��IO��Ϊ���ù��������������GPIO_Init();
*********************************************************************
       ע�⣺ GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;   
*********************************************************************
������������Ҫ��PB5������ʱ����PWM������ţ�����Ҫ��ӳ�����ã�������Ҫ����AFIOʱ�ӡ�ͬʱ������ӳ�䡣����
        RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);
        GPIO_PinRemapConfig(GPIO_PartialRemap_TIM3, ENABLE); ****���ݸ��ļ��µĽ���ѡ����ʲô���͵�ӳ��***
				
	  //���ø�����Ϊ�����������,���TIM3 CH2��PWM���岨��	GPIOB.5
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_5; //TIM_CH2
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF_PP;  //�����������
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIO_InitStruct);//��ʼ��GPIO
�ܳ�ʼ����ʱ����ARR,PSC�ȣ�TIM_TimeBaseInit();
*****************************************************************************************************
	TIM_TimeBaseStructure.TIM_Period = arr; //��������һ�������¼�װ�����Զ���װ�ؼĴ������ڵ�ֵ	 ������5000Ϊ500ms
	TIM_TimeBaseStructure.TIM_Prescaler =psc; //����������ΪTIMxʱ��Ƶ�ʳ�����Ԥ��Ƶֵ  10Khz�ļ���Ƶ��  
	TIM_TimeBaseStructure.TIM_ClockDivision =TIM_CKD_DIV1; //����ʱ�ӷָ�:TDTS = Tck_tim*********��������ѡ
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIM���ϼ���ģʽ
	TIM_TimeBaseInit(TIM1, &TIM_TimeBaseStructure); //����TIM_TimeBaseInitStruct��ָ���Ĳ�����ʼ��TIMx��ʱ�������λ
******************************************************************************************************
�ݳ�ʼ������Ƚϲ���:TIM_OC2Init();ͨ��2�ĳ�ʼ����������
*****************************************************************************************
	//��ʼ��TIM3 Channel2 PWMģʽ	 
	TIM_OCInitStruct.TIM_OCMode = TIM_OCMode_PWM2; //ѡ��ʱ��ģʽ:TIM�����ȵ���ģʽ2(���غ�����)ģʽ1���������ƣ�
 	TIM_OCInitStruct.TIM_OutputState = TIM_OutputState_Enable; //�Ƚ����ʹ��
	TIM_OCInitStruct.TIM_OCPolarity = TIM_OCPolarity_High; //�������:TIM����Ƚϼ��Ը�
	TIM_OC2Init(TIM3, &TIM_OCInitStruct);  //����Tָ���Ĳ�����ʼ������TIM3 OC2
******************************************************************************************
��ʹ��Ԥװ�ؼĴ����� TIM_OC2PreloadConfig(TIM3, TIM_OCPreload_Enable); ����
*******************************************************************************************
****TIM_OC2PreloadConfig(TIM3, TIM_OCPreload_Enable);  //ʹ��TIM3��CCR2�ϵ�Ԥװ�ؼĴ���****��ͨ������2����Ҫ����
*****************************************************************************************
��ʹ�ܶ�ʱ����TIM_Cmd();����
*******************************************************************************************
	TIM_Cmd(TIM3, ENABLE);  //ʹ��TIM3
*******************************************************************************************
����������������������������������������������������������������������������������������������������
�಻�ϸı�Ƚ�ֵCCRx���ﵽ��ͬ��ռ�ձ�Ч��:TIM_SetCompare2();���¡���������������д��������

		TIM_SetCompare1(TIM1,led0pwmval);	//ͨ�ı�led0pwmval�ı�ռ�ձ�

//TIM_SetCompare1����������е�����1�������TIMx��ͨ��1,TIMx�е�x����ȡ1��17�ҳ���6��7������
����TIM_SetCompare1(TIM_TypeDef* TIMx, uint16_t Compare1)�ĵ���ʱ��
ǰһ�����ΪTIMx,TIMx�е�x����ȡ1��17�ҳ���6��7����,Compare1��������TIMx�Ƚϵ�����
�൱����TIMx��һ�����ڵ�ʱ���ȥ���Compare1��ʹ��TIMx�����ڴӺ��濪ʼ��Compare1��ʱ��ΪTIMx��ǰ����ʱ��ķ���
����ǰ����ʱ��Ϊ�ߵ�ƽ����Compare1������ʱ��Ϊ�͵�ƽ����ǰ����ʱ��Ϊ�͵�ƽ����Compare1������ʱ��Ϊ�ߵ�ƽ


u8 dir=1;	

TIM1_PWM_Init(899,0);//����Ƶ��PWMƵ��=72000/(899+1)=80Khz 


#include "led.h"
#include "delay.h"
#include "sys.h"
#include "sumjess_pwm.h"


 int main(void)
 {	
	u16 led0pwmval=0;    
	u8 dir=1;	
	delay_init();	    	 //��ʱ������ʼ��	  
	LED_Init();		  	//��ʼ����LED���ӵ�Ӳ���ӿ�
	TIM1_PWM_Init(899,0);//����Ƶ��PWMƵ��=72000/(899+1)=80Khz 
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




