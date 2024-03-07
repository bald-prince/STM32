#ifndef __USER_UART_H
#define __USER_UART_H

#include "stm32f1xx.h"
#define UART_RXBUFFER_SIZE 200
#define UART_FRAME_SIZE  2

/*命令码*/
#define CMD_READREG 	0x01
#define CMD_WRITEDREG 0x02
#define CMD_CONFIGURE 0x03
#define CMD_IAP			  0x04
/*协议相关*/
#define FRAME_LEN_POS  2//数据帧长度索引
#define FRAME_CMD_POS  3//命令码索引
#define FRAME_HEAD1 0xAA
#define FRAME_HEAD2 0x55

typedef enum {
	frame_head1status = 0,
	frame_head2status = 0x01,
	frame_lenstatus = 0x02,
	frame_datastatus = 0x03
}_E_FRAME_STATUS;



typedef struct {
	uint8_t len;				//数据接收长度
	uint8_t rxbuffer[UART_RXBUFFER_SIZE];//数据接收缓存

}_S_UART_RX;


typedef struct{
	uint8_t queue_head;//队列头
	uint8_t queue_tail;//对列尾
}_S_QUEUE;

typedef struct{
	uint8_t cmd;//命令
	uint8_t (*callback_func)(uint8_t cmd, uint8_t *msg, uint8_t len);//命令对应的函数

}_S_FUNCCALLBACK;


extern _S_UART_RX s_uart_rx[UART_FRAME_SIZE];
extern _S_QUEUE s_queue;


extern void User_UartIRQInit(uint8_t CMD);
extern uint8_t User_UartDataParse(uint8_t data);
extern uint8_t User_UartPoll(void);
extern void User_UartCFGInit();
extern void User_UartFrameParse(uint8_t cmd, uint8_t *msg, uint8_t len);
extern uint8_t User_UartFrameSend(uint8_t cmd,uint8_t *pdata, uint8_t *msg, uint8_t len);

#endif