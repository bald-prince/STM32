#ifndef __MY_DMA_H
#define __MY_DMA_H
#include "sys.h"

#define DATE_SIZE 7200
/* DMA_FUNCTION EXTERN */
void DMA_Init(u32 reg_addr,u32 per_addr,u16 date_size);
void DMA_TX(void);
/* extern values */
extern u8 Caches[DATE_SIZE];

#endif 



