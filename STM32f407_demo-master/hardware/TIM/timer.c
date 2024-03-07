#include "timer.h"
//////////////////////////////////////////////////////////////////////////////////	 
//������ֻ��ѧϰʹ�ã�δ��������ɣ��������������κ���;
//ALIENTEK STM32F407������
//��ʱ���ж���������	   
//����ԭ��@ALIENTEK
//������̳:www.openedv.com
//��������:2017/4/7
//�汾��V1.0
//��Ȩ���У�����ؾ���
//Copyright(C) ������������ӿƼ����޹�˾ 2014-2024
//All rights reserved									  
////////////////////////////////////////////////////////////////////////////////// 	
TIM_HandleTypeDef TIM2_Handler;      //��ʱ��2��� 
TIM_HandleTypeDef TIM3_Handler;      //��ʱ��3��� 
TIM_HandleTypeDef TIM4_Handler;      //��ʱ��4��� 
TIM_HandleTypeDef TIM5_Handler;      //��ʱ��5��� 
TIM_HandleTypeDef TIM7_Handler;      //��ʱ��9��� 
//ͨ�ö�ʱ��TIM3�жϳ�ʼ��
//arr���Զ���װֵ��
//psc��ʱ��Ԥ��Ƶ��
//��ʱ�����ʱ����㷽��:Tout=((arr+1)*(psc+1))/Ft us.
//Ft=��ʱ������Ƶ��,��λ:Mhz
//����ʹ�õ��Ƕ�ʱ��3!(��ʱ��3����APB1�ϣ�ʱ��ΪAPB1clk*2=42*2=84M)
void TIM2_Init(u16 arr,u16 psc)
{  
    TIM2_Handler.Instance=TIM2;                            //ͨ�ö�ʱ��2
    TIM2_Handler.Init.Prescaler=psc;                       //��Ƶϵ��
    TIM2_Handler.Init.CounterMode=TIM_COUNTERMODE_UP;      //���ϼ�����
    TIM2_Handler.Init.Period=arr;                          //�Զ�װ��ֵ
    TIM2_Handler.Init.ClockDivision=TIM_CLOCKDIVISION_DIV1;//ʱ�ӷ�Ƶ����
    HAL_TIM_Base_Init(&TIM2_Handler);					   //��ʼ��ʱ����Ԫ
                                                           //
    HAL_TIM_Base_Start_IT(&TIM2_Handler); 				   //ʹ�ܶ�ʱ��2�Ͷ�ʱ��2�����жϣ�TIM_IT_UPDATE   
}

void TIM3_Init(u16 arr,u16 psc)
{  
    TIM3_Handler.Instance=TIM3;                            //ͨ�ö�ʱ��3
    TIM3_Handler.Init.Prescaler=psc;                       //��Ƶϵ��
    TIM3_Handler.Init.CounterMode=TIM_COUNTERMODE_UP;      //���ϼ�����
    TIM3_Handler.Init.Period=arr;                          //�Զ�װ��ֵ
    TIM3_Handler.Init.ClockDivision=TIM_CLOCKDIVISION_DIV1;//ʱ�ӷ�Ƶ����
    HAL_TIM_Base_Init(&TIM3_Handler);					   //��ʼ��ʱ����Ԫ
														   //
    HAL_TIM_Base_Start_IT(&TIM3_Handler); 				   //ʹ�ܶ�ʱ��3�Ͷ�ʱ��3�����жϣ�TIM_IT_UPDATE   
}

void TIM4_Init(u16 arr,u16 psc)
{  
    TIM4_Handler.Instance=TIM4;                            //ͨ�ö�ʱ��4
    TIM4_Handler.Init.Prescaler=psc;                       //��Ƶϵ��
    TIM4_Handler.Init.CounterMode=TIM_COUNTERMODE_UP;      //���ϼ�����
    TIM4_Handler.Init.Period=arr;                          //�Զ�װ��ֵ
    TIM4_Handler.Init.ClockDivision=TIM_CLOCKDIVISION_DIV1;//ʱ�ӷ�Ƶ����
    HAL_TIM_Base_Init(&TIM4_Handler);					   //��ʼ��ʱ����Ԫ
														   //
    HAL_TIM_Base_Start_IT(&TIM4_Handler);				   //ʹ�ܶ�ʱ��4�Ͷ�ʱ��4�����жϣ�TIM_IT_UPDATE   
}

