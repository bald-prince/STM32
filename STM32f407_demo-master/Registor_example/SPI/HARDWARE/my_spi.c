#include "my_spi.h"
#include "delay.h"
/* function defination */
void my_spi_init(void)
{
	/* SPI端口初始化 */
	RCC->AHB1ENR |= (1<<1);
	/* GPIO初始化 */
	GPIOC->MODER &= ~(0xFF<<16);    /* 清空GPIOB_PIN_8~11 */
	GPIOC->MODER |=  (0x51<<16);    /* 配置GPIOB_PIN_8~11模式 */
	GPIOC->OTYPER &= ~(0x0F<<8);    /* 配置GPIOB_PIN_8~11为推挽输出  */
	GPIOC->OSPEEDR &= ~(0xFF<<16);  /* 清空低16位 */
	GPIOC->OSPEEDR |=  (0xFF<<16);  /* 设置GPIOB_PIN_8~11速度为100Mhz */
	GPIOC->PUPDR &= ~(0xFF<<16);
	GPIOC->PUPDR |=  (0x55<<16);    /* 上拉 */
	
	/* SPI初始化 */
	SCK = 0;/* 总线拉低 */
	SDO = 0;/* 数据清零 */
	
	CS = 0; /* 外设使能 或0或1 */
}
/* 数据交换 */
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
		/* 上升沿从机接收到数据 */
		SCK = 0;
		SCK = 1;
		delay_us(5);
		/* 下降沿主机接收数据 */
		SCK = 0;
		rec = SDI;
		date<<=1;
		rec<<=1;
	}
	return rec;
}

