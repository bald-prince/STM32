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
  S_bus = 0;			//拉低总线	
  S_bus_Enable = 0;	//钳制开始信号
}

void S_bus_TX(float Data)
{
	//开始信号
	u8 distance_fix;
	u8 ii;
	distance_fix = Data;
  S_bus_Enable = 1;
	//数据传输
	for(ii=0;ii<8;ii++)
	{
		if(distance_fix&0x08)
			S_bus = 1;
		else
			S_bus = 0;
		delay_us(2);
		distance_fix<<=1;	
	}
	
	//结束信号
	S_bus_Enable = 0;
}

//时序图
//一次性发送八位数据
//数据脉冲变化间隔2us,读数据时先检测Enable的起始信号，检测到后延时1us开始每隔2us秒读一个数据,一次性读够8位
//           \|/ \|/ \|/ \|/ \|/ 上位机读数据时序
//            _   _   _   _   _
//Data:  ____| |_| |_| |_| |_| |_
//          
//           |<----u8 data---->...|
//            ____________________
//Enable:____|                    |_______
//                
//          /|\                  /|\
//         Start_signal          End_signal      