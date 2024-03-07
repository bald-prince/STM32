#ifndef H_LCD_H_
#define H_LCD_H_

/* Includes ------------------------------------------------------------------*/
#include <main.h>
#include <stdint.h>
//片选

#define	Lcd_Select()		HAL_GPIO_WritePin(LCD_CS_GPIO_Port,LCD_CS_Pin,GPIO_PIN_RESET)
#define	Lcd_Deselect()	HAL_GPIO_WritePin(LCD_CS_GPIO_Port,LCD_CS_Pin,GPIO_PIN_SET)

//指令/数据模式
#define	Lcd_CmdMode()		HAL_GPIO_WritePin(LCD_DC_GPIO_Port,LCD_DC_Pin,GPIO_PIN_RESET)//指令模式
#define	Lcd_DataMode()	HAL_GPIO_WritePin(LCD_DC_GPIO_Port,LCD_DC_Pin,GPIO_PIN_SET)	//数据模式

//复位
#define	Lcd_RST_L()			HAL_GPIO_WritePin(LCD_RST_GPIO_Port,LCD_RST_Pin,GPIO_PIN_RESET) //复位
#define	Lcd_RST_H()			HAL_GPIO_WritePin(LCD_RST_GPIO_Port,LCD_RST_Pin,GPIO_PIN_SET)		//失能复位

#define LCD_WIDTH			192
#define LCD_PAGE			8

#define	LCD_CMD_MODE	0
#define LCD_DAT_MODE	1
#define LCD_COMMAND_LENGTH	11
/*Flash Command*/
typedef enum 
{
	LCD_DISPLAY_ON	=  0xAF,
	LCD_DISPLAY_OFF	=	0xAE,
	LCD_DISPLAY_START_LINE_SET	=	0x40,
	LCD_PAGE_ADDRESS_SET	= 0xB0,
	LCD_COL_ADD_SET_UPPER	= 0x10,
	LCD_COL_ADD_SET_LOWER	= 	0x00,
	LCD_DIS_MODE_NORMAL		= 0xA6,
	LCD_DIS_MODE_REVERSE = 	0xA7,
	LCD_SEG_OUTPUT_NORMAL	= 	0xA0,
	LCD_SEG_OUTPUT_REVERSE	=	0xA1,
	LCD_DISPLAY_ALLPOINTS_ON =	0xA5,
	LCD_DISPLAY_ALLPOINTS_OFF	= 0xA4,
	LCD_BIAS_SET_9	= 0xA2,
	LCD_BIAS_SET_7	= 0xA3,
	LCD_READ_MODIFY_WRITE = 	0xE0,
	LCD_END	= 0xEE,
	LCD_RESET= 0xE2,
	LCD_COMMON_OUTPUT_NORMAL	= 0xC0,
	LCD_COMMON_OUTPUT_REVERSE		= 0xC8,
	LCD_POWER_CONTROL_SET = 0x28,
	LCD_V0_VOLTAGE_SET	= 0x20,
	LCD_EV_SET = 0x81,
	LCD_REGISTER_SET = 0x00,
	LCD_STATIC_INDON = 	 0xAC,
	LCD_STATIC_INDOFF	= 0xAD,
	LCD_STATIC_IND_SET	= 0x00,
	LCD_BOOSTER_RATIO_SET	= 	0xF8,
	LCD_NOP	= 0xE3,
	LCD_POWER_ON = 0x2F,
	LCD_POWER_OFF = 0x28
}LCD_COMMAND;

void SPI1_ReadWriteByte(uint8_t TxData);
void FL_SPISend_NByte(unsigned char *DispBuf,uint8_t LCD_CMD,uint8_t Len);
void FL_vDISP_ResetLcd(void);
void FL_LCD_Init(void);
void Lcd_SetPosition(uint8_t lcdpage,uint8_t lcdcolum);
void Lcd_FillRam(uint8_t data);
void Lcd_DisplayDatas(uint8_t lcdpage, uint8_t lcdcolum, uint8_t *ptdata, uint8_t len);
void Lcd_DispOneChar(uint8_t x,uint8_t y,uint8_t chr);
void Lcd_DispString(uint8_t x,uint8_t y,char *ChrString);
void Lcd_DispNumber(uint8_t x,uint8_t y,int16_t num);

#endif
