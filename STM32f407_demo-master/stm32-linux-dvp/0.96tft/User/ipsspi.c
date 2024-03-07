#include "ipsspi.h"
#include "font.h"
#include "delay.h"
#include "../Include/stm32f407xx.h"

void myspi_init()
{
    /* gpio init */
    RCC->AHB1ENR |= (1<<5); //GPIOF CLK ENABLE
    /* GND VCC SCL  SDA RES  DC  CS  BKL  */
    /* 地  高   时钟 数据 复位  SW 片选  背光 */
    /* 0   1    F0   F2  F4   F6  F8   1  */
    GPIOF->MODER &= (0x1<<16);  //清空低十六位
    GPIOF->MODER |= (0x5555);   //F0 F2 F4 F6 F8 为输出模式
    GPIOF->OTYPER &= (1<<16);   //推挽输出
    GPIOF->OSPEEDR &= (1<<16);  // [清空低16位] 
    GPIOF->OSPEEDR |= (0xAAAA); // [设置PIN0~7速度为50Mhz]
    GPIOF->PUPDR &= (1<<16);
    GPIOF->PUPDR |= (0x5555);

    SDA_CLR;
    SCL_CLR;
    CS = 0;
}

void  SPI_WriteData(u8 Data)
{
	unsigned char i=0;
	for(i=8;i>0;i--)
	{
	  if(Data&0x80)	
	  	SDA_SET; //Êä³öÊýŸÝ
      else SDA_CLR;
	   
      SCL_CLR;       
      SCL_SET;
      Data<<=1; 
	}
}

//ÏòÒºŸ§ÆÁÐŽÒ»žö8Î»ÖžÁî
void Lcd_WriteIndex(u8 Index)
{
   //SPI ÐŽÃüÁîÊ±Ðò¿ªÊŒ
   DC = 0;
	 SPI_WriteData(Index);
}

//ÏòÒºŸ§ÆÁÐŽÒ»žö8Î»ÊýŸÝ
void Lcd_WriteData(u8 Data)
{
   DC = 1;
   SPI_WriteData(Data); 
}
//ÏòÒºŸ§ÆÁÐŽÒ»žö16Î»ÊýŸÝ
void LCD_WriteData_16Bit(u16 Data)
{

   DC = 1;
	 SPI_WriteData(Data>>8); 	//ÐŽÈëžß8Î»ÊýŸÝ
	 SPI_WriteData(Data); 			//ÐŽÈëµÍ8Î»ÊýŸÝ

}

void Lcd_WriteReg(u8 Index,u8 Data)
{
	Lcd_WriteIndex(Index);
    Lcd_WriteData(Data);
}

void Lcd_Reset(void)
{
	RES = 0;;
	delay_ms(100);
	RES = 1;
	delay_ms(50);
}

