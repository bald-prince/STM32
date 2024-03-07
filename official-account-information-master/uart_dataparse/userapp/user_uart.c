/*
串口协议解析

数据头+功能码+数据长度+数据+CRC-16校验码格式为例解析

以AA 55  len(数据长度) xx(功能码) data(数据区) CRC校验

*/



#include "user_uart.h"
#include "string.h"
#include "crc.h"

extern UART_HandleTypeDef huart1;

_S_UART_RX s_uart_rx[UART_FRAME_SIZE];
_S_QUEUE s_queue;
/***********************************************
*函数名称：User_ReadRegCallback
*函数功能：
*入口参数：
*返回参数：NULL
*说明：
*作用域：内部
***********************************************/
uint8_t User_ReadRegCallback(uint8_t cmd, uint8_t *msg, uint8_t len)
{
	uint8_t TestData[5] = {0x01,0x02,0x03,0x04,0x05};
	User_UartFrameSend(cmd,TestData,msg,5);
}
/***********************************************
*函数名称：User_WriteRegCallback
*函数功能：
*入口参数：
*返回参数：NULL
*说明：
*作用域：内部
***********************************************/
uint8_t User_WriteRegCallback(uint8_t cmd, uint8_t *msg, uint8_t len)
{
	uint8_t TestData[5] = {0x01};
	User_UartFrameSend(cmd,TestData,msg,5);
}
/***********************************************
*函数名称：User_ConfigCallback
*函数功能：
*入口参数：
*返回参数：NULL
*说明：
*作用域：内部
***********************************************/
uint8_t User_ConfigCallback(uint8_t cmd, uint8_t *msg, uint8_t len)
{
	uint8_t TestData[5] = {0x01,0x02,0x03};
	User_UartFrameSend(cmd,TestData,msg,5);
}
/***********************************************
*函数名称：User_IAPCallback
*函数功能：
*入口参数：
*返回参数：NULL
*说明：
*作用域：内部
***********************************************/
uint8_t User_IAPCallback(uint8_t cmd, uint8_t *msg, uint8_t len)
{
	uint8_t TestData[5] = {0x01,0x02,0x03,0x04};
	User_UartFrameSend(cmd,TestData,msg,5);
}
_S_FUNCCALLBACK callback_list[]=
{
    {   CMD_READREG,User_ReadRegCallback},
    {   CMD_WRITEDREG,User_WriteRegCallback},
    {   CMD_CONFIGURE,User_ConfigCallback},
    {   CMD_IAP,User_IAPCallback},

};
/***********************************************
*函数名称：User_UartCFGInit
*函数功能：串口中断初始化
*入口参数：CMD
*返回参数：NULL
*说明：
*作用域：内部
***********************************************/
void User_UartCFGInit()
{
	s_queue.queue_head = 0;
	s_queue.queue_tail = 0;
}

/***********************************************
*函数名称：User_UartIRQInit
*函数功能：串口中断初始化
*入口参数：CMD
*返回参数：NULL
*说明：
*作用域：内部
***********************************************/
void User_UartIRQInit(uint8_t CMD)
{
	if(ENABLE==CMD)
	{
		__HAL_UART_ENABLE_IT(&huart1,UART_IT_RXNE);
	}
	if(DISABLE==CMD)
	{
		__HAL_UART_DISABLE_IT(&huart1,UART_IT_RXNE);
	}
}
/***********************************************
*函数名称：User_UartFrameParseEnd
*函数功能：串口数据解析
*入口参数：NULL
*返回参数：NULL
*说明：
*作用域：内部
***********************************************/
void User_UartFrameParseEnd(void)
{
	s_queue.queue_head = 0;
	s_queue.queue_tail = 0;

}
/***********************************************
*函数名称：User_UartPoll
*函数功能：串口任务轮询
*入口参数：CMD
*返回参数：NULL
*说明：
*作用域：内部
***********************************************/
	uint8_t rec_flag;		//数据中

uint8_t User_UartPoll(void)
{
	
	if(rec_flag)
		return 0;
	rec_flag = 1;
	
	if(0 == s_uart_rx[s_queue.queue_head].len)
	{
		rec_flag = 0;
		return 0;
	}
	
	if(s_queue.queue_head == s_queue.queue_tail)
	{
		if(s_queue.queue_tail>=UART_RXBUFFER_SIZE-1)
		{
			s_queue.queue_tail = 0;
		}
		else
		{
			s_queue.queue_tail++;
		}
	}
	
	for(uint8_t i = 0;i<s_uart_rx[s_queue.queue_head].len;i++)
	{
		User_UartDataParse(s_uart_rx[s_queue.queue_head].rxbuffer[i]);
	}

	s_uart_rx[s_queue.queue_head].len = 0;
	

	if(s_queue.queue_head>=UART_RXBUFFER_SIZE-1)
	{
		s_queue.queue_head = 0;
	}
	else
	{
		s_queue.queue_head++;
	}

	rec_flag = 0;
	return 1;
}

