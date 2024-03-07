/*
����Э�����

����ͷ+������+���ݳ���+����+CRC-16У�����ʽΪ������

��AA 55  len(���ݳ���) xx(������) data(������) CRCУ��

*/



#include "user_uart.h"
#include "string.h"
#include "crc.h"

extern UART_HandleTypeDef huart1;

_S_UART_RX s_uart_rx[UART_FRAME_SIZE];
_S_QUEUE s_queue;
/***********************************************
*�������ƣ�User_ReadRegCallback
*�������ܣ�
*��ڲ�����
*���ز�����NULL
*˵����
*�������ڲ�
***********************************************/
uint8_t User_ReadRegCallback(uint8_t cmd, uint8_t *msg, uint8_t len)
{
	uint8_t TestData[5] = {0x01,0x02,0x03,0x04,0x05};
	User_UartFrameSend(cmd,TestData,msg,5);
}
/***********************************************
*�������ƣ�User_WriteRegCallback
*�������ܣ�
*��ڲ�����
*���ز�����NULL
*˵����
*�������ڲ�
***********************************************/
uint8_t User_WriteRegCallback(uint8_t cmd, uint8_t *msg, uint8_t len)
{
	uint8_t TestData[5] = {0x01};
	User_UartFrameSend(cmd,TestData,msg,5);
}
/***********************************************
*�������ƣ�User_ConfigCallback
*�������ܣ�
*��ڲ�����
*���ز�����NULL
*˵����
*�������ڲ�
***********************************************/
uint8_t User_ConfigCallback(uint8_t cmd, uint8_t *msg, uint8_t len)
{
	uint8_t TestData[5] = {0x01,0x02,0x03};
	User_UartFrameSend(cmd,TestData,msg,5);
}
/***********************************************
*�������ƣ�User_IAPCallback
*�������ܣ�
*��ڲ�����
*���ز�����NULL
*˵����
*�������ڲ�
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
*�������ƣ�User_UartCFGInit
*�������ܣ������жϳ�ʼ��
*��ڲ�����CMD
*���ز�����NULL
*˵����
*�������ڲ�
***********************************************/
void User_UartCFGInit()
{
	s_queue.queue_head = 0;
	s_queue.queue_tail = 0;
}

/***********************************************
*�������ƣ�User_UartIRQInit
*�������ܣ������жϳ�ʼ��
*��ڲ�����CMD
*���ز�����NULL
*˵����
*�������ڲ�
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
*�������ƣ�User_UartFrameParseEnd
*�������ܣ��������ݽ���
*��ڲ�����NULL
*���ز�����NULL
*˵����
*�������ڲ�
***********************************************/
void User_UartFrameParseEnd(void)
{
	s_queue.queue_head = 0;
	s_queue.queue_tail = 0;

}
/***********************************************
*�������ƣ�User_UartPoll
*�������ܣ�����������ѯ
*��ڲ�����CMD
*���ز�����NULL
*˵����
*�������ڲ�
***********************************************/
	uint8_t rec_flag;		//������

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
*�������ƣ�User_UartDataParse
*�������ܣ��������ݽ���
*��ڲ�����NULL
*���ز�����NULL
*˵����
*�������ڲ�
***********************************************/
uint8_t User_UartDataParse(uint8_t data)
{
	static uint8_t e_frame_status = frame_head1status;
	static uint8_t frame_len = 0;
	static uint8_t index = 0;
	static uint8_t rx_bufftemp[256] = {0};
	uint16_t crc_temp = 0;

	
	switch (e_frame_status){
		case frame_head1status:	//�ж�����ͷ1
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
		case frame_head2status://�ж�����ͷ2
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
		case frame_lenstatus://�ж����ݳ���
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
		case frame_datastatus://��������
			if(index>0 && index <= 255)
			{
				rx_bufftemp[index] = data;
				index++;

				if(index == (rx_bufftemp[FRAME_LEN_POS] + 3))//�������ݳ����жϽ���һ֡�����Ƿ�������
				{
					crc_temp = rx_bufftemp[index-2]+(rx_bufftemp[index-1]<<8);
					if(crc_temp == CRC16(rx_bufftemp+FRAME_CMD_POS,index-5))//CRCУ����ͬ
					{
						 User_UartFrameParse(rx_bufftemp[FRAME_CMD_POS],rx_bufftemp,index);
						 e_frame_status = frame_head1status;
						 index = 0;
						 memset(rx_bufftemp,0,256);
					}
					else//��ͬ
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
*�������ƣ�User_UartFrameParse
*�������ܣ����ڹ�����Ӧ����
*��ڲ�����NULL
*���ز�����NULL
*˵����
*�������ڲ�
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
*�������ƣ�User_UartFrameSend
*�������ܣ����ڷ����������
*��ڲ�����NULL
*���ز�����NULL
*˵����
*�������ڲ�
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
