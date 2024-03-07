#ifndef __ST7789V_H
#define __ST7789V_H

#include "main.h"
#ifdef __cplusplus
extern "C"
{
#endif 

/* Includes ------------------------------------------------------------------*/
//#include "mhscpu.h"
	
/************** TFT_LCD 管脚连接线**************
			PB8 --------> CS 
			PB9 --------> RESET
			PC5 --------> DB0
			PC6 --------> DB1
			PC7 --------> DB2
			PC8 --------> DB3
			PC9 --------> DB4
			PC10--------> DB5
			PC11--------> DB6
			PC12--------> DB7
			PC13--------> RD
			PC14--------> WR
			PC15--------> CD
**********************************************/	

/***************** 行列数 ******************/
#define LCD_ROW_NUM                     320	
#define LCD_COL_NUM                     240	

/************** 颜色(RGB 5,6,5) **************/
#define LCD_DISP_RED                    0xF800       //先高字节，后低字节      
#define LCD_DISP_GREEN                  0x07E0
#define LCD_DISP_BLUE                   0x001F
#define LCD_DISP_WRITE                  0xFFFF
#define LCD_DISP_BLACK                  0x0000
#define LCD_DISP_GRAY                   0xEF5D
#define LCD_DISP_GRAY75                 0x39E7
#define LCD_DISP_GRAY50                 0x7BEF
#define LCD_DISP_GRAY25                 0xADB5

/******************* 命令 ********************/
#define LCD_CMD_READID					0x04	 ///< Read Display ID
#define LCD_CMD_SLPOUT                  0x11     ///< Sleep Out
#define LCD_CMD_DISPOFF                 0x28     ///< Display Off
#define LCD_CMD_DISPON                  0x29     ///< Display On
#define LCD_CMD_CASET                   0x2A     ///< Column Address Set
#define LCD_CMD_RASET                   0x2B     ///< Row Address Set
#define LCD_CMD_RAMWR                   0x2C     ///< Memory Write
#define LCD_CMD_RAWRD					0x2E	 ///< Memory Read
#define LCD_CMD_VSCRDEF					0x33 	 ///< Vertical Scrolling Definition
#define LCD_CMD_MADCTL                  0x36     ///< Memory Data Access Control
#define LCD_CMD_VSCSAD					0x37	 ///< Vertical Scroll Start Address of RAM
#define LCD_CMD_COLMOD                  0x3A     ///< Interface Pixel Format
#define LCD_CMD_SCANLINE				0x45	 ///< Get scanline
#define LCD_CMD_PORCTRL                 0xB2     ///< Porch Setting
#define LCD_CMD_GCTRL                   0xB7     ///< Gate Control
#define LCD_CMD_VCOMS                   0xBB     ///< VCOM Setting
#define LCD_CMD_LCMCTRL                 0xC0     ///< LCM Control
#define LCD_CMD_VDVVRHEN                0xC2     ///< VDV and VRH Command Enable
#define LCD_CMD_VRHS                    0xC3     ///< VRH Set
#define LCD_CMD_VDVS                    0xC4     ///< VDV Set
#define LCD_CMD_FRCTRL2                 0xC6     ///< Frame Rate Control in Normal Mode
#define LCD_CMD_PWCTRL1                 0xD0     ///< Power Control 1
#define LCD_CMD_PVGAMCTRL               0xE0     ///< Positive Voltage Gamma Control
#define LCD_CMD_NVGAMCTRL               0xE1     ///< Negative Voltage Gamma Control


#define LCD_FONT_W                      8
#define LCD_FONT_H                      16

#define uint8_t  unsigned char
#define  uint32_t	 unsigned int


void LCD_DMAInit(uint8_t *base,uint8_t pageLenth);
void LCD_DMAWriteEnable(uint8_t *buf);

void LCD_WriteEx(uint8_t u8CD, uint8_t u8Value);
void LCD_ReadEx(uint8_t u8CD, uint8_t *u8Value);

void LCD_IOConfig(void);
void LCD_Reset(void);
void LCD_InitSequence(void);

void LCD_BlockWritePrep(unsigned int xStart, unsigned int xEnd, unsigned int yStart, unsigned int yEnd);

void LCD_DisplayColor(uint32_t color);
void LCD_DisplayGrayHor16(void);
void LCD_DisplayGrayHor32(void);
void LCD_DisplayBand(void);
void LCD_DisplayFrame(void);
void LCD_DisplayScaleHor1(void);
void LCD_DisplayScaleHor2(void);
void LCD_DisplayScaleVer(void);
void LCD_DisplayPicDirect(const uint8_t *picture);
void LCD_DisplayPicDMA(uint8_t *picture);

void LCD_WriteOneDot(uint32_t color);
void LCD_DisplayOneChar(uint8_t ord, uint32_t xStart, uint32_t yStart, uint32_t textColor, uint32_t backColor);
extern void LCD_DisplayStr(uint8_t *str, uint32_t xStart, uint32_t yStart, uint32_t textColor, uint32_t backColor);

void LCD_DrawLine(uint32_t xStart, uint32_t xEnd, uint32_t yStart, uint32_t yEnd, uint32_t color);
void LCD_DrawGird(uint32_t color);

void LCD_VerticalScrolling(uint32_t vsp);

#ifdef __cplusplus
}
#endif

#endif  ///< __ST7789V_H

