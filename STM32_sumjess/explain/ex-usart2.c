/*
*******************************************************************************
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
********************************************************************************
http://blog.csdn.net/liukais/article/details/53926768
http://blog.csdn.net/ybhuangfugui/article/details/51308289
#include "led.h"
#include "delay.h"
#include "sys.h"
#include "sumjess_USART2.h"

 int main(void)
 {	
	u8 t;
	u8 len;	
	u16 times=0; 
 
	delay_init();	    	 //��ʱ������ʼ��	
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);// �����ж����ȼ�����2
	USART2_Init(9600);	 //���ڳ�ʼ��Ϊ9600
	LED_Init();		  	 //��ʼ����LED���ӵ�Ӳ���ӿ� 
 
	while(1)
	{
		if(USART2_RX_STA&0x8000)//һ�ν������
		{	
			len=USART2_RX_STA&0x3fff;//�õ��˴ν��յ������ݳ���
			printf("\r\n�����͵���ϢΪ:\r\n");
			for(t=0;t<len;t++)
			{
				USART2->DR=USART2_RX_BUF[t];//�򴮿�2��������
				while((USART2->SR&0X40)==0);//�ȴ����ͽ���
			}
			printf("\r\n\r\n");//���뻻��
			USART2_RX_STA=0;//����
		}else
		{
			times++;
			if(times%1000==1)
			{
				printf("\r\nsumjess ������ ����ʵ��\r\n");
				printf("���ͣ�https://blog.csdn.net/qq_38351824\r\n\r\n\r\n");
			}
			if(times%200==0)printf("����������,�Իس�������\r\n");  
			if(times%30==0)LED0=!LED0;//��˸LED,��ʾϵͳ��������.
			delay_ms(10);   
		}
	}	 
}


���������ڷ������ݣ�����

sprintf(send,"value=%5.3f",value);
for (i = 0; send[i] != 0; i++) 
{
  USART_SendData(USART2,send[i]);
  delay_ms(5);			//����ʱ����ȷ�������ܹ������ͳ�ȥ
} 



���������ڽ������ݣ�����

#include <math.h>


		if(USART2_RX_STA&0x8000)//һ�ν������
		{	
			len=USART2_RX_STA&0x3fff;//�õ��˴ν��յ������ݳ���
			printf("\r\n�����͵���ϢΪ:\r\n");
			for(t=0;t<len;t++)
			{
				USART2->DR=USART2_RX_BUF[t];//�򴮿�2��������
				while((USART2->SR&0X40)==0);//�ȴ����ͽ���
				if(USART2_RX_BUF[t]==32) USART2_RX_BUF[t]=48;
				 x=x+(USART2_RX_BUF[t]-48)*pow(10,(len-t-1));printf("---%d++++",x);
			}
	  x=0;
    delay_ms(5);			//����ʱ����ȷ�������ܹ������ͳ�ȥ
		USART2_RX_STA=0;//����
		}
















*/