//LCD Init For 1.44Inch LCD Panel with ST7735R.
void Lcd_Init(void)
{	
	myspi_init();
	Lcd_Reset(); //Reset before LCD Init.

	//LCD Init For 1.44Inch LCD Panel with ST7735R.
	Lcd_WriteIndex(0x11);//Sleep exit 
	delay_ms (120);
	Lcd_WriteIndex(0x21); 
    Lcd_WriteIndex(0x21); 

    Lcd_WriteIndex(0xB1); 
    Lcd_WriteData(0x05);
    Lcd_WriteData(0x3A);
    Lcd_WriteData(0x3A);

    Lcd_WriteIndex(0xB2);
    Lcd_WriteData(0x05);
    Lcd_WriteData(0x3A);
    Lcd_WriteData(0x3A);

    Lcd_WriteIndex(0xB3); 
    Lcd_WriteData(0x05);  
    Lcd_WriteData(0x3A);
    Lcd_WriteData(0x3A);
    Lcd_WriteData(0x05);
    Lcd_WriteData(0x3A);
    Lcd_WriteData(0x3A);

    Lcd_WriteIndex(0xB4);
    Lcd_WriteData(0x03);

    Lcd_WriteIndex(0xC0);
    Lcd_WriteData(0x62);
    Lcd_WriteData(0x02);
    Lcd_WriteData(0x04);

    Lcd_WriteIndex(0xC1);
    Lcd_WriteData(0xC0);

    Lcd_WriteIndex(0xC2);
    Lcd_WriteData(0x0D);
    Lcd_WriteData(0x00);

    Lcd_WriteIndex(0xC3);
    Lcd_WriteData(0x8D);
    Lcd_WriteData(0x6A);   

    Lcd_WriteIndex(0xC4);
    Lcd_WriteData(0x8D); 
    Lcd_WriteData(0xEE); 

    Lcd_WriteIndex(0xC5);  /*VCOM*/
    Lcd_WriteData(0x0E);    

    Lcd_WriteIndex(0xE0);
    Lcd_WriteData(0x10);
    Lcd_WriteData(0x0E);
    Lcd_WriteData(0x02);
    Lcd_WriteData(0x03);
    Lcd_WriteData(0x0E);
    Lcd_WriteData(0x07);
    Lcd_WriteData(0x02);
    Lcd_WriteData(0x07);
    Lcd_WriteData(0x0A);
    Lcd_WriteData(0x12);
    Lcd_WriteData(0x27);
    Lcd_WriteData(0x37);
    Lcd_WriteData(0x00);
    Lcd_WriteData(0x0D);
    Lcd_WriteData(0x0E);
    Lcd_WriteData(0x10);

    Lcd_WriteIndex(0xE1);
    Lcd_WriteData(0x10);
    Lcd_WriteData(0x0E);
    Lcd_WriteData(0x03);
    Lcd_WriteData(0x03);
    Lcd_WriteData(0x0F);
    Lcd_WriteData(0x06);
    Lcd_WriteData(0x02);
    Lcd_WriteData(0x08);
    Lcd_WriteData(0x0A);
    Lcd_WriteData(0x13);
    Lcd_WriteData(0x26);
    Lcd_WriteData(0x36);
    Lcd_WriteData(0x00);
    Lcd_WriteData(0x0D);
    Lcd_WriteData(0x0E);
    Lcd_WriteData(0x10);

    Lcd_WriteIndex(0x3A); 
    Lcd_WriteData(0x05);

    Lcd_WriteIndex(0x36);
    Lcd_WriteData(0xC8);

    Lcd_WriteIndex(0x29); 
}


/*************************************************
º¯ÊýÃû£ºLCD_Set_Region
¹ŠÄÜ£ºÉèÖÃlcdÏÔÊŸÇøÓò£¬ÔÚŽËÇøÓòÐŽµãÊýŸÝ×Ô¶¯»»ÐÐ
Èë¿Ú²ÎÊý£ºxyÆðµãºÍÖÕµã
·µ»ØÖµ£ºÎÞ
*************************************************/
void Lcd_SetRegion(u16 x_start,u16 y_start,u16 x_end,u16 y_end)
{		
	Lcd_WriteIndex(0x2a);
	Lcd_WriteData(0x00);
	Lcd_WriteData(x_start+0x1A);
	Lcd_WriteData(0x00);
	Lcd_WriteData(x_end+0x1A);

	Lcd_WriteIndex(0x2b);
	Lcd_WriteData(0x00);
	Lcd_WriteData(y_start);
	Lcd_WriteData(0x00);
	Lcd_WriteData(y_end);	
	Lcd_WriteIndex(0x2c);

}

/*************************************************
º¯ÊýÃû£ºLCD_Set_XY
¹ŠÄÜ£ºÉèÖÃlcdÏÔÊŸÆðÊŒµã
Èë¿Ú²ÎÊý£ºxy×ø±ê
·µ»ØÖµ£ºÎÞ
*************************************************/
void Lcd_SetXY(u16 x,u16 y)
{
  	Lcd_SetRegion(x,y,x,y);
}

	
/*************************************************
º¯ÊýÃû£ºLCD_DrawPoint
¹ŠÄÜ£º»­Ò»žöµã
Èë¿Ú²ÎÊý£ºÎÞ
·µ»ØÖµ£ºÎÞ
*************************************************/
void Gui_DrawPoint(u16 x,u16 y,u16 Data)
{
	Lcd_SetRegion(x,y,x+1,y+1);
	LCD_WriteData_16Bit(Data);

}    

