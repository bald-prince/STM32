#ifndef __LED_H
#define __LED_H	 
#include "sys.h"
/*******************************************************************************
================================================================================
【平    台】stm32f103zet6_sumjess平台
【编    写】sumjess
【E-mail  】1371129880@qq.com
【软件版本】V2.0
【最后更新】2018年09月06日
【相关信息参考下列地址】
【网    站】
           https://blog.csdn.net/qq_38351824
           http://www.openedv.com/
           http://www.stmcu.org/
					 http://www.firebbs.cn/forum.php
---------------------------------------------------------------------------------
【dev.env.】MDK5.14及以上版本
【Target  】stm32f103zet6
第一次修订：2017/11/09
第二次修订：2018/01/21
第三次修订：2018/09/06
---------------------------------------------------------------------------------
没有完美的代码，只有不断的奉献，大家一起努力；
赠人玫瑰手留余香，欢迎大家反馈bug！
================================================================================
********************************************************************************/	
//LED驱动 代码	  


#define LED0 PBout(0)	// PB8
#define LED1 PBout(12)// PB12	
#define LED2 PDout(13)	// PE2	
#define Relay PDout(15)	// PE2

#define LIGHT   GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_4)//读取

void LED_Init(void);//初始化
void relay_Init(void);//继电器初始化
void light_Init(void);

#endif
