#include "sumjess_key4x4.h"

/*******************************************************************************
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
********************************************************************************/	
//�������� ����	      

//��ʼ��PB0-7Ϊ�����.��ʹ���������ڵ�ʱ��		    

void key44_Init(void)
{

 GPIO_InitTypeDef  GPIO_InitStruct;
 RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);	 //ʹ��PB�˿�ʱ��
	
 GPIO_InitStruct.GPIO_Pin = GPIO_Pin_8|GPIO_Pin_9|GPIO_Pin_10|GPIO_Pin_11;				 //�˿�����
 GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP; 		 //�������
 GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;		 //IO���ٶ�Ϊ50MHz
 GPIO_Init(GPIOB, &GPIO_InitStruct);					 //�����趨������ʼ��GPIOB

 GPIO_InitStruct.GPIO_Pin = GPIO_Pin_12|GPIO_Pin_13|GPIO_Pin_14|GPIO_Pin_15;				 //�˿�����
 GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IPD; 		 //��������
 GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;		 //IO���ٶ�Ϊ50MHz
 GPIO_Init(GPIOB, &GPIO_InitStruct);					 //�����趨������ʼ��GPIOB
	
}
 
/**-------------------------------------------------------
  * @������ STM32_KEYScan
  * @����   ��ȡKEY�����������ƽ״̬����������ʱΪ�͵�ƽ0
  * @����   ��
  * @����ֵ 1  ��Ӧ�������ϵ�һ��KEY�������ڰ���״̬
  *         2  ��Ӧ�������ϵڶ���KEY�������ڰ���״̬
  *         3  ��Ӧ�������ϵ�����KEY�������ڰ���״̬
  *         4  ��Ӧ�������ϵ��ĸ�KEY�������ڰ���״̬
  *         0  ��������û��KEY�������ڰ���״̬
***------------------------------------------------------*/
int STM32_KEYScan(void) //ʵ�־�����̡�����ֵΪ���������ļ�ֵ���˼�ֵ���û��Լ����塣
{
	u8 KeyVal;	 //keyValΪ��󷵻صļ�ֵ��

	GPIO_Write(GPIOB,(GPIOB->ODR & 0xf0ff | 0x0100));	//��PB11��PB8��������Ƶ�0001.

		switch(GPIOB->IDR & 0xf000)//��PB12��PB15��ֵ�����жϣ��������ͬ�ļ�ֵ��
			{
				case 0x1000: KeyVal=1; break;
				case 0x2000: KeyVal=2;	break;
				case 0x4000: KeyVal=3;	break;
				case 0x8000: KeyVal='A';	break;
			}
	   
	GPIO_Write(GPIOB,(GPIOB->ODR & 0xf0ff | 0x0200));	//��PB11��PB8��������Ƶ�0.
		switch(GPIOB->IDR & 0xf000)		        //��PB12��PB15��ֵ�����жϣ��������ͬ�ļ�ֵ��
		{
			case 0x1000: KeyVal=4;	break;
			case 0x2000: KeyVal=5;	break;
			case 0x4000: KeyVal=6;	break;
			case 0x8000: KeyVal='B';	break;
		}

	GPIO_Write(GPIOB,(GPIOB->ODR & 0xf0ff | 0x0400));	//��PB11��PB8��������Ƶ�1011.
		switch(GPIOB->IDR & 0xf000)		        //��PB12��PB15��ֵ�����жϣ��������ͬ�ļ�ֵ��
		{
			case 0x1000: KeyVal=7;	break;
			case 0x2000: KeyVal=8;	break;
			case 0x4000: KeyVal=9;	break;
			case 0x8000: KeyVal='C';	break;
		}
 
	 GPIO_Write(GPIOB,(GPIOB->ODR & 0xf0ff | 0x0800));	//��PB11��PB8��������Ƶ�0111.
		switch(GPIOB->IDR & 0xf000)		        //��PB12��PB15��ֵ�����жϣ��������ͬ�ļ�ֵ��
		{
			case 0x1000: KeyVal='*';	break;
			case 0x2000: KeyVal=0;	break;
			case 0x4000: KeyVal='#';	break;
			case 0x8000: KeyVal='D';	break;
		}									  
	return KeyVal;
}



