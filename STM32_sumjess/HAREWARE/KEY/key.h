#ifndef __KEY_H
#define __KEY_H	 
#include "sys.h"
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
//�������� ����	        	 
 
#define left_rd      GPIO_ReadInputDataBit(GPIOD,GPIO_Pin_3)//��ȡ��
#define leftmid_rd   GPIO_ReadInputDataBit(GPIOD,GPIO_Pin_4)//��ȡ����
#define mid_rd       GPIO_ReadInputDataBit(GPIOD,GPIO_Pin_5)//��ȡ��  
#define rightmid_rd  GPIO_ReadInputDataBit(GPIOD,GPIO_Pin_6)//��ȡ����
#define right_rd     GPIO_ReadInputDataBit(GPIOD,GPIO_Pin_7)//��ȡ��
#define WK_UP   GPIO_ReadInputDataBit(GPIOD,GPIO_Pin_0)     //��ȡ 
#define KEY0  GPIO_ReadInputDataBit(GPIOD,GPIO_Pin_1)       //��ȡ
#define KEY1  GPIO_ReadInputDataBit(GPIOD,GPIO_Pin_2)      //��ȡ

#define KE  GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_5)//��ȡ����0
#define KEY  GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_15)//��ȡ����1
#define WK_U   GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_0)//��ȡ����2 
 

#define KEY0_PRES	1		//KEY0  
#define KEY1_PRES	2		//KEY1 
#define WKUP_PRES	3		//WK_UP  

void KEY_Init(void);//IO��ʼ��
u8 KEY_Scan(u8 mode);  	//����ɨ�躯��			


#endif



