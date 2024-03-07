#include "sys.h"
#include "delay.h"
#include "usart.h"
#include "usart3.h"
#include "common.h" 
#include "malloc.h"  
#include "key.h"  
#include "led.h"
#include "timer.h"
#include "exti.h"
u8 key_buf;
int main()
{
	u8 rlen,*p;
  HAL_Init();
  Stm32_Clock_Init(336,8,2,7); 
	//NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//设置系统中断优先级分组2
	delay_init(168);  			//初始化延时函数
	uart_init(115200);		  //初始化串口波特率为115200
	//usart3_init(115200);
	usart3_init(42,115200); //初始化串口3波特率为115200
	LED_Init();							//初始化LED  				
	EXTI_Init();         	  //外部中断初始化
  //KEY_Init();					  //按键初始化  
  my_mem_init(SRAMIN);		//初始化内部内存池 
	my_mem_init(SRAMCCM);		//初始化CCM内存池 
	key_buf = 0;
 
	//atk_8266_test();
	while(!key_buf)
	{
		check_wifi();
		Mode_Choose(key_buf);
		LED1 = !LED1;
	} 
	AP_STA_mode_set();
	AP_STA_MSG();
	while(1)
	{
		if(key_buf == 2)
		esp_8266_send(9);
	  usart_recive_esp();
		/*	
		p=mymalloc(SRAMIN,100);
		if(USART3_RX_STA&0X8000)		    								//接收到一次数据了
			{ 
				rlen=USART3_RX_STA&0X7FFF;									//得到本次接收到的数据长度
				USART3_RX_BUF[rlen]=0;		  								//添加结束符 
				printf("%s",USART3_RX_BUF);									//发送到串口 	
				sprintf((char*)p,"收到%d字节,内容如下",rlen);//接收到的字节数 		
				 GPIOC->ODR = (u8)USART3_RX_BUF[11];
				USART3_RX_STA=0;
			}	
		*/
	  myfree(SRAMIN,p);
		usart_msg_cmt();
		GPIOC->ODR = (u8)USART3_RX_BUF[11];
		//LED0 = !LED0;
	}
	
}
