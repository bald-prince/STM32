#ifndef _LED_H
#define _LED_H

#include "sys.h"
void led_reg_init(void);
void Led_Init(void);
/* º¯ÊıÉùÃ÷ */
void led_flow(void);

#define LED0  PCout(0)
#define LED1  PCout(1)

extern int ct;
extern int ct_l;
extern int ct_h;

#endif



