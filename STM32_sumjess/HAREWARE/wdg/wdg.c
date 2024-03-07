#include "wdg.h"

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
//独立看门狗

//独立看门狗   //Tout=[2^prer)×rlr]/10000s  prer:3位0-8 rlr:12位1-4096
void IWDG_Init(u8 prer,u16 rlr)    //IWDG_Init(5,625);//Tout=(2^6*625)/10000s=2s
{	
 	IWDG_WriteAccessCmd(IWDG_WriteAccess_Enable);  //使能对寄存器IWDG_PR和IWDG_RLR的写操作
	IWDG_SetPrescaler(prer);                       //设置IWDG预分频值:设置IWDG预分频值为64
	IWDG_SetReload(rlr);                           //设置IWDG重装载值
	IWDG_ReloadCounter();                          //按照IWDG重装载寄存器的值重装载IWDG计数器
	IWDG_Enable();                                 //使能IWDG
}
//喂独立看门狗
void IWDG_Feed(void)
{   
 	IWDG_ReloadCounter();	//重载计数值									   
}




/*//一般不用

//保存WWDG计数器的设置值,默认为最大. 
u8 WWDG_CNT=0x7f; 
//初始化窗口看门狗 	
//tr   :T[6:0],计数器值 0-127
//wr   :W[5:0],窗口值 0-64
//fprer:分频系数（WDGTB）,仅最低2位有效 
//Fwwdg=(4096*2^fprer)*(上：tr-wr   下：tr-0x3f)/PCLK1(36Mhz)

void WWDG_Init(u8 tr,u8 wr,u32 fprer)//Fwwdg=(4096*2^fprer)*(上：tr-wr   下：tr-0x3f)/PCLK1(36Mhz)
{ 
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_WWDG, ENABLE);  //WWDG时钟使能
	WWDG_CNT=tr&WWDG_CNT;                                 //初始化WWDG_CNT.   
	WWDG_SetPrescaler(fprer);                             //设置IWDG预分频值
	WWDG_SetWindowValue(wr);                              //设置窗口值
	WWDG_Enable(WWDG_CNT);	                              //使能看门狗 ,设置 counter .                  
	WWDG_ClearFlag();                                     //清除提前唤醒中断标志位 
	WWDG_NVIC_Init();                                     //初始化窗口看门狗 NVIC
	WWDG_EnableIT();                                      //开启窗口看门狗中断
} 
//重设置WWDG计数器的值
void WWDG_Set_Counter(u8 cnt)
{
    WWDG_Enable(cnt);//使能看门狗 ,	设置 counter .	 
}

void WWDG_NVIC_Init(void)
{
	NVIC_InitTypeDef NVIC_InitStructure;
	NVIC_InitStructure.NVIC_IRQChannel = WWDG_IRQn;   
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = WWDG_IRQHandler_NVIC_IRQChannelPreemptionPriority;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;	 
  NVIC_InitStructure.NVIC_IRQChannelCmd=ENABLE; 
	NVIC_Init(&NVIC_InitStructure);
}
//窗口看门狗中断服务程序
void WWDG_IRQHandler(void)
{
	WWDG_SetCounter(WWDG_CNT);	  //当禁掉此句后,窗口看门狗将产生复位
	WWDG_ClearFlag();	  //清除提前唤醒中断标志位
}

*/

