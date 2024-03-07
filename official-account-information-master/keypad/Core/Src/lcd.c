#include "lcd.h"
#include "gpio.h"
#include "stdio.h"
#include "ST7789.h"
#include "stdlib.h"
#include "string.h"
#include "gui.h"
#include "userfont.h"

extern SPI_HandleTypeDef hspi1;
#define USE_ASCII_FONT_LIB

GUI_FONT_SHOW *font_show;


void lcd_draw_rectangle(uint16_t x_start, uint16_t y_start, uint16_t x_end, uint16_t y_end, uint16_t color);
void lcd_SendBytes(uint8_t byte)
{
    HAL_SPI_Transmit(&hspi1, &byte, 1, 100);
}
/**
 * @brief		д16λ�����ݣ������ֽڣ���LCD
 * @param   dat ���� ��Ҫ���͵�16bit����
 * @return  none
 */
void LCD_Write_2Bytes(const uint16_t dat)
{
    uint8_t data[2] = {0};

    data[0] = dat >> 8;
    LCD_data_write(data[0]);
    data[1] = dat;
    LCD_data_write(data[1]);
}

void LCD_command_write(uint8_t command)
{ // д����
    LCD_DC_LOW();
    LCD_CS_LOW();
    lcd_SendBytes(command);
    LCD_CS_HIGH();
}
void LCD_data_write(uint8_t data)
{ //д����
    LCD_DC_HIGH();
    LCD_CS_LOW();
    lcd_SendBytes(data);
    LCD_CS_HIGH();
}

void delay_lcd(unsigned int time)
{
    while (time)
    {
        time--;
        time--;
        time--;
        time--;
    }
}

void LCD_Reset(void)
{
    LCD_REST_HIGH();
    delay_lcd(1000);
    LCD_REST_LOW();
    delay_lcd(10000);
    LCD_REST_HIGH();
    delay_lcd(10000);
    LCD_CS_HIGH();
}

void lcd_init(void)
{
    LCD_CS_HIGH();
    LCD_Reset();

    /************* display Setting *************/
    LCD_command_write(0x01);
    delay_lcd(10000);
    LCD_command_write(LCD_CMD_SLPOUT);
    delay_lcd(10000);

    //�޸Ĵ˴������Ըı���Ļ����ʾ���򣬺�����������
    LCD_command_write(LCD_CMD_MADCTL); // 0x36  ///< Memory Data Access Control
    LCD_data_write(0xc0);              //50//40//C0

    LCD_command_write(LCD_CMD_COLMOD); //  0x3A     ///< Interface Pixel Format
    LCD_data_write(0x05);              /// 16bit/pixel

    /*********** Frame Rate Setting ***********/
    LCD_command_write(LCD_CMD_PORCTRL); //0xB2     ///< Porch Setting
    LCD_data_write(0x0c);               ///< Back porch in normal mode
    LCD_data_write(0x0c);               ///< Front porch in normal mode
    LCD_data_write(0x00);               ///< Disable separate porch control
    LCD_data_write(0x33);               ///< Back and front porch in idle mode
    LCD_data_write(0x33);               ///< Back and front porch in partial mode

    LCD_command_write(LCD_CMD_GCTRL); //  0xB7     ///< Gate Control
    LCD_data_write(0x72);             ///< VGH:13.26, VGL:-10.43

    LCD_command_write(LCD_CMD_VCOMS); // 0xBB     ///< VCOM Setting
    LCD_data_write(0x3d);             ///< VCOM: 1.425

    LCD_command_write(LCD_CMD_LCMCTRL); ///0xC0     ///< LCM Control
    LCD_data_write(0x2c);

    LCD_command_write(LCD_CMD_VDVVRHEN); //0xC2     ///< VDV and VRH Command Enable
    LCD_data_write(0x01);
    LCD_data_write(0xFF);

    /* VRH Set */
    LCD_command_write(LCD_CMD_VRHS); //0xC3
    LCD_data_write(0x19);

    /* VDV Set */
    LCD_command_write(LCD_CMD_VDVS); //0xC4
    LCD_data_write(0x20);

    LCD_command_write(LCD_CMD_FRCTRL2); //  0xC6     ///< Frame Rate Control in Normal Mode
    LCD_data_write(0x0f);               ///< 60Hz

    LCD_command_write(LCD_CMD_PWCTRL1); // 0xD0     ///< Power Control 1
    LCD_data_write(0xa4);
    LCD_data_write(0xa1); ///< AVDD:6.8V, AVCL:-4.8V, VDDS:2.3V

    /* Positive Voltage Gamma Control */
    LCD_command_write(0xE0);
    LCD_data_write(0xD0);
    LCD_data_write(0x04);
    LCD_data_write(0x0D);
    LCD_data_write(0x11);
    LCD_data_write(0x13);
    LCD_data_write(0x2B);
    LCD_data_write(0x3F);
    LCD_data_write(0x54);
    LCD_data_write(0x4C);
    LCD_data_write(0x18);
    LCD_data_write(0x0D);
    LCD_data_write(0x0B);
    LCD_data_write(0x1F);
    LCD_data_write(0x23);

    /* Negative Voltage Gamma Control */
    LCD_command_write(0xE1);
    LCD_data_write(0xD0);
    LCD_data_write(0x04);
    LCD_data_write(0x0C);
    LCD_data_write(0x11);
    LCD_data_write(0x13);
    LCD_data_write(0x2C);
    LCD_data_write(0x3F);
    LCD_data_write(0x44);
    LCD_data_write(0x51);
    LCD_data_write(0x2F);
    LCD_data_write(0x1F);
    LCD_data_write(0x1F);
    LCD_data_write(0x20);
    LCD_data_write(0x23);

    // LCD_command_write( 0x21);     ///< Display Inversion On
    //LCD_command_write( 0x13);
    //LCD_InitSequence();
    //Display_logo();
    // lcd_clear(LCD_DISP_RED);
    lcd_clear(LCD_DISP_WRITE);
		/*
    LCD_command_write(LCD_CMD_DISPON); ///< Display on
    HAL_Delay(100);
    lcd_clear(LCD_DISP_BLUE);
    HAL_Delay(100);
    lcd_clear(LCD_DISP_BLACK);
    HAL_Delay(100);
    lcd_clear(LCD_DISP_WRITE);
    HAL_Delay(100);
    LCD_Draw_ColorCircle(120, 160, 50, LCD_DISP_RED);
    HAL_Delay(100);
    LCD_Draw_ColorCircle(120, 160, 60, LCD_DISP_RED);
    HAL_Delay(100);
    LCD_Draw_ColorCircle(120, 160, 70, LCD_DISP_RED);
    HAL_Delay(100);
    LCD_Draw_ColorCircle(120, 160, 80, LCD_DISP_RED);
    HAL_Delay(100);
    lcd_clear(LCD_DISP_GREEN);
    HAL_Delay(100);
    lcd_clear(LCD_DISP_RED);
    HAL_Delay(100);
    lcd_clear(LCD_DISP_GRAY50);
    HAL_Delay(100);
    lcd_clear(LCD_DISP_WRITE);
    HAL_Delay(100);
    lcd_draw_rectangle(50, 100, 200, 200, LCD_DISP_GREEN);
    HAL_Delay(100);
    lcd_draw_rectangle(50, 120, 190, 190, LCD_DISP_GREEN);
    HAL_Delay(100);
    lcd_clear(LCD_DISP_BLACK);
    HAL_Delay(100);
    lcd_clear(LCD_DISP_GREEN);
    HAL_Delay(100);
    lcd_clear(LCD_DISP_RED);
    HAL_Delay(100);
    lcd_clear(LCD_DISP_GRAY50);
    HAL_Delay(100);
    lcd_clear(LCD_DISP_WRITE);
    HAL_Delay(100);
    lcd_clear(LCD_DISP_BLACK);
    HAL_Delay(100);
    lcd_clear(LCD_DISP_GREEN);
    HAL_Delay(100);
    lcd_clear(LCD_DISP_RED);
    HAL_Delay(100);
    lcd_clear(LCD_DISP_GRAY50);
    HAL_Delay(100);
    lcd_clear(LCD_DISP_WRITE);
    LCD_CS_HIGH();
		*/
    LCD_ShowChinese(65, 180, "����", LCD_DISP_BLACK, LCD_DISP_WRITE, 48, 1);
    LCD_ShowChar_Str(20, 20, 20, "Embeded_Party", 0xffff, 0, 32);
    HAL_Delay(100);

    //txt_show();
    // lcd_clear(LCD_DISP_WRITE);
}

