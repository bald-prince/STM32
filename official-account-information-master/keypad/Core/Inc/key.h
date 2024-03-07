#ifndef __KEY_H
#define __KEY_H

#include "stm32f4xx.h"
#include "main.h"
#include "gpio.h"

//下面的方式是通过直接操作HAL库函数方式读取IO
#define KEY0 HAL_GPIO_ReadPin(KEY0_GPIO_Port, KEY0_Pin)  //KEY0按键PE4
#define KEY1 HAL_GPIO_ReadPin(KEY1_GPIO_Port, KEY1_Pin)  //KEY1按键PE3
#define KEY2 HAL_GPIO_ReadPin(KEY2_GPIO_Port, KEY2_Pin)  //KEY2按键PE2
#define WK_UP HAL_GPIO_ReadPin(WK_UP_GPIO_Port, WK_UP_Pin) //WKUP按键PA0

#define KEY0_PRES 1
#define KEY1_PRES 2
#define KEY2_PRES 3
#define WKUP_PRES 4



typedef enum 
{
    key_no_Press,   //按键尚未按下
    key_Press,      //按键按下
    key_PressCheck, //按键是否松开
    key_Release     //按键松开
    
}key_status;

uint8_t KEY_Scan(void);
uint8_t Key_Scan_TimCallBack(void);

#endif
