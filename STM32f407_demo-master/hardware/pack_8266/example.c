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
	//NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//����ϵͳ�ж����ȼ�����2
	delay_init(168);  			//��ʼ����ʱ����
	uart_init(115200);		  //��ʼ�����ڲ�����Ϊ115200
	//usart3_init(115200);
	usart3_init(42,115200); //��ʼ������3������Ϊ115200
	LED_Init();							//��ʼ��LED  				
	EXTI_Init();         	  //�ⲿ�жϳ�ʼ��
  //KEY_Init();					  //������ʼ��  
  my_mem_init(SRAMIN);		//��ʼ���ڲ��ڴ�� 
	my_mem_init(SRAMCCM);		//��ʼ��CCM�ڴ�� 
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
		if(USART3_RX_STA&0X8000)		    								//���յ�һ��������
			{ 
				rlen=USART3_RX_STA&0X7FFF;									//�õ����ν��յ������ݳ���
				USART3_RX_BUF[rlen]=0;		  								//��ӽ����� 
				printf("%s",USART3_RX_BUF);									//���͵����� 	
				sprintf((char*)p,"�յ�%d�ֽ�,��������",rlen);//���յ����ֽ��� 		
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