//ST7789V2
//========================================================
//DISPON (29h): Display On
//========================================================
void lcd_display_on(void)
{
    LCD_command_write(0x11); //sleep out
    LCD_command_write(0x13);
    LCD_command_write(0x29);
}
//========================================================
//DISPOFF (28h): Display Off
//========================================================
void lcd_display_off(void)
{

    LCD_command_write(0x13);
    LCD_command_write(0x28);
    LCD_command_write(0x10); //sleep in

    //Display off power save
    //LCD_command_write(0xBD);
    //LCD_data_write(0XFE);
}
//========================================================
//Memory Write ʹ��д�����ݵ�RAM
//========================================================
void lcd_write_ram(void)
{
    LCD_command_write(0x2C);
}
//========================================================
//CASET (2Ah): Column Address Set
//RASET (2Bh): Row Address Set
//x1,y1:��ʼ��ַ,x2,y2:�յ��ַ
//========================================================
void lcd_set_address(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2)
{
    LCD_command_write(0x2a);
    LCD_data_write(x1 >> 8);
    LCD_data_write(x1);
    LCD_data_write(x2 >> 8);
    LCD_data_write(x2);

    LCD_command_write(0x2b);
    LCD_data_write(y1 >> 8);
    LCD_data_write(y1);
    LCD_data_write(y2 >> 8);
    LCD_data_write(y2);

    LCD_command_write(0x2C); // write_ram
}
//========================================================
//LCD����  color:Ҫд�����ɫ
//�ȹ���ʾ�������е�����д�뵽RAM���ٴ���ʾ
//========================================================
void lcd_clear(uint16_t color)
{

    uint16_t i, j;
    LCD_command_write(0x2A);
    LCD_data_write(0);
    LCD_data_write(0);
    LCD_data_write(0);
    LCD_data_write(240);
    LCD_command_write(0X2B);
    LCD_data_write(0);
    LCD_data_write(0);
    LCD_data_write(0X01);
    LCD_data_write(0X40);

    LCD_command_write(0X2C);

    for (i = 0; i < 240; i++)
    {
        for (j = 0; j < 320; j++)
        {
            LCD_data_write(color >> 8);
            LCD_data_write(color);
        }
    }
    lcd_display_on(); /* ��LCD��ʾ */
}

void lcd_clear_size(uint16_t x_star, uint16_t y_star, uint16_t x_end, uint16_t y_end, uint16_t color)
{

    uint16_t color_dma[4096];
    unsigned int area;
    memset(color_dma, color, 4096 * 2);
    // lcd_display_off();		/*��LCD��ʾ */
    lcd_set_address(x_star, y_star, x_end - 1, y_end - 1);
    area = (x_end - x_star) * (y_end - y_star);
    LCD_DC_HIGH();
    LCD_CS_LOW();
    while (area > 4094)
    {
        //DMA_Sendhalfword(color_dma, 4094);
        area = area - 4094;
    }
    if (area)
        //HAL_SPI_Transmit_DMA(&hspi1,&color_dma,area);
        ;
    LCD_CS_HIGH();

    //lcd_display_on();		/* ��LCD��ʾ */
}

