#include "led.h"
#include "../Include/stm32f407xx.h"
#include "delay.h"
//[第一个Linux下的STM32项目] -------- [Light LED]
//[日期 ：] ---- [ 2020.9.16 ] ----  [ 16:34 ]
//[作者 ：] ---- [ 熊诺晔 ] ---- [ Xiong Nuoye ]
//[版本 ：] ---- [ V1.0  ]
//[License :] ---- [GPL]

//[LED初始化 ：]

void Led_Init(void)
{
    /*
    //1.初始化AHB1时钟
    AHB1_ENR  |= (0x1<<2);              // [使能GPIOC的时钟]
    //2.初始化GPIO
    GPIOC_R->MODER &= (1<<17);          // [清空寄存器低16位]
	GPIOC_R->MODER |= (0x5555);         // [配置PIN0~7为输出模式] 
	GPIOC_R->OTYPER &= (1<<17);         // [配置PIN0~7为推挽输出] 
	GPIOC_R->OSPEEDR &= (1<<17);        // [清空低16位] 
	GPIOC_R->OSPEEDR |= (0xAAAA);       // [设置PIN0~7速度为50Mhz]
	GPIOC_R->PUPDR &= (1<<17);
	GPIOC_R->PUPDR |= (0x5555);
	
	// [初始状态led全亮]
	GPIOC_R->ODR = 0x00;
    */
   RCC->AHB1ENR |= (1<<2);
   GPIOC->MODER &= (1<<17);
   GPIOC->MODER |= (0x5555);
   GPIOC->OTYPER &= (1<<17);
   GPIOC->OSPEEDR &= (1<<17);        // [清空低16位] 
   GPIOC->OSPEEDR |= (0xAAAA);       // [设置PIN0~7速度为50Mhz]
   GPIOC->PUPDR &= (1<<17);
   GPIOC->PUPDR |= (0x5555);

   GPIOC->ODR |= 0xff;
}

void Led_Write(int index,int state)
{
    /*
    if( state && (index>0) )
        GPIOC_R->ODR &= ( ~(0x1<<((index-1)%7) ) );         // [ 亮灯 ]
    else if( !state && (index>0) )
        GPIOC_R->ODR |= ( 0x1<<((index-1)%7) );             // [ 灭灯 ]
    */
    if( state && (index>=0) )
        GPIOC->ODR &= ( ~(0x1<<((index)%8) ) );           // [ 亮灯 ]
    else if( !state && (index>=0) )
        GPIOC->ODR |= ( 0x1<<((index)%8) );               // [ 灭灯 ]
}

#define ON      1
#define OFF     0

void Led_Flash(void)
{
    // [ 放在循环里 ]
    for(int i=0;i<8;i++)
        Led_Write(i,ON);
    for(int i=0;i<1680000;i++)
	;
    for(int i=0;i<8;i++)
        Led_Write(i,OFF);
    for(int i=0;i<1680000;i++)
	;
}

void Led_Flow(void)
{
	static u8 led_flow = 0x01;
	GPIOC->ODR = ~led_flow;
	led_flow <<= 1;
	if(led_flow == 0)
	{
		led_flow = 0x01;
	}
	delay_ms(200);
	// for(int i=0;i<168000;i++)
	// ;
}
