#include "exti.h"
#include "delay.h"
#include "led.h"
#include "key.h"


//�ⲿ�жϳ�ʼ��
void EXTI_Init(void)
{
    GPIO_InitTypeDef GPIO_Initure;
    
    __HAL_RCC_GPIOG_CLK_ENABLE();              														 //����GPIOGʱ��
		__HAL_RCC_GPIOA_CLK_ENABLE();
   
		GPIO_Initure.Pin=GPIO_PIN_0; 
		GPIO_Initure.Mode=GPIO_MODE_IT_RISING;
		GPIO_Initure.Pull=GPIO_PULLDOWN; 
		HAL_GPIO_Init(GPIOA,&GPIO_Initure);
	
    GPIO_Initure.Pin=GPIO_PIN_9|GPIO_PIN_10|GPIO_PIN_11|GPIO_PIN_13; 			//PG9,10,11,13
    GPIO_Initure.Mode=GPIO_MODE_IT_FALLING;    						 								//�½��ش���
    GPIO_Initure.Pull=GPIO_PULLUP;    																		//����
    HAL_GPIO_Init(GPIOG,&GPIO_Initure);
    
    //�ж���0-PG9
    HAL_NVIC_SetPriority(EXTI0_IRQn,2,0);       //��ռ���ȼ�Ϊ2�������ȼ�Ϊ0
    HAL_NVIC_EnableIRQ(EXTI0_IRQn);             //ʹ���ж���0
    
    //�ж���2-PG10
    HAL_NVIC_SetPriority(EXTI9_5_IRQn,2,1);       //��ռ���ȼ�Ϊ2�������ȼ�Ϊ1
    HAL_NVIC_EnableIRQ(EXTI9_5_IRQn);             //ʹ���ж���2
    
    //�ж���3-PG11
    HAL_NVIC_SetPriority(EXTI15_10_IRQn,2,2);       //��ռ���ȼ�Ϊ2�������ȼ�Ϊ2
    HAL_NVIC_EnableIRQ(EXTI15_10_IRQn);             //ʹ���ж���2
}


//�жϷ�����
void EXTI0_IRQHandler(void)
{
    HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_0);			//�����жϴ����ú���
		
}

void EXTI9_5_IRQHandler(void)
{
    HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_9);		//�����жϴ����ú���
	 
}

void EXTI15_10_IRQHandler(void)
{
    HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_13);		//�����жϴ����ú���
		HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_11);		//�����жϴ����ú���
		HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_10);		//�����жϴ����ú���
}


//�жϷ����������Ҫ��������
//��HAL�������е��ⲿ�жϷ�����������ô˺���
//GPIO_Pin:�ж����ź�
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
	delay_ms(10);      									//����
  switch(GPIO_Pin)
  {
		case GPIO_PIN_0:
			if(WEKEUP==1) 
      {
				L1=0;					//����LED0,LED1�������
				L0=1;
      }
    break;
    case GPIO_PIN_10:
			if(KEY2==0)  						
      {
				L1=1; 
				L0=0;
      }
    break;
  }
}
