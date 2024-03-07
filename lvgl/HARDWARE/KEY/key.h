#ifndef _KEY_H
#define _KEY_H
#include "sys.h"
//////////////////////////////////////////////////////////////////////////////////	 
//������ֻ��ѧϰʹ�ã�δ��������ɣ��������������κ���;
//ALIENTEK STM32F407������
//KEY��������	   
//����ԭ��@ALIENTEK
//������̳:www.openedv.com
//��������:2017/4/6
//�汾��V1.0
//��Ȩ���У�����ؾ���
//Copyright(C) ������������ӿƼ����޹�˾ 2014-2024
//All rights reserved									  
//////////////////////////////////////////////////////////////////////////////////

//����ķ�ʽ��ͨ��λ��������ʽ��ȡIO
//#define KEY0        PHin(3) //KEY0����PH3
//#define KEY1        PHin(2) //KEY1����PH2
//#define KEY2        PCin(13)//KEY2����PC13
//#define WK_UP       PAin(0) //WKUP����PA0


//����ķ�ʽ��ͨ��ֱ�Ӳ���HAL�⺯����ʽ��ȡIO
#define KEY0        HAL_GPIO_ReadPin(GPIOG,GPIO_PIN_9)  //KEY0����PE4
#define KEY1        HAL_GPIO_ReadPin(GPIOG,GPIO_PIN_10)  //KEY1����PE3
#define KEY2        HAL_GPIO_ReadPin(GPIOG,GPIO_PIN_11) 	//KEY2����PE2
#define KEY3        HAL_GPIO_ReadPin(GPIOG,GPIO_PIN_13) 	//KEY2����PE2
#define WEKEUP       HAL_GPIO_ReadPin(GPIOA,GPIO_PIN_0)  //WKUP����PA0

#define KEY0_PRES 	1
#define KEY1_PRES		2
#define KEY2_PRES		3
#define KEY3_PRES   4
#define WEKEUP_PRES   5


void KEY_Init(void);
u8 KEY_Scan(u8 mode);
#endif
