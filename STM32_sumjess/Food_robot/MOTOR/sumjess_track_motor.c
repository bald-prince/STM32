#include "sumjess_track_motor.h" 
#include "sumjess_pwm.h"

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
//FoodDelivered-Robot 循迹部分 ----电机



void forward(void)         //前进
{
  TIM_SetCompare1(TIM3,7);
	TIM_SetCompare2(TIM3,0);
	TIM_SetCompare3(TIM3,7);
	TIM_SetCompare4(TIM3,0);
}

void turnSRight(void)      //小右
{
  TIM_SetCompare1(TIM3,0);
	TIM_SetCompare2(TIM3,0);
	TIM_SetCompare3(TIM3,7);
	TIM_SetCompare4(TIM3,0);
}

void turnRight(void)       //右转
{
  TIM_SetCompare1(TIM3,5);
	TIM_SetCompare2(TIM3,0);
	TIM_SetCompare3(TIM3,15);
	TIM_SetCompare4(TIM3,0);
}

void turnSLeft(void)       //小左
{
  TIM_SetCompare1(TIM3,7);
	TIM_SetCompare2(TIM3,0);
	TIM_SetCompare3(TIM3,0);
	TIM_SetCompare4(TIM3,0);
}

void turnLeft(void)        //左转
{
  TIM_SetCompare1(TIM3,15);
	TIM_SetCompare2(TIM3,0);
	TIM_SetCompare3(TIM3,5);
	TIM_SetCompare4(TIM3,0);
}

void stop(void)            //停车
{
  TIM_SetCompare1(TIM3,0);
	TIM_SetCompare2(TIM3,0);
	TIM_SetCompare3(TIM3,0);
	TIM_SetCompare4(TIM3,0);
}

void turnright_90d(void)   //右90度
{
  TIM_SetCompare1(TIM3,0);
	TIM_SetCompare2(TIM3,15);
	TIM_SetCompare3(TIM3,15);
	TIM_SetCompare4(TIM3,0);
}

void turnleft_90d(void)    //左90度
{
  TIM_SetCompare1(TIM3,15);
	TIM_SetCompare2(TIM3,0);
	TIM_SetCompare3(TIM3,0);
	TIM_SetCompare4(TIM3,0);
}

                                                                     






