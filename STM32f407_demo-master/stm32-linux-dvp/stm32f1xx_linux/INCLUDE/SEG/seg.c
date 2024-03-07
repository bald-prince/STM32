#include "seg.h"

void self_delay(int times);
u8 pos_code[8] = {0x01,0x02,0x04,0x08,0x10,0x20,0x40,0x80};
u8 seg_code[10] = {0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,0x7f,0x6f}; // 0 ~ 9

void HC595_IO_Init(void)
{
	RCC->APB1ENR |= (0x1<<1); // Port A CLK ENABLE
	GPIOA->CRL  &= 0x000fffff;
	GPIOA->CRL  |= (0x333<<20);
	
	/* 将时钟线拉低 */
	GPIOA_SET(5,0);    // SH_CP
	GPIOA_SET(7,0);		 // ST_CP
}

void HC595_TRANS_BYTE(u8 data)
{
	for (int i=0;i<8;i++)
	{
		if (data & 0x80)
		{
			GPIOA_SET(6,1); // DS
		}
		else
		{
			GPIOA_SET(6,0); 
		}
		GPIOA_SET(5,1);    // CP UP
		// self_delay(20);
		GPIOA_SET(5,0);    // CP DOWN
		data <<= 1;
	}
}

void HC595_DISPLAY(u8 pos,u8 dat)
{
	HC595_TRANS_BYTE(~pos_code[pos]);
	HC595_TRANS_BYTE(seg_code[dat]);
	GPIOA_SET(7,1);      // CP UP
	// self_delay(20);
  GPIOA_SET(7,0);      // CP DOWN
}

void SEG_DISPLAY(u8 array[])
{
	for (int i=0;i<4;i++)
	{
		HC595_DISPLAY(i,array[i]);
		// self_delay(20);
	}
}

void self_delay(int times)
{
	for (int i=0;i<times;i++)
	{
		;
	}
}




