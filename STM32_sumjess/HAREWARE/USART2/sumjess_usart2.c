/*******************************************************************************
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
********************************************************************************/	
//usat2 ����	 


#include "sumjess_USART2.h"
#include "sys.h"

//----------------------------------------/�ض���c�⺯��----printf----��USART1-----------------------------------
#if     0
#pragma import(__use_no_semihosting)             
//��׼����Ҫ��֧�ֺ���                 
struct __FILE 
{ 
	int handle; 

}; 

 FILE __stdout;       
//����_sys_exit()�Ա���ʹ�ð�����ģʽ    
_sys_exit(int x) 
{ 
	x = x; 
} 


int fputc(int ch, FILE *f)
{
        USART_SendData(USART2, (uint8_t) ch);  //����һ���ֽ����ݵ�USART1 
        while (USART_GetFlagStatus(USART2, USART_FLAG_TC) == RESET); // �ȴ��������
        return (ch);
}

//-----------------------------------------/�ض���c�⺯��----scanf------��USART1-----------------------
int fgetc(FILE *f)
{
        while (USART_GetFlagStatus(USART2, USART_FLAG_RXNE) == RESET); //�ȴ�����1�������� 
        return (int)USART_ReceiveData(USART2);
}
//------���������ض���----�ǽ�ԭ��C��ĺ���������Ӳ�������Ӧ---------
//------����Ҳ�����Լ���д���ƺ���--------���û�������������----����---USART_SendData����-----����------USART_ReceiveData����---
//-----------------************************************************-------����--------%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%-----
void MyPrintfByte(unsigned char byte)   //���ڷ���һ���ֽ�
{
        USART_SendData(USART2, byte);        //ͨ���⺯��  ��������
        while( USART_GetFlagStatus(USART2,USART_FLAG_TC)!= SET);  //�ȴ�������ɣ���� USART_FLAG_TC �Ƿ���1       
}
//---------------------------------------------
void MyPrintfStr(unsigned char *s)   //�����ַ��� ����--ָ��--
{
        uint8_t i=0;  //����һ���ֲ�����  ���� �����ַ��� ++����

        while(s[i]!='\0')  // ÿ���ַ�����β ������  \0 ��β��
        {
                USART_SendData(USART2,s[i]);       //ͨ���⺯��  ��������
                while( USART_GetFlagStatus(USART2,USART_FLAG_TC)!= SET); //�ȴ��������,��� USART_FLAG_TC �Ƿ���1
                 i++;                 //i++һ��
        }
}
//--------------------------------------------------
void MyPrintfArray(uint8_t send_array[],uint8_t num) //�������� һ���������ݣ� �������鳤��1-255 
{
        uint8_t i=0;  //����һ���ֲ�����  ���� �����ַ��� ++����

         while(i<num)   //i�϶�С��num ����ȷ  ��ִ��
        {
          USART_SendData(USART2,send_array[i]);        //ͨ���⺯��  ��������
         while( USART_GetFlagStatus(USART2,USART_FLAG_TC)!= SET);  //�ȴ�������ɣ���� USART_FLAG_TC �Ƿ���1
          i++;  //��һ         
        }        
}
#endif

#if EN_USART1_RX
u16 USART2_RX_STA=0; 
u8 USART2_RX_BUF[USART2_REC_LEN];
void USART2_Init(u32 bound)
{
    GPIO_InitTypeDef GPIO_InitStructure;
    USART_InitTypeDef USART_InitStructure;
	  NVIC_InitTypeDef NVIC_InitStructure;
	
	
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_AFIO, ENABLE);	//����GPIOʱ��
		RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2, ENABLE); 
	
		//TX��������
		GPIO_InitStructure.GPIO_Pin   = GPIO_Pin_2;		
		GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_AF_PP;
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
		GPIO_Init(GPIOA, &GPIO_InitStructure);
		
		//RX��������
		GPIO_InitStructure.GPIO_Pin   = GPIO_Pin_3;
		GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_IN_FLOATING;	//��������
		GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	      //������ʽ����
	USART_InitStructure.USART_BaudRate            = bound;	                        //������
	USART_InitStructure.USART_WordLength          = USART_WordLength_8b;            //�ֳ�
	USART_InitStructure.USART_StopBits            = USART_StopBits_1;               //ֹͣλ
	USART_InitStructure.USART_Parity              = USART_Parity_No;                //����λ
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None; //Ӳ��������λ
	USART_InitStructure.USART_Mode                = USART_Mode_Tx | USART_Mode_Rx;  //ģʽ����
	USART_Init(USART2, &USART_InitStructure);                                       //��ʼ�����ò���
	
	//�жϽ���ѡ������
	//����ʹ���жϽ��գ�Ӧ����֮ǰ��֮������NVIC�жϿ�������M_USARTx_NVIC_Configuration(...,...,...)
	USART_ITConfig(USART2, USART_IT_RXNE, ENABLE);								//ʹ���жϽ���
	USART_Cmd(USART2, ENABLE);														        //ʹ�ܴ���
	
	//�����һ���ֽ��޷����ͳ�ȥ������
	USART_ClearFlag(USART2, USART_FLAG_TC);                                         //���������ɱ�־λ

	//���ȼ��������
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	
	//ѡ��USARTxͨ��

  NVIC_InitStructure.NVIC_IRQChannel = USART2_IRQn;
	
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;	//ѡ����ռ���ȼ�
	NVIC_InitStructure.NVIC_IRQChannelSubPriority        = 2; //ѡ����Ӧ���ȼ�
	NVIC_InitStructure.NVIC_IRQChannelCmd                = ENABLE;      //ʹ���ж�
	NVIC_Init(&NVIC_InitStructure);

}

/*
 // * @brief  USARTx�����ַ���
 // * @param  USARTx ���ں�
 // * @param  str Ҫ���͵��ַ���
//  * @retval none
 // * example: USART_SendString(USART1, "Hello World!\n");
 
void USART_SendString(USART_TypeDef* USARTx, char* str)
{
	char k = 0;
	do{
		USART_SendData(USARTx, *(str+k));
		while(USART_GetFlagStatus(USARTx, USART_FLAG_TXE) == RESET);
		k++;
	}while(*(str+k) != '\0');
}
 

 */
void USART2_IRQHandler(void)                	//����2�жϷ������
	{
	u8 Res2;

	if(USART_GetITStatus(USART2, USART_IT_RXNE) != RESET)  //�����ж�(���յ������ݱ�����0x0d 0x0a��β)
		{
		Res2 =USART_ReceiveData(USART2);	//��ȡ���յ�������
		
		if((USART2_RX_STA&0x8000)==0)//����δ���
			{
			if(USART2_RX_STA&0x4000)//���յ���0x0d
				{
				if(Res2!=0x0a)USART2_RX_STA=0;//���մ���,���¿�ʼ
				else USART2_RX_STA|=0x8000;	//��������� 
				}
			else //��û�յ�0X0D
				{	
				if(Res2==0x0d)USART2_RX_STA|=0x4000;
				else
					{
					USART2_RX_BUF[USART2_RX_STA&0X3FFF]=Res2 ;
					USART2_RX_STA++;
					if(USART2_RX_STA>(USART2_REC_LEN-1))USART2_RX_STA=0;//�������ݴ���,���¿�ʼ����	  
					}		 
				}
			}   		 
     } 

} 
	#endif	


