#include "led.h"
#include "delay.h"
#include "key.h"
#include "sys.h"
#include "lcd.h"
#include "usart.h"	 	 
#include "dac.h"
#include "adc.h"
#include "usmart.h"
#include "timer.h"

u8 num=0;									//num���ڿ��������������
u8 i=0,j=0,k=0;						//ijk���ڿ��������������ԡ�ֻ�������ļ���ȫ��������ijk��ֵ�Ż�䡣

int main(void)
 {	 
 	u8 t=0;	 
	u8 key;
	delay_init();	    	 														//��ʱ������ʼ��	  
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);	//�����ж����ȼ�����Ϊ��2��2λ��ռ���ȼ���2λ��Ӧ���ȼ�
	uart_init(115200);	 														//���ڳ�ʼ��Ϊ115200
	KEY_Init();			  															//��ʼ����������
 	LED_Init();			     														//LED�˿ڳ�ʼ��
	usmart_dev.init(72);														//��ʼ��USMART	
 	Adc_Init();		  																//ADC��ʼ��
	Dac1_Init();																		//DAC��ʼ��
  TIM3_Int_Init(11231,0);													//10Khz�ļ���Ƶ�ʣ�������5000Ϊ500ms  
	 
	DAC_SetChannel1Data(DAC_Align_8b_R, 0);//��ʼֵΪ0	    	      
	while(1)
	{
		t++;
		key=KEY_Scan(0);	
		//����1���£���Ӧԭ�ӿ�����WK_UP���������ŵ�һ������
    if(key==WKUP_PRES&&i==0)
    {
      num=1; 
		  TIM_ITConfig(TIM3, TIM_IT_Update, ENABLE);
			TIM_Cmd(TIM3, ENABLE);
			DAC_Cmd(DAC_Channel_1, ENABLE);
    }
		else if(key==KEY1_PRES&&j==0)
		{
			num=2; 
			TIM_ITConfig(TIM3, TIM_IT_Update, ENABLE);
			TIM_Cmd(TIM3, ENABLE);
			DAC_Cmd(DAC_Channel_1, ENABLE);
    }
		else if (key==KEY2_PRES&&k==0)
		{
			num=3; 
			TIM_ITConfig(TIM3, TIM_IT_Update, ENABLE);
			TIM_Cmd(TIM3, ENABLE);
			DAC_Cmd(DAC_Channel_1, ENABLE);
		}
		printf("i= %d \r\nj= %d \r\nk= %d \r\nnum= %d \r\n",i,j,k,num); //��ӡ��Щֵ���ڵ��� 
		if(t==10||key==KEY1_PRES||key==KEY0_PRES) //KEY0/KEY1������,���߶�ʱʱ�䵽��
		{	  
			
		}	    
	}
 }

