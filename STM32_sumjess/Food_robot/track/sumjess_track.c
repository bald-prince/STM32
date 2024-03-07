#include "sumjess_track.h" 
#include "sumjess_track_motor.h" 
#include "key.h"
#include "delay.h"  
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
//FoodDelivered-Robot ѭ������

int sensor[5] = {0, 0, 0, 0, 0}; //ѭ��ģ�����ݲɼ��洢����
int error = 0;
extern int track_media ;

void track_data(void)    //���ݲɼ�
{
  sensor[0] = 0;//left_rd;
  sensor[1] = leftmid_rd;
  sensor[2] = mid_rd;
  sensor[3] = rightmid_rd;
  sensor[4] = 0;//right_rd;
}
///////1Ϊ����///////
int track_decide(void)    //���ݴ���
{
 //ƫ���
 if ((sensor[1] == 0) && (sensor[2] == 0) && (sensor[3] == 0)) {
      error = 0;/////////////000///ͣ��//////////////
    } else if ((sensor[1] == 0) && (sensor[2] == 0) && (sensor[3] == 1)) {
      error = -2;////////////001///��ת//////////////
    } else if ((sensor[1] == 0) && (sensor[2] == 1) && (sensor[3] == 0)) {
      error = 0;/////////////010///ֱ��//////////////
    } else if ((sensor[1] == 0) && (sensor[2] == 1) && (sensor[3] == 1)) {
      error = -1;////////////011///��ת//////////////
    } else if ((sensor[1] == 1) && (sensor[2] == 0) && (sensor[3] == 0)) {
      error = 2;/////////////100///��ת//////////////
    } else if ((sensor[1] == 1) && (sensor[2] == 1) && (sensor[3] == 0)) {
      error = 1;/////////////110///��ת//////////////
    } else if ((sensor[1] == 1) && (sensor[2] == 1) && (sensor[3] == 1)) {
      error = 6;/////////////111///ֱ��//////////////
    } 
 //Ԫ�ش���
    if ((sensor[4] == 1)&&(sensor[0] == 1))  {
		     error=0;////////////1XXX1///ͣ��//////////////////
		   } else if (sensor[4] == 1)  {
		     error=5;////////////0XXX1///��ת90��//////////////
		   } else if (sensor[0] == 1)   {
				 error=6;////////////1XXX0///��ת90��//////////////
       }
			 
    return error;     //����Ŀǰ���
}

void track_motor(void)    //���ִ��
{
  switch (track_media){              //��ȡ��ֵ  
     case 0:  forward();          break; //ֱ��
     case -1: turnSRight();       break; //С��
     case -2: turnRight();        break; //���� 
     case 1:  turnSLeft();        break; //С��
     case 2:  turnLeft();         break; //����    
     case 3:  stop();             break; //ͣ
     case 5:  turnright_90d();    break; //��ת90��
     case 6:  turnleft_90d();     break; //��ת90��
     default: stop();             break; //ͣ  
     }
	 }


