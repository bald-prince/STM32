#include "digital.h"

u8 Segment_code[]={0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,0x7f,0x6f,0x77,0x7f,0x39,0x5e,0x79};//0~9 A b c d e 
u8 Position[]={0x01,0x02,0x04,0x08,0x10,0x20,0x40,0x80};


void Digital_Init(void)
{
	GPIO_InitTypeDef  GPIO_Initure;
	__HAL_RCC_GPIOF_CLK_ENABLE();           
	
	GPIO_Initure.Pin=GPIO_PIN_13|GPIO_PIN_14|GPIO_PIN_15;
	GPIO_Initure.Mode=GPIO_MODE_OUTPUT_PP;
	GPIO_Initure.Pull=GPIO_PULLUP;
	GPIO_Initure.Speed=GPIO_SPEED_FREQ_HIGH;
	
	HAL_GPIO_Init(GPIOF,&GPIO_Initure);
	
}

void HC595_Transmit_Byte(u8 dat)
{
	u8 i;
	for(i=0;i<8;i++)
	{
		if(dat&0x80)
			HC595_Ds=1;
		else
			HC595_Ds=0;
		
		HC595_STclk=1;
		delay_us(100);
		HC595_STclk=0;
		
		dat<<=1;
	}
	
}

void HC595_Disp_Number(u8 *Disp)
{
	u8 i;
	for(i=7;i>6;i--)//数码管显示位数
	{
	  HC595_Transmit_Byte(~Position[i]);
	  HC595_Transmit_Byte(Segment_code[Disp[i]]);
	  HC595_SHclk=1;
	  delay_us(1);
	  HC595_SHclk=0;
	}
}

	



