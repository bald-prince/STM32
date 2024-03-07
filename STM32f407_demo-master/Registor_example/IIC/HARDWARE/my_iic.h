#ifndef __MY_IIC_H
#define __MY_IIC_H
#include "sys.h"
/* define */
#define SDA_OUT GPIOC->MODER |= (0x01<<16) 
#define SDA_IN GPIOC->MODER &= ~(0x03<<16) 
#define SDA_RD PCin(8)
#define SDA PCout(8)
#define SCL PCout(9)
/* function externation */
void my_iic_init(void);
void my_iic_trans_byte(u8 date);
u8 my_iic_get_ack(void);
void trans_bytes(u8* date);
void my_iic_stop(void);
#endif




