#include "sys.h"
#include "delay.h"
#include "usart.h"
#include "led.h"
#include "key.h"

#include "usmart.h"
#include "24cxx.h"
#include "oled.h"


//要写入到24c02的字符串数组
const u8 TEXT_Buffer[]={"Explorer STM32F4 IIC TEST"};
#define SIZE sizeof(TEXT_Buffer)

int main(void)
{
  u8 key;
	u16 i=0;
	u8 datatemp[SIZE];	 
	
  HAL_Init();                   	//初始化HAL库    
  SystemClock_Config();  	        //设置时钟,168Mhz
	delay_init(168);               	//初始化延时函数
	uart_init(115200);             	//初始化USART
	usmart_dev.init(84); 		    //初始化USMART
	LED_Init();						      //初始化LED	
	KEY_Init();						    //初始化KEY
	OLED_Init();
	
	AT24CXX_Init();				    //初始化IIC 
	
	while(AT24CXX_Check())   //检测不到24c02
	{
		delay_ms(500);
		LED0 = !LED0;
	}
  
	while(1)
	{
		key = KEY_Scan(0);
		if(key == KEY0_PRES)//KEY1按下,写入24C02
		{
			AT24CXX_Write(0,(u8*)TEXT_Buffer,SIZE);
			LED1 = !LED1;
		}
		if(key == WEKEUP_PRES )//KEY0按下,读取字符串并显示
		{
			AT24CXX_Read(0,datatemp,SIZE);
			LED2= !LED2;
		}
		i++;
		delay_ms(10);
		if(i == 20)
		{
			LED3 = !LED3;//提示系统正在运行	
			i = 0;
		}	
			IIC_Send_Byte(1);
	} 
}