//========================================================
//LCD��һ����
//x,y	--> ��������,color --> ������ɫ
//========================================================
void lcd_draw_point(uint16_t x, uint16_t y, uint16_t color)
{
    lcd_set_address(x, y, x, y);
    LCD_data_write(color >> 8);
    LCD_data_write(color & 0x00ff);
}

void LCD_DrawFRONT_COLOR(uint16_t x, uint16_t y, uint16_t color)//���� 
{
	lcd_draw_point(x,y,color);
}



void lcd_clear_area(uint16_t x, uint16_t y, uint16_t x_end, uint16_t y_end, uint16_t color)
{
    uint16_t i, j;
    lcd_set_address(x, y, x_end, y_end);

    for (i = x; i < x_end + 1; i++)
    {
        for (j = y; j < y_end + 1; j++)
        {
            LCD_data_write(color >> 8);
            LCD_data_write(color & 0x00ff);
        }
    }
}

void lcd_draw_x_line(uint16_t x_start, uint16_t y_start, uint16_t x_end, uint16_t y_end, uint16_t color)
{
    uint16_t i;
    lcd_set_address(x_start, y_start, x_end, y_end);
    for (i = x_start; i < x_end + 1; i++)
    {
        LCD_data_write(color >> 8);
        LCD_data_write(color & 0x00ff);
    }
}

void lcd_draw_y_line(uint16_t x_start, uint16_t y_start, uint16_t x_end, uint16_t y_end, uint16_t color)
{
    uint16_t i;
    lcd_set_address(x_start, y_start, x_end, y_end);
    for (i = y_start; i < y_end + 1; i++)
    {
        LCD_data_write(color >> 8);
        LCD_data_write(color & 0x00ff);
    }
}

void lcd_draw_rectangle(uint16_t x_start, uint16_t y_start, uint16_t x_end, uint16_t y_end, uint16_t color)
{
    uint16_t i;

    lcd_set_address(x_start, y_start, x_end, y_start);
    for (i = x_start; i < x_end + 1; i++)
    {
        LCD_data_write(color >> 8);
        LCD_data_write(color & 0x00ff);
    }
    lcd_set_address(x_start, y_end, x_end, y_end);
    for (i = x_start; i < x_end + 1; i++)
    {
        LCD_data_write(color >> 8);
        LCD_data_write(color & 0x00ff);
    }

    lcd_set_address(x_start, y_start, x_start, y_end);
    for (i = y_start; i < y_end + 1; i++)
    {
        LCD_data_write(color >> 8);
        LCD_data_write(color & 0x00ff);
    }

    lcd_set_address(x_end, y_start, x_end, y_end);
    for (i = y_start; i < y_end + 1; i++)
    {
        LCD_data_write(color >> 8);
        LCD_data_write(color & 0x00ff);
    }
}
void DMA_Sendhalfword(uint16_t *byte, unsigned int lenth)
{
    int i = 0;

    for (i = 0; i < lenth; i++)
    {
        LCD_Write_2Bytes(byte[i]);
    }
}

static uint8_t lcd_buf[LCD_Buf_Size];

/**
 * @brief	LCD�ײ�SPI�������ݺ���
 * @param   data ���� ���ݵ���ʼ��ַ
 * @param   size ���� ���������ֽ���
 * @return  none
 */

uint8_t SPI2_WriteByte(uint8_t *TxData, uint16_t size)
{
    return HAL_SPI_Transmit(&hspi1, TxData, size, 100);
}

static void LCD_SPI_Send(uint8_t *data, uint16_t size)
{
    SPI2_WriteByte(data, size);
}

/**
 * @brief	д���LCD
 * @param   cmd ���� ��Ҫ���͵�����
 * @return  none
 */
void LCD_Write_Cmd(uint8_t cmd)
{
    LCD_command_write(cmd);
}

/**
 * @brief	д���ݵ�LCD
 * @param 	dat ���� ��Ҫ���͵�����
 * @return  none
 */
void LCD_Write_Data(uint8_t dat)
{
    LCD_data_write(dat);
}
/**
 * @brief		д16λ�����ݣ������ֽڣ���LCD
 * @param   dat ���� ��Ҫ���͵�16bit����
 * @return  none
 */
void LCD_Write_2Byte(const uint16_t dat)
{
    uint8_t data[2] = {0};

    data[0] = dat >> 8;
    LCD_data_write(data[0]);
    data[1] = dat;
    LCD_data_write(data[1]);
}
/**
 * @brief	��������д��LCD��������
 * @param   x1,y1	���� �������
 * @param   x2,y2	���� �յ�����
 * @return  none
 */
void LCD_Address_Set(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2)
{
    LCD_Write_Cmd(0x2a);
    LCD_Write_Data(x1 >> 8);
    LCD_Write_Data(x1);
    LCD_Write_Data(x2 >> 8);
    LCD_Write_Data(x2);

    LCD_Write_Cmd(0x2b);
    LCD_Write_Data(y1 >> 8);
    LCD_Write_Data(y1);
    LCD_Write_Data(y2 >> 8);
    LCD_Write_Data(y2);

    LCD_Write_Cmd(0x2C);
}

/**
  * ��������: ��LCD��ʾ���Ͽ���һ������
  * �������: usX �����ض�ɨ�跽���´��ڵ����X����
  *           usY �����ض�ɨ�跽���´��ڵ����Y����
  *           usWidth �����ڵĿ��
  *           usHeight �����ڵĸ߶�
  * �� �� ֵ: ��
  * ˵    ������
  */
