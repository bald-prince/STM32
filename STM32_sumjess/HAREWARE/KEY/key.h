#ifndef __KEY_H
#define __KEY_H	 
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
【problem 】
    （1）库内补充的不全面；
    （2）库内解释部分不全面；
    （3）库内还存在一定的bug；
【direction】
      下一步的目标就是把库继续集成！
【explain 】
      本库是根据正点原子、中景园电子、优信电子等商家改编而成，
      同时为了方便使用，我也自己写了很多的库，和优化了算法和表示方式！
【warning】
      目前程序中暂无警告 ！   
---------------------------------------------------------------------------------
没有完美的代码，只有不断的奉献，大家一起努力；
赠人玫瑰手留余香，欢迎大家反馈bug！
================================================================================
********************************************************************************/	
//按键驱动 代码	        	 
 
#define left_rd      GPIO_ReadInputDataBit(GPIOD,GPIO_Pin_3)//读取左
#define leftmid_rd   GPIO_ReadInputDataBit(GPIOD,GPIO_Pin_4)//读取左中
#define mid_rd       GPIO_ReadInputDataBit(GPIOD,GPIO_Pin_5)//读取中  
#define rightmid_rd  GPIO_ReadInputDataBit(GPIOD,GPIO_Pin_6)//读取右中
#define right_rd     GPIO_ReadInputDataBit(GPIOD,GPIO_Pin_7)//读取右
#define WK_UP   GPIO_ReadInputDataBit(GPIOD,GPIO_Pin_0)     //读取 
#define KEY0  GPIO_ReadInputDataBit(GPIOD,GPIO_Pin_1)       //读取
#define KEY1  GPIO_ReadInputDataBit(GPIOD,GPIO_Pin_2)      //读取

#define KE  GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_5)//读取按键0
#define KEY  GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_15)//读取按键1
#define WK_U   GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_0)//读取按键2 
 

#define KEY0_PRES	1		//KEY0  
#define KEY1_PRES	2		//KEY1 
#define WKUP_PRES	3		//WK_UP  

void KEY_Init(void);//IO初始化
u8 KEY_Scan(u8 mode);  	//按键扫描函数			


#endif



