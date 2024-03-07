#include "sumjess_stepper_motor.h"
#include "delay.h"
/*******************************************************************************
================================================================================
��ƽ    ̨��stm32f103zet6_sumjessƽ̨
����    д��sumjess
��E-mail  ��1371129880@qq.com
������汾��V2.0
�������¡�2018��01��21��
�������Ϣ�ο����е�ַ��
����    վ��http://www.openedv.com/
           http://www.stmcu.org/
					 http://www.firebbs.cn/forum.php
---------------------------------------------------------------------------------
��dev.env.��MDK5.14�����ϰ汾
��Target  ��stm32f103zet6
��һ���޶���2017/11/09
�ڶ����޶���2018/01/21
---------------------------------------------------------------------------------
û�������Ĵ��룬ֻ�в��ϵķ��ף����һ��Ŭ����
����õ���������㣬��ӭ��ҷ���bug��
================================================================================
********************************************************************************/	
//������� ��������

/*********************
���߷�ʽ:
IN1 ---- PC0
IN2 ---- PC2
IN3 ---- PC3
IN4 ---- PC10
+   ---- +5V
-   ---- GND
*********************/
void bujin_Init(void)
{
	
	
 GPIO_InitTypeDef  GPIO_InitStructure;
 	
 RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);	 
	
 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;				 
 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		
 GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		
 GPIO_Init(GPIOC, &GPIO_InitStructure);					
 GPIO_SetBits(GPIOC,GPIO_Pin_0);		
	
 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;				 
 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		
 GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		
 GPIO_Init(GPIOC, &GPIO_InitStructure);					
 GPIO_SetBits(GPIOC,GPIO_Pin_2);		
	
 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;				 
 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		
 GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		
 GPIO_Init(GPIOC, &GPIO_InitStructure);					
 GPIO_SetBits(GPIOC,GPIO_Pin_3);		
	
 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;				 
 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		
 GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		
 GPIO_Init(GPIOC, &GPIO_InitStructure);					
 GPIO_SetBits(GPIOC,GPIO_Pin_10);		
		
}


/**********************************************
***********************************************
**********��ͷ��50ms��ʱ�ȴ�ϵͳ�ȶ�***********
***********************************************
***********************************************/

//delay_ms(x);x����ת��

void bujin_Z_Init(void)//˳ʱ��
{
	 GPIO_SetBits(GPIOC,GPIO_Pin_0);	
	 GPIO_ResetBits(GPIOC,GPIO_Pin_2);	
	 GPIO_ResetBits(GPIOC,GPIO_Pin_3);
	 GPIO_ResetBits(GPIOC,GPIO_Pin_10);		
	 delay_ms(3);
	
	 GPIO_ResetBits(GPIOC,GPIO_Pin_0);	
	 GPIO_SetBits(GPIOC,GPIO_Pin_2);	
	 GPIO_ResetBits(GPIOC,GPIO_Pin_3);
	 GPIO_ResetBits(GPIOC,GPIO_Pin_10);		
	 delay_ms(3);
	
	 GPIO_ResetBits(GPIOC,GPIO_Pin_0);	
	 GPIO_ResetBits(GPIOC,GPIO_Pin_2);	
	 GPIO_SetBits(GPIOC,GPIO_Pin_3);
	 GPIO_ResetBits(GPIOC,GPIO_Pin_10);		
	 delay_ms(3);
	
	 GPIO_ResetBits(GPIOC,GPIO_Pin_0);	
	 GPIO_ResetBits(GPIOC,GPIO_Pin_2);	
	 GPIO_ResetBits(GPIOC,GPIO_Pin_3);
	 GPIO_SetBits(GPIOC,GPIO_Pin_10);		
	 delay_ms(3);
	
}


void bujin_F_Init(void)//��ʱ��
{
	
	 GPIO_ResetBits(GPIOC,GPIO_Pin_0);	
	 GPIO_ResetBits(GPIOC,GPIO_Pin_2);	
	 GPIO_ResetBits(GPIOC,GPIO_Pin_3);
	 GPIO_SetBits(GPIOC,GPIO_Pin_10);		
	 delay_ms(4);	
	
	 GPIO_ResetBits(GPIOC,GPIO_Pin_0);	
	 GPIO_ResetBits(GPIOC,GPIO_Pin_2);	
	 GPIO_SetBits(GPIOC,GPIO_Pin_3);
	 GPIO_ResetBits(GPIOC,GPIO_Pin_10);		
	 delay_ms(4);
	 
	 GPIO_ResetBits(GPIOC,GPIO_Pin_0);	
	 GPIO_SetBits(GPIOC,GPIO_Pin_2);	
	 GPIO_ResetBits(GPIOC,GPIO_Pin_3);
	 GPIO_ResetBits(GPIOC,GPIO_Pin_10);		
	 delay_ms(4);	

	 GPIO_SetBits(GPIOC,GPIO_Pin_0);	
	 GPIO_ResetBits(GPIOC,GPIO_Pin_2);	
	 GPIO_ResetBits(GPIOC,GPIO_Pin_3);
	 GPIO_ResetBits(GPIOC,GPIO_Pin_10);		
	 delay_ms(4);
}

void bujin_D_Init(void)
{
	 GPIO_ResetBits(GPIOC,GPIO_Pin_0);	
	 GPIO_ResetBits(GPIOC,GPIO_Pin_2);	
	 GPIO_ResetBits(GPIOC,GPIO_Pin_3);
	 GPIO_ResetBits(GPIOC,GPIO_Pin_10);			
}




/*

#include "stm32f10x.h"
#include "bujin.h"
#include "delay.h"



 int main(void)
 {	
	 bujin_Init();
   delay_init();
	 delay_ms(50);//�ȴ�ϵͳ�ȶ�
	 while(1)
	 {
		 
	 
		 bujin_Z_Init();
		 bujin_F_Init();
		 bujin_D_Init();
		 
	}
}





*/

















