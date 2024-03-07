#ifndef _Digital_H
#define _Digital_H

#include "sys.h"
#include "delay.h"
//移植映射表
#define HC595_STclk  PFout(13)
#define HC595_SHclk  PFout(14)
#define HC595_Ds     PFout(15)
//外部引用
extern u8 Segment_code[];
extern u8 Position[];
extern u8 Disp_Number[];

void Digital_Init(void);

void HC595_Transmit_Byte(u8 dat);
void HC595_Disp_Number(u8 *Disp);


#endif