void LCD_OpenWindow(uint16_t usX, uint16_t usY, uint16_t usWidth, uint16_t usHeight)
{
    LCD_Write_Cmd(0x2A);                        /* ����X���� */
    LCD_Write_Data(usX >> 8);                   /* ������ʼ�㣺�ȸ�8λ */
    LCD_Write_Data(usX & 0xff);                 /* Ȼ���8λ */
    LCD_Write_Data((usX + usWidth - 1) >> 8);   /* ���ý����㣺�ȸ�8λ */
    LCD_Write_Data((usX + usWidth - 1) & 0xff); /* Ȼ���8λ */

    LCD_Write_Cmd(0x2B);                         /* ����Y����*/
    LCD_Write_Data(usY >> 8);                    /* ������ʼ�㣺�ȸ�8λ */
    LCD_Write_Data(usY & 0xff);                  /* Ȼ���8λ */
    LCD_Write_Data((usY + usHeight - 1) >> 8);   /* ���ý����㣺�ȸ�8λ */
    LCD_Write_Data((usY + usHeight - 1) & 0xff); /* Ȼ���8λ */
}

/**
 * @breif	��LCD��ʾ����
 * @param   none
 * @return  none
 */
void LCD_DisplayOn(void)
{
}
/**
 * @brief	�ر�LCD��ʾ����
 * @param   none
 * @return  none
 */
void LCD_DisplayOff(void)
{
}

void tos_knl_sched_lock(void)
{
    return;
}

void tos_knl_sched_unlock(void)
{
    return;
}

/**
 * @brief	��һ����ɫ���LCD��
 * @param   color ���� ������ɫ(16bit)
 * @return  none
 */
void LCD_Clear(uint16_t color)
{
    tos_knl_sched_lock();
    uint16_t i, j;
    uint8_t data[2] = {0}; //LCD��Ļɫ�����16bit��data[0]����ɫ���ݵĸ�λ��data[1]����ɫ���ݵĵ�λ

    data[0] = color >> 8;
    data[1] = color;

    LCD_Address_Set(0, 0, LCD_Width - 1, LCD_Height - 1);

    for (j = 0; j < LCD_Buf_Size / 2; j++)
    {
        lcd_buf[j * 2] = data[0];
        lcd_buf[j * 2 + 1] = data[1];
    }

    //LCD_WR_RS(1);

    for (i = 0; i < (LCD_TOTAL_BUF_SIZE / LCD_Buf_Size); i++)
    {
        LCD_SPI_Send(lcd_buf, LCD_Buf_Size);
    }
    tos_knl_sched_unlock();
}

/**
 * @brief		����ɫ���㺯��
 * @param   x,y	���� ��������
 * @return  none
 */
void LCD_Draw_ColorPoint(uint16_t x, uint16_t y, uint16_t color)
{
    LCD_Address_Set(x, y, x, y);
    LCD_Write_2Byte(color);
}
/**
 * @brief		����ɫ���ߺ���(ֱ�ߡ�б��)
 * @param   x1,y1	�������
 * @param   x2,y2	�յ�����
 * @return  none
 */
void LCD_Draw_ColorLine(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, uint16_t color)
{
    uint16_t i = 0;
    int16_t delta_x = 0, delta_y = 0;
    int8_t incx = 0, incy = 0;
    uint16_t distance = 0;
    uint16_t t = 0;
    uint16_t x = 0, y = 0;
    uint16_t x_temp = 0, y_temp = 0;

    if (y1 == y2)
    {
        /* ���ٻ�ˮƽ�� */
        LCD_Address_Set(x1, y1, x2, y2);

        for (i = 0; i < x2 - x1; i++)
        {
            lcd_buf[2 * i] = color >> 8;
            lcd_buf[2 * i + 1] = color;
        }

        //LCD_WR_RS(1);
        LCD_SPI_Send(lcd_buf, (x2 - x1) * 2);
        return;
    }
    else
    {
        /* ��б�ߣ�Bresenham�㷨�� */
        /* ��������֮����x��y����ļ�࣬�õ�������x��y����Ĳ���ֵ */
        delta_x = x2 - x1;
        delta_y = y2 - y1;
        if (delta_x > 0)
        {
            //б��(������)
            incx = 1;
        }
        else if (delta_x == 0)
        {
            //��ֱб��(����)
            incx = 0;
        }
        else
        {
            //б��(���ҵ���)
            incx = -1;
            delta_x = -delta_x;
        }
        if (delta_y > 0)
        {
            //б��(������)
            incy = 1;
        }
        else if (delta_y == 0)
        {
            //ˮƽб��(ˮƽ��)
            incy = 0;
        }
        else
        {
            //б��(���ҵ���)
            incy = -1;
            delta_y = -delta_y;
        }

        /* ���㻭�ʴ�����(ȡ��������е����ֵ) */
        if (delta_x > delta_y)
        {
            distance = delta_x;
        }
        else
        {
            distance = delta_y;
        }

        /* ��ʼ��� */
        x = x1;
        y = y1;
        //��һ������Ч������t�Ĵ�����һ
        for (t = 0; t <= distance + 1; t++)
        {
            LCD_Draw_ColorPoint(x, y, color);

            /* �ж���ʵ��ֵ��������ص� */
            x_temp += delta_x;
            if (x_temp > distance)
            {
                //x����Խ�磬��ȥ����ֵ��Ϊ��һ�μ����׼��
                x_temp -= distance;
                //��x����������
                x += incx;
            }
            y_temp += delta_y;
            if (y_temp > distance)
            {
                //y����Խ�磬��ȥ����ֵ��Ϊ��һ�μ����׼��
                y_temp -= distance;
                //��y����������
                y += incy;
            }
        }
    }
}
/**
 * @breif	����ɫ�����κ���
 * @param   x1,y1 ���� ������ʼ��
 * @param	x2,y2 ���� �����յ�
 * @param	color	���� ��ɫ
 * @retval	none
 */
