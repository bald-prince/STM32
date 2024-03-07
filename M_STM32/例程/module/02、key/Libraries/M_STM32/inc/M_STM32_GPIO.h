#ifndef __M_STM32_GPIO_H
#define __M_STM32_GPIO_H

#include "stm32f10x.h"

//***************************GPIOA引脚定义***********************************
#define A0 0x10
#define A1 0x11
#define A2 0x12
#define A3 0x13
#define A4 0x14
#define A5 0x15
#define A6 0x16
#define A7 0x17
#define A8 0x18
#define A9 0x19
#define A10 0x1A
#define A11 0x1B
#define A12 0x1C
#define A13 0x1D
#define A14 0x1E
#define A15 0x1F
//***************************GPIOB引脚定义***********************************
#define B0 0x20
#define B1 0x21
#define B2 0x22
#define B3 0x23
#define B4 0x24
#define B5 0x25
#define B6 0x26
#define B7 0x27
#define B8 0x28
#define B9 0x29
#define B10 0x2A
#define B11 0x2B
#define B12 0x2C
#define B13 0x2D
#define B14 0x2E
#define B15 0x2F
//***************************GPIOC引脚定义***********************************
#define C0 0x30
#define C1 0x31
#define C2 0x32
#define C3 0x33
#define C4 0x34
#define C5 0x35
#define C6 0x36
#define C7 0x37
#define C8 0x38
#define C9 0x39
#define C10 0x3A
#define C11 0x3B
#define C12 0x3C
#define C13 0x3D
#define C14 0x3E
#define C15 0x3F
//***************************GPIOD引脚定义***********************************
#define D0 0x40
#define D1 0x41
#define D2 0x42
#define D3 0x43
#define D4 0x44
#define D5 0x45
#define D6 0x46
#define D7 0x47
#define D8 0x48
#define D9 0x49
#define D10 0x4A
#define D11 0x4B
#define D12 0x4C
#define D13 0x4D
#define D14 0x4E
#define D15 0x4F
//***************************GPIOA引脚定义***********************************
#define E0 0x50
#define E1 0x51
#define E2 0x52
#define E3 0x53
#define E4 0x54
#define E5 0x55
#define E6 0x56
#define E7 0x57
#define E8 0x58
#define E9 0x59
#define E10 0x5A
#define E11 0x5B
#define E12 0x5C
#define E13 0x5D
#define E14 0x5E
#define E15 0x5F
//***************************GPIOF引脚定义***********************************
#define F0 0x60
#define F1 0x61
#define F2 0x62
#define F3 0x63
#define F4 0x64
#define F5 0x65
#define F6 0x66
#define F7 0x67
#define F8 0x68
#define F9 0x69
#define F10 0x6A
#define F11 0x6B
#define F12 0x6C
#define F13 0x6D
#define F14 0x6E
#define F15 0x6F
//***************************GPIOG引脚定义***********************************
#define G0 0x70
#define G1 0x71
#define G2 0x72
#define G3 0x73
#define G4 0x74
#define G5 0x75
#define G6 0x76
#define G7 0x77
#define G8 0x78
#define G9 0x79
#define G10 0x7A
#define G11 0x7B
#define G12 0x7C
#define G13 0x7D
#define G14 0x7E
#define G15 0x7F

#define HIGH 1
#define LOW  0

void M_GPIO_Init(uint16_t PTx, uint16_t GPIO_Mode);				//初始化GPIO口
void M_GPIO_Set(uint16_t PTx, char Data);	                //设置引脚输出高低电平
uint8_t M_READ_Data(uint16_t PTx);			                //读取引脚数据

#endif
