#include "sys.h"
#include "delay.h"
#include "usart.h"
#include "led.h"
#include "key.h"
#include "usmart.h"
#include "adc.h"
#include "dac.h"
#include "oled.h"
/************************************************
 ALIENTEK ̽����STM32F407������ ʵ��21
 DACʵ��-HAL�⺯����
 ����֧�֣�www.openedv.com
 �Ա����̣�http://eboard.taobao.com 
 ��ע΢�Ź���ƽ̨΢�źţ�"����ԭ��"����ѻ�ȡSTM32���ϡ�
 ������������ӿƼ����޹�˾  
 ���ߣ�����ԭ�� @ALIENTEK
************************************************/

int main(void)
{
  u16 adcx;
	float temp;
 	u8 t=0;	 
	u16 dacval=0;
	u8 key;	
	
  HAL_Init();                   	//��ʼ��HAL��    
  Stm32_Clock_Init(336,8,2,7);  	//����ʱ��,168Mhz
	delay_init(168);               	//��ʼ����ʱ����
	uart_init(115200);             	//��ʼ��USART
	usmart_dev.init(84); 		    //��ʼ��USMART
	LED_Init();						//��ʼ��LED	
	KEY_Init();						//��ʼ��KEY
	MY_ADC_Init();                  //��ʼ��ADC1
  DAC1_Init();                    //��ʼ��DAC1
	OLED_Init();	
	
	OLED_ShowString(0,0, "ADC TEST",12);
	OLED_ShowString(60,0,"2020/2/3",12);  
 	OLED_ShowString(0,12,"WK_UP:+  KEY1:-",12);  
	OLED_ShowString(0,24,"DAC VAL:",12);  
	OLED_ShowString(0,36,"DAC VOL:  0.000V",12);  
	OLED_ShowString(0,48,"ADC VOL:  0.000V",12); 
	OLED_Refresh_Gram();//������ʾ��OLED	 
    
  HAL_DAC_SetValue(&DAC1_Handler,DAC_CHANNEL_1,DAC_ALIGN_12B_R,0);//��ʼֵΪ0 	
  while(1)
	{
		t++;
		key=KEY_Scan(0);			  
		if(key==WEKEUP_PRES)
		{		 
			if(dacval<4000)
				dacval+=200;
			HAL_DAC_SetValue(&DAC1_Handler,DAC_CHANNEL_1,DAC_ALIGN_12B_R,dacval);//����DACֵ
		}else if(key==2)	
		{
			if(dacval>200)dacval-=200;
			else 
				dacval=0;
      HAL_DAC_SetValue(&DAC1_Handler,DAC_CHANNEL_1,DAC_ALIGN_12B_R,dacval);//����DACֵ
		}	 
		if(t==10||key==KEY1_PRES||key==WEKEUP_PRES) 	    //WKUP/KEY1������,���߶�ʱʱ�䵽��
		{	  
      adcx=HAL_DAC_GetValue(&DAC1_Handler,DAC_CHANNEL_1);//��ȡǰ������DAC��ֵ
			OLED_ShowNum(60,24,adcx,4,12); 
			OLED_Refresh_Gram();//������ʾ��OLED     	    //��ʾDAC�Ĵ���ֵ
			temp=(float)adcx*(3.3/4096);			    //�õ�DAC��ѹֵ
			adcx=temp;
 			OLED_ShowNum(48,36,temp,3,12); 
			OLED_Refresh_Gram();//������ʾ��OLED    	    //��ʾ��ѹֵ��������
 			temp-=adcx;
			temp*=1000;
			OLED_ShowNum(72,36,temp,3,12); 
			OLED_Refresh_Gram();//������ʾ��OLED 	    //��ʾ��ѹֵ��С������
 			adcx=Get_Adc_Average(ADC_CHANNEL_5,10);     //�õ�ADCת��ֵ	  
			temp=(float)adcx*(3.3/4096);			    //�õ�ADC��ѹֵ
			adcx=temp;
 			OLED_ShowNum(48,48,temp,3,12); 
			OLED_Refresh_Gram();//������ʾ��OLED    	    //��ʾ��ѹֵ��������
 			temp-=adcx;
			temp*=1000;
			OLED_ShowNum(72,48,temp,3,12); 
			OLED_Refresh_Gram();//������ʾ��OLED 	    //��ʾ��ѹֵ��С������
			LED0=!LED0;	   
			t=0;
		}	    
		delay_ms(10);	
	}
}

