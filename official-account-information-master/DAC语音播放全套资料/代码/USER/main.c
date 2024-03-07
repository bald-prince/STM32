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

u8 num=0;									//num用于控制输出哪条语音
u8 i=0,j=0,k=0;						//ijk用于控制语音的完整性。只有语音文件完全播放完了ijk的值才会变。

int main(void)
 {	 
 	u8 t=0;	 
	u8 key;
	delay_init();	    	 														//延时函数初始化	  
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);	//设置中断优先级分组为组2：2位抢占优先级，2位响应优先级
	uart_init(115200);	 														//串口初始化为115200
	KEY_Init();			  															//初始化按键程序
 	LED_Init();			     														//LED端口初始化
	usmart_dev.init(72);														//初始化USMART	
 	Adc_Init();		  																//ADC初始化
	Dac1_Init();																		//DAC初始化
  TIM3_Int_Init(11231,0);													//10Khz的计数频率，计数到5000为500ms  
	 
	DAC_SetChannel1Data(DAC_Align_8b_R, 0);//初始值为0	    	      
	while(1)
	{
		t++;
		key=KEY_Scan(0);	
		//按键1按下，对应原子开发板WK_UP按键，播放第一条语音
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
		printf("i= %d \r\nj= %d \r\nk= %d \r\nnum= %d \r\n",i,j,k,num); //打印这些值用于调试 
		if(t==10||key==KEY1_PRES||key==KEY0_PRES) //KEY0/KEY1按下了,或者定时时间到了
		{	  
			
		}	    
	}
 }

