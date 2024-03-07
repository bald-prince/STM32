#ifndef __OLED_H
#define __OLED_H
#include "sys.h"
#include "u8g2.h"
#include "u8x8.h"
						  
//OLED模式设置
//0: 4线串行模式  （模块的BS1，BS2均接GND）
//1: 并行8080模式 （模块的BS1，BS2均接VCC）
#define OLED_MODE 	0
		    						  
//-----------------OLED端口定义----------------  		
#define OLED_CS 	PBout(12)    //CS
#define OLED_RST  PBout(10)	   //RES
#define OLED_RS 	PBout(11)    //DC
//使用4线串行接口时使用 
#define OLED_SCLK 	PDout(12)    //D0
#define OLED_SDIN 	PDout(13)    //D1
		     
#define OLED_CMD  	0		//写命令
#define OLED_DATA 	1		//写数据

//OLED控制用函数
void OLED_WR_Byte(u8 dat,u8 cmd);	    
void OLED_Display_On(void);
void OLED_Display_Off(void);
void OLED_Refresh_Gram(void);		   
	
void OLED_Init(void);	
void OLED_Clear(void);
void OLED_DrawPoint(u8 x,u8 y,u8 t);
void OLED_Fill(u8 x1,u8 y1,u8 x2,u8 y2,u8 dot);
void OLED_ShowChar(u8 x,u8 y,u8 chr,u8 size,u8 mode);
void OLED_ShowNum(u8 x,u8 y,u32 num,u8 len,u8 size);
void OLED_ShowString(u8 x,u8 y,const u8 *p,u8 size);
void OLED_ShowChinese(u8 x,u8 y,u8 chr,u8 size,u8 mode);
void OLED_ShowChinese2424(u16 x,u16 y,u8 index,u8 size);
void OLED_Set_Pos(unsigned char x, unsigned char y) ;
void OLED_ShowPicture(u8 x,u8 y,u8 sizex,u8 sizey,u8 BMP[],u8 mode);
void OLED_DrawBMP(unsigned char x0, unsigned char y0,unsigned char x1, unsigned char y1,unsigned char BMP[]);
void OLED_DrawGIF(unsigned char x0, unsigned char y0,unsigned char x1, unsigned char y1, unsigned char k, int m, unsigned char GIF[][m]);
void OLED_DrawQRCode(char *website,int mode);
void OLED_ShowFloat(u8 x,u8 y,float num,u8 size);
uint8_t u8x8_stm32_gpio_and_delay(U8X8_UNUSED u8x8_t *u8x8,U8X8_UNUSED uint8_t msg, U8X8_UNUSED uint8_t arg_int,U8X8_UNUSED void *arg_ptr);
void u8g2Init(u8g2_t *u8g2);
void draw(u8g2_t *u8g2);

#endif
