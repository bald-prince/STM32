#ifndef __LCD_H
#define __LCD_H

#include "stm32f4xx.h"
#include "main.h"
#include "gpio.h"

#define LCD_WIDTH 240
#define LCD_HEIHGT 320

#define LCD_TOTAL_BUF_SIZE (240 * 320 * 2)
#define LCD_Buf_Size 1536


#define LCD_Width		240
#define LCD_Height		240

#define LCD_REST_LOW()   HAL_GPIO_WritePin(LCD_RST_GPIO_Port, LCD_RST_Pin, GPIO_PIN_RESET);
#define LCD_REST_HIGH()  HAL_GPIO_WritePin(LCD_RST_GPIO_Port, LCD_RST_Pin, GPIO_PIN_SET);

#define LCD_DC_LOW()     HAL_GPIO_WritePin(LCD_DC_GPIO_Port, LCD_DC_Pin, GPIO_PIN_RESET);
#define LCD_DC_HIGH()    HAL_GPIO_WritePin(LCD_DC_GPIO_Port, LCD_DC_Pin, GPIO_PIN_SET);

#define LCD_CS_LOW()     HAL_GPIO_WritePin(LCD_CS_GPIO_Port, LCD_CS_Pin, GPIO_PIN_RESET);
#define LCD_CS_HIGH()    HAL_GPIO_WritePin(LCD_CS_GPIO_Port, LCD_CS_Pin, GPIO_PIN_SET);


#define	LCD_WR_RS(n)	(n?HAL_GPIO_WritePin(LCD_DC_GPIO_Port,LCD_DC_Pin,GPIO_PIN_SET):HAL_GPIO_WritePin(LCD_DC_GPIO_Port,LCD_DC_Pin,GPIO_PIN_RESET))


// ST7789 specific commands used in init
#define ST7789_NOP 0x00
#define ST7789_SWRESET 0x01
#define ST7789_RDDID 0x04
#define ST7789_RDDST 0x09

#define ST7789_RDDPM 0x0A      // Read display power mode
#define ST7789_RDD_MADCTL 0x0B // Read display MADCTL
#define ST7789_RDD_COLMOD 0x0C // Read display pixel format
#define ST7789_RDDIM 0x0D      // Read display image mode
#define ST7789_RDDSM 0x0E      // Read display signal mode
#define ST7789_RDDSR 0x0F      // Read display self-diagnostic result (ST7789V)

#define ST7789_SLPIN 0x10
#define ST7789_SLPOUT 0x11
#define ST7789_PTLON 0x12
#define ST7789_NORON 0x13

#define ST7789_INVOFF 0x20
#define ST7789_INVON 0x21
#define ST7789_GAMSET 0x26 // Gamma set
#define ST7789_DISPOFF 0x28
#define ST7789_DISPON 0x29
#define ST7789_CASET 0x2A
#define ST7789_RASET 0x2B
#define ST7789_RAMWR 0x2C
#define ST7789_RGBSET 0x2D // Color setting for 4096, 64K and 262K colors
#define ST7789_RAMRD 0x2E

#define ST7789_PTLAR 0x30
#define ST7789_VSCRDEF 0x33 // Vertical scrolling definition (ST7789V)
#define ST7789_TEOFF 0x34   // Tearing effect line off
#define ST7789_TEON 0x35    // Tearing effect line on
#define ST7789_MADCTL 0x36  // Memory data access control
#define ST7789_IDMOFF 0x38  // Idle mode off
#define ST7789_IDMON 0x39   // Idle mode on
#define ST7789_RAMWRC 0x3C  // Memory write continue (ST7789V)
#define ST7789_RAMRDC 0x3E  // Memory read continue (ST7789V)
#define ST7789_COLMOD 0x3A

