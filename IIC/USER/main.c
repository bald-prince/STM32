#include "sys.h"
#include "delay.h"
#include "usart.h"
#include "led.h"
#include "key.h"

#include "usmart.h"
#include "24cxx.h"
#include "oled.h"


//Ҫд�뵽24c02���ַ�������
const u8 TEXT_Buffer[]={"Explorer STM32F4 IIC TEST"};
#define SIZE sizeof(TEXT_Buffer)

int main(void)
{
  u8 key;
	u16 i=0;
	u8 datatemp[SIZE];	 
	
  HAL_Init();                   	//��ʼ��HAL��    
  SystemClock_Config();  	        //����ʱ��,168Mhz
	delay_init(168);               	//��ʼ����ʱ����
	uart_init(115200);             	//��ʼ��USART
	usmart_dev.init(84); 		    //��ʼ��USMART
	LED_Init();						      //��ʼ��LED	
	KEY_Init();						    //��ʼ��KEY
	OLED_Init();
	
	AT24CXX_Init();				    //��ʼ��IIC 
	
	while(AT24CXX_Check())   //��ⲻ��24c02
	{
		delay_ms(500);
		LED0 = !LED0;
	}
  
	while(1)
	{
		key = KEY_Scan(0);
		if(key == KEY0_PRES)//KEY1����,д��24C02
		{
			AT24CXX_Write(0,(u8*)TEXT_Buffer,SIZE);
			LED1 = !LED1;
		}
		if(key == WEKEUP_PRES )//KEY0����,��ȡ�ַ�������ʾ
		{
			AT24CXX_Read(0,datatemp,SIZE);
			LED2= !LED2;
		}
		i++;
		delay_ms(10);
		if(i == 20)
		{
			LED3 = !LED3;//��ʾϵͳ��������	
			i = 0;
		}	
			IIC_Send_Byte(1);
	} 
}

