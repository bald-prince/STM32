/*

#include "led.h"
#include "delay.h"
#include "key.h"
#include "sys.h"
#include "lcd.h"
#include "usart.h"	 
#include "dht11.h" 	
 
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


 
 int main(void)
 {	 
	u8 t=0;			    
	u8 temperature;  	    
	u8 humidity;    	   

	delay_init();	    	 //��ʱ������ʼ��	  
  NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//�����ж����ȼ�����Ϊ��2��2λ��ռ���ȼ���2λ��Ӧ���ȼ�
	uart_init(115200);	 	//���ڳ�ʼ��Ϊ115200
	LED_Init();		  		//��ʼ����LED���ӵ�Ӳ���ӿ�
	LCD_Init();			   	//��ʼ��LCD  
 	POINT_COLOR=RED;		//��������Ϊ��ɫ 
	LCD_ShowString(30,50,200,16,16,"WarShip STM32");	
	LCD_ShowString(30,70,200,16,16,"DHT11 TEST");	
	LCD_ShowString(30,90,200,16,16,"ATOM@ALIENTEK");
	LCD_ShowString(30,110,200,16,16,"2015/1/16");		  
 	while(DHT11_Init())	//DHT11��ʼ��	
	{
		LCD_ShowString(30,130,200,16,16,"DHT11 Error");
		delay_ms(200);
		LCD_Fill(30,130,239,130+16,WHITE);
 		delay_ms(200);
	}								   
	LCD_ShowString(30,130,200,16,16,"DHT11 OK");
	POINT_COLOR=BLUE;//��������Ϊ��ɫ 
 	LCD_ShowString(30,150,200,16,16,"Temp:  C");	 
 	LCD_ShowString(30,170,200,16,16,"Humi:  %");	 
	while(1)
	{	    	    
 		if(t%10==0)			//ÿ100ms��ȡһ��
		{									  
			DHT11_Read_Data(&temperature,&humidity);	//��ȡ��ʪ��ֵ					    
			LCD_ShowNum(30+40,150,temperature,2,16);	//��ʾ�¶�	   		   
			LCD_ShowNum(30+40,170,humidity,2,16);		//��ʾʪ��	 	   
		}				   
	 	delay_ms(10);
		t++;
		if(t==20)
		{
			t=0;
			LED0=!LED0;
		}
	}
}

               */


