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

	HAL_Init();                   	//初始化HAL库    
	Stm32_Clock_Init(336,8,2,7);  	//设置时钟,168Mhz  
	delay_init(168);               	//初始化延时函数
	uart_init(115200);             	//初始化USART
	usmart_dev.init(84); 		        //初始化USMART 
	LED_Init();											//初始化LED	
	KEY_Init();											//初始化KEY
	MY_ADC_Init();                  //初始化ADC1通道5  
	OLED_Init();
	
	
	OLED_ShowString(0,0, "ADC TEST",12);
	OLED_ShowString(60,0,"2020/2/2",12);  
 	OLED_ShowString(0,12,"ATOM@ALIENTEK",12);  
	OLED_ShowString(0,24,"ADC1_CH5_VAL:",12);  
	OLED_ShowString(0,36,"ADC1_CH5_VOL:0.000V",12);  	
	OLED_Refresh_Gram();													//更新显示到OLED	 
    
	while(1)
	{
		adcx = Get_Adc_Average(ADC_CHANNEL_5,20);    //获取通道5的转换值，20次取平均
		OLED_ShowNum(80,24,adcx,3,12);             	//显示ADC采样后的原始值
		OLED_Refresh_Gram();						           //更新显示到OLED	
		
		temp = (float)adcx*(3.3/4096);               //获取计算后的带小数的实际电压值，比如3.1111
		adcx = temp;                                 //赋值整数部分给adcx变量，因为adcx为u16整形
		OLED_ShowNum(65,36,adcx,3,12);             //显示电压值的整数部分，3.1111的话，这里就是显示3
		OLED_Refresh_Gram();                       //更新显示到OLED	
		
		temp -= adcx;                                //把已经显示的整数部分去掉，留下小数部分，比如3.1111-3=0.1111
		temp *= 1000;                                //小数部分乘以1000，例如：0.1111就转换为111.1，相当于保留三位小数。
		OLED_ShowNum(90,36,temp,3,12);             //显示小数部分（前面转换为了整形显示），这里显示的就是111.
		OLED_Refresh_Gram();                       //更新显示到OLED	
		LED0 = !LED0;
		delay_ms(250);	
	} 
}

