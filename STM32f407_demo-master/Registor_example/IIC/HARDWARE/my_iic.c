#include "my_iic.h"
#include "delay.h"
/* functon defination */

void my_iic_init(void)
{
	/* SDA SCL initure */
	RCC->AHB1ENR |= (1<<2);
	/* GPIO��ʼ�� */
	GPIOC->MODER &= ~(0x0F<<16);   /* ���GPIOC_PIN_8,9 MODER�Ĵ��� */
	GPIOC->MODER |=  (0x05<<16);   /* ����GPIOC_PIN_8,9Ϊ���ģʽ */
	GPIOC->OTYPER &= ~(0x0F<<16);  /* ����GPIOC_PIN_8,9Ϊ������� */
	GPIOC->OSPEEDR &= ~(0x0F<<16); /* ���GPIOC_PIN_8,9OSPEEDR�Ĵ��� */
	GPIOC->OSPEEDR |=  (0x0F<<16); /* ����GPIOC_PIN_8,9�ٶ�Ϊ100Mhz */
	GPIOC->PUPDR &= ~(0x0F<<16);   /* ���GPIOC_PIN_8,9PUPDR�Ĵ��� */
	GPIOC->PUPDR |= (0x05<<16);    /* ����GPIOC_PIN_8,9���� */
	/* SDA=GPIOC_PIN_8 */
	/* SCL=GPIOC_PIN_9 */
	/* IIC ��ʼ�� */
	/* ��ʼ�ź� */
	SCL = 0;/* ����SDA */
	SDA = 1;/* ����SDA */
	SCL = 1;/* ����SCL */
	delay_us(5);/* GET SDA=1 */
	SDA = 0;/* ����SDA */
	delay_us(5);/* GET SDA=0 */
	SCL = 0;/* �ͷ����� */
}
/* �ȷ��͵�λ */
void my_iic_trans_byte(u8 date)
{
	int i;
	for(i=0;i<8;i++)
	{
		if( (date&(0x1))==1 )
			SDA = 1;
		else
			SDA = 0;
		/* SCL���� */
		SCL = 1;
		delay_us(5);
		date>>=1;
		SCL = 0;
	}
}
/* ����Ӧ���ź� */
u8 my_iic_get_ack(void)
{
	u8 ack;
	SDA_IN;/* �ı�SDAΪ����ģʽ */
	SCL = 1;
  ack = SDA_RD;
	delay_us(5);
	SCL = 0;/* �ͷ����� */
	SDA_OUT;
	return ack;
}
/* ���ֽڷ��� */
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
