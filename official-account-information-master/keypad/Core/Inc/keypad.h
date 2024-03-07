#ifndef __KEYPAD_H
#define __KEYPAD_H

#include "main.h"
#include "stm32f4xx.h"

#define KEYPADROW GPIOF->IDR
#define KEYPADCOL GPIOG->IDR

#define D_Key_Count 16

#define D_ERR_KEY_CODE 0xFF
#define D_NO_KEY_CODE 0xFF

///===============================================================
typedef struct keypad
{
    uint8_t KeyStatus;
    uint8_t KeyValue_New;
    uint8_t KeyValue_Old;
    uint8_t KeyPress;
    
}Keypad_para;

uint8_t
KeyPad_KEY_Scan(void);
uint8_t KeyPad_GetKeyValue(void);

#endif



