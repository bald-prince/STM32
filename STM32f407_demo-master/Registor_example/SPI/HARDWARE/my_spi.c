#include "my_spi.h"
#include "delay.h"
/* function defination */
void my_spi_init(void)
{
	/* SPI�˿ڳ�ʼ�� */
	RCC->AHB1ENR |= (1<<1);
	/* GPIO��ʼ�� */
	GPIOC->MODER &= ~(0xFF<<16);    /* ���GPIOB_PIN_8~11 */
	GPIOC->MODER |=  (0x51<<16);    /* ����GPIOB_PIN_8~11ģʽ */
	GPIOC->OTYPER &= ~(0x0F<<8);    /* ����GPIOB_PIN_8~11Ϊ�������  */
	GPIOC->OSPEEDR &= ~(0xFF<<16);  /* ��յ�16λ */
	GPIOC->OSPEEDR |=  (0xFF<<16);  /* ����GPIOB_PIN_8~11�ٶ�Ϊ100Mhz */
	GPIOC->PUPDR &= ~(0xFF<<16);
	GPIOC->PUPDR |=  (0x55<<16);    /* ���� */
	
	/* SPI��ʼ�� */
	SCK = 0;/* �������� */
	SDO = 0;/* �������� */
	
	CS = 0; /* ����ʹ�� ��0��1 */
}
/* ���ݽ��� */
u8 SPI_TR_BYTE(u8 date)
{
	int i;
	u8 rec;
	for(i=0;i<8;i++)
	{
		if( (date&(1<<7)) ==1 )
			SDO = 1;
		else
			SDO = 0;
		/* �����شӻ����յ����� */
		SCK = 0;
		SCK = 1;
		delay_us(5);
		/* �½��������������� */
		SCK = 0;
		rec = SDI;
		date<<=1;
		rec<<=1;
	}
	return rec;
}

