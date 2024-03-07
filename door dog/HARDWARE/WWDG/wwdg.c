#include "wwdg.h"
#include "led.h"

WWDG_HandleTypeDef WWDG_Handler;    					 //���ڿ��Ź����

//��ʼ�����ڿ��Ź� 	
//tr   :T[6:0],������ֵ 
//wr   :W[6:0],����ֵ 
//fprer:��Ƶϵ����WDGTB��,�����2λ��Ч 
//Fwwdg=PCLKT/(4096*2^fprer). һ��PCLK1=42Mhz
void WWDG_Init(u8 tr,u8 wr,u32 fprer)
{
    WWDG_Handler.Instance=WWDG;
    WWDG_Handler.Init.Prescaler=fprer; 					//���÷�Ƶϵ��
    WWDG_Handler.Init.Window=wr;       					//���ô���ֵ
    WWDG_Handler.Init.Counter=tr;     					//���ü�����ֵ
		WWDG_Handler.Init.EWIMode=WWDG_EWI_ENABLE;	//ʹ����ǰ�����ж�
    HAL_WWDG_Init(&WWDG_Handler);      					//��ʼ��WWDG
}

//WWDG�ײ�������ʱ�����ã��ж�����
//�˺����ᱻHAL_WWDG_Init()����
//hwwdg:���ڿ��Ź����
void HAL_WWDG_MspInit(WWDG_HandleTypeDef *hwwdg)
{   
    __HAL_RCC_WWDG_CLK_ENABLE();    						//ʹ�ܴ��ڿ��Ź�ʱ��
        
    HAL_NVIC_SetPriority(WWDG_IRQn,2,3);   		 	//��ռ���ȼ�2�������ȼ�Ϊ3
    HAL_NVIC_EnableIRQ(WWDG_IRQn);         			 //ʹ�ܴ��ڿ��Ź��ж�
}

//���ڿ��Ź��жϷ�����
void WWDG_IRQHandler(void)
{
    HAL_WWDG_IRQHandler(&WWDG_Handler);						//����WWDG�����жϴ�������
}

//�жϷ�������������
//�˺����ᱻHAL_WWDG_IRQHandler()����
void HAL_WWDG_EarlyWakeupCallback(WWDG_HandleTypeDef* hwwdg)
{
    HAL_WWDG_Refresh(&WWDG_Handler);							//���´��ڿ��Ź�ֵ
    LED1=!LED1; 
}