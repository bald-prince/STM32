/*

*******************************************************************************
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
********************************************************************************





void IWDG_WriteAccessCmd(uint16_t IWDG_WriteAccess);//ȡ��д������0x5555ʹ��
void IWDG_SetPrescaler(uint8_t IWDG_Prescaler);//����Ԥ��Ƶϵ����дPR
void IWDG_SetReload(uint16_t Reload);//������װ��ֵ��дRLR
void IWDG_ReloadCounter(void);//ι����д0xAAAA��KR
void IWDG_Enable(void);//ʹ�ܿ��Ź���д0xCCCC��KR
FlagStatus IWDG_GetFlagStatus(uint16_t IWDG_FLAG);//״̬����װ��/Ԥ��Ƶ ����


��  ȡ���Ĵ���д������
      IWDG_WriteAccessCmd();
��  ���ö������Ź���Ԥ��Ƶϵ����ȷ��ʱ��:
     IWDG_SetPrescaler();
��  ���ÿ��Ź���װ��ֵ��ȷ�����ʱ��:
    IWDG_SetReload();
��  ʹ�ܿ��Ź�
    IWDG_Enable();
��  Ӧ�ó���ι��:
   IWDG_ReloadCounter();

���ʱ����㣺
   Tout=((4��2^prer) ��rlr) /40 ��M3)







#include "led.h"
#include "delay.h"
#include "key.h"
#include "sys.h"
#include "wdg.h"


 int main(void)
 {		
	delay_init();	    	 //��ʱ������ʼ��	  
 	LED_Init();		  	 //��ʼ����LED���ӵ�Ӳ���ӿ�
	KEY_Init();          //������ʼ��	 
	delay_ms(500);   	 //���˿��õ���
	IWDG_Init(4,625);    //���Ƶ��Ϊ64,����ֵΪ625,���ʱ��Ϊ1s	   
	LED0=0;				 //����LED0
	while(1)
	{
		if(KEY_Scan(0)==WK_UP)
		{
			IWDG_Feed();//���WK_UP����,��ι��
		}
		delay_ms(10);
	};	 
}
  
  
  
  
  
  
  
  
  */
