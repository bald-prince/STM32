/*******************************************************************************
================================================================================
【平    台】stm32f103zet6_sumjess平台
【编    写】sumjess
【E-mail  】1371129880@qq.com
【软件版本】V2.0
【最后更新】2018年01月21日
【相关信息参考下列地址】
【网    站】http://www.openedv.com/
           http://www.stmcu.org/
					 http://www.firebbs.cn/forum.php
---------------------------------------------------------------------------------
【dev.env.】MDK5.14及以上版本
【Target  】stm32f103zet6
第一次修订：2017/11/09
第二次修订：2018/01/21
---------------------------------------------------------------------------------
没有完美的代码，只有不断的奉献，大家一起努力；
赠人玫瑰手留余香，欢迎大家反馈bug！
================================================================================
********************************************************************************/	
//usat2 代码	 


#include "sumjess_USART2.h"
#include "sys.h"

//----------------------------------------/重定向c库函数----printf----到USART1-----------------------------------
#if     0
#pragma import(__use_no_semihosting)             
//标准库需要的支持函数                 
struct __FILE 
{ 
	int handle; 

}; 

 FILE __stdout;       
//定义_sys_exit()以避免使用半主机模式    
_sys_exit(int x) 
{ 
	x = x; 
} 


int fputc(int ch, FILE *f)
{
        USART_SendData(USART2, (uint8_t) ch);  //发送一个字节数据到USART1 
        while (USART_GetFlagStatus(USART2, USART_FLAG_TC) == RESET); // 等待发送完毕
        return (ch);
}

//-----------------------------------------/重定向c库函数----scanf------到USART1-----------------------
int fgetc(FILE *f)
{
        while (USART_GetFlagStatus(USART2, USART_FLAG_RXNE) == RESET); //等待串口1输入数据 
        return (int)USART_ReceiveData(USART2);
}
//------上面两个重定向----是将原来C库的函数与现在硬件的相对应---------
//------我们也可以自己编写相似函数--------运用基本的两个函数----发送---USART_SendData（）-----接收------USART_ReceiveData（）---
//-----------------************************************************-------比如--------%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%-----
void MyPrintfByte(unsigned char byte)   //串口发送一个字节
{
        USART_SendData(USART2, byte);        //通过库函数  发送数据
        while( USART_GetFlagStatus(USART2,USART_FLAG_TC)!= SET);  //等待发送完成，检测 USART_FLAG_TC 是否置1       
}
//---------------------------------------------
void MyPrintfStr(unsigned char *s)   //发送字符串 函数--指针--
{
        uint8_t i=0;  //定义一个局部变量  用来 发送字符串 ++运算

        while(s[i]!='\0')  // 每个字符串结尾 都是以  \0 结尾的
        {
                USART_SendData(USART2,s[i]);       //通过库函数  发送数据
                while( USART_GetFlagStatus(USART2,USART_FLAG_TC)!= SET); //等待发送完成,检测 USART_FLAG_TC 是否置1
                 i++;                 //i++一次
        }
}
//--------------------------------------------------
void MyPrintfArray(uint8_t send_array[],uint8_t num) //两个参数 一是数组内容， 二是数组长度1-255 
{
        uint8_t i=0;  //定义一个局部变量  用来 发送字符串 ++运算

         while(i<num)   //i肯定小于num 是正确  就执行
        {
          USART_SendData(USART2,send_array[i]);        //通过库函数  发送数据
         while( USART_GetFlagStatus(USART2,USART_FLAG_TC)!= SET);  //等待发送完成，检测 USART_FLAG_TC 是否置1
          i++;  //加一         
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
	
	
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_AFIO, ENABLE);	//配置GPIO时钟
		RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2, ENABLE); 
	
		//TX引脚配置
		GPIO_InitStructure.GPIO_Pin   = GPIO_Pin_2;		
		GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_AF_PP;
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
		GPIO_Init(GPIOA, &GPIO_InitStructure);
		
		//RX引脚配置
		GPIO_InitStructure.GPIO_Pin   = GPIO_Pin_3;
		GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_IN_FLOATING;	//浮空输入
		GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	      //工作方式配置
	USART_InitStructure.USART_BaudRate            = bound;	                        //波特率
	USART_InitStructure.USART_WordLength          = USART_WordLength_8b;            //字长
	USART_InitStructure.USART_StopBits            = USART_StopBits_1;               //停止位
	USART_InitStructure.USART_Parity              = USART_Parity_No;                //检验位
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None; //硬件流控制位
	USART_InitStructure.USART_Mode                = USART_Mode_Tx | USART_Mode_Rx;  //模式配置
	USART_Init(USART2, &USART_InitStructure);                                       //初始化配置参数
	
	//中断接收选择及配置
	//若是使用中断接收，应该在之前或之后配置NVIC中断控制器：M_USARTx_NVIC_Configuration(...,...,...)
	USART_ITConfig(USART2, USART_IT_RXNE, ENABLE);								//使能中断接收
	USART_Cmd(USART2, ENABLE);														        //使能串口
	
	//解决第一个字节无法发送出去的问题
	USART_ClearFlag(USART2, USART_FLAG_TC);                                         //清除发送完成标志位

	//优先级组别配置
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	
	//选择USARTx通道

  NVIC_InitStructure.NVIC_IRQChannel = USART2_IRQn;
	
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;	//选择抢占优先级
	NVIC_InitStructure.NVIC_IRQChannelSubPriority        = 2; //选择响应优先级
	NVIC_InitStructure.NVIC_IRQChannelCmd                = ENABLE;      //使能中断
	NVIC_Init(&NVIC_InitStructure);

}

/*
 // * @brief  USARTx发送字符串
 // * @param  USARTx 串口号
 // * @param  str 要发送的字符串
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
void USART2_IRQHandler(void)                	//串口2中断服务程序
	{
	u8 Res2;

	if(USART_GetITStatus(USART2, USART_IT_RXNE) != RESET)  //接收中断(接收到的数据必须是0x0d 0x0a结尾)
		{
		Res2 =USART_ReceiveData(USART2);	//读取接收到的数据
		
		if((USART2_RX_STA&0x8000)==0)//接收未完成
			{
			if(USART2_RX_STA&0x4000)//接收到了0x0d
				{
				if(Res2!=0x0a)USART2_RX_STA=0;//接收错误,重新开始
				else USART2_RX_STA|=0x8000;	//接收完成了 
				}
			else //还没收到0X0D
				{	
				if(Res2==0x0d)USART2_RX_STA|=0x4000;
				else
					{
					USART2_RX_BUF[USART2_RX_STA&0X3FFF]=Res2 ;
					USART2_RX_STA++;
					if(USART2_RX_STA>(USART2_REC_LEN-1))USART2_RX_STA=0;//接收数据错误,重新开始接收	  
					}		 
				}
			}   		 
     } 

} 
	#endif	