/*****************************************
 º¯Êý¹ŠÄÜ£º¶ÁTFTÄ³Ò»µãµÄÑÕÉ«                          
 ³ö¿Ú²ÎÊý£ºcolor  µãÑÕÉ«Öµ                                 
******************************************/
unsigned int Lcd_ReadPoint(u16 x,u16 y)
{
  unsigned int Data;
  Lcd_SetXY(x,y);

  //Lcd_ReadData();//¶ªµôÎÞÓÃ×ÖœÚ
  //Data=Lcd_ReadData();
  Lcd_WriteData(Data);
  return Data;
}
/*************************************************
º¯ÊýÃû£ºLcd_Clear
¹ŠÄÜ£ºÈ«ÆÁÇåÆÁº¯Êý
Èë¿Ú²ÎÊý£ºÌî³äÑÕÉ«COLOR
·µ»ØÖµ£ºÎÞ
*************************************************/
void Lcd_Clear(u16 Color)               
{	
   unsigned int i,m;
   Lcd_SetRegion(0,0,X_MAX_PIXEL-1,Y_MAX_PIXEL-1);
   Lcd_WriteIndex(0x2C);
   for(i=0;i<X_MAX_PIXEL;i++)
    for(m=0;m<Y_MAX_PIXEL;m++)
    {	
	  	LCD_WriteData_16Bit(Color);
    }   
}

u16 LCD_BGR2RGB(u16 c)
{
  u16  r,g,b,rgb;   
  b=(c>>0)&0x1f;
  g=(c>>5)&0x3f;
  r=(c>>11)&0x1f;	 
  rgb=(b<<11)+(g<<5)+(r<<0);		 
  return(rgb);

}




