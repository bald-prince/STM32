#include "M_STM32_USART.h"

/**
  * @brief  USART��������
  * @param  USARTx: ���ں�
  * @retval None
  */
void M_USART_GPIO_Config(USART_TypeDef* USARTx)
{
	GPIO_InitTypeDef GPIO_InitStructure;	
	
	//USART��������
	if(USARTx == USART1){
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);	//����GPIOʱ��
		
		//TX��������
		GPIO_InitStructure.GPIO_Pin   = GPIO_Pin_9;		
		GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_AF_PP;
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
		GPIO_Init(GPIOA, &GPIO_InitStructure);
		
		//RX��������
		GPIO_InitStructure.GPIO_Pin   = GPIO_Pin_10;
		GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_IN_FLOATING;	//��������
		GPIO_Init(GPIOA, &GPIO_InitStructure);
	}
	else if(USARTx == USART2){
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_AFIO, ENABLE);	//����GPIOʱ��
		
		//TX��������
		GPIO_InitStructure.GPIO_Pin   = GPIO_Pin_2;		
		GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_AF_PP;
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
		GPIO_Init(GPIOA, &GPIO_InitStructure);
		
		//RX��������
		GPIO_InitStructure.GPIO_Pin   = GPIO_Pin_3;
		GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_IN_FLOATING;	//��������
		GPIO_Init(GPIOA, &GPIO_InitStructure);
	}
	else if(USARTx == USART3){
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB  | RCC_APB2Periph_AFIO, ENABLE);	//����GPIOʱ��
		
		//TX��������
		GPIO_InitStructure.GPIO_Pin   = GPIO_Pin_10;		
		GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_AF_PP;
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
		GPIO_Init(GPIOB, &GPIO_InitStructure);
		
		//RX��������
		GPIO_InitStructure.GPIO_Pin   = GPIO_Pin_11;
		GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_IN_FLOATING;	//��������
		GPIO_Init(GPIOB, &GPIO_InitStructure);
	}
}

/**
  * @brief  USART������ʽ����
  * @param  USARTx: ���ں�
  * @param  USART_BautRate��������
  * @retval None
  */
void M_USART_Mode_Config(USART_TypeDef* USARTx, uint32_t USART_BautRate)
{
	USART_InitTypeDef USART_InitStructure;
	
	//���ô���ʱ��
	if(USARTx == USART1){
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);
	}
	else if(USARTx == USART2){
		RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2, ENABLE); 
	}
	else if(USARTx == USART3){	
		RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3, ENABLE);
	}	

    //������ʽ����
	USART_InitStructure.USART_BaudRate            = USART_BautRate;	                //������
	USART_InitStructure.USART_WordLength          = USART_WordLength_8b;            //�ֳ�
	USART_InitStructure.USART_StopBits            = USART_StopBits_1;               //ֹͣλ
	USART_InitStructure.USART_Parity              = USART_Parity_No;                //����λ
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None; //Ӳ��������λ
	USART_InitStructure.USART_Mode                = USART_Mode_Tx | USART_Mode_Rx;  //ģʽ����
	USART_Init(USARTx, &USART_InitStructure);                                       //��ʼ�����ò���
	
	//�жϽ���ѡ������
	//����ʹ���жϽ��գ�Ӧ����֮ǰ��֮������NVIC�жϿ�������M_USARTx_NVIC_Configuration(...,...,...)
	USART_ITConfig(USARTx, USART_IT_RXNE, ENABLE);								//ʹ���жϽ���
	USART_Cmd(USARTx, ENABLE);														//ʹ�ܴ���
	
	//�����һ���ֽ��޷����ͳ�ȥ������
	USART_ClearFlag(USARTx, USART_FLAG_TC);                                         //���������ɱ�־λ
}

/**
  * @brief  ����USART�ж�
  * @param  USARTx:���ں�
  * @param  NVIC_PriorityGroup_x: �ж����
  * @param  Pre_LEVEL_x����ռ���ȼ�
  * @param  Sub_LEVEL_x����Ӧ���ȼ� 
  * @retval None
  * example: M_USARTx_NVIC_Configuration(USART1, NVIC_PriorityGroup_0, LEVEL_0, LEVEL_0);
  */
void M_USARTx_NVIC_Configuration(USART_TypeDef* USARTx, uint32_t NVIC_PriorityGroup_x, uint8_t Pre_LEVEL_x, uint8_t Sub_LEVEL_x)
{
	NVIC_InitTypeDef NVIC_InitStructure;
	
	//���ȼ��������
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_x);
	
	//ѡ��USARTxͨ��
	if(USARTx == USART1){
		NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;
	}
	else if(USARTx == USART2){
		NVIC_InitStructure.NVIC_IRQChannel = USART2_IRQn;
	}
	else if(USARTx == USART3){
		NVIC_InitStructure.NVIC_IRQChannel = USART3_IRQn;
	}
	
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = Pre_LEVEL_x;	//ѡ����ռ���ȼ�
	NVIC_InitStructure.NVIC_IRQChannelSubPriority        = Sub_LEVEL_x; //ѡ����Ӧ���ȼ�
	NVIC_InitStructure.NVIC_IRQChannelCmd                = ENABLE;      //ʹ���ж�
	NVIC_Init(&NVIC_InitStructure);
}

/**
  * @brief  USART��ʼ��
  * @param  USARTx:���ں�
  * @param  UART_BautRate��������
  * @retval None
  * example �� M_USART_Init(USART1, 115200)
  */
void M_USART_Init(USART_TypeDef* USARTx, uint32_t USART_BautRate)
{
	M_USART_GPIO_Config(USARTx);
	M_USART_Mode_Config(USARTx, USART_BautRate);
}

/**
  * @brief  USARTx�����ַ���
  * @param  USARTx ���ں�
  * @param  str Ҫ���͵��ַ���
  * @retval none
  * example: USART_SendString(USART1, "Hello World!\n");
  */
void USART_SendString(USART_TypeDef* USARTx, char* str)
{
	char k = 0;
	do{
		USART_SendData(USARTx, *(str+k));
		while(USART_GetFlagStatus(USARTx, USART_FLAG_TXE) == RESET);
		k++;
	}while(*(str+k) != '\0');
}

/**
  * @brief  printf�����ض���
  * @retval 
  */
int fputc(int ch, FILE* f)
{
	USART_SendData(USART1, (uint8_t)ch);
	while(USART_GetFlagStatus(USART1, USART_FLAG_TXE) == RESET);
	return ch;
}

