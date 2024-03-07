/*

*******************************************************************************
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
********************************************************************************





void IWDG_WriteAccessCmd(uint16_t IWDG_WriteAccess);//取消写保护：0x5555使能
void IWDG_SetPrescaler(uint8_t IWDG_Prescaler);//设置预分频系数：写PR
void IWDG_SetReload(uint16_t Reload);//设置重装载值：写RLR
void IWDG_ReloadCounter(void);//喂狗：写0xAAAA到KR
void IWDG_Enable(void);//使能看门狗：写0xCCCC到KR
FlagStatus IWDG_GetFlagStatus(uint16_t IWDG_FLAG);//状态：重装载/预分频 更新


①  取消寄存器写保护：
      IWDG_WriteAccessCmd();
②  设置独立看门狗的预分频系数，确定时钟:
     IWDG_SetPrescaler();
③  设置看门狗重装载值，确定溢出时间:
    IWDG_SetReload();
④  使能看门狗
    IWDG_Enable();
⑤  应用程序喂狗:
   IWDG_ReloadCounter();

溢出时间计算：
   Tout=((4×2^prer) ×rlr) /40 （M3)







#include "led.h"
#include "delay.h"
#include "key.h"
#include "sys.h"
#include "wdg.h"


 int main(void)
 {		
	delay_init();	    	 //延时函数初始化	  
 	LED_Init();		  	 //初始化与LED连接的硬件接口
	KEY_Init();          //按键初始化	 
	delay_ms(500);   	 //让人看得到灭
	IWDG_Init(4,625);    //与分频数为64,重载值为625,溢出时间为1s	   
	LED0=0;				 //点亮LED0
	while(1)
	{
		if(KEY_Scan(0)==WK_UP)
		{
			IWDG_Feed();//如果WK_UP按下,则喂狗
		}
		delay_ms(10);
	};	 
}
  
  
  
  
  
  
  
  
  */