void LCD_Draw_ColorRect(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, uint16_t color)
{
    tos_knl_sched_lock();
    LCD_Draw_ColorLine(x1, y1, x2, y1, color);
    LCD_Draw_ColorLine(x1, y1, x1, y2, color);
    LCD_Draw_ColorLine(x1, y2, x2, y2, color);
    LCD_Draw_ColorLine(x2, y1, x2, y2, color);
    tos_knl_sched_unlock();
}
/**
 * @breif	����ɫ��Բ����
 * @param   x1,x2 ���� Բ������
 * @param	r ���� �뾶
 * @param	color	���� ��ɫ
 * @retval	none
 */
void LCD_Draw_ColorCircle(uint16_t x, uint16_t y, uint16_t r, uint16_t color)
{
    /* Bresenham��Բ�㷨 */
    int16_t a = 0, b = r;
    int16_t d = 3 - (r << 1); //�㷨���߲���

    /* ���Բ����Ļ�ɼ������⣬ֱ���˳� */
    if (x - r < 0 || x + r > LCD_Width || y - r < 0 || y + r > LCD_Height)
    {
        return;
    }
    /* ��ʼ��Բ */
    while (a <= b)
    {
        LCD_Draw_ColorPoint(x - b, y - a, color);
        LCD_Draw_ColorPoint(x + b, y - a, color);
        LCD_Draw_ColorPoint(x - a, y + b, color);
        LCD_Draw_ColorPoint(x - b, y - a, color);
        LCD_Draw_ColorPoint(x - a, y - b, color);
        LCD_Draw_ColorPoint(x + b, y + a, color);
        LCD_Draw_ColorPoint(x + a, y - b, color);
        LCD_Draw_ColorPoint(x + a, y + b, color);
        LCD_Draw_ColorPoint(x - b, y + a, color);
        a++;

        if (d < 0)
        {
            d += 4 * a + 6;
        }
        else
        {
            d += 10 + 4 * (a - b);
            b--;
        }

        LCD_Draw_ColorPoint(x + a, y + b, color);
    }
}
/**
 * @brief	��һ����ɫ���/���ĳ����������
 * @param   color ���� ������ɫ(16bit)
 * @return  none
 */
void LCD_Fill(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, uint16_t color)
{
    tos_knl_sched_lock();
    uint16_t i = 0;
    uint32_t size = 0, size_remain = 0;

    size = (x2 - x1 + 1) * (y2 - y1 + 1) * 2;

    if (size > LCD_Buf_Size)
    {
        size_remain = size - LCD_Buf_Size;
        size = LCD_Buf_Size;
    }

    LCD_Address_Set(x1, y1, x2, y2);

    while (1)
    {
        for (i = 0; i < size / 2; i++)
        {
            lcd_buf[2 * i] = color >> 8;
            lcd_buf[2 * i + 1] = color;
        }

        LCD_WR_RS(1);
        LCD_SPI_Send(lcd_buf, size);

        if (size_remain == 0)
            break;

        if (size_remain > LCD_Buf_Size)
        {
            size_remain = size_remain - LCD_Buf_Size;
        }

        else
        {
            size = size_remain;
            size_remain = 0;
        }
    }
    tos_knl_sched_unlock();
}

/**
 * @brief	��ʾһ��ASCII���ַ�
 * @param   x,y		��ʾ��ʼ����
 * @param   ch		��Ҫ��ʾ���ַ�
 * @param   size	�����С(֧��16/24/32������)
 * @return  none
 * @note	��Ҫfont.h�ֿ��ļ���֧��
 */
void LCD_ShowChar(uint16_t x, uint16_t y, char ch, uint16_t back_color, uint16_t font_color, uint8_t font_size)
{
    int i = 0, j = 0;
    uint8_t temp = 0;
    uint8_t size = 0;
    uint8_t t = 0;

    /* �����ʾ�Ƿ��Խ�� */
    if ((x > (LCD_Width - font_size / 2)) || (y > (LCD_Height - font_size)))
        return;

    /* �����ַ���С�����Դ�������� */
    LCD_Address_Set(x, y, x + font_size / 2 - 1, y + font_size - 1);

    /* �����ַ����ֿ��е�ƫ��ֵ*/
    ch = ch - ' ';

    /* ��ʾ16��/32������ */
    if ((font_size == 16) || (font_size == 32))
    {
        /* ��������һ���ַ���Ӧ������ռ���ֽ��� */
        size = (font_size / 8 + ((font_size % 8) ? 1 : 0)) * (font_size / 2);

        for (i = 0; i < size; i++)
        {
            if (font_size == 16)
                temp = asc2_1608[ch][i]; //����1608����
            else if (font_size == 32)
                temp = asc2_3216[ch][i]; //����3216����
            else
                return; //û�е��ֿ�

            for (j = 0; j < 8; j++)
            {
                if (temp & 0x80)
                    LCD_Write_2Byte(font_color);
                else
                    LCD_Write_2Byte(back_color);

                temp <<= 1;
            }
        }
    }
    /* ��ʾ12������ */
    else if (font_size == 12)
    {
        /* ��������һ���ַ���Ӧ������ռ���ֽ��� */
        size = (font_size / 8 + ((font_size % 8) ? 1 : 0)) * (font_size / 2);

        for (i = 0; i < size; i++)
        {
            temp = asc2_1206[ch][i];

            for (j = 0; j < 6; j++)
            {
                if (temp & 0x80)
                    LCD_Write_2Byte(font_color);
                else
                    LCD_Write_2Byte(back_color);

                temp <<= 1;
            }
        }
    }
    /* ��ʾ24������ */
    else if (font_size == 24)
    {
        /* ��������һ���ַ���Ӧ������ռ���ֽ��� */
        size = (font_size * 16) / 8;

        for (i = 0; i < size; i++)
        {
            temp = asc2_2412[ch][i];
            if (i % 2 == 0)
                t = 8;
            else
                t = 4;
            for (j = 0; j < t; j++)
            {
                if (temp & 0x80)
                    LCD_Write_2Byte(font_color);
                else
                    LCD_Write_2Byte(back_color);

                temp <<= 1;
            }
        }
    }
    /* �������� */
    else
        return;
}
/**
 * @brief		��ʾһ��ASCII���ַ���
 * @param   x,y		��ʾ��ʼ����
 * @param   str		��Ҫ��ʾ���ַ���
 * @param   size	�����С(֧��16/24/32������)
 * @return  none
 * @note		1. ��Ҫfont.h�ֿ��ļ���֧��
 * 					2. ����ָ��width����ʾ�������ַ�
 */
