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




#include "led.h"
#include "delay.h"
#include "sys.h"
#include "usart.h"
#include "remote.h"   


 int main(void)
 { 
	u8 key;
	u8 t=0;	
	u8 *str=0; 	
	delay_init();	    	 //��ʱ������ʼ?
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);// �����ж����ȼ�����2	  
	uart_init(9600);	 	//���ڳ�ʼ��Ϊ9600
	LED_Init();		  		//��ʼ����LED���ӵ�Ӳ���ӿ�
	Remote_Init();			//������ճ�ʼ��	 
 		 	  		    							  
	while(1)
	{
		key=Remote_Scan();	
		if(key)
		{	 
      printf("%d",key);		//��ʾ��ֵ
      printf("%d",RmtCnt);	//��ʾ��������		  
			switch(key)
			{
				case 0:str="ERROR";break;			   //ERROR
				case 162:str="POWER";break;	    //POWER
				case 98:str="UP";break;	    //UP
				case 2:str="PLAY";break;		 //PLAY
				case 226:str="ALIENTEK";break;		 // ALIENTEK    *****************str="ALIENTEK"�ⲿ�ֿ����������********************
				case 194:str="RIGHT";break;	   //RIGHT
				case 34:str="LEFT";break;		  //LEFT
				case 224:str="VOL-";break;		  //VOL-
				case 168:str="DOWN";break;		   //DOWN
				case 144:str="VOL+";break;		    //VOL
				case 104:str="1";break;		  //1
				case 152:str="2";break;	   //2
				case 176:str="3";break;	    //3
				case 48:str="4";break;		    //4
				case 24:str="5";break;		    //5
				case 122:str="6";break;		  //6
				case 16:str="7";break;			//7	
				case 56:str="8";break;	 //8
				case 90:str="9";break;//9
				case 66:str="0";break;//0
				case 82:str="DELETE";break;		 //DELETE
			}
		}else delay_ms(10);	  
		t++;
		if(t==20)
		{
			t=0;
			LED0=!LED0;
		}
	}
}










*/









