#include "lcd.h"
#include "DotARRAY.h"

uint8_t LCDCOMMAND[11] = 
{	
	0x40,	  	//SCOLL LINE=0	 ST7539
	0xf1,63,  //SET COM END=63
	0xa6,	  	//NORMAL DISPLAY
	0x89,	  	//SET RAM ADDRESS CONTROL
	0xa0,	  	//FRAME RATE=76Hz
	0xeb,	  	//SET BIAS=1/9
	0x81, 125,//SET VOP
//	0xc2, 
	0xc4, 	
	0xaf

};

extern SPI_HandleTypeDef hspi1;

void SPI1_ReadWriteByte(uint8_t TxData)
{
	HAL_SPI_Transmit(&hspi1, &TxData, 1, 1000);
}

void FL_SPISend_NByte(uint8_t *Txbuf,uint8_t LCD_CMD,uint8_t Len)
{
	uint8_t	i;
	
	Lcd_Select();	
	
	if(LCD_CMD)
	{
		Lcd_DataMode();
	}
	else
	{
		Lcd_CmdMode();
	}
	for(i=0;i<Len;i++)
	{
		SPI1_ReadWriteByte(Txbuf[i]);
	}
	Lcd_Deselect();
	Lcd_DataMode();

}
///===============================================================
//vDISP_ResetLcd
//LCD��ʼ��ʱ���临λ�ź�
///===============================================================
void FL_vDISP_ResetLcd(void)
{
		Lcd_RST_H();
		HAL_Delay(10); //
		Lcd_RST_L();
		HAL_Delay(10);	//
		Lcd_RST_H();
}

void FL_LCD_Init(void)
{ 
		//Һ����ʼ��
		FL_vDISP_ResetLcd();
		FL_SPISend_NByte(LCDCOMMAND,LCD_CMD_MODE,LCD_COMMAND_LENGTH);
}
/******************************************************
**Lcd_SetPosition
**Input1:	lcdpage��ҳ���
**Input2:	lcdcolum�������
**Output:	none
**Return:	none
******************************************************/
void Lcd_SetPosition(uint8_t lcdpage,uint8_t lcdcolum)
{
	uint8_t lcdorderbuf[4];

	lcdorderbuf[0] = LCD_PAGE_ADDRESS_SET + lcdpage;
	lcdorderbuf[1] = LCD_COL_ADD_SET_UPPER + ((lcdcolum >> 4) & 0x0F);
	lcdorderbuf[2] = LCD_COL_ADD_SET_LOWER + (lcdcolum & 0x0F);
	lcdorderbuf[3] = 0x40;
	FL_SPISend_NByte(lcdorderbuf,LCD_CMD_MODE,4);
}

/******************************************************
**Lcd_FillRam�������ͬ������
**Input:data ���������
**Output:	none
**Return:	none
******************************************************/
void Lcd_FillRam(uint8_t data)
{
	uint8_t i,buf[LCD_WIDTH];
	
	for(i=0; i<LCD_WIDTH; i++)
	{
		buf[i]=data;
	}

	for(i = 0;i < LCD_PAGE;i ++)
	{
		Lcd_SetPosition(i, 0);
		FL_SPISend_NByte(buf,LCD_DAT_MODE,LCD_WIDTH);
	}
}

/******************************************************
**Lcd_DisplayDatas,��ָ��λ��д��һ�����ݣ����ݳ��Ȳ��ó�����ʣ������
**Input1: lcdpage��ҳ���	
**Input2:	lcdcolum�������
**Input3:	*ptdata�����ݵ�ַ
**Input4:	len�����ݳ���
**Output:	none
**Return:	none
******************************************************/
void Lcd_DisplayDatas(uint8_t lcdpage, uint8_t lcdcolum, uint8_t *ptdata, uint8_t len)
{
	Lcd_SetPosition(lcdpage, lcdcolum);
	FL_SPISend_NByte(ptdata,LCD_DAT_MODE,len);
}

/******************************************************
**��������:Lcd_DispOneChar
**��ڲ���:x,y,chr
**˵��:��ʾһ���ַ�
**���ڲ���:��
******************************************************/
void Lcd_DispOneChar(uint8_t x,uint8_t y,uint8_t chr)
{
	uint8_t i,m=0,temp,chr1;

	chr1=chr-' ';  //����ƫ�ƺ��ֵ
	Lcd_SetPosition(x,y);
	for(i=0;i<16;i++)
	{
		if(i<8)
		{	
			Lcd_SetPosition(x,y+i);
			temp=asc2_1608[chr1][i];
			FL_SPISend_NByte(&temp,LCD_DAT_MODE,1);

		}
		else
		{
			Lcd_SetPosition(x+1,y+m);
			temp=asc2_1608[chr1][i];
			FL_SPISend_NByte(&temp,LCD_DAT_MODE,1);
		
			m++;		
		}
	}
}

/******************************************************
**��������:Lcd_DispString
**��ڲ���:x,y,*ChrString
**˵��:��ʾһ���ַ�
**���ڲ���:��
******************************************************/
void Lcd_DispString(uint8_t x,uint8_t y,char *ChrString)
{
	uint8_t j=0;
	
	while(*ChrString!='\0')
	{
		Lcd_DispOneChar(x,y+j*8,*ChrString);
		j++;
		ChrString++;
		
	}
}
/******************************************************
**��������:Lcd_DispNumber
**��ڲ���:x,y,num
**˵��:��ʾ����
**���ڲ���:��
******************************************************/
void Lcd_DispNumber(uint8_t x,uint8_t y,int16_t num)
{
	uint8_t temp = 0,j=0;
	//��ʾ4λ����
	if(num/1000!=0)
	{
		temp = 	num/1000;
		temp+=0x30;
		Lcd_DispOneChar(x,y+j*8,temp);	
		j++;
		
		temp = 	num%1000/100;
		temp+=0x30;
		Lcd_DispOneChar(x,y+j*8,temp);
		j++;
		
		temp = 	num%1000%100/10;
		temp+=0x30;
		Lcd_DispOneChar(x,y+j*8,temp);
		j++;
		
		temp = 	num%1000%100%10;
		temp+=0x30;
		Lcd_DispOneChar(x,y+j*8,temp);	
	}
	else if(num/100!=0)
	{
		temp = 	num/100;
		temp+=0x30;
		Lcd_DispOneChar(x,y+j*8,temp);	
		j++;
		
		temp = 	num%100/10;
		temp+=0x30;
		Lcd_DispOneChar(x,y+j*8,temp);
		j++;
				
		temp = 	num%100%10;
		temp+=0x30;
		Lcd_DispOneChar(x,y+j*8,temp);		
	}
	else if(num/10!=0)
	{
		temp = 	num/10;
		temp+=0x30;
		Lcd_DispOneChar(x,y+j*8,temp);	
		j++;
		
		temp = 	num%10;
		temp+=0x30;
		Lcd_DispOneChar(x,y+j*8,temp);	
	}
	else
	{
		temp = 	num%10;
		temp+=0x30;
		Lcd_DispOneChar(x,y+j*8,temp);	
	}
}
