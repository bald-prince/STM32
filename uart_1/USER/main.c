#include "sys.h"
#include "delay.h"
#include "usart.h"
#include "led.h"
#include "key.h"
#include "string.h"

int main(void)
{
	u8 len;	
	u16 t;
	char cmd[200];
	u16 times=0; 

  HAL_Init();                    	//初始化HAL库    
  Stm32_Clock_Init(336,8,2,7);  	//设置时钟,168Mhz
	delay_init(168);               	//初始化延时函数
	uart_init(115200);              //初始化USART
	LED_Init();											//初始化LED	
  KEY_Init();                     //初始化按键
	
	printf("开灯：led_on\r\n");
	printf("关灯：led_off\r\n");
	
  while(1)
  {
		if( USART_RX_STA & 0x8000 )
		{
			len = USART_RX_STA & 0x3FFF;
			for(t = 0;t < len;t++)
			{
				cmd[t] = USART_RX_BUF[t];
				while( (USART1->SR&0X40) == 0);
			}
			printf("%c",cmd);
			USART_RX_STA = 0;
		}
		if( !(strcmp(cmd,"led_on")) )               //判断strcmp中两个字符是否相等
		{
			LED0 = 0;
			memset( cmd,0,strlen(cmd) );               //清除cmd[]
		}
		else if( !(strcmp(cmd,"led_off")) )
		{
			LED0 = 1;
			memset( cmd,0,strlen(cmd) );               //清除cmd[]
		}
		else 
		{
			printf("\r\n input error \r\n");
			delay_ms(100);
		}
			memset( cmd,0,strlen(cmd) );               //清除cmd[]
	}
	/*	if( USART_RX_STA & 0x8000 )
		{	
			len = USART_RX_STA&0x3fff;																							//得到此次接收到的数据长度
			printf("\r\n您发送的消息为:\r\n");
			for(t = 0;t < len;t++)
      {
				USART1->DR = USART_RX_BUF[t];
        while( (USART1->SR&0x40) == 0 );                                        //等待发送完成	
      }
			printf("\r\n\r\n");																										  //插入换行
			USART_RX_STA = 0;
		}
    else
			LED0 =! LED0;																						               //闪烁LED,提示系统正在运行.
			delay_ms(200);   */
		/*if(USART_RX_STA&0x8000)
		{					  
			len=USART_RX_STA&0x3fff;//得到此次接收到的数据长度
			printf("\r\n您发送的消息为:\r\n");
			HAL_UART_Transmit(&UART1_Handler,(uint8_t*)USART_RX_BUF,len,1000);	//发送接收到的数据
			while(__HAL_UART_GET_FLAG(&UART1_Handler,UART_FLAG_TC)!=SET);		//等待发送结束
			printf("\r\n\r\n");//插入换行
			USART_RX_STA=0;
		}else
		{
			times++;
			if(times%5000==0)
			{
				printf("\r\n江西科技师范大学\r\n");
				printf("通信与电子学院\r\n\r\n\r\n");
			}
			if(times%200==0)printf("请输入数据,以回车键结束\r\n");  
			if(times%30==0)LED0=!LED0;//闪烁LED,提示系统正在运行.
			delay_ms(10);   
		} */
  }


