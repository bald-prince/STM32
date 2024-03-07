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

  HAL_Init();                    	//��ʼ��HAL��    
  Stm32_Clock_Init(336,8,2,7);  	//����ʱ��,168Mhz
	delay_init(168);               	//��ʼ����ʱ����
	uart_init(115200);              //��ʼ��USART
	LED_Init();											//��ʼ��LED	
  KEY_Init();                     //��ʼ������
	
	printf("���ƣ�led_on\r\n");
	printf("�صƣ�led_off\r\n");
	
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
		if( !(strcmp(cmd,"led_on")) )               //�ж�strcmp�������ַ��Ƿ����
		{
			LED0 = 0;
			memset( cmd,0,strlen(cmd) );               //���cmd[]
		}
		else if( !(strcmp(cmd,"led_off")) )
		{
			LED0 = 1;
			memset( cmd,0,strlen(cmd) );               //���cmd[]
		}
		else 
		{
			printf("\r\n input error \r\n");
			delay_ms(100);
		}
			memset( cmd,0,strlen(cmd) );               //���cmd[]
	}
	/*	if( USART_RX_STA & 0x8000 )
		{	
			len = USART_RX_STA&0x3fff;																							//�õ��˴ν��յ������ݳ���
			printf("\r\n�����͵���ϢΪ:\r\n");
			for(t = 0;t < len;t++)
      {
				USART1->DR = USART_RX_BUF[t];
        while( (USART1->SR&0x40) == 0 );                                        //�ȴ��������	
      }
			printf("\r\n\r\n");																										  //���뻻��
			USART_RX_STA = 0;
		}
    else
			LED0 =! LED0;																						               //��˸LED,��ʾϵͳ��������.
			delay_ms(200);   */
		/*if(USART_RX_STA&0x8000)
		{					  
			len=USART_RX_STA&0x3fff;//�õ��˴ν��յ������ݳ���
			printf("\r\n�����͵���ϢΪ:\r\n");
			HAL_UART_Transmit(&UART1_Handler,(uint8_t*)USART_RX_BUF,len,1000);	//���ͽ��յ�������
			while(__HAL_UART_GET_FLAG(&UART1_Handler,UART_FLAG_TC)!=SET);		//�ȴ����ͽ���
			printf("\r\n\r\n");//���뻻��
			USART_RX_STA=0;
		}else
		{
			times++;
			if(times%5000==0)
			{
				printf("\r\n�����Ƽ�ʦ����ѧ\r\n");
				printf("ͨ�������ѧԺ\r\n\r\n\r\n");
			}
			if(times%200==0)printf("����������,�Իس�������\r\n");  
			if(times%30==0)LED0=!LED0;//��˸LED,��ʾϵͳ��������.
			delay_ms(10);   
		} */
  }


