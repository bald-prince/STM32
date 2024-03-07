#ifndef __SEG_H
#define __SEG_H
#include "../../USER/stm32f10x.h"
#include "../../USER/system_stm32f10x.h"

#define GPIOA_SET(p,x) do{ \
												 GPIOA->ODR &= ~(0x1<<p); \
												 GPIOA->ODR |= (x<<p); \
											 }while(0);
void HC595_IO_Init(void);
void SEG_DISPLAY(u8 array[]);
void HC595_DISPLAY(u8 pos,u8 dat);
#endif											 
							 
											 
											 