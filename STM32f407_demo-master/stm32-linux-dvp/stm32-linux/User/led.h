#ifndef __LED_H
#define __LED_H

//[第一个Linux下的STM32项目] -------- [Light LED]
//[日期 ：] ---- [ 2020.9.16 ] ----  [ 16:34 ]
//[作者 ：] ---- [ 熊诺晔 ] ---- [ Xiong Nuoye ]
//[版本 ：] ---- [ V1.0  ]
//[License :] ---- [GPL]

/* 寄存器基地址 */
//[ 参考ST官网的用户手册即可 ] ----- [ http://www.st.com ]
//[ 原理图参考自己的开发板   ] ----- [ ... ]
/*
#define RCC_BASE            (0x40023800U)

#define AHB1_ENR_BASE       (0x40023830U)

//[ GPIOC挂在AHB1上 ] --- [ 使能AHB1的时间 ]
#define AHB1_ENR *((volatile unsigned int *)AHB1_ENR_BASE)

//[ GPIOC通用寄存器 ]
#define GPIOC_BASE (0x40020800U)

typedef struct
{
    volatile unsigned int MODER;
    volatile unsigned int OTYPER;
    volatile unsigned int OSPEEDR;
    volatile unsigned int PUPDR;
    volatile unsigned int IDR;
    volatile unsigned int ODR;
    volatile unsigned int BSRR;
    volatile unsigned int LCKR;
    volatile unsigned int AFRL;
    volatile unsigned int AFRH;
}GPIOC;

#define GPIOC_R ((GPIOC*)GPIOC_BASE)
*/

typedef unsigned char u8;

//[extern]
void Led_Init(void);
void Led_Write(int index,int state);
void Led_Flash(int delay);
void mydelay(int ms);
void Led_Flow(void);

#endif





