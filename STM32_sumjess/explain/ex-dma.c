/*

*******************************************************************************
================================================================================
��ƽ    ̨��stm32f103zet6_sumjessƽ̨
����    д��sumjess
��E-mail  ��1371129880@qq.com
������汾��V2.0
�������¡�2018��01��21��
�������Ϣ�ο����е�ַ��
����    վ��http://www.openedv.com/
           http://www.stmcu.org/
					 http://www.firebbs.cn/forum.php
---------------------------------------------------------------------------------
��dev.env.��MDK5.14�����ϰ汾
��Target  ��stm32f103zet6
��һ���޶���2017/11/09
�ڶ����޶���2018/01/21
---------------------------------------------------------------------------------
û�������Ĵ��룬ֻ�в��ϵķ��ף����һ��Ŭ����
����õ���������㣬��ӭ��ҷ���bug��
================================================================================
********************************************************************************




DMA���� 

�ֲ�
��-����void MYDMA_Config(DMA_Channel_TypeDef* DMA_CHx,u32 cpar,u32 cmar,u16 cndtr)
����void MYDMA_Enable(DMA_Channel_TypeDef*DMA_CHx)



�� ʹ��DMAʱ��
   RCC_AHBPeriphClockCmd();
�� ��ʼ��DMAͨ������
   DMA_Init();
��ʹ�ܴ���DMA����,����DMAʹ�ܺ�����
  USART_DMACmd();
��ʹ��DMA1ͨ�����������䡣
   DMA_Cmd();
�ݲ�ѯDMA����״̬
  DMA_GetFlagStatus();
�޻�ȡ/����ͨ����ǰʣ����������
  DMA_GetCurrDataCounter();
  DMA_SetCurrDataCounter();


void MYDMA_Config(DMA_Channel_TypeDef* DMA_CHx,u32 cpar,u32 cmar,u16 cndtr)
{
 	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1, ENABLE);	//ʹ��DMA����
	
  DMA_DeInit(DMA_CHx);   //��DMA��ͨ��1�Ĵ�������Ϊȱʡֵ
	DMA1_MEM_LEN=cndtr;
	DMA_InitStructure.DMA_PeripheralBaseAddr = cpar;  //DMA����ADC����ַ
	DMA_InitStructure.DMA_MemoryBaseAddr = cmar;  //DMA�ڴ����ַ
	DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralDST;  //���ݴ��䷽�򣬴��ڴ��ȡ���͵�����
	DMA_InitStructure.DMA_BufferSize = cndtr;  //DMAͨ����DMA����Ĵ�С
	DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;  //�����ַ�Ĵ�������
	DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;  //�ڴ��ַ�Ĵ�������
	DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;  //���ݿ��Ϊ8λ
	DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte; //���ݿ��Ϊ8λ
	DMA_InitStructure.DMA_Mode = DMA_Mode_Normal;  //��������������ģʽ
	DMA_InitStructure.DMA_Priority = DMA_Priority_Medium; //DMAͨ�� xӵ�������ȼ� 
	DMA_InitStructure.DMA_M2M = DMA_M2M_Disable;  //DMAͨ��xû������Ϊ�ڴ浽�ڴ洫��
	DMA_Init(DMA_CHx, &DMA_InitStructure);  //����DMA_InitStruct��ָ���Ĳ�����ʼ��DMA��ͨ��USART1_Tx_DMA_Channel����ʶ�ļĴ���
***��һ������ DMA_PeripheralBaseAddr �������� DMA ������������ַ������Ҫ���д���
DMA ���䣬��ô�������ַΪ���ڽ��ܷ������ݴ洢�� USART1->DR �ĵ�ַ����ʾ����Ϊ
&USART1->DR��
***�ڶ������� DMA_MemoryBaseAddrΪ�ڴ����ַ��Ҳ�������Ǵ�� DMA�������ݵ��ڴ��ַ��
***���������� DMA_DIR �������ݴ��䷽�򣬾����Ǵ������ȡ���ݵ��ڴ滹�ʹ��ڴ��ȡ��
�ݷ��͵����裬Ҳ����������Դ�ػ���Ŀ�ĵأ�������������Ϊ���ڴ��ȡ���ݷ��͵����ڣ�
����������Ȼ����Ŀ�ĵ��ˣ�����ѡ��ֵΪ DMA_DIR_PeripheralDST��
***���ĸ����� DMA_BufferSize ����һ�δ����������Ĵ�С�������������⡣
***��������� DMA_PeripheralInc ���ô������ݵ�ʱ�������ַ�ǲ��仹�ǵ������������
Ϊ��������ô��һ�δ����ʱ���ַ�� 1��������Ϊ������һֱ���̶������ַ&USART1->DR
�������ݣ����Ե�ַ��������ֵΪ DMA_PeripheralInc_Disable��
***�������� �� DMA_MemoryInc ���ô�������ʱ ���ڴ��ַ �Ƿ������ ���������
DMA_PeripheralInc ��˼�ӽ���ֻ������Ե����ڴ档�������ǵĳ����ǽ��ڴ��������洢��
Ԫ�����ݷ��͵����ڣ����������ڴ��ַ����Ҫ�����ģ�����ֵΪ DMA_MemoryInc_Enable��
***���߸����� DMA_PeripheralDataSize ������������ĵ����ݳ�����Ϊ�ֽڴ��䣨8bits����
���ִ��� (16bits)�����ִ��� (32bits)������������ 8 λ�ֽڴ��䣬����ֵ����Ϊ
DMA_PeripheralDataSize_Byte��
***�ڰ˸����� DMA_MemoryDataSize �����������ڴ�����ݳ��ȣ��͵��߸�������˼�ӽ�����
������ͬ������Ϊ�ֽڴ��� DMA_MemoryDataSize_Byte��
***�ھŸ������ڷ��͵����ڣ��������Ϊ�ظ��ɼ�����ô������ 64 ���ֽڲɼ����֮���������
��ĵ�һ����ַ�ɼ������ѭ����������������Ϊһ�������ɼ����֮��ѭ������������ֵ
Ϊ DMA_Mode_Normal�������������ʵ���У�������ô˲���Ϊѭ���ɼ�����ô��ῴ������
��ͣ�Ĵ�ӡ���ݣ������жϣ������ʵ���п����޸������������һ�¡�
***��ʮ������������ DMA ͨ�������ȼ����еͣ��У��ߣ���������ģʽ�������ǰ�潲�����
���������������ȼ���Ϊ�м�������ֵΪ DMA_Priority_Medium�����Ҫ�������ͨ������ô
���ֵ�ͷǳ������塣
***�� ʮ һ �� �� �� DMA_M2M �� �� �� �� �� �� �� �� �� �� �� �� ģ ʽ �� �� �� �� �� �� �� ѡ ��
DMA_M2M_Disable��  	
} 


//����һ��DMA����
void MYDMA_Enable(DMA_Channel_TypeDef*DMA_CHx)
{ 
	DMA_Cmd(DMA_CHx, DISABLE );  //�ر�USART1 TX DMA1 ��ָʾ��ͨ��      
 	DMA_SetCurrDataCounter(DMA1_Channel4,DMA1_MEM_LEN);//DMAͨ����DMA����Ĵ�С
 	DMA_Cmd(DMA_CHx, ENABLE);  //ʹ��USART1 TX DMA1 ��ָʾ��ͨ�� 
}	  
��ʹ�ܴ��� DMA ����
���� DMA ����֮�����Ǿ�Ҫ�������ڵ� DMA ���͹��ܣ�ʹ�õĺ����ǣ�
USART_DMACmd(USART1,USART_DMAReq_Tx,ENABLE);
�����Ҫʹ�ܴ��� DMA ���ܣ���ô�ڶ��������޸�Ϊ USART_DMAReq_Rx ���ɡ�


�ݲ�ѯ DMA ����״̬
�� DMA ��������У�����Ҫ��ѯ DMA ����ͨ����״̬��ʹ�õĺ����ǣ�
FlagStatus DMA_GetFlagStatus(uint32_t DMAy_FLAG)
�ޱ�������Ҫ��ѯ DMA ͨ�� 4 �����Ƿ���ɣ������ǣ�
DMA_GetFlagStatus(DMA2_FLAG_TC4);
�����ﻹ��һ���Ƚ���Ҫ�ĺ������ǻ�ȡ��ǰʣ����������С�ĺ�����
uint16_t DMA_GetCurrDataCounter(DMA_Channel_TypeDef* DMAy_Channelx)
���������Ҫ��ȡ DMA ͨ�� 4 ���ж��ٸ�����û�д��䣬�����ǣ�
DMA_GetCurrDataCounter(DMA1_Channel4);
 








#include "led.h"
#include "delay.h"
#include "sys.h"
#include "usart.h"
#include "key.h"
#include "dma.h"

//ALIENTEK Mini STM32�����巶������18
//DMAʵ��  
//����֧�֣�www.openedv.com
//������������ӿƼ����޹�˾
   	
const u8 TEXT_TO_SEND[]={"ALIENTEK Mini STM32 DMA ����ʵ��"};
#define TEXT_LENTH  sizeof(TEXT_TO_SEND)-1			//TEXT_TO_SEND�ַ�������(������������)
u8 SendBuff[(TEXT_LENTH+2)*100];//�����(TEXT_LENTH+2)��������

 int main(void)
 { 
	u16 i;
	u8 t=0; 
	float pro=0;			//���� 
	delay_init();	    	 //��ʱ������ʼ��
	uart_init(9600);	 	//���ڳ�ʼ��Ϊ9600
	LED_Init();		  		//��ʼ����LED���ӵ�Ӳ���ӿ�		   	//��ʼ��LCD 
	KEY_Init();				//������ʼ��		 	
 	MYDMA_Config(DMA1_Channel4,(u32)&USART1->DR,(u32)SendBuff,(TEXT_LENTH+2)*100);//DMA1ͨ��4,����Ϊ����1,�洢��ΪSendBuff,��(TEXT_LENTH+2)*100.
 //��������Ϊ��ɫ 
	//��ʾ��ʾ��Ϣ	

							//for������������з�//  
	for(i=0;i<(TEXT_LENTH+2)*100;i++)//���ASCII�ַ�������
    {
		if(t>=TEXT_LENTH)//���뻻�з�
		{ 
			SendBuff[i++]=0x0d; 
			SendBuff[i]=0x0a; 
			t=0;
		}else SendBuff[i]=TEXT_TO_SEND[t++];//����TEXT_TO_SEND���    
    }		 //��������Ϊ��ɫ	  
	i=0;
		
		
	while(1)
	{
		t=KEY_Scan(0);
		if(t==KEY0_PRES)//KEY0����
		{
//��ʾ�ٷֺ�
			printf("\r\nDMA DATA:\r\n "); 	    
		  USART_DMACmd(USART1,USART_DMAReq_Tx,ENABLE); //????1?DMA??        
			MYDMA_Enable(DMA1_Channel4);//��ʼһ��DMA���䣡	  
		    //�ȴ�DMA������ɣ���ʱ������������һЩ�£����
		    //ʵ��Ӧ���У����������ڼ䣬����ִ�����������
			LED1=!LED1;
		    while(1)
		    {
				if(DMA_GetFlagStatus(DMA1_FLAG_TC4)!=RESET)//�ȴ�ͨ��4�������
				{
					DMA_ClearFlag(DMA1_FLAG_TC4);//���ͨ��4������ɱ�־
					break; 
		        }
				pro=DMA_GetCurrDataCounter(DMA1_Channel4);//�õ���ǰ��ʣ����ٸ�����
				pro=1-pro/((TEXT_LENTH+2)*100);//�õ��ٷֱ�	  
				pro*=100;      //����100��
				//dayin pro  
		    }			    
//��ʾ100%	  
//��ʾ�������
		}
		i++;
		delay_ms(10);
		if(i==20)
		{
			LED0=!LED0;//��ʾϵͳ��������	
			i=0;
		}		   
	}
}









*/


