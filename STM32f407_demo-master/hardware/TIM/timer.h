#ifndef _TIMER_H
#define _TIMER_H
#include "sys.h"
#include "delay.h"
//////////////////////////////////////////////////////////////////////////////////	 
//������ֻ��ѧϰʹ�ã�δ��������ɣ��������������κ���;
//ALIENTEK STM32F407������
//��ʱ����������	   
//����ԭ��@ALIENTEK
//������̳:www.openedv.com
//��������:2017/4/7
//�汾��V1.0
//��Ȩ���У�����ؾ���
//Copyright(C) ������������ӿƼ����޹�˾ 2014-2024
//All rights reserved									  
////////////////////////////////////////////////////////////////////////////////// 	
//˽�к�



//�ⲿ����
extern TIM_HandleTypeDef TIM2_Handler;      //��ʱ����� 
extern TIM_HandleTypeDef TIM3_Handler;      //��ʱ����� 
extern TIM_HandleTypeDef TIM4_Handler;      //��ʱ����� 
extern TIM_HandleTypeDef TIM5_Handler;      //��ʱ����� 
extern TIM_HandleTypeDef TIM7_Handler;      //��ʱ����� 
//��������
void TIM2_Init(u16 arr,u16 psc);
void TIM3_Init(u16 arr,u16 psc);
void TIM4_Init(u16 arr,u16 psc);
void TIM5_Init(u16 arr,u16 psc);
void TIM7_Init(u16 arr,u16 psc);
//˽�б���


#endif

