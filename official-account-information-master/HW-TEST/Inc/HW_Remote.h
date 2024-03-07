#ifndef __HW_REMOTE_H
#define __HW_REMOTE_H
#include "stm32f4xx.h"

//红外遥控识别码(ID),每款遥控器的该值基本都不一样,但也有一样的.
//我们选用的遥控器识别码为0

#define REMOTE_ID 0    
#define RDATA HAL_GPIO_ReadPin(HW_DAT_GPIO_Port,HW_DAT_Pin)
void RemoteInit(void);
uint8_t Remote_Scan(void);
void RemoteDataTimerCallBack(void);
char *KeyValueConvert(uint8_t keyValue);

#endif
