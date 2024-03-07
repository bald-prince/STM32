#include "Single_bus.h"


void S_bus_Init()
{
	GPIO_InitTypeDef S_bus_GPIO_structure;
	S_bus_GPIO_structure.GPIO_Pin = GPIO_Pin_9;
	S_bus_GPIO_structure.GPIO_Mode = GPIO_Mode_Out_PP;
	S_bus_GPIO_structure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &S_bus_GPIO_structure);	
	
	S_bus_GPIO_structure.GPIO_Pin = GPIO_Pin_1;
  GPIO_Init(GPIOA, &S_bus_GPIO_structure);					 
  S_bus = 0;			//��������	
  S_bus_Enable = 0;	//ǯ�ƿ�ʼ�ź�
}

void S_bus_TX(float Data)
{
	//��ʼ�ź�
	u8 distance_fix;
	u8 ii;
	distance_fix = Data;
  S_bus_Enable = 1;
	//���ݴ���
	for(ii=0;ii<8;ii++)
	{
		if(distance_fix&0x08)
			S_bus = 1;
		else
			S_bus = 0;
		delay_us(2);
		distance_fix<<=1;	
	}
	
	//�����ź�
	S_bus_Enable = 0;
}

//ʱ��ͼ
//һ���Է��Ͱ�λ����
//��������仯���2us,������ʱ�ȼ��Enable����ʼ�źţ���⵽����ʱ1us��ʼÿ��2us���һ������,һ���Զ���8λ
//           \|/ \|/ \|/ \|/ \|/ ��λ��������ʱ��
//            _   _   _   _   _
//Data:  ____| |_| |_| |_| |_| |_
//          
//           |<----u8 data---->...|
//            ____________________
//Enable:____|                    |_______
//                
//          /|\                  /|\
//         Start_signal          End_signal      