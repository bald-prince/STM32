//////////////////////////////////////////////////////////////////////////////////	 
//
//
//  ������ֻ��ѧϰʹ�ã�δ��������ɣ��������������κ���;
//
//  �� �� ��   : main.c
//  �� �� ��   : v2.0
//  ��    ��   : sumjess
//  ��������   : 2017-11/21
//  ����޸�   : 2018-01/22
//  ��������   : OLED 4�ӿ���ʾ����
//              ˵��: 
//              ----------------------------------------------------------------
//              GND  ��Դ��
//              VCC  ��5V��3.3v��Դ
//              D0   ��PB13��SCL��
//              D1   ��PB15��SDA��
//              RES  ��PB11
//              DC   ��PB10
//              CS   ��PB12               
//              ----------------------------------------------------------------
// �޸���ʷ   :
// ��    ��   : 2018-01/22
// ��    ��   : sumjess
// �޸�����   : �����ļ�

//******************************************************************************/


#ifndef __SUMJESS_OLED_H
#define __SUMJESS_OLED_H			  	 
#include "sys.h"
#include "stdlib.h"	    	
//OLEDģʽ����
//0:4�ߴ���ģʽ
//1:����8080ģʽ
#define OLED_MODE 0     //0,������ʾ;1,������ʾ
#define SIZE 16         //�����С
#define XLevelL		0x00
#define XLevelH		0x10
#define Max_Column	128  //128��
#define Max_Row		64     //64��
#define	Brightness	0xFF //����
#define X_WIDTH 	128    //x���
#define Y_WIDTH 	64	    //y���

//-----------------����LED�˿ڶ���---------------- 
//#define LED_ON GPIO_ResetBits(GPIOD,GPIO_Pin_2)
//#define LED_OFF GPIO_SetBits(GPIOD,GPIO_Pin_2)

//-----------------OLED�˿ڶ���----------------  					   


#define OLED_SCLK_Clr() GPIO_ResetBits(GPIOF,GPIO_Pin_3)//CLK
#define OLED_SCLK_Set() GPIO_SetBits(GPIOF,GPIO_Pin_3)

#define OLED_SDIN_Clr() GPIO_ResetBits(GPIOF,GPIO_Pin_4)//DIN
#define OLED_SDIN_Set() GPIO_SetBits(GPIOF,GPIO_Pin_4)

#define OLED_RST_Clr() GPIO_ResetBits(GPIOF,GPIO_Pin_1)//RES
#define OLED_RST_Set() GPIO_SetBits(GPIOF,GPIO_Pin_1)

#define OLED_DC_Clr() GPIO_ResetBits(GPIOF,GPIO_Pin_0)//DC
#define OLED_DC_Set() GPIO_SetBits(GPIOF,GPIO_Pin_0)
 		     
#define OLED_CS_Clr()  GPIO_ResetBits(GPIOF,GPIO_Pin_2)//CS
#define OLED_CS_Set()  GPIO_SetBits(GPIOF,GPIO_Pin_2)

#define OLED_CMD  0	//д����
#define OLED_DATA 1	//д����


//OLED�����ú���
void OLED_WR_Byte(u8 dat,u8 cmd);	    
void OLED_Display_On(void);
void OLED_Display_Off(void);	   							   		    
void OLED_Init(void);
void OLED_Clear(void);
void OLED_DrawPoint(u8 x,u8 y,u8 t);
void OLED_Fill(u8 x1,u8 y1,u8 x2,u8 y2,u8 dot);
void OLED_ShowChar(u8 x,u8 y,u8 chr);
void OLED_ShowNum(u8 x,u8 y,u32 num,u8 len,u8 size);
void OLED_ShowString(u8 x,u8 y, u8 *p);	 
void OLED_Set_Pos(unsigned char x, unsigned char y);
void OLED_ShowCHinese(u8 x,u8 y,u8 no);
void OLED_DrawBMP(unsigned char x0, unsigned char y0,unsigned char x1, unsigned char y1,unsigned char BMP[]);
#endif  
	 



