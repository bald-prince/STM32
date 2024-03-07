#ifndef _KEY_H
#define _KEY_H
#include "sys.h"
//私有宏
//*移植映射表*
#define WK_UP       HAL_GPIO_ReadPin(GPIOA,GPIO_PIN_0)  //WKUP
#define KEY0        HAL_GPIO_ReadPin(GPIOG,GPIO_PIN_9)  //KEY0
#define KEY1        HAL_GPIO_ReadPin(GPIOG,GPIO_PIN_10) //KEY1
#define KEY2        HAL_GPIO_ReadPin(GPIOG,GPIO_PIN_11) //KEY2
#define KEY3        HAL_GPIO_ReadPin(GPIOG,GPIO_PIN_13) //KEY3
//按键优先级
#define WKUP_PRES   4
#define KEY0_PRES 	1
#define KEY1_PRES   2
#define KEY2_PRES	3
#define KEY3_PRES   5

void KEY_Init(void);
u8 KEY_Scan(u8 mode);

#endif
