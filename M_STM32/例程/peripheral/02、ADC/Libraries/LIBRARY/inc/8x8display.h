#include "stm32f10x.h"

#define Max7219_pinDIN	    B9
#define Max7219_pinCS		B8
#define Max7219_pinCLK	    B7

#define Max7219_pinDIN_H	M_GPIO_Set(Max7219_pinDIN, HIGH)
#define Max7219_pinDIN_L	M_GPIO_Set(Max7219_pinDIN, LOW)

#define Max7219_pinCS_H		M_GPIO_Set(Max7219_pinCS, HIGH)
#define Max7219_pinCS_L		M_GPIO_Set(Max7219_pinCS, LOW)

#define Max7219_pinCLK_H	M_GPIO_Set(Max7219_pinCLK, HIGH)
#define Max7219_pinCLK_L	M_GPIO_Set(Max7219_pinCLK, LOW)

void Write_Max7219_byte(u8 DATA);         
void Write_Max7219(u8 address,u8 dat);
void Init_MAX7219(void);
void Clear_Display(void);
void Motor_Display(u16 Motor_L, u16 Motor_R);
void Number_Display(float number);