#define ST7789_RAMCTRL 0xB0   // RAM control
#define ST7789_RGBCTRL 0xB1   // RGB control
#define ST7789_PORCTRL 0xB2   // Porch control
#define ST7789_FRCTRL1 0xB3   // Frame rate control
#define ST7789_PARCTRL 0xB5   // Partial mode control
#define ST7789_GCTRL 0xB7     // Gate control
#define ST7789_GTADJ 0xB8     // Gate on timing adjustment
#define ST7789_DGMEN 0xBA     // Digital gamma enable
#define ST7789_VCOMS 0xBB     // VCOMS setting
#define ST7789_LCMCTRL 0xC0   // LCM control
#define ST7789_IDSET 0xC1     // ID setting
#define ST7789_VDVVRHEN 0xC2  // VDV and VRH command enable
#define ST7789_VRHS 0xC3      // VRH set
#define ST7789_VDVSET 0xC4    // VDV setting
#define ST7789_VCMOFSET 0xC5  // VCOMS offset set
#define ST7789_FRCTR2 0xC6    // FR Control 2
#define ST7789_CABCCTRL 0xC7  // CABC control
#define ST7789_REGSEL1 0xC8   // Register value section 1
#define ST7789_REGSEL2 0xCA   // Register value section 2
#define ST7789_PWMFRSEL 0xCC  // PWM frequency selection
#define ST7789_PWCTRL1 0xD0   // Power control 1
#define ST7789_VAPVANEN 0xD2  // Enable VAP/VAN signal output
#define ST7789_CMD2EN 0xDF    // Command 2 enable
#define ST7789_PVGAMCTRL 0xE0 // Positive voltage gamma control
#define ST7789_NVGAMCTRL 0xE1 // Negative voltage gamma control
#define ST7789_DGMLUTR 0xE2   // Digital gamma look-up table for red
#define ST7789_DGMLUTB 0xE3   // Digital gamma look-up table for blue
#define ST7789_GATECTRL 0xE4  // Gate control
#define ST7789_SPI2EN 0xE7    // SPI2 enable
#define ST7789_PWCTRL2 0xE8   // Power control 2
#define ST7789_EQCTRL 0xE9    // Equalize time control
#define ST7789_PROMCTRL 0xEC  // Program control
#define ST7789_PROMEN 0xFA    // Program mode enable
#define ST7789_NVMSET 0xFC    // NVM setting
#define ST7789_PROMACT 0xFE   // Program action

void LCD_command_write(uint8_t command);
void LCD_data_write(uint8_t data);
void LCD_Write_2Byte(const uint16_t dat);

void lcd_init(void);
void lcd_clear(uint16_t color);
void lcd_show_pic1(uint16_t *color);
void lcd_set_address(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2);
void lcd_SendBytes_length(uint16_t *byte, unsigned int length);

extern void lcd_display_off(void);
extern void lcd_display_on(void);

extern void lcd_clear_area(uint16_t x, uint16_t y, uint16_t x_end, uint16_t y_end, uint16_t color);
extern void lcd_clear_size(uint16_t x_star, uint16_t y_star, uint16_t x_end, uint16_t y_end, uint16_t color);

extern void lcd_draw_x_line(uint16_t x_start, uint16_t y_start, uint16_t x_end, uint16_t y_end, uint16_t color);
extern void lcd_draw_y_line(uint16_t x_start, uint16_t y_start, uint16_t x_end, uint16_t y_end, uint16_t color);

extern void lcd_SendRam_length(uint16_t *byte, unsigned int length);
extern void show_camera_err(void);
extern void DMA_Sendhalfword(uint16_t *byte, unsigned int lenth);
void LCD_DisplayOn(void);


void LCD_Draw_ColorCircle(uint16_t x, uint16_t y, uint16_t r, uint16_t color);

void LCD_ShowChinese(uint16_t x,uint16_t y,uint8_t *s,uint16_t fc,uint16_t bc,uint8_t sizey,uint8_t mode);
void LCD_ShowChinese12x12(uint16_t x,uint16_t y,uint8_t *s,uint16_t fc,uint16_t bc,uint8_t sizey,uint8_t mode);
void LCD_ShowChinese16x16(uint16_t x,uint16_t y,uint8_t *s,uint16_t fc,uint16_t bc,uint8_t sizey,uint8_t mode);
void LCD_ShowChinese24x24(uint16_t x,uint16_t y,uint8_t *s,uint16_t fc,uint16_t bc,uint8_t sizey,uint8_t mode);
void LCD_ShowChinese32x32(uint16_t x,uint16_t y,uint8_t *s,uint16_t fc,uint16_t bc,uint8_t sizey,uint8_t mode);
void LCD_ShowChinese48x48(uint16_t x,uint16_t y,uint8_t *s,uint16_t fc,uint16_t bc,uint8_t sizey,uint8_t mode);
void LCD_ShowChar_Str(uint16_t x, uint16_t y, uint8_t max_width, char *str, uint16_t back_color, uint16_t font_color, uint8_t font_size);
void LCD_DrawFRONT_COLOR(uint16_t x, uint16_t y, uint16_t color);//»­µã 

void txt_show(void);
#endif
