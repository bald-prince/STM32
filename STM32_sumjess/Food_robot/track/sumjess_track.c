#include "sumjess_track.h" 
#include "sumjess_track_motor.h" 
#include "key.h"
#include "delay.h"  
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
//FoodDelivered-Robot 循迹部分

int sensor[5] = {0, 0, 0, 0, 0}; //循迹模块数据采集存储数组
int error = 0;
extern int track_media ;

void track_data(void)    //数据采集
{
  sensor[0] = 0;//left_rd;
  sensor[1] = leftmid_rd;
  sensor[2] = mid_rd;
  sensor[3] = rightmid_rd;
  sensor[4] = 0;//right_rd;
}
///////1为黑线///////
int track_decide(void)    //数据处理
{
 //偏差处理
 if ((sensor[1] == 0) && (sensor[2] == 0) && (sensor[3] == 0)) {
      error = 0;/////////////000///停车//////////////
    } else if ((sensor[1] == 0) && (sensor[2] == 0) && (sensor[3] == 1)) {
      error = -2;////////////001///右转//////////////
    } else if ((sensor[1] == 0) && (sensor[2] == 1) && (sensor[3] == 0)) {
      error = 0;/////////////010///直行//////////////
    } else if ((sensor[1] == 0) && (sensor[2] == 1) && (sensor[3] == 1)) {
      error = -1;////////////011///右转//////////////
    } else if ((sensor[1] == 1) && (sensor[2] == 0) && (sensor[3] == 0)) {
      error = 2;/////////////100///左转//////////////
    } else if ((sensor[1] == 1) && (sensor[2] == 1) && (sensor[3] == 0)) {
      error = 1;/////////////110///左转//////////////
    } else if ((sensor[1] == 1) && (sensor[2] == 1) && (sensor[3] == 1)) {
      error = 6;/////////////111///直行//////////////
    } 
 //元素处理
    if ((sensor[4] == 1)&&(sensor[0] == 1))  {
		     error=0;////////////1XXX1///停车//////////////////
		   } else if (sensor[4] == 1)  {
		     error=5;////////////0XXX1///右转90度//////////////
		   } else if (sensor[0] == 1)   {
				 error=6;////////////1XXX0///左转90度//////////////
       }
			 
    return error;     //返回目前情况
}

void track_motor(void)    //电机执行
{
  switch (track_media){              //读取初值  
     case 0:  forward();          break; //直行
     case -1: turnSRight();       break; //小左
     case -2: turnRight();        break; //大左 
     case 1:  turnSLeft();        break; //小右
     case 2:  turnLeft();         break; //大右    
     case 3:  stop();             break; //停
     case 5:  turnright_90d();    break; //右转90度
     case 6:  turnleft_90d();     break; //左转90度
     default: stop();             break; //停  
     }
	 }


