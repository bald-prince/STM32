#include "sumjess_L298N.h" 

/*******************************************************************************
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
********************************************************************************/	
//ֱ����� ��������


void L298N_Init(void)
{

 GPIO_InitTypeDef  GPIO_InitStructure;
 	
 RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);	 
	
 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;				 
 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		
 GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		
 GPIO_Init(GPIOC, &GPIO_InitStructure);					
 GPIO_SetBits(GPIOC,GPIO_Pin_0);		
	
 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;				 
 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		
 GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		
 GPIO_Init(GPIOC, &GPIO_InitStructure);					
 GPIO_SetBits(GPIOC,GPIO_Pin_2);		
	
 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;				 
 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		
 GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		
 GPIO_Init(GPIOC, &GPIO_InitStructure);					
 GPIO_SetBits(GPIOC,GPIO_Pin_3);		
	
 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;				 
 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		
 GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		
 GPIO_Init(GPIOC, &GPIO_InitStructure);					
 GPIO_SetBits(GPIOC,GPIO_Pin_10);		
 
}



