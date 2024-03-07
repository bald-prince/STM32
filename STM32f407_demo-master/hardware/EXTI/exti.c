#include "exti.h"

//////////////////////////////////////////////////////////////////////////////////	 
//������ֻ��ѧϰʹ�ã�δ��������ɣ��������������κ���;
//ALIENTEK STM32F429������
//�ⲿ�ж���������	   
//����ԭ��@ALIENTEK
//������̳:www.openedv.com
//��������:2016/1/5
//�汾��V1.0
//��Ȩ���У�����ؾ���
//Copyright(C) ������������ӿƼ����޹�˾ 2014-2024
//All rights reserved									  
////////////////////////////////////////////////////////////////////////////////// 	
//�ⲿ�жϳ�ʼ��
void EXTI_Init(void)
{
    GPIO_InitTypeDef GPIO_Initure;
    
    __HAL_RCC_GPIOA_CLK_ENABLE();               //����GPIOAʱ��
    __HAL_RCC_GPIOG_CLK_ENABLE();               //����GPIOGʱ��
    
    GPIO_Initure.Pin=GPIO_PIN_0;                //PA0
    GPIO_Initure.Mode=GPIO_MODE_IT_RISING;      //�����ش���
    GPIO_Initure.Pull=GPIO_PULLDOWN;
    HAL_GPIO_Init(GPIOA,&GPIO_Initure);
    
    GPIO_Initure.Pin=GPIO_PIN_9;                //PG9
    GPIO_Initure.Mode=GPIO_MODE_IT_FALLING;     //�½��ش���
    GPIO_Initure.Pull=GPIO_PULLUP;
    HAL_GPIO_Init(GPIOG,&GPIO_Initure);
    
    GPIO_Initure.Pin=GPIO_PIN_10|GPIO_PIN_11|GPIO_PIN_13;     //PG13,11,10
    HAL_GPIO_Init(GPIOG,&GPIO_Initure);
    
    //�ж���0-PA0
    HAL_NVIC_SetPriority(EXTI0_IRQn,2,0);       	  //��ռ���ȼ�Ϊ2�������ȼ�Ϊ0
    HAL_NVIC_EnableIRQ(EXTI0_IRQn);            	    //ʹ���ж���0
    
    
	  //�ж���2-PG9
    HAL_NVIC_SetPriority(EXTI9_5_IRQn,2,1);         //��ռ���ȼ�Ϊ2�������ȼ�Ϊ1
    HAL_NVIC_EnableIRQ(EXTI9_5_IRQn);               //ʹ���ж���2
    
    //�ж���3-PG10,11,13
    HAL_NVIC_SetPriority(EXTI15_10_IRQn,2,2);       //��ռ���ȼ�Ϊ2�������ȼ�Ϊ2
    HAL_NVIC_EnableIRQ(EXTI15_10_IRQn);             //ʹ���ж���2
}


//�жϷ�����
void EXTI0_IRQHandler(void)
{
	__HAL_GPIO_EXTI_CLEAR_IT(GPIO_PIN_0);	
}

void EXTI9_5_IRQHandler(void)
{
	__HAL_GPIO_EXTI_CLEAR_IT(GPIO_PIN_9);
}

void EXTI15_10_IRQHandler(void)
{
	__HAL_GPIO_EXTI_CLEAR_IT(GPIO_PIN_10|GPIO_PIN_11|GPIO_PIN_13);
}