void Gui_Circle(u16 X,u16 Y,u16 R,u16 fc) 
{//BresenhamËã·š 
    unsigned short  a,b; 
    int c; 
    a=0; 
    b=R; 
    c=3-2*R; 
    while (a<b) 
    { 
        Gui_DrawPoint(X+a,Y+b,fc);     //        7 
        Gui_DrawPoint(X-a,Y+b,fc);     //        6 
        Gui_DrawPoint(X+a,Y-b,fc);     //        2 
        Gui_DrawPoint(X-a,Y-b,fc);     //        3 
        Gui_DrawPoint(X+b,Y+a,fc);     //        8 
        Gui_DrawPoint(X-b,Y+a,fc);     //        5 
        Gui_DrawPoint(X+b,Y-a,fc);     //        1 
        Gui_DrawPoint(X-b,Y-a,fc);     //        4 

        if(c<0) c=c+4*a+6; 
        else 
        { 
            c=c+4*(a-b)+10; 
            b-=1; 
        } 
       a+=1; 
    } 
    if (a==b) 
    { 
        Gui_DrawPoint(X+a,Y+b,fc); 
        Gui_DrawPoint(X+a,Y+b,fc); 
        Gui_DrawPoint(X+a,Y-b,fc); 
        Gui_DrawPoint(X-a,Y-b,fc); 
        Gui_DrawPoint(X+b,Y+a,fc); 
        Gui_DrawPoint(X-b,Y+a,fc); 
        Gui_DrawPoint(X+b,Y-a,fc); 
        Gui_DrawPoint(X-b,Y-a,fc); 
    } 
	
} 
//»­Ïßº¯Êý£¬Ê¹ÓÃBresenham »­ÏßËã·š
void Gui_DrawLine(u16 x0, u16 y0,u16 x1, u16 y1,u16 Color)   
{
int dx,             // difference in x's
    dy,             // difference in y's
    dx2,            // dx,dy * 2
    dy2, 
    x_inc,          // amount in pixel space to move during drawing
    y_inc,          // amount in pixel space to move during drawing
    error,          // the discriminant i.e. error i.e. decision variable
    index;          // used for looping	


	Lcd_SetXY(x0,y0);
	dx = x1-x0;//ŒÆËãxŸàÀë
	dy = y1-y0;//ŒÆËãyŸàÀë

	if (dx>=0)
	{
		x_inc = 1;
	}
	else
	{
		x_inc = -1;
		dx    = -dx;  
	} 
	
	if (dy>=0)
	{
		y_inc = 1;
	} 
	else
	{
		y_inc = -1;
		dy    = -dy; 
	} 

	dx2 = dx << 1;
	dy2 = dy << 1;

	if (dx > dy)//xŸàÀëŽóÓÚyŸàÀë£¬ÄÇÃŽÃ¿žöxÖáÉÏÖ»ÓÐÒ»žöµã£¬Ã¿žöyÖáÉÏÓÐÈôžÉžöµã
	{//ÇÒÏßµÄµãÊýµÈÓÚxŸàÀë£¬ÒÔxÖáµÝÔö»­µã
		// initialize error term
		error = dy2 - dx; 

		// draw the line
		for (index=0; index <= dx; index++)//Òª»­µÄµãÊý²»»á³¬¹ýxŸàÀë
		{
			//»­µã
			Gui_DrawPoint(x0,y0,Color);
			
			// test if error has overflowed
			if (error >= 0) //ÊÇ·ñÐèÒªÔöŒÓy×ø±êÖµ
			{
				error-=dx2;

				// move to next line
				y0+=y_inc;//ÔöŒÓy×ø±êÖµ
			} // end if error overflowed

			// adjust the error term
			error+=dy2;

			// move to the next pixel
			x0+=x_inc;//x×ø±êÖµÃ¿ŽÎ»­µãºó¶ŒµÝÔö1
		} // end for
	} // end if |slope| <= 1
	else//yÖáŽóÓÚxÖá£¬ÔòÃ¿žöyÖáÉÏÖ»ÓÐÒ»žöµã£¬xÖáÈôžÉžöµã
	{//ÒÔyÖáÎªµÝÔö»­µã
		// initialize error term
		error = dx2 - dy; 

		// draw the line
		for (index=0; index <= dy; index++)
		{
			// set the pixel
			Gui_DrawPoint(x0,y0,Color);

			// test if error overflowed
			if (error >= 0)
			{
				error-=dy2;

				// move to next line
				x0+=x_inc;
			} // end if error overflowed

			// adjust the error term
			error+=dx2;

			// move to the next pixel
			y0+=y_inc;
		} // end for
	} // end else |slope| > 1
}



void Gui_box(u16 x, u16 y, u16 w, u16 h,u16 bc)
{
	Gui_DrawLine(x,y,x+w,y,0xEF7D);
	Gui_DrawLine(x+w-1,y+1,x+w-1,y+1+h,0x2965);
	Gui_DrawLine(x,y+h,x+w,y+h,0x2965);
	Gui_DrawLine(x,y,x,y+h,0xEF7D);
    Gui_DrawLine(x+1,y+1,x+1+w-2,y+1+h-2,bc);
}
void Gui_box2(u16 x,u16 y,u16 w,u16 h, u8 mode)
{
	if (mode==0)	{
		Gui_DrawLine(x,y,x+w,y,0xEF7D);
		Gui_DrawLine(x+w-1,y+1,x+w-1,y+1+h,0x2965);
		Gui_DrawLine(x,y+h,x+w,y+h,0x2965);
		Gui_DrawLine(x,y,x,y+h,0xEF7D);
		}
	if (mode==1)	{
		Gui_DrawLine(x,y,x+w,y,0x2965);
		Gui_DrawLine(x+w-1,y+1,x+w-1,y+1+h,0xEF7D);
		Gui_DrawLine(x,y+h,x+w,y+h,0xEF7D);
		Gui_DrawLine(x,y,x,y+h,0x2965);
	}
	if (mode==2)	{
		Gui_DrawLine(x,y,x+w,y,0xffff);
		Gui_DrawLine(x+w-1,y+1,x+w-1,y+1+h,0xffff);
		Gui_DrawLine(x,y+h,x+w,y+h,0xffff);
		Gui_DrawLine(x,y,x,y+h,0xffff);
	}
}


