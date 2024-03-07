#include "graph.h"
#include "oled.h"
//////////////////////////////////////////////////////////////////////////////////	 
//本程序只供学习使用，未经作者许可，不得用于其它任何用途
//ALIENTEK Mini STM32开发板
//OLED汉字显示驱动代码
//驱动方式:8080并口/4线串口
//正点原子@ALIENTEK
//技术论坛:www.openedv.com
//修改日期:2014/03/25
//版本：V1.0
//版权所有，盗版必究。
//Copyright(C) 广州市星翼电子科技有限公司 2009-2019
//All rights reserved	   
////////////////////////////////////////////////////////////////////////////////// 	
#define img_numbers 100
#define img_size    1023

//24*24的OLED汉字点阵，包括三个汉字：开、发、板。这三个汉字的点阵库，是利用PCtoLCD2002生产的，
//软件设置的取模方式同OLED实验ASCII的取模方式一模一样，字体采用24*24大小，一个汉字点阵占用72字节。
const u8 OLED_HZK_TBL[img_numbers][img_size]=
{
	
};


	 
//在指定位置，显示一个24*24大小的汉字
//x,y :汉字的坐标
//fnum:汉字编号（在字库数组里面的编号） 
void OLED_Show_Font(u16 x,u16 y,u8 fnum)
{
	u8 temp,t1;
	u16 t;
	u16 y0=y;
	u8 *dzk;   
	u16 csize=1024;					//一个24*24的汉字72字节/字节计算公式：cows*rows/8[长*宽(:size)/8]:EG:128*64的图像，size为128*64/8=1024
	dzk=(u8*)OLED_HZK_TBL[fnum];	//得到汉字编号对应的点阵库 
	for(t=0;t<csize;t++)
	{   												   
		temp=dzk[t];				//得到点阵数据                          
		for(t1=0;t1<8;t1++)
		{ 						    //此处可以修改反白显示
			if(temp&0x80)OLED_DrawPoint(x,y,1);
			else OLED_DrawPoint(x,y,0); 
			temp<<=1;
			y++;
			if((y-y0)==64)          //oled:128*64  图像所占的屏幕的cows
			{
				y=y0;
				x++;
				break;
			}
		}  	 
	}  
}
