void LCD_ShowChar_Str(uint16_t x, uint16_t y, uint8_t max_width, char *str, uint16_t back_color, uint16_t font_color, uint8_t font_size)
{
    tos_knl_sched_lock();
    max_width += x;

    while ((*str <= '~') && (*str >= ' ')) //�ж��Ƿ�Ƿ��ַ�
    {
        if (x >= max_width * font_size)
        {
            //x����Խ�磬����
            break;
        }

        LCD_ShowChar(x, y, *str, back_color, font_color, font_size);
        x += font_size / 2;
        str++;
    }
    tos_knl_sched_unlock();
}

/* USE_ASCII_FONT_LIB */
/**
 * @breif		����ɫ����â�Ǻ���
 * @param   x,y ���� ��â�����ĵ�
 * @param		r ���� ��â�ǰ뾶
 * @param		color	���� ��ɫ
 * @retval	none
 */
void LCD_Draw_ColorSixPointStar(uint16_t x, uint16_t y, uint8_t r, uint16_t color)
{
    uint16_t a = r / 2;
    uint16_t b = 1.432 * r;

    /* ���Ƶ����� */
    LCD_Draw_ColorLine(x - b, y - a, x + b, y - a, color);
    LCD_Draw_ColorLine(x + b, y - a, x, y + r, color);
    LCD_Draw_ColorLine(x, y + r, x - b, y - a, color);

    /* ���������� */
    LCD_Draw_ColorLine(x - b, y + a, x + b, y + a, color);
    LCD_Draw_ColorLine(x + b, y + a, x, y - r, color);
    LCD_Draw_ColorLine(x, y - r, x - b, y + a, color);
}

/**
 * @brief	��ʾͼƬ����
 * @param   x,y	    ���� �������
 * @param   width	���� ͼƬ���
 * @param   height	���� ͼƬ�߶�
 * @param   p       ���� ͼƬ����������ʼ��ַ
 * @return  none
 * @note	Image2Lcdȡģ��ʽ��C��������/ˮƽɨ��/16λ���ɫ(RGB565)/��λ��ǰ�������Ĳ�ѡ
 */
void LCD_Show_Image(uint16_t x, uint16_t y, uint16_t width, uint16_t height, const uint8_t *p)
{
    uint32_t img_size = width * height * 2; //ͼƬ��ռ�ֽ���
    uint32_t remain_size = img_size;        //ͼƬÿ�η��ͺ�ʣ����ֽ���
    uint8_t i = 0;

    /* ������ */
    if (x + width > LCD_Width || y + height > LCD_Height)
    {
        return;
    }

    LCD_Address_Set(x, y, x + width - 1, y + height - 1);

    LCD_WR_RS(1);

    /* SPIÿ�������2^16 = 65536������,ͼƬ����СΪ240*240*2 = 115200���ᳬ���˴�С���������ѭ�������㷨 */
    for (i = 0; i <= img_size / 65536; i++)
    {
        if (remain_size / 65536 >= 1)
        {
            LCD_SPI_Send((uint8_t *)p, 65535);
            p += 65535;
            remain_size -= 65535;
        }
        else
        {
            LCD_SPI_Send((uint8_t *)p, remain_size % 65535);
        }
    }
}
/*  USE_PICTURE_DISPLAY */