/**************************************************************************************
¹ŠÄÜÃèÊö: ÔÚÆÁÄ»ÏÔÊŸÒ»Í¹ÆðµÄ°ŽÅ¥¿ò
Êä    Èë: u16 x1,y1,x2,y2 °ŽÅ¥¿ò×óÉÏœÇºÍÓÒÏÂœÇ×ø±ê
Êä    ³ö: ÎÞ
**************************************************************************************/
void DisplayButtonDown(u16 x1,u16 y1,u16 x2,u16 y2)
{
	Gui_DrawLine(x1,  y1,  x2,y1, GRAY2);  //H
	Gui_DrawLine(x1+1,y1+1,x2,y1+1, GRAY1);  //H
	Gui_DrawLine(x1,  y1,  x1,y2, GRAY2);  //V
	Gui_DrawLine(x1+1,y1+1,x1+1,y2, GRAY1);  //V
	Gui_DrawLine(x1,  y2,  x2,y2, WHITE);  //H
	Gui_DrawLine(x2,  y1,  x2,y2, WHITE);  //V
}

/**************************************************************************************
¹ŠÄÜÃèÊö: ÔÚÆÁÄ»ÏÔÊŸÒ»°ŒÏÂµÄ°ŽÅ¥¿ò
Êä    Èë: u16 x1,y1,x2,y2 °ŽÅ¥¿ò×óÉÏœÇºÍÓÒÏÂœÇ×ø±ê
Êä    ³ö: ÎÞ
**************************************************************************************/
void DisplayButtonUp(u16 x1,u16 y1,u16 x2,u16 y2)
{
	Gui_DrawLine(x1,  y1,  x2,y1, WHITE); //H
	Gui_DrawLine(x1,  y1,  x1,y2, WHITE); //V
	
	Gui_DrawLine(x1+1,y2-1,x2,y2-1, GRAY1);  //H
	Gui_DrawLine(x1,  y2,  x2,y2, GRAY2);  //H
	Gui_DrawLine(x2-1,y1+1,x2-1,y2, GRAY1);  //V
    Gui_DrawLine(x2  ,y1  ,x2,y2, GRAY2); //V
}


void Gui_DrawFont_GBK16(u16 x, u16 y, u16 fc, u16 bc, u8 *s)
{
	unsigned char i,j;
	unsigned short k,x0;
	x0=x;

	while(*s) 
	{	
		if((*s) < 128) 
		{
			k=*s;
			if (k==13) 
			{
				x=x0;
				y+=16;
			}
			else 
			{
				if (k>32) k-=32; else k=0;
	
			    for(i=0;i<16;i++)
				for(j=0;j<8;j++) 
					{
				    	if(asc16[k*16+i]&(0x80>>j))	Gui_DrawPoint(x+j,y+i,fc);
						else 
						{
							if (fc!=bc) Gui_DrawPoint(x+j,y+i,bc);
						}
					}
				x+=8;
			}
			s++;
		}
			
		else 
		{
		

			for (k=0;k<hz16_num;k++) 
			{
			  if ((hz16[k].Index[0]==*(s))&&(hz16[k].Index[1]==*(s+1)))
			  { 
				    for(i=0;i<16;i++)
				    {
						for(j=0;j<8;j++) 
							{
						    	if(hz16[k].Msk[i*2]&(0x80>>j))	Gui_DrawPoint(x+j,y+i,fc);
								else {
									if (fc!=bc) Gui_DrawPoint(x+j,y+i,bc);
								}
							}
						for(j=0;j<8;j++) 
							{
						    	if(hz16[k].Msk[i*2+1]&(0x80>>j))	Gui_DrawPoint(x+j+8,y+i,fc);
								else 
								{
									if (fc!=bc) Gui_DrawPoint(x+j+8,y+i,bc);
								}
							}
				    }
				}
			  }
			s+=2;x+=16;
		} 
		
	}
}

