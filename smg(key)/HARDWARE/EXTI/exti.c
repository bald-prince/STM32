#include "exti.h"
#include "delay.h"
#include "key.h"
#include "SMG.h"


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
    HAL_NVIC_SetPriority(EXTI2_IRQn,2,1);       //��ռ���ȼ�Ϊ2�������ȼ�Ϊ1
    HAL_NVIC_EnableIRQ(EXTI2_IRQn);             //ʹ���ж���2
    
    //�ж���3-PG11
    HAL_NVIC_SetPriority(EXTI3_IRQn,2,2);       //��ռ���ȼ�Ϊ2�������ȼ�Ϊ2
    HAL_NVIC_EnableIRQ(EXTI3_IRQn);             //ʹ���ж���2
    
    //�ж���4-PG13
    HAL_NVIC_SetPriority(EXTI4_IRQn,2,3);   		//��ռ���ȼ�Ϊ2�������ȼ�Ϊ3
    HAL_NVIC_EnableIRQ(EXTI4_IRQn);         		//ʹ���ж���4
}


//�жϷ�����
void EXTI0_IRQHandler(void)
{
    HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_0);			//�����жϴ����ú���
		
}

void EXTI2_IRQHandler(void)
{
    HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_10);		//�����жϴ����ú���
	 
}

void EXTI3_IRQHandler(void)
{
    HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_11);		//�����жϴ����ú���
	  
}

void EXTI4_IRQHandler(void)
{
    HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_13);		//�����жϴ����ú���
		
}


//�жϷ����������Ҫ��������
//��HAL�������е��ⲿ�жϷ�����������ô˺���
//GPIO_Pin:�ж����ź�
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{   
		u32 counter=99999999;
    delay_ms(10);      									//����
    switch(GPIO_Pin)
    {
        case GPIO_PIN_13:
        if(KEY0==0)  
        {
					DIV_number(counter);
					SMG_Disp(Disp_Code);						//����LED0��ת
        }
        break;
    }
}