/**********************************************************/
//��ʾ����
/******************************************************************************
      ����˵������ʾ���ִ�
      ������ݣ�x,y��ʾ����
                *s Ҫ��ʾ�ĺ��ִ�
                fc �ֵ���ɫ
                bc �ֵı���ɫ
                sizey �ֺ� ��ѡ 16 24 32
                mode:  0�ǵ���ģʽ  1����ģʽ
      ����ֵ��  ��
******************************************************************************/
void LCD_ShowChinese(uint16_t x, uint16_t y, uint8_t *s, uint16_t fc, uint16_t bc, uint8_t sizey, uint8_t mode)
{
    tos_knl_sched_lock();
    while (*s != 0)
    {
        if (sizey == 12)
            LCD_ShowChinese12x12(x, y, s, fc, bc, sizey, mode);
        else if (sizey == 16)
            LCD_ShowChinese16x16(x, y, s, fc, bc, sizey, mode);
        else if (sizey == 24)
            LCD_ShowChinese24x24(x, y, s, fc, bc, sizey, mode);
        else if (sizey == 32)
            LCD_ShowChinese32x32(x, y, s, fc, bc, sizey, mode);
        else if (sizey == 48)
            LCD_ShowChinese48x48(x, y, s, fc, bc, sizey, mode);
        else
            return;
        s += 2;
        x += sizey;
    }
    tos_knl_sched_unlock();
}
/******************************************************************************
      ����˵������ʾ����12x12����
      ������ݣ�x,y��ʾ����
                *s Ҫ��ʾ�ĺ���
                fc �ֵ���ɫ
                bc �ֵı���ɫ
                sizey �ֺ�
                mode:  0�ǵ���ģʽ  1����ģʽ
      ����ֵ��  ��
******************************************************************************/
void LCD_ShowChinese12x12(uint16_t x, uint16_t y, uint8_t *s, uint16_t fc, uint16_t bc, uint8_t sizey, uint8_t mode)
{
    uint8_t i, j, m = 0;
    uint16_t k;
    uint16_t HZnum;       //������Ŀ
    uint16_t TypefaceNum; //һ���ַ���ռ�ֽڴ�С
    uint16_t x0 = x;
    TypefaceNum = (sizey / 8 + ((sizey % 8) ? 1 : 0)) * sizey;

    HZnum = sizeof(tfont12) / sizeof(typFNT_GB12); //ͳ�ƺ�����Ŀ
    for (k = 0; k < HZnum; k++)
    {
        if ((tfont12[k].Index[0] == *(s)) && (tfont12[k].Index[1] == *(s + 1)))
        {
            LCD_Address_Set(x, y, x + sizey - 1, y + sizey - 1);
            for (i = 0; i < TypefaceNum; i++)
            {
                for (j = 0; j < 8; j++)
                {
                    if (!mode) //�ǵ��ӷ�ʽ
                    {
                        if (tfont12[k].Msk[i] & (0x01 << j))
                            LCD_Write_Data(fc);
                        else
                            LCD_Write_Data(bc);
                        m++;
                        if (m % sizey == 0)
                        {
                            m = 0;
                            break;
                        }
                    }
                    else //���ӷ�ʽ
                    {
                        if (tfont12[k].Msk[i] & (0x01 << j))
                            LCD_Draw_ColorPoint(x, y, fc);
                        x++;
                        if ((x - x0) == sizey)
                        {
                            x = x0;
                            y++;
                            break;
                        }
                    }
                }
            }
        }
        continue; //���ҵ���Ӧ�����ֿ������˳�����ֹ��������ظ�ȡģ����Ӱ��
    }
}

/******************************************************************************
      ����˵������ʾ����16x16����
      ������ݣ�x,y��ʾ����
                *s Ҫ��ʾ�ĺ���
                fc �ֵ���ɫ
                bc �ֵı���ɫ
                sizey �ֺ�
                mode:  0�ǵ���ģʽ  1����ģʽ
      ����ֵ��  ��
******************************************************************************/

void LCD_ShowChinese16x16(uint16_t x, uint16_t y, uint8_t *s, uint16_t fc, uint16_t bc, uint8_t sizey, uint8_t mode)
{
    uint8_t i, j, m = 0;
    uint16_t k;
    uint16_t HZnum;       //������Ŀ
    uint16_t TypefaceNum; //һ���ַ���ռ�ֽڴ�С
    uint16_t x0 = x;
    TypefaceNum = (sizey / 8 + ((sizey % 8) ? 1 : 0)) * sizey;
    HZnum = sizeof(tfont16) / sizeof(typFNT_GB16); //ͳ�ƺ�����Ŀ
    for (k = 0; k < HZnum; k++)
    {
        if ((tfont16[k].Index[0] == *(s)) && (tfont16[k].Index[1] == *(s + 1)))
        {
            LCD_Address_Set(x, y, x + sizey - 1, y + sizey - 1);
            for (i = 0; i < TypefaceNum; i++)
            {
                for (j = 0; j < 8; j++)
                {
                    if (!mode) //�ǵ��ӷ�ʽ
                    {
                        if (tfont16[k].Msk[i] & (0x01 << j))
                            LCD_Write_Data(fc);
                        else
                            LCD_Write_Data(bc);
                        m++;
                        if (m % sizey == 0)
                        {
                            m = 0;
                            break;
                        }
                    }
                    else //���ӷ�ʽ
                    {
                        if (tfont16[k].Msk[i] & (0x01 << j))
                            LCD_Draw_ColorPoint(x, y, fc); //��һ����
                        x++;
                        if ((x - x0) == sizey)
                        {
                            x = x0;
                            y++;
                            break;
                        }
                    }
                }
            }
        }
        continue; //���ҵ���Ӧ�����ֿ������˳�����ֹ��������ظ�ȡģ����Ӱ��
    }
}

