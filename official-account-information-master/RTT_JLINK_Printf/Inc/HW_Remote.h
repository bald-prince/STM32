#ifndef __HW_REMOTE_H
#define __HW_REMOTE_H
#include "stm32f4xx.h"

//����ң��ʶ����(ID),ÿ��ң�����ĸ�ֵ��������һ��,��Ҳ��һ����.
//����ѡ�õ�ң����ʶ����Ϊ0

#define REMOTE_ID 0    
#define RDATA HAL_GPIO_ReadPin(HW_DAT_GPIO_Port,HW_DAT_Pin)
void RemoteInit(void);
uint8_t Remote_Scan(void);
void RemoteDataTimerCallBack(void);
char *KeyValueConvert(uint8_t keyValue);

#endif
