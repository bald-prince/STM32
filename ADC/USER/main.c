#include "sys.h"
#include "delay.h"
#include "usart.h"
#include "led.h"
#include "key.h"
#include "usmart.h"
#include "adc.h"
#include "oled.h"

int main(void)
{
	u16 adcx;
	float temp;

	HAL_Init();                   	//��ʼ��HAL��    
	Stm32_Clock_Init(336,8,2,7);  	//����ʱ��,168Mhz  
	delay_init(168);               	//��ʼ����ʱ����
	uart_init(115200);             	//��ʼ��USART
	usmart_dev.init(84); 		        //��ʼ��USMART 
	LED_Init();											//��ʼ��LED	
	KEY_Init();											//��ʼ��KEY
	MY_ADC_Init();                  //��ʼ��ADC1ͨ��5  
	OLED_Init();
	
	
	OLED_ShowString(0,0, "ADC TEST",12);
	OLED_ShowString(60,0,"2020/2/2",12);  
 	OLED_ShowString(0,12,"ATOM@ALIENTEK",12);  
	OLED_ShowString(0,24,"ADC1_CH5_VAL:",12);  
	OLED_ShowString(0,36,"ADC1_CH5_VOL:0.000V",12);  	
	OLED_Refresh_Gram();													//������ʾ��OLED	 
    
	while(1)
	{
		adcx = Get_Adc_Average(ADC_CHANNEL_5,20);    //��ȡͨ��5��ת��ֵ��20��ȡƽ��
		OLED_ShowNum(80,24,adcx,3,12);             	//��ʾADC�������ԭʼֵ
		OLED_Refresh_Gram();						           //������ʾ��OLED	
		
		temp = (float)adcx*(3.3/4096);               //��ȡ�����Ĵ�С����ʵ�ʵ�ѹֵ������3.1111
		adcx = temp;                                 //��ֵ�������ָ�adcx��������ΪadcxΪu16����
		OLED_ShowNum(65,36,adcx,3,12);             //��ʾ��ѹֵ���������֣�3.1111�Ļ������������ʾ3
		OLED_Refresh_Gram();                       //������ʾ��OLED	
		
		temp -= adcx;                                //���Ѿ���ʾ����������ȥ��������С�����֣�����3.1111-3=0.1111
		temp *= 1000;                                //С�����ֳ���1000�����磺0.1111��ת��Ϊ111.1���൱�ڱ�����λС����
		OLED_ShowNum(90,36,temp,3,12);             //��ʾС�����֣�ǰ��ת��Ϊ��������ʾ����������ʾ�ľ���111.
		OLED_Refresh_Gram();                       //������ʾ��OLED	
		LED0 = !LED0;
		delay_ms(250);	
	} 
}

