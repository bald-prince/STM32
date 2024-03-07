#ifndef __DMA_H
#define __DMA_H

#include "delay.h"
/* extern */
extern unsigned char dma_buf[4096];
/* op */
void My_DMA_Init();
void My_DMA_Start();
void My_DMA_Stop();

#endif