//ÏÔÊŸÊý×Ö
void Gui_DrawFont_char(u16 x, u16 y, u8 s)
{
	unsigned char i,j;

			if (s>32) s-=32; else s=0;
	
			    for(i=0;i<16;i++)
				for(j=0;j<8;j++) 
					{
				    	if(asc16[s*16+i]&(0x80>>j))	Gui_DrawPoint(x+j,y+i,RED);
						else 
						{
							 Gui_DrawPoint(x+j,y+i,GRAY0);
						}
					}


}
//m^nº¯Êý
int	oled_pow(u8 m,u8 n)
{
	u32 result=1;	 
	while(n--)result*=m;    
	return result;
}		
//ÏÔÊŸ2žöÊý×Ö
//x,y :Æðµã×ø±ê	 
//len :Êý×ÖµÄÎ»Êý
//size:×ÖÌåŽóÐ¡
//mode:Ä£Êœ	0,Ìî³äÄ£Êœ;1,µþŒÓÄ£Êœ
//num:ÊýÖµ(0~4294967295);	 		  
void LCD_ShowNum(u8 x,u8 y,u16 num,u8 len)
{         	
	u8 t,temp;
	u8 enshow=0;						   
	for(t=0;t<len;t++)
	{
		temp=(num/oled_pow(10,len-t-1))%10;
		if(enshow==0&&t<(len-1))
		{
			if(temp==0)
			{
				Gui_DrawFont_char(x+8*t,y,' ');
				continue;
			}else enshow=1; 
		 	 
		}
	 	Gui_DrawFont_char(x+8*t,y,temp+'0'); 
	}
} 


void Gui_DrawFont_GBK24(u16 x, u16 y, u16 fc, u16 bc, u8 *s)
{
	unsigned char i,j;
	unsigned short k;

	while(*s) 
	{
		if( *s < 0x80 ) 
		{
			k=*s;
			if (k>32) k-=32; else k=0;

		    for(i=0;i<16;i++)
			for(j=0;j<8;j++) 
				{
			    	if(asc16[k*16+i]&(0x80>>j))	
					Gui_DrawPoint(x+j,y+i,fc);
					else 
					{
						if (fc!=bc) Gui_DrawPoint(x+j,y+i,bc);
					}
				}
			s++;x+=8;
		}
		else 
		{

			for (k=0;k<hz24_num;k++) 
			{
			  if ((hz24[k].Index[0]==*(s))&&(hz24[k].Index[1]==*(s+1)))
			  { 
				    for(i=0;i<24;i++)
				    {
						for(j=0;j<8;j++) 
							{
						    	if(hz24[k].Msk[i*3]&(0x80>>j))
								Gui_DrawPoint(x+j,y+i,fc);
								else 
								{
									if (fc!=bc) Gui_DrawPoint(x+j,y+i,bc);
								}
							}
						for(j=0;j<8;j++) 
							{
						    	if(hz24[k].Msk[i*3+1]&(0x80>>j))	Gui_DrawPoint(x+j+8,y+i,fc);
								else {
									if (fc!=bc) Gui_DrawPoint(x+j+8,y+i,bc);
								}
							}
						for(j=0;j<8;j++) 
							{
						    	if(hz24[k].Msk[i*3+2]&(0x80>>j))	
								Gui_DrawPoint(x+j+16,y+i,fc);
								else 
								{
									if (fc!=bc) Gui_DrawPoint(x+j+16,y+i,bc);
								}
							}
				    }
			  }
			}
			s+=2;x+=24;
		}
	}
}
void Gui_DrawFont_Num32(u16 x, u16 y, u16 fc, u16 bc, u16 num)
{
	unsigned char i,j,k,c;
	//lcd_text_any(x+94+i*42,y+34,32,32,0x7E8,0x0,sz32,knum[i]);
//	w=w/8;

    for(i=0;i<32;i++)
	{
		for(j=0;j<4;j++) 
		{
			c=*(sz32+num*32*4+i*4+j);
			for (k=0;k<8;k++)	
			{
	
		    	if(c&(0x80>>k))	Gui_DrawPoint(x+j*8+k,y+i,fc);
				else {
					if (fc!=bc) Gui_DrawPoint(x+j*8+k,y+i,bc);
				}
			}
		}
	}
}