#ifndef __DAC_H
#define __DAC_H
#include "sys.h"
//////////////////////////////////////////////////////////////////////////////////	 
//������ֻ��ѧϰʹ�ã�δ��������ɣ��������������κ���;
//ALIENTEK STM32F7������
//DAC��������	   
//����ԭ��@ALIENTEK
//������̳:www.openedv.com
//��������:2015/12/28
//�汾��V1.0
//��Ȩ���У�����ؾ���
//Copyright(C) ������������ӿƼ����޹�˾ 2014-2024
//All rights reserved									  
////////////////////////////////////////////////////////////////////////////////// 	
extern  u32  dac_sin_buffer[33];
extern  u32  dac_triangle[7];
extern  u32  dac_heasived[2];
extern DAC_HandleTypeDef DAC1_Handler;//DAC���
extern int ct;
void DAC1_Init(void);
void DAC1_Set_Vol(u16 vol);
#endif