/***********************************************
*函数名称：User_UartDataParse
*函数功能：串口数据解析
*入口参数：NULL
*返回参数：NULL
*说明：
*作用域：内部
***********************************************/
uint8_t User_UartDataParse(uint8_t data)
{
	static uint8_t e_frame_status = frame_head1status;
	static uint8_t frame_len = 0;
	static uint8_t index = 0;
	static uint8_t rx_bufftemp[256] = {0};
	uint16_t crc_temp = 0;

	
	switch (e_frame_status){
		case frame_head1status:	//判断数据头1
			if(data == FRAME_HEAD1)
			{
				e_frame_status = frame_head2status;
				rx_bufftemp[index] = data;
				index++;
			}
			else
			{
				e_frame_status = frame_head1status;
				index = 0;
				memset(rx_bufftemp,0,256);

			}
			break;
		case frame_head2status://判断数据头2
			if(data == FRAME_HEAD2)
			{
				e_frame_status = frame_lenstatus;
				rx_bufftemp[index] = data;
				index++;
			}
			else
			{
				e_frame_status = frame_head1status;
				index = 0;
				memset(rx_bufftemp,0,256);
				
			}
		break;
		case frame_lenstatus://判断数据长度
			if(data>0 && data <= 255)
			{
				e_frame_status = frame_datastatus;
				rx_bufftemp[index] = data;
				index++;
				
			}
			else
			{
				e_frame_status = frame_head1status;
				index = 0;
				memset(rx_bufftemp,0,256);
			}
			break;
		case frame_datastatus://接收数据
			if(index>0 && index <= 255)
			{
				rx_bufftemp[index] = data;
				index++;

				if(index == (rx_bufftemp[FRAME_LEN_POS] + 3))//根据数据长度判断接收一帧数据是否接收完成
				{
					crc_temp = rx_bufftemp[index-2]+(rx_bufftemp[index-1]<<8);
					if(crc_temp == CRC16(rx_bufftemp+FRAME_CMD_POS,index-5))//CRC校验相同
					{
						 User_UartFrameParse(rx_bufftemp[FRAME_CMD_POS],rx_bufftemp,index);
						 e_frame_status = frame_head1status;
						 index = 0;
						 memset(rx_bufftemp,0,256);
					}
					else//不同
					{
						
					}
				}	
				
			}
			else
			{
				e_frame_status = frame_head1status;
				index = 0;
				memset(rx_bufftemp,0,256);

			}
		break;
			default:
				e_frame_status = frame_head1status;
				index = 0;
				memset(rx_bufftemp,0,256);

			break;
	}
}
/***********************************************
*函数名称：User_UartFrameParse
*函数功能：串口功能响应函数
*入口参数：NULL
*返回参数：NULL
*说明：
*作用域：内部
***********************************************/
void User_UartFrameParse(uint8_t cmd, uint8_t *msg, uint8_t len)
{
	uint8_t cmd_indexmax = sizeof(callback_list) / sizeof(_S_FUNCCALLBACK);
  uint8_t cmd_index = 0;
	
	for (cmd_index = 0; cmd_index < cmd_indexmax; cmd_index++)
	{
		if (callback_list[cmd_index].cmd == cmd)
		{
			if(callback_list[cmd_index].callback_func != NULL)
			{
				callback_list[cmd_index].callback_func(cmd, msg, len);
			}
		}
	}
}
/***********************************************
*函数名称：User_UartFrameSend
*函数功能：串口发送数据组包
*入口参数：NULL
*返回参数：NULL
*说明：
*作用域：内部
***********************************************/
uint8_t User_UartFrameSend(uint8_t cmd,uint8_t *pdata, uint8_t *msg, uint8_t len)
{
	uint8_t index = 0;
	uint16_t crc_temp = 0;
	
	msg[index++] = FRAME_HEAD1;
	msg[index++] = FRAME_HEAD2;
	msg[index++] = len;
	msg[index++] = cmd;

	for(uint8_t i = 0;i<len;i++)
	{
		msg[index++] = pdata[i];
	}
	
	crc_temp = CRC16(msg+FRAME_CMD_POS,index-3);
	msg[index++] = crc_temp & 0x00FF;
	msg[index++] = crc_temp>>8 & 0x00FF;

	HAL_UART_Transmit(&huart1,msg,index,100);
	
	return  index;
}
