#include "M_key.h"

uint16_t KEY_Pxn[KEY_MAX] = {A0, A1, A2, A3}; //���尴����Ӧ������

/**
  * @brief  ������ʼ��
  * @param  key �����˿�ö��
  * @retval None
  */
void M_Key_Init(KEY_e key)
{
	if(key < KEY_MAX){
		M_GPIO_Init(KEY_Pxn[key], GPIO_Mode_IPU); //��������
	}
	else{
		key = KEY_MAX;
		
		//��ʼ��ȫ������
		while(key--){
			M_GPIO_Init(KEY_Pxn[key], GPIO_Mode_IPU); //��������
		}
	}
}

/**
  * @brief  ��ȡ����״̬����������
  * @param  key �����˿�ö��
  * @retval KEY_STATUS_e ����״̬
  */
KEY_STATUS_e key_get(KEY_e key)
{
	if(M_READ_Data(KEY_Pxn[key]) == KEY_DOWN){
		return KEY_DOWN;
	}
	return KEY_UP;
}

/**
  * @brief  ��ⰴ��״̬��������
  * @param  key �����˿�ö��
  * @retval KEY_STATUS_e ����״̬
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

//===================��ʱɨ��========================
//���尸����ϢFIFO��ر���
KEY_MSG_t key_msg[KEY_MSG_FIFO_SIZE];                  //������ϢFIFO
volatile  uint8_t key_msg_front = 0, key_msg_rear = 0; //����FIFOָ��
volatile  uint8_t key_msg_flag = KEY_MSG_EMPTY;        //������Ϣ��FIFO״̬

/**
  * @brief  ���Ͱ�����Ϣ��FIFO
  * @param  keymsg ������Ϣ
  * @retval none
  */
void send_key_msg(KEY_MSG_t keymsg)
{
	uint8_t tmp;
	
	//������FIFO
	if(key_msg_flag == KEY_MSG_FULL){
		//��Ϣ�����˳�
		return ;
	}
	key_msg[key_msg_rear].key    = keymsg.key;
	key_msg[key_msg_rear].status = keymsg.status;
	key_msg_rear++;
	
	if(key_msg_rear >= KEY_MSG_FIFO_SIZE){
		key_msg_rear = 0; //��ͷ��ʼ
	}
	
	tmp = key_msg_rear;
	if(tmp == key_msg_front){
		key_msg_flag = KEY_MSG_FULL;   //��
	}
	else{
		key_msg_flag = KEY_MSG_NORMAL; //����
	}
	
}	

/**
  * @brief  ��FIFO��ȡ��Ϣ
  * @param  keymsg ������Ϣ
  * @retval ����ֵΪ1 ����Ϣ
			����ֵΪ0 ����Ϣ
  */
uint8_t get_key_msg(KEY_MSG_t *keymsg)
{
	uint8_t tmp;
	
	if(key_msg_flag == KEY_MSG_EMPTY){
		return 0;	//������ϢFIFOΪ�գ�ֱ�ӷ���0
	}
	
	keymsg->key    = key_msg[key_msg_front].key;    //��FIFO�����л�ȡ����ֵ
	keymsg->status = key_msg[key_msg_front].status; //��FIFO���׻�ȡ����״̬
	
	key_msg_front++;								//FIFO��ָ���1��ָ����һ����Ϣ
	
	if(key_msg_front >= KEY_MSG_FIFO_SIZE){
		key_msg_front = 0;	//��ͷ��ʼ����
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
  * @brief  ��ʱ���key״̬
  * @retval none
  */
void key_IRQHandler(void)
{
	KEY_e  keynum;
	static uint8_t keytime[KEY_MAX];	//��������鰴��ʱ��
	
	KEY_MSG_t keymsg;
	
	for(keynum = (KEY_e)0; keynum < KEY_MAX; keynum++){     //��ѯÿ������                 
		if(key_get(keynum) == KEY_DOWN){                    //�жϰ����Ƿ���
			keytime[keynum]++;	                            //����ʱ���ۼ�
			
			if(keytime[keynum] <= KEY_DOWN_TIME){            //�ж�ʱ���Ƿ�û��������ȷ�ϰ���ʱ��
				continue;                                   //δ�ﵽ����
			}
			else if(keytime[keynum] == KEY_DOWN_TIME + 1){  //�Ƿ�Ϊ���µ�ȷ��ʱ��
				keymsg.key    = keynum;
				keymsg.status = KEY_DOWN;
				send_key_msg(keymsg);                       //���Ͱ���ֵ������
			}
			else if(keytime[keynum] <= KEY_HOLD_TIME){       //�Ƿ�û��������HOLD����ȷ��ʱ��
                continue;                                    //û������������ȴ�
            }                                         
            else if(keytime[keynum]  == KEY_HOLD_TIME + 1){  //�Ƿ�Ϊ����holdȷ��ʱ��
                keymsg.key    = keynum;                         
                keymsg.status = KEY_HOLD;
                send_key_msg(keymsg);                        //����
                keytime[keynum] = KEY_DOWN_TIME + 1;
            }
            else{
                keytime[keynum] = KEY_DOWN_TIME + 1;        //�����ظ���� hold ״̬
            }
		}
		else{
            if(keytime[keynum] > KEY_DOWN_TIME){             //���ȷ�Ϲ����°���
                keymsg.key = keynum;
                keymsg.status = KEY_UP;
                send_key_msg(keymsg);                       //���Ͱ���������Ϣ
            }

            keytime[keynum] = 0;                            //ʱ���ۼ���0
        }
	}
}


//=================================key_event=================================
//������ʼ��
void key_event_init(void)
{
	M_Key_Init(KEY_MAX);
}

//�������½��
KEY_Event key_val;

//�������¼�
void deal_key_enent(void)
{
	KEY_MSG_t keymsg;
	
	while(get_key_msg(&keymsg))
	{
		if(keymsg.status == KEY_DOWN){
			switch(keymsg.key){
				case KEY_U:
					//�û���Ӵ���
					key_val.up++;
					break;
					
				case KEY_D:
					//�û���Ӵ���
					key_val.down--;
					break;
					
				case KEY_L:
					//�û���Ӵ���
					key_val.dec--;
					break;
					
				case KEY_R:
					//�û���Ӵ���
					key_val.add++;
					break;
					
				default:
					break;
			}
		}
		else if(keymsg.status == KEY_HOLD){
			switch(keymsg.key){
				case KEY_U:
					//�û���Ӵ���
					
					break;
					
				case KEY_D:
					//�û���Ӵ���
					
					break;
					
				case KEY_L:
					//�û���Ӵ���
					
					break;
					
				case KEY_R:
					//�û���Ӵ���
					
					break;
					
				default:
					break;
			}
		}
		else {
			//������
		}
	}
}



















