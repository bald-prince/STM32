#include "wdg.h"

/*******************************************************************************
================================================================================
��ƽ    ̨��stm32f103zet6_sumjessƽ̨
����    д��sumjess
��E-mail  ��1371129880@qq.com
������汾��V2.0
�������¡�2018��09��06��
�������Ϣ�ο����е�ַ��
����    վ��
           https://blog.csdn.net/qq_38351824
           http://www.openedv.com/
           http://www.stmcu.org/
					 http://www.firebbs.cn/forum.php
---------------------------------------------------------------------------------
��dev.env.��MDK5.14�����ϰ汾
��Target  ��stm32f103zet6
��һ���޶���2017/11/09
�ڶ����޶���2018/01/21
�������޶���2018/09/06
��problem ��
    ��1�����ڲ���Ĳ�ȫ�棻
    ��2�����ڽ��Ͳ��ֲ�ȫ�棻
    ��3�����ڻ�����һ����bug��
��direction��
      ��һ����Ŀ����ǰѿ�������ɣ�
��explain ��
      �����Ǹ�������ԭ�ӡ��о�԰���ӡ����ŵ��ӵ��̼Ҹı���ɣ�
      ͬʱΪ�˷���ʹ�ã���Ҳ�Լ�д�˺ܶ�Ŀ⣬���Ż����㷨�ͱ�ʾ��ʽ��
��warning��
      Ŀǰ���������޾��� ��   
---------------------------------------------------------------------------------
û�������Ĵ��룬ֻ�в��ϵķ��ף����һ��Ŭ����
����õ���������㣬��ӭ��ҷ���bug��
================================================================================
********************************************************************************/	
//�������Ź�

//�������Ź�   //Tout=[2^prer)��rlr]/10000s  prer:3λ0-8 rlr:12λ1-4096
void IWDG_Init(u8 prer,u16 rlr)    //IWDG_Init(5,625);//Tout=(2^6*625)/10000s=2s
{	
 	IWDG_WriteAccessCmd(IWDG_WriteAccess_Enable);  //ʹ�ܶԼĴ���IWDG_PR��IWDG_RLR��д����
	IWDG_SetPrescaler(prer);                       //����IWDGԤ��Ƶֵ:����IWDGԤ��ƵֵΪ64
	IWDG_SetReload(rlr);                           //����IWDG��װ��ֵ
	IWDG_ReloadCounter();                          //����IWDG��װ�ؼĴ�����ֵ��װ��IWDG������
	IWDG_Enable();                                 //ʹ��IWDG
}
//ι�������Ź�
void IWDG_Feed(void)
{   
 	IWDG_ReloadCounter();	//���ؼ���ֵ									   
}




/*//һ�㲻��

//����WWDG������������ֵ,Ĭ��Ϊ���. 
u8 WWDG_CNT=0x7f; 
//��ʼ�����ڿ��Ź� 	
//tr   :T[6:0],������ֵ 0-127
//wr   :W[5:0],����ֵ 0-64
//fprer:��Ƶϵ����WDGTB��,�����2λ��Ч 
//Fwwdg=(4096*2^fprer)*(�ϣ�tr-wr   �£�tr-0x3f)/PCLK1(36Mhz)

void WWDG_Init(u8 tr,u8 wr,u32 fprer)//Fwwdg=(4096*2^fprer)*(�ϣ�tr-wr   �£�tr-0x3f)/PCLK1(36Mhz)
{ 
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_WWDG, ENABLE);  //WWDGʱ��ʹ��
	WWDG_CNT=tr&WWDG_CNT;                                 //��ʼ��WWDG_CNT.   
	WWDG_SetPrescaler(fprer);                             //����IWDGԤ��Ƶֵ
	WWDG_SetWindowValue(wr);                              //���ô���ֵ
	WWDG_Enable(WWDG_CNT);	                              //ʹ�ܿ��Ź� ,���� counter .                  
	WWDG_ClearFlag();                                     //�����ǰ�����жϱ�־λ 
	WWDG_NVIC_Init();                                     //��ʼ�����ڿ��Ź� NVIC
	WWDG_EnableIT();                                      //�������ڿ��Ź��ж�
} 
//������WWDG��������ֵ
void WWDG_Set_Counter(u8 cnt)
{
    WWDG_Enable(cnt);//ʹ�ܿ��Ź� ,	���� counter .	 
}

void WWDG_NVIC_Init(void)
{
	NVIC_InitTypeDef NVIC_InitStructure;
	NVIC_InitStructure.NVIC_IRQChannel = WWDG_IRQn;   
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = WWDG_IRQHandler_NVIC_IRQChannelPreemptionPriority;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;	 
  NVIC_InitStructure.NVIC_IRQChannelCmd=ENABLE; 
	NVIC_Init(&NVIC_InitStructure);
}
//���ڿ��Ź��жϷ������
void WWDG_IRQHandler(void)
{
	WWDG_SetCounter(WWDG_CNT);	  //�������˾��,���ڿ��Ź���������λ
	WWDG_ClearFlag();	  //�����ǰ�����жϱ�־λ
}

*/

