/*

*******************************************************************************
================================================================================
��ƽ    ̨��stm32f103zet6_sumjessƽ̨
����    д��sumjess
��E-mail  ��1371129880@qq.com
�������汾��V2.0
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



**************************************************
****************�ⲿ�ж����ù���*******************
**************************************************

***************����****************

�����-�ݶ���д�� EXTI_Init();�����EXTI_Init����
�����-��Ϊһ���֡�


�ٳ�ʼ��IO��Ϊ���롣************��ʵ����Ϊ����,����ĳ�ʼ��ʵΪ8��ģʽ***********
      GPIO_Init();
�ڿ���IO�ڸ���ʱ�ӡ�
      RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);
������IO�����ж��ߵ�ӳ���ϵ��@@@@�����Ӧ���ļ������н���@@@@

      void GPIO_EXTILineConfig();Ϊ��������
    ************GPIO_EXTILineConfig(GPIO_PortSourceGPIOx,GPIO_PinSourcea);************
		
�ܳ�ʼ�������жϣ����ô��������ȡ�
      EXTI_Init();Ϊ��������
			
	 ****************************GPIOx.a �ж����Լ��жϳ�ʼ������**********************************ע�������x��a
  	GPIO_EXTILineConfig(GPIO_PortSourceGPIOx,GPIO_PinSourcea);

  	EXTI_InitStruct.EXTI_Line=EXTI_Linea;
  	EXTI_InitStruct.EXTI_Mode = EXTI_Mode_Interrupt;	**************ѡ���ж����� �� EXTI_Mode_Interrupt
  	EXTI_InitStruct.EXTI_Trigger = EXTI_Trigger_Falling;//�½��ش���**********��λ����Ҫͨ��ʵ��ʹ����д******���磬�������µ�ƽ��������������ء�
  	EXTI_InitStruct.EXTI_LineCmd = ENABLE;************����
  	EXTI_Init(&EXTI_InitStruct);	 	//����EXTI_InitStruct��ָ���Ĳ�����ʼ������EXTI�Ĵ���
	  *********************************************************************************************	
			
�������жϷ��飨NVIC������ʹ���жϡ�
      NVIC_Init();Ϊ��������
			
		***************************************************************************************************
		NVIC_InitStruct.NVIC_IRQChannel = EXTI0_IRQn;			//ʹ�ܰ������ڵ��ⲿ�ж�ͨ��********��stm32f10x.c��190������
  	NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority =2;	//��ռ���ȼ�2 
  	NVIC_InitStruct.NVIC_IRQChannelSubPriority =1;					//�����ȼ�1
  	NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;								//ʹ���ⲿ�ж�ͨ��
  	NVIC_Init(&NVIC_InitStruct);  	  //����NVIC_InitStruct��ָ���Ĳ�����ʼ������NVIC�Ĵ���
		****************************************************************************************************	
			
			
�ޱ�д�жϷ�������
      EXTIx_IRQHandler();
������жϱ�־λ
      EXTI_ClearITPendingBit();

��-�޸�ʽΪ��

void EXTI0_IRQHandler(void)  ****��  startup_stm32f10x_hd.s  ��80������*****
{
  delay_ms(10);    //����*************************
	if(WK_UP==1)					**************************
	{	  									**************************�ò������ݸ�����Ҫ��д����
		LED0=!LED0;					**************************
		LED1=!LED1;					**************************
	}
	EXTI_ClearITPendingBit(EXTI_Line0);  //���EXTI0��·����λ
}

**************************************************************************************
***********************ע�⣺������EXTI_LineX��X��ƥ��Ͷ�Ӧ****************************
**************************************************************************************
***********************ע�⣺��Ҫ�������������н����ж����ȼ�����************************
*********NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);// �����ж����ȼ�����2*********
**************************************************************************************

**************�򵥵Ĵ���***************
#include "usart.h"

 int main(void)
 {	
 
	uart_init(9600);	 //���ڳ�ʼ��Ϊ9600
	
	while(1)
	{	    
		printf("OK\n");	  
  
	} 
}










*/


