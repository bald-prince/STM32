#include "sumjess_key4x4.h"

/*******************************************************************************
================================================================================
【平    台】stm32f103zet6_sumjess平台
【编    写】sumjess
【E-mail  】1371129880@qq.com
【软件版本】V2.0
【最后更新】2018年01月21日
【相关信息参考下列地址】
【网    站】http://www.openedv.com/
           http://www.stmcu.org/
					 http://www.firebbs.cn/forum.php
---------------------------------------------------------------------------------
【dev.env.】MDK5.14及以上版本
【Target  】stm32f103zet6
第一次修订：2017/11/09
第二次修订：2018/01/21
---------------------------------------------------------------------------------
没有完美的代码，只有不断的奉献，大家一起努力；
赠人玫瑰手留余香，欢迎大家反馈bug！
================================================================================
********************************************************************************/	
//按键驱动 代码	      

//初始化PB0-7为输出口.并使能这两个口的时钟		    

void key44_Init(void)
{

 GPIO_InitTypeDef  GPIO_InitStruct;
 RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);	 //使能PB端口时钟
	
 GPIO_InitStruct.GPIO_Pin = GPIO_Pin_8|GPIO_Pin_9|GPIO_Pin_10|GPIO_Pin_11;				 //端口配置
 GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP; 		 //推挽输出
 GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;		 //IO口速度为50MHz
 GPIO_Init(GPIOB, &GPIO_InitStruct);					 //根据设定参数初始化GPIOB

 GPIO_InitStruct.GPIO_Pin = GPIO_Pin_12|GPIO_Pin_13|GPIO_Pin_14|GPIO_Pin_15;				 //端口配置
 GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IPD; 		 //下拉输入
 GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;		 //IO口速度为50MHz
 GPIO_Init(GPIOB, &GPIO_InitStruct);					 //根据设定参数初始化GPIOB
	
}
 
/**-------------------------------------------------------
  * @函数名 STM32_KEYScan
  * @功能   获取KEY按键的输入电平状态，按键按下时为低电平0
  * @参数   无
  * @返回值 1  对应开发板上第一个KEY按键处于按下状态
  *         2  对应开发板上第二个KEY按键处于按下状态
  *         3  对应开发板上第三个KEY按键处于按下状态
  *         4  对应开发板上第四个KEY按键处于按下状态
  *         0  开发板上没有KEY按键处于按下状态
***------------------------------------------------------*/
int STM32_KEYScan(void) //实现矩阵键盘。返回值为，各按键的键值，此键值由用户自己定义。
{
	u8 KeyVal;	 //keyVal为最后返回的键值。

	GPIO_Write(GPIOB,(GPIOB->ODR & 0xf0ff | 0x0100));	//让PB11到PB8输出二进制的0001.

		switch(GPIOB->IDR & 0xf000)//对PB12到PB15的值进行判断，以输出不同的键值。
			{
				case 0x1000: KeyVal=1; break;
				case 0x2000: KeyVal=2;	break;
				case 0x4000: KeyVal=3;	break;
				case 0x8000: KeyVal='A';	break;
			}
	   
	GPIO_Write(GPIOB,(GPIOB->ODR & 0xf0ff | 0x0200));	//让PB11到PB8输出二进制的0.
		switch(GPIOB->IDR & 0xf000)		        //对PB12到PB15的值进行判断，以输出不同的键值。
		{
			case 0x1000: KeyVal=4;	break;
			case 0x2000: KeyVal=5;	break;
			case 0x4000: KeyVal=6;	break;
			case 0x8000: KeyVal='B';	break;
		}

	GPIO_Write(GPIOB,(GPIOB->ODR & 0xf0ff | 0x0400));	//让PB11到PB8输出二进制的1011.
		switch(GPIOB->IDR & 0xf000)		        //对PB12到PB15的值进行判断，以输出不同的键值。
		{
			case 0x1000: KeyVal=7;	break;
			case 0x2000: KeyVal=8;	break;
			case 0x4000: KeyVal=9;	break;
			case 0x8000: KeyVal='C';	break;
		}
 
	 GPIO_Write(GPIOB,(GPIOB->ODR & 0xf0ff | 0x0800));	//让PB11到PB8输出二进制的0111.
		switch(GPIOB->IDR & 0xf000)		        //对PB12到PB15的值进行判断，以输出不同的键值。
		{
			case 0x1000: KeyVal='*';	break;
			case 0x2000: KeyVal=0;	break;
			case 0x4000: KeyVal='#';	break;
			case 0x8000: KeyVal='D';	break;
		}									  
	return KeyVal;
}



