#ifndef _LED_H
#define _LED_H
#include "sys.h"

#define LED0 PCout(0)
#define LED1 PCout(1)
#define LED2 PCout(2)
#define LED3 PCout(3)
#define LED4 PCout(4)
#define LED5 PCout(5)
#define LED6 PCout(6)
#define LED7 PCout(7)

void LED_Init(void);
void LED_light(int num);

extern u8 table[4][8];
void LED_Init(void);
u8 youyi_led(u8 dat,u8 number);          
u8 zuoyi_led(u8 dat,u8 number);
void kekong_Led(u8 Led_dat,u8 direct);
void Write_Pin(u8 dat); 
void shuzu_Led(void);
void Flow_Led(u8 Led_dat);
void kekong_Led_led(u8 Led_dat);
  
#endif
