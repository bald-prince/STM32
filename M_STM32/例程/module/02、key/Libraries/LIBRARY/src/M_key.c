#include "M_key.h"

uint16_t KEY_Pxn[KEY_MAX] = {A0, A1, A2, A3}; //定义按键对应的引脚

/**
  * @brief  按键初始化
  * @param  key 按键端口枚举
  * @retval None
  */
void M_Key_Init(KEY_e key)
{
	if(key < KEY_MAX){
		M_GPIO_Init(KEY_Pxn[key], GPIO_Mode_IPU); //上拉输入
	}
	else{
		key = KEY_MAX;
		
		//初始化全部按键
		while(key--){
			M_GPIO_Init(KEY_Pxn[key], GPIO_Mode_IPU); //上拉输入
		}
	}
}

/**
  * @brief  获取按键状态（无消抖）
  * @param  key 按键端口枚举
  * @retval KEY_STATUS_e 按键状态
  */
KEY_STATUS_e key_get(KEY_e key)
{
	if(M_READ_Data(KEY_Pxn[key]) == KEY_DOWN){
		return KEY_DOWN;
	}
	return KEY_UP;
}

/**
  * @brief  检测按键状态（消抖）
  * @param  key 按键端口枚举
  * @retval KEY_STATUS_e 按键状态
  */
KEY_STATUS_e key_check(KEY_e key)
{
	if(key_get(key) == KEY_DOWN){
		M_Delay_ms(10);
		if(key_get(key) == KEY_DOWN){
			return KEY_DOWN;
		}
	}
	return KEY_UP;
}

//===================定时扫描========================
//定义案件消息FIFO相关变量
KEY_MSG_t key_msg[KEY_MSG_FIFO_SIZE];                  //按键消息FIFO
volatile  uint8_t key_msg_front = 0, key_msg_rear = 0; //接受FIFO指针
volatile  uint8_t key_msg_flag = KEY_MSG_EMPTY;        //按键消息的FIFO状态

/**
  * @brief  发送按键消息到FIFO
  * @param  keymsg 按键消息
  * @retval none
  */
void send_key_msg(KEY_MSG_t keymsg)
{
	uint8_t tmp;
	
	//保存在FIFO
	if(key_msg_flag == KEY_MSG_FULL){
		//消息满，退出
		return ;
	}
	key_msg[key_msg_rear].key    = keymsg.key;
	key_msg[key_msg_rear].status = keymsg.status;
	key_msg_rear++;
	
	if(key_msg_rear >= KEY_MSG_FIFO_SIZE){
		key_msg_rear = 0; //重头开始
	}
	
	tmp = key_msg_rear;
	if(tmp == key_msg_front){
		key_msg_flag = KEY_MSG_FULL;   //满
	}
	else{
		key_msg_flag = KEY_MSG_NORMAL; //正常
	}
	
}	

/**
  * @brief  从FIFO获取消息
  * @param  keymsg 按键消息
  * @retval 返回值为1 有消息
			返回值为0 无消息
  */
uint8_t get_key_msg(KEY_MSG_t *keymsg)
{
	uint8_t tmp;
	
	if(key_msg_flag == KEY_MSG_EMPTY){
		return 0;	//按键消息FIFO为空，直接返回0
	}
	
	keymsg->key    = key_msg[key_msg_front].key;    //从FIFO队首中获取按键值
	keymsg->status = key_msg[key_msg_front].status; //从FIFO队首获取按键状态
	
	key_msg_front++;								//FIFO首指针加1，指向下一个消息
	
	if(key_msg_front >= KEY_MSG_FIFO_SIZE){
		key_msg_front = 0;	//重头开始计数
	}
	
	tmp = key_msg_rear;
	if(tmp == key_msg_front){
		key_msg_flag = KEY_MSG_EMPTY;
	}
	else{
		key_msg_flag = KEY_MSG_NORMAL;
	}
	
	return 1;
}

/**
  * @brief  定时检测key状态
  * @retval none
  */
void key_IRQHandler(void)
{
	KEY_e  keynum;
	static uint8_t keytime[KEY_MAX];	//保存各数组按下时间
	
	KEY_MSG_t keymsg;
	
	for(keynum = (KEY_e)0; keynum < KEY_MAX; keynum++){     //轮询每个按键                 
		if(key_get(keynum) == KEY_DOWN){                    //判断按键是否按下
			keytime[keynum]++;	                            //按键时间累加
			
			if(keytime[keynum] <= KEY_DOWN_TIME){            //判断时间是否没超过消抖确认按下时间
				continue;                                   //未达到继续
			}
			else if(keytime[keynum] == KEY_DOWN_TIME + 1){  //是否为按下的确认时间
				keymsg.key    = keynum;
				keymsg.status = KEY_DOWN;
				send_key_msg(keymsg);                       //发送按键值和类型
			}
			else if(keytime[keynum] <= KEY_HOLD_TIME){       //是否没超过长按HOLD按键确认时间
                continue;                                    //没超过，则继续等待
            }                                         
            else if(keytime[keynum]  == KEY_HOLD_TIME + 1){  //是否为长按hold确认时间
                keymsg.key    = keynum;                         
                keymsg.status = KEY_HOLD;
                send_key_msg(keymsg);                        //发送
                keytime[keynum] = KEY_DOWN_TIME + 1;
            }
            else{
                keytime[keynum] = KEY_DOWN_TIME + 1;        //继续重复检测 hold 状态
            }
		}
		else{
            if(keytime[keynum] > KEY_DOWN_TIME){             //如果确认过按下按键
                keymsg.key = keynum;
                keymsg.status = KEY_UP;
                send_key_msg(keymsg);                       //发送按键弹起消息
            }

            keytime[keynum] = 0;                            //时间累计清0
        }
	}
}


//=================================key_event=================================
//按键初始化
void key_event_init(void)
{
	M_Key_Init(KEY_MAX);
}

//按键按下结果
KEY_Event key_val;

//处理按键事件
void deal_key_enent(void)
{
	KEY_MSG_t keymsg;
	
	while(get_key_msg(&keymsg))
	{
		if(keymsg.status == KEY_DOWN){
			switch(keymsg.key){
				case KEY_U:
					//用户添加处理
					key_val.up++;
					break;
					
				case KEY_D:
					//用户添加处理
					key_val.down--;
					break;
					
				case KEY_L:
					//用户添加处理
					key_val.dec--;
					break;
					
				case KEY_R:
					//用户添加处理
					key_val.add++;
					break;
					
				default:
					break;
			}
		}
		else if(keymsg.status == KEY_HOLD){
			switch(keymsg.key){
				case KEY_U:
					//用户添加处理
					
					break;
					
				case KEY_D:
					//用户添加处理
					
					break;
					
				case KEY_L:
					//用户添加处理
					
					break;
					
				case KEY_R:
					//用户添加处理
					
					break;
					
				default:
					break;
			}
		}
		else {
			//不处理
		}
	}
}



