/******************************************************************************
      ����˵������ʾ����24x24����
      ������ݣ�x,y��ʾ����
                *s Ҫ��ʾ�ĺ���
                fc �ֵ���ɫ
                bc �ֵı���ɫ
                sizey �ֺ�
                mode:  0�ǵ���ģʽ  1����ģʽ
      ����ֵ��  ��
******************************************************************************/
void LCD_ShowChinese24x24(uint16_t x, uint16_t y, uint8_t *s, uint16_t fc, uint16_t bc, uint8_t sizey, uint8_t mode)
{
    uint8_t i, j, m = 0;
    uint16_t k;
    uint16_t HZnum;       //������Ŀ
    uint16_t TypefaceNum; //һ���ַ���ռ�ֽڴ�С
    uint16_t x0 = x;
    TypefaceNum = (sizey / 8 + ((sizey % 8) ? 1 : 0)) * sizey;
    HZnum = sizeof(tfont24) / sizeof(typFNT_GB24); //ͳ�ƺ�����Ŀ
    for (k = 0; k < HZnum; k++)
    {
        if ((tfont24[k].Index[0] == *(s)) && (tfont24[k].Index[1] == *(s + 1)))
        {
            LCD_Address_Set(x, y, x + sizey - 1, y + sizey - 1);
            for (i = 0; i < TypefaceNum; i++)
            {
                for (j = 0; j < 8; j++)
                {
                    if (!mode) //�ǵ��ӷ�ʽ
                    {
                        if (tfont24[k].Msk[i] & (0x01 << j))
                            LCD_Write_Data(fc);
                        else
                            LCD_Write_Data(bc);
                        m++;
                        if (m % sizey == 0)
                        {
                            m = 0;
                            break;
                        }
                    }
                    else //���ӷ�ʽ
                    {
                        if (tfont24[k].Msk[i] & (0x01 << j))
                            LCD_Draw_ColorPoint(x, y, fc); //��һ����
                        x++;
                        if ((x - x0) == sizey)
                        {
                            x = x0;
                            y++;
                            break;
                        }
                    }
                }
            }
        }
        continue; //���ҵ���Ӧ�����ֿ������˳�����ֹ��������ظ�ȡģ����Ӱ��
    }
}

/******************************************************************************
      ����˵������ʾ����32x32����
      ������ݣ�x,y��ʾ����
                *s Ҫ��ʾ�ĺ���
                fc �ֵ���ɫ
                bc �ֵı���ɫ
                sizey �ֺ�
                mode:  0�ǵ���ģʽ  1����ģʽ
      ����ֵ��  ��
******************************************************************************/
void LCD_ShowChinese32x32(uint16_t x, uint16_t y, uint8_t *s, uint16_t fc, uint16_t bc, uint8_t sizey, uint8_t mode)
{
    uint8_t i, j, m = 0;
    uint16_t k;
    uint16_t HZnum;       //������Ŀ
    uint16_t TypefaceNum; //һ���ַ���ռ�ֽڴ�С
    uint16_t x0 = x;
    TypefaceNum = (sizey / 8 + ((sizey % 8) ? 1 : 0)) * sizey;
    HZnum = sizeof(tfont32) / sizeof(typFNT_GB32); //ͳ�ƺ�����Ŀ
    for (k = 0; k < HZnum; k++)
    {
        if ((tfont32[k].Index[0] == *(s)) && (tfont32[k].Index[1] == *(s + 1)))
        {
            LCD_Address_Set(x, y, x + sizey - 1, y + sizey - 1);
            for (i = 0; i < TypefaceNum; i++)
            {
                for (j = 0; j < 8; j++)
                {
                    if (!mode) //�ǵ��ӷ�ʽ
                    {
                        if (tfont32[k].Msk[i] & (0x01 << j))
                            LCD_Write_Data(fc);
                        else
                            LCD_Write_Data(bc);
                        m++;
                        if (m % sizey == 0)
                        {
                            m = 0;
                            break;
                        }
                    }
                    else //���ӷ�ʽ
                    {
                        if (tfont32[k].Msk[i] & (0x01 << j))
                            LCD_Draw_ColorPoint(x, y, fc); //��һ����
                        x++;
                        if ((x - x0) == sizey)
                        {
                            x = x0;
                            y++;
                            break;
                        }
                    }
                }
            }
        }
        continue; //���ҵ���Ӧ�����ֿ������˳�����ֹ��������ظ�ȡģ����Ӱ��
    }
}

/******************************************************************************
      ����˵������ʾ����48x48����
      ������ݣ�x,y��ʾ����
                *s Ҫ��ʾ�ĺ���
                fc �ֵ���ɫ
                bc �ֵı���ɫ
                sizey �ֺ�
                mode:  0�ǵ���ģʽ  1����ģʽ
      ����ֵ��  ��
******************************************************************************/
void LCD_ShowChinese48x48(uint16_t x, uint16_t y, uint8_t *s, uint16_t fc, uint16_t bc, uint8_t sizey, uint8_t mode)
{
    uint16_t i, j, m = 0;
    uint16_t k;
    uint16_t HZnum;       //������Ŀ
    uint16_t TypefaceNum; //һ���ַ���ռ�ֽڴ�С
    uint16_t x0 = x;
    TypefaceNum = (sizey / 8 + ((sizey % 8) ? 1 : 0)) * sizey;
    HZnum = sizeof(tfont48) / sizeof(typFNT_GB48); //ͳ�ƺ�����Ŀ
    for (k = 0; k < HZnum; k++)
    {
        if ((tfont48[k].Index[0] == *(s)) && (tfont48[k].Index[1] == *(s + 1)))
        {
            LCD_Address_Set(x, y, x + sizey - 1, y + sizey - 1);
            for (i = 0; i < TypefaceNum; i++)
            {
                for (j = 0; j < 8; j++)
                {
                    if (!mode) //�ǵ��ӷ�ʽ
                    {
                        if (tfont48[k].Msk[i] & (0x01 << j))
                            LCD_Write_Data(fc);
                        else
                            LCD_Write_Data(bc);
                        m++;
                        if (m % sizey == 0)
                        {
                            m = 0;
                            break;
                        }
                    }
                    else //���ӷ�ʽ
                    {
                        if (tfont48[k].Msk[i] & (0x01 << j))
                            LCD_Draw_ColorPoint(x, y, fc); //��һ����
                        x++;
                        if ((x - x0) == sizey)
                        {
                            x = x0;
                            y++;
                            break;
                        }
                    }
                }
            }
        }
        continue; //���ҵ���Ӧ�����ֿ������˳�����ֹ��������ظ�ȡģ����Ӱ��
    }
}
