#include "sys.h"
#include "delay.h"
#include "usart.h"
#include "led.h"
#include "key.h"
#include "usmart.h"
#include "dma.h"
#include "oled.h"


#define SEND_BUF_SIZE 8200	//发送数据长度,最好等于sizeof(TEXT_TO_SEND)+2的整数倍.

u8 SendBuff[SEND_BUF_SIZE]; //发送数据缓冲区
const u8 TEXT_TO_SEND[]={"ALIENTEK Explorer STM32F4 DMA 串口实验"}; 

int main(void)
{
	u16 i;
	u8 t = 0;
	u8 j,mask = 0;
	float pro = 0; 
	
  HAL_Init();                   	//初始化HAL库    
  Stm32_Clock_Init(336,8,2,7);  	//设置时钟,168Mhz
	delay_init(168);               	//初始化延时函数
	uart_init(115200);             	//初始化USART
	usmart_dev.init(84); 		        //初始化USMART
	LED_Init();						          //初始化LED	
	KEY_Init();						          //初始化KEY
	OLED_Init();

  MYDMA_Config(DMA2_Stream7,DMA_CHANNEL_4);//初始化DMA
	
	OLED_ShowString(0,0,"Explorer STM32F4",16);  
	OLED_ShowString(0,16, "DMA TEST",12);  
 	OLED_ShowString(0,26,"ATOM@ALIENTEK",12);  
 	OLED_ShowString(0,36,"2020/1/29",12);  
 	OLED_ShowString(64,36,"S3:Start",12);  
	OLED_Refresh_Gram();                    //更新显示到OLED	
	
	j = sizeof(TEXT_TO_SEND);	   
	for(i = 0;i < SEND_BUF_SIZE;i++)        //填充ASCII字符集数据
  {
		if(t>=j)//加入换行符
		{
			if(mask)
			{
				SendBuff[i] = 0x0a;
				t = 0;
			}
			else 
			{
				SendBuff[i] = 0x0d;
				mask++;
			}	
		}
		else                                  //复制TEXT_TO_SEND语句
		{
			mask = 0;
			SendBuff[i] = TEXT_TO_SEND[t];
			t++;
		}   	   
  }   
	i=0;
  while(1)
	{
    t = KEY_Scan(0);
		if(t == KEY0_PRES)  //KEY0按下
		{
			printf("\r\nDMA DATA:\r\n"); 	
			OLED_ShowString(0,50,"Start Transimit....",12);  
			OLED_ShowString(100,50,"   %",12);
			OLED_Refresh_Gram();			
			HAL_UART_Transmit_DMA(&UART1_Handler,SendBuff,SEND_BUF_SIZE);//启动传输
			//使能串口1的DMA发送 
			//等待DMA传输完成，此时我们来做另外一些事，点灯
		  //实际应用中，传输数据期间，可以执行另外的任务
		  while(1)
		  {
				if(__HAL_DMA_GET_FLAG(&UART1TxDMA_Handler,DMA_FLAG_TCIF3_7))//等待DMA2_Steam7传输完成
        {
          __HAL_DMA_CLEAR_FLAG(&UART1TxDMA_Handler,DMA_FLAG_TCIF3_7);//清除DMA2_Steam7传输完成标志
          HAL_UART_DMAStop(&UART1_Handler);      //传输完成以后关闭串口DMA
					break; 
        }
				pro = __HAL_DMA_GET_COUNTER(&UART1TxDMA_Handler);//得到当前还剩余多少个数据
				pro = 1-pro/SEND_BUF_SIZE;    //得到百分比	  
				pro *= 100;      			    //扩大100倍
				OLED_ShowNum(98,50,pro,3,12);	
				OLED_Refresh_Gram();								
		  }
			OLED_ShowNum(30,50,100,3,12);//显示100%	  
		  OLED_ShowString(0,56,"Transimit Finished!",12);//提示传送完成
			OLED_Refresh_Gram();
		}
		i++;
		delay_ms(10);
		if(i == 20)
		{
			LED0 =! LED0;//提示系统正在运行	
			i = 0;
		}		   
	}
}

