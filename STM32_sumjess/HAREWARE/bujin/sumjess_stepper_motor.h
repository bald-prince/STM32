#ifndef __SUMJESS_STEPPER_MOTOR_H
#define __SUMJESS_STEPPER_MOTOR_H

/*******************************************************************************
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
********************************************************************************/	
//������� ��������

/*********************
���߷�ʽ:
IN1 ---- PC0
IN2 ---- PC2
IN3 ---- PC3
IN4 ---- PC10
+   ---- +5V
-   ---- GND
*********************/

#include "sys.h"



void bujin_Init(void);

void bujin_Z_Init(void);//˳ʱ��

void bujin_F_Init(void);//��ʱ��

void bujin_D_Init(void);






#endif

