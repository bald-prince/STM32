#include "sys.h"
#include "delay.h"
#include "usart.h"
#include "led.h"
#include "key.h"
#include "usmart.h"
#include "dma.h"
#include "oled.h"


#define SEND_BUF_SIZE 8200	//�������ݳ���,��õ���sizeof(TEXT_TO_SEND)+2��������.

u8 SendBuff[SEND_BUF_SIZE]; //�������ݻ�����
const u8 TEXT_TO_SEND[]={"ALIENTEK Explorer STM32F4 DMA ����ʵ��"}; 

int main(void)
{
	u16 i;
	u8 t = 0;
	u8 j,mask = 0;
	float pro = 0; 
	
  HAL_Init();                   	//��ʼ��HAL��    
  Stm32_Clock_Init(336,8,2,7);  	//����ʱ��,168Mhz
	delay_init(168);               	//��ʼ����ʱ����
	uart_init(115200);             	//��ʼ��USART
	usmart_dev.init(84); 		        //��ʼ��USMART
	LED_Init();						          //��ʼ��LED	
	KEY_Init();						          //��ʼ��KEY
	OLED_Init();

  MYDMA_Config(DMA2_Stream7,DMA_CHANNEL_4);//��ʼ��DMA
	
	OLED_ShowString(0,0,"Explorer STM32F4",16);  
	OLED_ShowString(0,16, "DMA TEST",12);  
 	OLED_ShowString(0,26,"ATOM@ALIENTEK",12);  
 	OLED_ShowString(0,36,"2020/1/29",12);  
 	OLED_ShowString(64,36,"S3:Start",12);  
	OLED_Refresh_Gram();                    //������ʾ��OLED	
	
	j = sizeof(TEXT_TO_SEND);	   
	for(i = 0;i < SEND_BUF_SIZE;i++)        //���ASCII�ַ�������
  {
		if(t>=j)//���뻻�з�
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
		else                                  //����TEXT_TO_SEND���
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
		if(t == KEY0_PRES)  //KEY0����
		{
			printf("\r\nDMA DATA:\r\n"); 	
			OLED_ShowString(0,50,"Start Transimit....",12);  
			OLED_ShowString(100,50,"   %",12);
			OLED_Refresh_Gram();			
			HAL_UART_Transmit_DMA(&UART1_Handler,SendBuff,SEND_BUF_SIZE);//��������
			//ʹ�ܴ���1��DMA���� 
			//�ȴ�DMA������ɣ���ʱ������������һЩ�£����
		  //ʵ��Ӧ���У����������ڼ䣬����ִ�����������
		  while(1)
		  {
				if(__HAL_DMA_GET_FLAG(&UART1TxDMA_Handler,DMA_FLAG_TCIF3_7))//�ȴ�DMA2_Steam7�������
        {
          __HAL_DMA_CLEAR_FLAG(&UART1TxDMA_Handler,DMA_FLAG_TCIF3_7);//���DMA2_Steam7������ɱ�־
          HAL_UART_DMAStop(&UART1_Handler);      //��������Ժ�رմ���DMA
					break; 
        }
				pro = __HAL_DMA_GET_COUNTER(&UART1TxDMA_Handler);//�õ���ǰ��ʣ����ٸ�����
				pro = 1-pro/SEND_BUF_SIZE;    //�õ��ٷֱ�	  
				pro *= 100;      			    //����100��
				OLED_ShowNum(98,50,pro,3,12);	
				OLED_Refresh_Gram();								
		  }
			OLED_ShowNum(30,50,100,3,12);//��ʾ100%	  
		  OLED_ShowString(0,56,"Transimit Finished!",12);//��ʾ�������
			OLED_Refresh_Gram();
		}
		i++;
		delay_ms(10);
		if(i == 20)
		{
			LED0 =! LED0;//��ʾϵͳ��������	
			i = 0;
		}		   
	}
}

