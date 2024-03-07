#ifndef __GUI_H__
#define __GUI_H__
#include "FONT.h"
#include <stdlib.h>

#define U8    unsigned char
#define I8    signed char
#define U16   unsigned short
#define I16   signed short
#define U32   unsigned long
#define I32   signed long
#define  I16P   I16              /*   signed 16 bits OR MORE ! */
#define  U16P   U16              /* unsigned 16 bits OR MORE ! */	
#define LCD_PIXELINDEX U32
typedef int LCD_DRAWMODE;
typedef U32 LCD_COLOR;

typedef struct { I16P x,y; } GUI_POINT;
typedef struct { I16 x0,y0,x1,y1; } LCD_RECT;

typedef struct {
  int              NumEntries;
  char             HasTrans;
  const LCD_COLOR * pPalEntries;
} LCD_LOGPALETTE;


typedef const char *  GUI_ConstString;

typedef LCD_COLOR       GUI_COLOR;
typedef LCD_LOGPALETTE  GUI_LOGPALETTE;
typedef LCD_DRAWMODE    GUI_DRAWMODE;
typedef LCD_RECT        GUI_RECT;


typedef LCD_COLOR      tLCDDEV_Index2Color  (LCD_PIXELINDEX Index);
typedef LCD_PIXELINDEX tLCDDEV_Color2Index  (LCD_COLOR Color);
typedef LCD_PIXELINDEX tLCDDEV_GetIndexMask (void);

typedef void tLCDDEV_Index2ColorBulk(void * pIndex, LCD_COLOR * pColor, U32 NumItems, U8 SizeOfIndex);
typedef void tLCDDEV_Color2IndexBulk(LCD_COLOR * pColor, void * pIndex, U32 NumItems, U8 SizeOfIndex);






/*********************************************************************
*
*       Color conversion API tables
*/
typedef struct {
  tLCDDEV_Color2Index  * pfColor2Index;
  tLCDDEV_Index2Color  * pfIndex2Color;
  tLCDDEV_GetIndexMask * pfGetIndexMask;
  int NoAlpha;
  tLCDDEV_Color2IndexBulk * pfColor2IndexBulk;
  tLCDDEV_Index2ColorBulk * pfIndex2ColorBulk;
} LCD_API_COLOR_CONV;


typedef struct {
  void      (* pfDraw)  (int x0,
                         int y0,
                         int xsize, 
                         int ysize, 
                         const U8 * pPixel, 
                         const LCD_LOGPALETTE * pLogPal, 
                         int xMag, 
                         int yMag);
  GUI_COLOR (* pfIndex2Color)(LCD_PIXELINDEX Index);
  void      (* pfDrawHW)(int x0,
                         int y0,
                         int xsize, 
                         int ysize, 
                         const U8 * pPixel, 
                         const LCD_LOGPALETTE * pLogPal, 
                         int xMag, 
                         int yMag);
  const LCD_API_COLOR_CONV * pColorConvAPI;
} GUI_BITMAP_METHODS;




extern const   GUI_BITMAP_METHODS      GUI_BitmapMethods565;
#define        GUI_DRAW_BMP565        &GUI_BitmapMethods565        /* Method table ! */


typedef struct {
  U16P XSize;
  U16P YSize;
  U16P BytesPerLine;
  U16P BitsPerPixel;
  const U8 * pData;
  const GUI_LOGPALETTE * pPal;
  const GUI_BITMAP_METHODS * pMethods;
} GUI_BITMAP;


typedef struct {
  U16P Xstart;
  U16P Ystart;  
  const GUI_BITMAP *Bitmap;
} GUI_LCD_SHOW;



typedef struct{
         U8  cur;  //当前索引号
         U8  left; //left 的索引号
	       U8  ok; //OK 的索引号
         U8  right;  //right 的索引号         
	       int cursor;//光标
         void (*current_operation)(void);
} KEY_TABLE;

void show_test(void);


#endif
