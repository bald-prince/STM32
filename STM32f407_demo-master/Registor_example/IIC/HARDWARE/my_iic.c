#include "my_iic.h"
#include "delay.h"
/* functon defination */

void my_iic_init(void)
{
	/* SDA SCL initure */
	RCC->AHB1ENR |= (1<<2);
	/* GPIO初始化 */
	GPIOC->MODER &= ~(0x0F<<16);   /* 清空GPIOC_PIN_8,9 MODER寄存器 */
	GPIOC->MODER |=  (0x05<<16);   /* 配置GPIOC_PIN_8,9为输出模式 */
	GPIOC->OTYPER &= ~(0x0F<<16);  /* 配置GPIOC_PIN_8,9为推挽输出 */
	GPIOC->OSPEEDR &= ~(0x0F<<16); /* 清空GPIOC_PIN_8,9OSPEEDR寄存器 */
	GPIOC->OSPEEDR |=  (0x0F<<16); /* 设置GPIOC_PIN_8,9速度为100Mhz */
	GPIOC->PUPDR &= ~(0x0F<<16);   /* 清空GPIOC_PIN_8,9PUPDR寄存器 */
	GPIOC->PUPDR |= (0x05<<16);    /* 设置GPIOC_PIN_8,9上拉 */
	/* SDA=GPIOC_PIN_8 */
	/* SCL=GPIOC_PIN_9 */
	/* IIC 初始化 */
	/* 起始信号 */
	SCL = 0;/* 拉低SDA */
	SDA = 1;/* 拉高SDA */
	SCL = 1;/* 拉高SCL */
	delay_us(5);/* GET SDA=1 */
	SDA = 0;/* 拉低SDA */
	delay_us(5);/* GET SDA=0 */
	SCL = 0;/* 释放总线 */
}
/* 先发送低位 */
void my_iic_trans_byte(u8 date)
{
	int i;
	for(i=0;i<8;i++)
	{
		if( (date&(0x1))==1 )
			SDA = 1;
		else
			SDA = 0;
		/* SCL脉冲 */
		SCL = 1;
		delay_us(5);
		date>>=1;
		SCL = 0;
	}
}
/* 接收应答信号 */
u8 my_iic_get_ack(void)
{
	u8 ack;
	SDA_IN;/* 改变SDA为输入模式 */
	SCL = 1;
  ack = SDA_RD;
	delay_us(5);
	SCL = 0;/* 释放总线 */
	SDA_OUT;
	return ack;
}
/* 多字节发送 */
void trans_bytes(u8* date)
{
	while(date++)
	{
		my_iic_trans_byte(*date);
		if(my_iic_get_ack())
		{
			 printf("ack error\n");
			 break;
		}
	}
}

void my_iic_stop(void)
{
	SCL = 0;
	SDA = 0;
	SCL = 1;
	delay_us(5);
	SDA = 1;
	delay_us(5);
	SCL = 0;
}