void TIM5_Init(u16 arr,u16 psc)
{  
    TIM5_Handler.Instance=TIM5;                            //ͨ�ö�ʱ��5
    TIM5_Handler.Init.Prescaler=psc;                       //��Ƶϵ��
    TIM5_Handler.Init.CounterMode=TIM_COUNTERMODE_UP;      //���ϼ�����
    TIM5_Handler.Init.Period=arr;                          //�Զ�װ��ֵ
    TIM5_Handler.Init.ClockDivision=TIM_CLOCKDIVISION_DIV1;//ʱ�ӷ�Ƶ����
    HAL_TIM_Base_Init(&TIM5_Handler);					   //��ʼ��ʱ����Ԫ
														   //
    HAL_TIM_Base_Start_IT(&TIM5_Handler); 				   //ʹ�ܶ�ʱ��5�Ͷ�ʱ��5�����жϣ�TIM_IT_UPDATE   
}

void TIM9_Init(u16 arr,u16 psc)
{  
    TIM7_Handler.Instance=TIM7;                            //ͨ�ö�ʱ��9
    TIM7_Handler.Init.Prescaler=psc;                       //��Ƶϵ��
    TIM7_Handler.Init.CounterMode=TIM_COUNTERMODE_UP;      //���ϼ�����
    TIM7_Handler.Init.Period=arr;                          //�Զ�װ��ֵ
    TIM7_Handler.Init.ClockDivision=TIM_CLOCKDIVISION_DIV1;//ʱ�ӷ�Ƶ����
    HAL_TIM_Base_Init(&TIM7_Handler);					   //��ʼ��ʱ����Ԫ
														   //
    HAL_TIM_Base_Start_IT(&TIM7_Handler); 				   //ʹ�ܶ�ʱ��9�Ͷ�ʱ��9�����жϣ�TIM_IT_UPDATE   
}

//��ʱ���ײ�����������ʱ�ӣ������ж����ȼ�
//�˺����ᱻHAL_TIM_Base_Init()��������
void HAL_TIM_Base_MspInit(TIM_HandleTypeDef *htim)
{
	if(htim->Instance==TIM2)
	{
		__HAL_RCC_TIM2_CLK_ENABLE();            //ʹ��TIM2ʱ��
		HAL_NVIC_SetPriority(TIM2_IRQn,1,0);    //�����ж����ȼ�����ռ���ȼ�1�������ȼ�0
		HAL_NVIC_EnableIRQ(TIM2_IRQn);          //����ITM2�ж�   
	}
    if(htim->Instance==TIM3)
	{
		__HAL_RCC_TIM3_CLK_ENABLE();            //ʹ��TIM3ʱ��
		HAL_NVIC_SetPriority(TIM3_IRQn,1,1);    //�����ж����ȼ�����ռ���ȼ�1�������ȼ�1
		HAL_NVIC_EnableIRQ(TIM3_IRQn);          //����ITM3�ж�   
	}
	if(htim->Instance==TIM4)
	{
		__HAL_RCC_TIM4_CLK_ENABLE();            //ʹ��TIM4ʱ��
		HAL_NVIC_SetPriority(TIM4_IRQn,1,2);    //�����ж����ȼ�����ռ���ȼ�1�������ȼ�2
		HAL_NVIC_EnableIRQ(TIM4_IRQn);          //����ITM4�ж�   
	}
	if(htim->Instance==TIM5)
	{
		__HAL_RCC_TIM5_CLK_ENABLE();            //ʹ��TIM5ʱ��
		HAL_NVIC_SetPriority(TIM5_IRQn,1,3);    //�����ж����ȼ�����ռ���ȼ�1�������ȼ�3
		HAL_NVIC_EnableIRQ(TIM5_IRQn);          //����ITM5�ж�   
	}
	if(htim->Instance==TIM7)
	{
		__HAL_RCC_TIM9_CLK_ENABLE();            //ʹ��TIM7ʱ��
		HAL_NVIC_SetPriority(TIM7_IRQn,1,4);    //�����ж����ȼ�����ռ���ȼ�1�������ȼ�4
		HAL_NVIC_EnableIRQ(TIM7_IRQn);          //����ITM7�ж�   
	}
}

void TIM2_IRQHandler(void)
{
	 __HAL_TIM_CLEAR_IT(&TIM2_Handler,TIM_IT_UPDATE);
}

void TIM3_IRQHandler(void)
{
	 __HAL_TIM_CLEAR_IT(&TIM3_Handler,TIM_IT_UPDATE);
}

void TIM4_IRQHandler(void)
{
     __HAL_TIM_CLEAR_IT(&TIM4_Handler,TIM_IT_UPDATE);
}
void TIM5_IRQHandler(void)
{
	 __HAL_TIM_CLEAR_IT(&TIM5_Handler,TIM_IT_UPDATE);
}
void TIM7_IRQHandler(void)
{
	 __HAL_TIM_CLEAR_IT(&TIM9_Handler,TIM_IT_UPDATE);
}
