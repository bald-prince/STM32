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
 ALIENTEK 探索者STM32F407开发板 实验21
 DAC实验-HAL库函数版
 技术支持：www.openedv.com
 淘宝店铺：http://eboard.taobao.com 
 关注微信公众平台微信号："正点原子"，免费获取STM32资料。
 广州市星翼电子科技有限公司  
 作者：正点原子 @ALIENTEK
************************************************/

int main(void)
{
  u16 adcx;
	float temp;
 	u8 t=0;	 
	u16 dacval=0;
	u8 key;	
	
  HAL_Init();                   	//初始化HAL库    
  Stm32_Clock_Init(336,8,2,7);  	//设置时钟,168Mhz
	delay_init(168);               	//初始化延时函数
	uart_init(115200);             	//初始化USART
	usmart_dev.init(84); 		    //初始化USMART
	LED_Init();						//初始化LED	
	KEY_Init();						//初始化KEY
	MY_ADC_Init();                  //初始化ADC1
  DAC1_Init();                    //初始化DAC1
	OLED_Init();	
	
	OLED_ShowString(0,0, "ADC TEST",12);
	OLED_ShowString(60,0,"2020/2/3",12);  
 	OLED_ShowString(0,12,"WK_UP:+  KEY1:-",12);  
	OLED_ShowString(0,24,"DAC VAL:",12);  
	OLED_ShowString(0,36,"DAC VOL:  0.000V",12);  
	OLED_ShowString(0,48,"ADC VOL:  0.000V",12); 
	OLED_Refresh_Gram();//更新显示到OLED	 
    
  HAL_DAC_SetValue(&DAC1_Handler,DAC_CHANNEL_1,DAC_ALIGN_12B_R,0);//初始值为0 	
  while(1)
	{
		t++;
		key=KEY_Scan(0);			  
		if(key==WEKEUP_PRES)
		{		 
			if(dacval<4000)
				dacval+=200;
			HAL_DAC_SetValue(&DAC1_Handler,DAC_CHANNEL_1,DAC_ALIGN_12B_R,dacval);//设置DAC值
		}else if(key==2)	
		{
			if(dacval>200)dacval-=200;
			else 
				dacval=0;
      HAL_DAC_SetValue(&DAC1_Handler,DAC_CHANNEL_1,DAC_ALIGN_12B_R,dacval);//设置DAC值
		}	 
		if(t==10||key==KEY1_PRES||key==WEKEUP_PRES) 	    //WKUP/KEY1按下了,或者定时时间到了
		{	  
      adcx=HAL_DAC_GetValue(&DAC1_Handler,DAC_CHANNEL_1);//读取前面设置DAC的值
			OLED_ShowNum(60,24,adcx,4,12); 
			OLED_Refresh_Gram();//更新显示到OLED     	    //显示DAC寄存器值
			temp=(float)adcx*(3.3/4096);			    //得到DAC电压值
			adcx=temp;
 			OLED_ShowNum(48,36,temp,3,12); 
			OLED_Refresh_Gram();//更新显示到OLED    	    //显示电压值整数部分
 			temp-=adcx;
			temp*=1000;
			OLED_ShowNum(72,36,temp,3,12); 
			OLED_Refresh_Gram();//更新显示到OLED 	    //显示电压值的小数部分
 			adcx=Get_Adc_Average(ADC_CHANNEL_5,10);     //得到ADC转换值	  
			temp=(float)adcx*(3.3/4096);			    //得到ADC电压值
			adcx=temp;
 			OLED_ShowNum(48,48,temp,3,12); 
			OLED_Refresh_Gram();//更新显示到OLED    	    //显示电压值整数部分
 			temp-=adcx;
			temp*=1000;
			OLED_ShowNum(72,48,temp,3,12); 
			OLED_Refresh_Gram();//更新显示到OLED 	    //显示电压值的小数部分
			LED0=!LED0;	   
			t=0;
		}	    
		delay_ms(10);	
	}
}

