#include "sumjess_stepper_motor.h"
#include "delay.h"
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
//步进电机 驱动例程

/*********************
接线方式:
IN1 ---- PC0
IN2 ---- PC2
IN3 ---- PC3
IN4 ---- PC10
+   ---- +5V
-   ---- GND
*********************/
void bujin_Init(void)
{
	
	
 GPIO_InitTypeDef  GPIO_InitStructure;
 	
 RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);	 
	
 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;				 
 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		
 GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		
 GPIO_Init(GPIOC, &GPIO_InitStructure);					
 GPIO_SetBits(GPIOC,GPIO_Pin_0);		
	
 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;				 
 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		
 GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		
 GPIO_Init(GPIOC, &GPIO_InitStructure);					
 GPIO_SetBits(GPIOC,GPIO_Pin_2);		
	
 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;				 
 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		
 GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		
 GPIO_Init(GPIOC, &GPIO_InitStructure);					
 GPIO_SetBits(GPIOC,GPIO_Pin_3);		
	
 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;				 
 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		
 GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		
 GPIO_Init(GPIOC, &GPIO_InitStructure);					
 GPIO_SetBits(GPIOC,GPIO_Pin_10);		
		
}


/**********************************************
***********************************************
**********开头加50ms延时等待系统稳定***********
***********************************************
***********************************************/

//delay_ms(x);x调节转速

void bujin_Z_Init(void)//顺时针
{
	 GPIO_SetBits(GPIOC,GPIO_Pin_0);	
	 GPIO_ResetBits(GPIOC,GPIO_Pin_2);	
	 GPIO_ResetBits(GPIOC,GPIO_Pin_3);
	 GPIO_ResetBits(GPIOC,GPIO_Pin_10);		
	 delay_ms(3);
	
	 GPIO_ResetBits(GPIOC,GPIO_Pin_0);	
	 GPIO_SetBits(GPIOC,GPIO_Pin_2);	
	 GPIO_ResetBits(GPIOC,GPIO_Pin_3);
	 GPIO_ResetBits(GPIOC,GPIO_Pin_10);		
	 delay_ms(3);
	
	 GPIO_ResetBits(GPIOC,GPIO_Pin_0);	
	 GPIO_ResetBits(GPIOC,GPIO_Pin_2);	
	 GPIO_SetBits(GPIOC,GPIO_Pin_3);
	 GPIO_ResetBits(GPIOC,GPIO_Pin_10);		
	 delay_ms(3);
	
	 GPIO_ResetBits(GPIOC,GPIO_Pin_0);	
	 GPIO_ResetBits(GPIOC,GPIO_Pin_2);	
	 GPIO_ResetBits(GPIOC,GPIO_Pin_3);
	 GPIO_SetBits(GPIOC,GPIO_Pin_10);		
	 delay_ms(3);
	
}


void bujin_F_Init(void)//逆时针
{
	
	 GPIO_ResetBits(GPIOC,GPIO_Pin_0);	
	 GPIO_ResetBits(GPIOC,GPIO_Pin_2);	
	 GPIO_ResetBits(GPIOC,GPIO_Pin_3);
	 GPIO_SetBits(GPIOC,GPIO_Pin_10);		
	 delay_ms(4);	
	
	 GPIO_ResetBits(GPIOC,GPIO_Pin_0);	
	 GPIO_ResetBits(GPIOC,GPIO_Pin_2);	
	 GPIO_SetBits(GPIOC,GPIO_Pin_3);
	 GPIO_ResetBits(GPIOC,GPIO_Pin_10);		
	 delay_ms(4);
	 
	 GPIO_ResetBits(GPIOC,GPIO_Pin_0);	
	 GPIO_SetBits(GPIOC,GPIO_Pin_2);	
	 GPIO_ResetBits(GPIOC,GPIO_Pin_3);
	 GPIO_ResetBits(GPIOC,GPIO_Pin_10);		
	 delay_ms(4);	

	 GPIO_SetBits(GPIOC,GPIO_Pin_0);	
	 GPIO_ResetBits(GPIOC,GPIO_Pin_2);	
	 GPIO_ResetBits(GPIOC,GPIO_Pin_3);
	 GPIO_ResetBits(GPIOC,GPIO_Pin_10);		
	 delay_ms(4);
}

void bujin_D_Init(void)
{
	 GPIO_ResetBits(GPIOC,GPIO_Pin_0);	
	 GPIO_ResetBits(GPIOC,GPIO_Pin_2);	
	 GPIO_ResetBits(GPIOC,GPIO_Pin_3);
	 GPIO_ResetBits(GPIOC,GPIO_Pin_10);			
}




/*

#include "stm32f10x.h"
#include "bujin.h"
#include "delay.h"



 int main(void)
 {	
	 bujin_Init();
   delay_init();
	 delay_ms(50);//等待系统稳定
	 while(1)
	 {
		 
	 
		 bujin_Z_Init();
		 bujin_F_Init();
		 bujin_D_Init();
		 
	}
}





*/

















