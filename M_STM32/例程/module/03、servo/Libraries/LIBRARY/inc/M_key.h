#ifndef __M_KEY_H
#define __M_KEY_H

#include "stm32f10x.h"

//下面是定义按键的时间，单位为 ： 10ms（中断时间）
#define KEY_DOWN_TIME 1
#define KEY_HOLD_TIME 50

//定义按键消息FIFO大小
#define KEY_MSG_FIFO_SIZE       20      //最多 255，否则需要修改key_msg_front/key_msg_rear类型

//按键端口枚举
typedef enum
{
	KEY_U, //上
	KEY_D, //下
	
	KEY_L, //左
	KEY_R, //右
	
	KEY_MAX,
}KEY_e;

//按键状态枚举
typedef enum
{
	KEY_DOWN = 0, //按键按下对应的电平
	KEY_UP   = 1, //按键弹起对应的电平
	
	KEY_HOLD,     //长按按键
}KEY_STATUS_e;

//按键消息结构体
typedef struct
{
	KEY_e        key;    //按键编号
	KEY_STATUS_e status; //按键状态
}KEY_MSG_t;

//定义按键消息FIFO状态
typedef enum
{
	KEY_MSG_EMPTY,  //无按键消息
	KEY_MSG_NORMAL, //正常
    KEY_MSG_FULL,   //按键消息满	
}key_msg_e;

//事件处理结果
typedef struct
{
	int up;	  //上
	int down; //下
	int dec;  //减
	int add;  //加
}KEY_Event;

void M_Key_Init(KEY_e key);
KEY_STATUS_e key_get(KEY_e key);
KEY_STATUS_e M_key_check(KEY_e key);

//定时扫描
uint8_t get_key_msg(KEY_MSG_t *keymsg);
void key_IRQHandler(void);

//事件处理方式
void key_event_init(void);
void deal_key_enent(void);

#endif
