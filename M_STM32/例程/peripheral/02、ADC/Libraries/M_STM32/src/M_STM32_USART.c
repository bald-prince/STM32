#include "M_STM32_USART.h"

/**
  * @brief  USART引脚配置
  * @param  USARTx: 串口号
  * @retval None
  */
void M_USART_GPIO_Config(USART_TypeDef* USARTx)
{
	GPIO_InitTypeDef GPIO_InitStructure;	
	
	//USART引脚配置
	if(USARTx == USART1){
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);	//配置GPIO时钟
		
		//TX引脚配置
		GPIO_InitStructure.GPIO_Pin   = GPIO_Pin_9;		
		GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_AF_PP;
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
		GPIO_Init(GPIOA, &GPIO_InitStructure);
		
		//RX引脚配置
		GPIO_InitStructure.GPIO_Pin   = GPIO_Pin_10;
		GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_IN_FLOATING;	//浮空输入
		GPIO_Init(GPIOA, &GPIO_InitStructure);
	}
	else if(USARTx == USART2){
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_AFIO, ENABLE);	//配置GPIO时钟
		
		//TX引脚配置
		GPIO_InitStructure.GPIO_Pin   = GPIO_Pin_2;		
		GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_AF_PP;
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
		GPIO_Init(GPIOA, &GPIO_InitStructure);
		
		//RX引脚配置
		GPIO_InitStructure.GPIO_Pin   = GPIO_Pin_3;
		GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_IN_FLOATING;	//浮空输入
		GPIO_Init(GPIOA, &GPIO_InitStructure);
	}
	else if(USARTx == USART3){
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB  | RCC_APB2Periph_AFIO, ENABLE);	//配置GPIO时钟
		
		//TX引脚配置
		GPIO_InitStructure.GPIO_Pin   = GPIO_Pin_10;		
		GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_AF_PP;
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
		GPIO_Init(GPIOB, &GPIO_InitStructure);
		
		//RX引脚配置
		GPIO_InitStructure.GPIO_Pin   = GPIO_Pin_11;
		GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_IN_FLOATING;	//浮空输入
		GPIO_Init(GPIOB, &GPIO_InitStructure);
	}
}

/**
  * @brief  USART工作方式配置
  * @param  USARTx: 串口号
  * @param  USART_BautRate：波特率
  * @retval None
  */
void M_USART_Mode_Config(USART_TypeDef* USARTx, uint32_t USART_BautRate)
{
	USART_InitTypeDef USART_InitStructure;
	
	//配置串口时钟
	if(USARTx == USART1){
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);
	}
	else if(USARTx == USART2){
		RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2, ENABLE); 
	}
	else if(USARTx == USART3){	
		RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3, ENABLE);
	}	

    //工作方式配置
	USART_InitStructure.USART_BaudRate            = USART_BautRate;	                //波特率
	USART_InitStructure.USART_WordLength          = USART_WordLength_8b;            //字长
	USART_InitStructure.USART_StopBits            = USART_StopBits_1;               //停止位
	USART_InitStructure.USART_Parity              = USART_Parity_No;                //检验位
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None; //硬件流控制位
	USART_InitStructure.USART_Mode                = USART_Mode_Tx | USART_Mode_Rx;  //模式配置
	USART_Init(USARTx, &USART_InitStructure);                                       //初始化配置参数
	
	//中断接收选择及配置
	//若是使用中断接收，应该在之前或之后配置NVIC中断控制器：M_USARTx_NVIC_Configuration(...,...,...)
	USART_ITConfig(USARTx, USART_IT_RXNE, ENABLE);								//使能中断接收
	USART_Cmd(USARTx, ENABLE);														//使能串口
	
	//解决第一个字节无法发送出去的问题
	USART_ClearFlag(USARTx, USART_FLAG_TC);                                         //清除发送完成标志位
}

/**
  * @brief  配置USART中断
  * @param  USARTx:串口号
  * @param  NVIC_PriorityGroup_x: 中断组别
  * @param  Pre_LEVEL_x：抢占优先级
  * @param  Sub_LEVEL_x：响应优先级 
  * @retval None
  * example: M_USARTx_NVIC_Configuration(USART1, NVIC_PriorityGroup_0, LEVEL_0, LEVEL_0);
  */
void M_USARTx_NVIC_Configuration(USART_TypeDef* USARTx, uint32_t NVIC_PriorityGroup_x, uint8_t Pre_LEVEL_x, uint8_t Sub_LEVEL_x)
{
	NVIC_InitTypeDef NVIC_InitStructure;
	
	//优先级组别配置
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_x);
	
	//选择USARTx通道
	if(USARTx == USART1){
		NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;
	}
	else if(USARTx == USART2){
		NVIC_InitStructure.NVIC_IRQChannel = USART2_IRQn;
	}
	else if(USARTx == USART3){
		NVIC_InitStructure.NVIC_IRQChannel = USART3_IRQn;
	}
	
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = Pre_LEVEL_x;	//选择抢占优先级
	NVIC_InitStructure.NVIC_IRQChannelSubPriority        = Sub_LEVEL_x; //选择响应优先级
	NVIC_InitStructure.NVIC_IRQChannelCmd                = ENABLE;      //使能中断
	NVIC_Init(&NVIC_InitStructure);
}

/**
  * @brief  USART初始化
  * @param  USARTx:串口号
  * @param  UART_BautRate：波特率
  * @retval None
  * example ： M_USART_Init(USART1, 115200)
  */
void M_USART_Init(USART_TypeDef* USARTx, uint32_t USART_BautRate)
{
	M_USART_GPIO_Config(USARTx);
	M_USART_Mode_Config(USARTx, USART_BautRate);
}

/**
  * @brief  USARTx发送字符串
  * @param  USARTx 串口号
  * @param  str 要发送的字符串
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
  * @brief  printf函数重定向
  * @retval 
  */
int fputc(int ch, FILE* f)
{
	USART_SendData(USART1, (uint8_t)ch);
	while(USART_GetFlagStatus(USART1, USART_FLAG_TXE) == RESET);
	return ch;
}

