#ifndef __M_KEY_H
#define __M_KEY_H

#include "stm32f10x.h"

//�����Ƕ��尴����ʱ�䣬��λΪ �� 10ms���ж�ʱ�䣩
#define KEY_DOWN_TIME 1
#define KEY_HOLD_TIME 50

//���尴����ϢFIFO��С
#define KEY_MSG_FIFO_SIZE       20      //��� 255��������Ҫ�޸�key_msg_front/key_msg_rear����

//�����˿�ö��
typedef enum
{
	KEY_U, //��
	KEY_D, //��
	
	KEY_L, //��
	KEY_R, //��
	
	KEY_MAX,
}KEY_e;

//����״̬ö��
typedef enum
{
	KEY_DOWN = 0, //�������¶�Ӧ�ĵ�ƽ
	KEY_UP   = 1, //���������Ӧ�ĵ�ƽ
	
	KEY_HOLD,     //��������
}KEY_STATUS_e;

//������Ϣ�ṹ��
typedef struct
{
	KEY_e        key;    //�������
	KEY_STATUS_e status; //����״̬
}KEY_MSG_t;

//���尴����ϢFIFO״̬
typedef enum
{
	KEY_MSG_EMPTY,  //�ް�����Ϣ
	KEY_MSG_NORMAL, //����
    KEY_MSG_FULL,   //������Ϣ��	
}key_msg_e;

//�¼�������
typedef struct
{
	int up;	  //��
	int down; //��
	int dec;  //��
	int add;  //��
}KEY_Event;

void M_Key_Init(KEY_e key);
KEY_STATUS_e key_get(KEY_e key);
KEY_STATUS_e M_key_check(KEY_e key);

//��ʱɨ��
uint8_t get_key_msg(KEY_MSG_t *keymsg);
void key_IRQHandler(void);

//�¼�����ʽ
void key_event_init(void);
void deal_key_enent(void);

#endif
