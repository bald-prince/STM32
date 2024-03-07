#include "stdlib.h"
#include "string.h"
#include "FONT.h"
#include "lcd.h"

extern SPI_HandleTypeDef hspi1;

extern const GUI_FONT GUI_FontRoboto18;
extern const GUI_FONT GUI_FontRoboto29;
extern const GUI_FONT GUI_FontRoboto27B;

unsigned short current_y_line;

void LCD_show_Font(unsigned short x, unsigned short y, GUI_FONT *font, char *data, unsigned short colour, unsigned short bgcolour)
{
	unsigned char endx, endy;
	int x1, y1, x2, y2;
	unsigned int i, k;

	unsigned char *cdata;
	unsigned int dataline;

	endy = font->YSize;

	x1 = x;
	y1 = y;
	while (*data != 0)
	{
		if (*data == '\n')
		{ //换行
			data++;
			x1 = x;
			y1 = y1 + font->YSize;
		}

		if ((*data > font->p.pProp->Last) || (*data < font->p.pProp->First))
		{
		}
		else
		{
			cdata = (unsigned char *)&font->p.pProp->paCharInfo[*data - font->p.pProp->First].pData[0];
			endx = font->p.pProp->paCharInfo[*data - font->p.pProp->First].XSize;
			x2 = x1 + endx;
			if (x2 > 240)
			{ //换行
				x1 = x;
				y1 = y1 + endy;
				x2 = x1 + endx;
			}
			y2 = y1 + endy;
			lcd_set_address(x1, y1, x2 - 1, y2 - 1);
			x1 = x2;
			for (i = 0; i < endy; i++)
			{
				switch (font->p.pProp->paCharInfo[*data - font->p.pProp->First].BytesPerLine)
				{
				case 4:
					dataline = cdata[0 + i * 4];
					dataline <<= 8;
					dataline += cdata[1 + i * 4];
					dataline <<= 8;
					dataline += cdata[2 + i * 4];
					dataline <<= 8;
					dataline += cdata[3 + i * 4];
					break;
				case 3:
					dataline = cdata[0 + i * 3];
					dataline <<= 8;
					dataline += cdata[1 + i * 3];
					dataline <<= 8;
					dataline += cdata[2 + i * 3];
					dataline <<= 8;
					break;
				case 2:
					dataline = cdata[0 + i * 2];
					dataline <<= 8;
					dataline += cdata[1 + i * 2];
					dataline <<= 16;
					break;
				case 1:
					dataline = cdata[0 + i * 1];
					dataline <<= 24;
					break;
				default:
					break;
				}
				for (k = 0; k < endx; k++)
				{
					if (dataline & 0x80000000)
					{
						//LCD_data_write(colour >> 8);
						//LCD_data_write(colour & 0x00ff);

						LCD_Write_2Byte(colour);
					}
					else
					{
						//LCD_data_write(bgcolour >> 8);
						//LCD_data_write(bgcolour & 0x00ff);
						LCD_Write_2Byte(bgcolour);
					}
					dataline <<= 1;
				}
			}
		}
		data++;
	}
}

void txt_show(void)
{

	LCD_show_Font(20, 15, (GUI_FONT *)&GUI_FontRoboto27B, "TRANSACTION", 0xffff, 0);
	LCD_show_Font(20, 45, (GUI_FONT *)&GUI_FontRoboto27B, "SIGNING", 0xffff, 0);
}


