#include "sumjess_track_motor.h" 
#include "sumjess_pwm.h"

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
//FoodDelivered-Robot ѭ������ ----���



void forward(void)         //ǰ��
{
  TIM_SetCompare1(TIM3,7);
	TIM_SetCompare2(TIM3,0);
	TIM_SetCompare3(TIM3,7);
	TIM_SetCompare4(TIM3,0);
}

void turnSRight(void)      //С��
{
  TIM_SetCompare1(TIM3,0);
	TIM_SetCompare2(TIM3,0);
	TIM_SetCompare3(TIM3,7);
	TIM_SetCompare4(TIM3,0);
}

void turnRight(void)       //��ת
{
  TIM_SetCompare1(TIM3,5);
	TIM_SetCompare2(TIM3,0);
	TIM_SetCompare3(TIM3,15);
	TIM_SetCompare4(TIM3,0);
}

void turnSLeft(void)       //С��
{
  TIM_SetCompare1(TIM3,7);
	TIM_SetCompare2(TIM3,0);
	TIM_SetCompare3(TIM3,0);
	TIM_SetCompare4(TIM3,0);
}

void turnLeft(void)        //��ת
{
  TIM_SetCompare1(TIM3,15);
	TIM_SetCompare2(TIM3,0);
	TIM_SetCompare3(TIM3,5);
	TIM_SetCompare4(TIM3,0);
}

void stop(void)            //ͣ��
{
  TIM_SetCompare1(TIM3,0);
	TIM_SetCompare2(TIM3,0);
	TIM_SetCompare3(TIM3,0);
	TIM_SetCompare4(TIM3,0);
}

void turnright_90d(void)   //��90��
{
  TIM_SetCompare1(TIM3,0);
	TIM_SetCompare2(TIM3,15);
	TIM_SetCompare3(TIM3,15);
	TIM_SetCompare4(TIM3,0);
}

void turnleft_90d(void)    //��90��
{
  TIM_SetCompare1(TIM3,15);
	TIM_SetCompare2(TIM3,0);
	TIM_SetCompare3(TIM3,0);
	TIM_SetCompare4(TIM3,0);
}

                                                                     






