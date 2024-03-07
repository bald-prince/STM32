/*
 * Copyright (c) 2006-2020, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2020-11-21     Administrator       the first version
 */


#include <rthw.h>
#include <rtthread.h>
#include <rtdevice.h>
#include <U8g2lib.h>
#include <stdio.h>

#include "drv_common.h"

#include <drv_soft_i2c.h>

extern "C"
{
 //#include <sht3x.h>
}
extern "C"
{

}


#define OLED_I2C_PIN_SCL                  GET_PIN(H, 11) // 22  // PH11
#define OLED_I2C_PIN_SDA                  GET_PIN(H, 12) // 23  // PH12

static U8G2_SSD1306_128X64_NONAME_F_SW_I2C u8g2(U8G2_R0,\
                                         /* clock=*/ OLED_I2C_PIN_SCL,\
                                         /* data=*/ OLED_I2C_PIN_SDA,\
                                         /* reset=*/ U8X8_PIN_NONE);
void oled_display()
{
    u8g2.begin();
    u8g2.clearBuffer();

    u8g2.setFont(u8g2_font_logisoso32_tf);
    u8g2.setCursor(48+3, 42);
    u8g2.print("Hi~");     // requires enableUTF8Print()


    u8g2.setFont(u8g2_font_6x13_tr);            // choose a suitable font
    u8g2.drawStr(30, 60, "Embeded FlyGe");   // write something to the internal memory
    u8g2.sendBuffer();

    rt_thread_mdelay(2000);
    u8g2.clearBuffer();


    char mstr[3];
    char hstr[3];

    time_t now;
    struct tm *p;
    int min = 0, hour = 0,display_page=0;

    while(1)
    {
        switch(display_page)
        {
            case 0:
                u8g2.firstPage();
                do{
                      u8g2.setFont(u8g2_font_10x20_tr);            // choose a suitable font
                      u8g2.drawStr(15, 40, "Hello Guys");   // write something to the internal memory
                      //u8g2.drawStr(30, 18, "Embeded FlyBrother");   // write something to the internal memory
                      u8g2.sendBuffer();                          // transfer internal memory to the display
                      rt_thread_mdelay(1000);
                      u8g2.clearBuffer();
                      u8g2.drawStr(15, 40, "Welcome to");   // write something to the internal memory
                      //u8g2.drawStr(30, 18, "Embeded FlyBrother");   // write something to the internal memory
                      u8g2.sendBuffer();
                      rt_thread_mdelay(1000);
                      u8g2.clearBuffer();

                      u8g2.drawStr(0, 30, "Join Embeded");   // write something to the internal memory
                      //u8g2.drawStr(30, 18, "Embeded FlyBrother");   // write something to the internal memory
                      u8g2.sendBuffer();
                      u8g2.drawStr(0, 50, "   Party!!!");
                      u8g2.sendBuffer();
                      rt_thread_mdelay(1000);
                      u8g2.clearBuffer();

                } while ( u8g2.nextPage() );
                display_page = 1;
                break;
            case 1:
                  now = time(RT_NULL);
                  p=gmtime((const time_t*) &now);
                  hour = p->tm_hour;
                  min = p->tm_min;
                  sprintf(mstr, "%02d", min);
                  sprintf(hstr, "%02d", hour);

                  u8g2.setFont(u8g2_font_logisoso42_tn);
                  u8g2.drawStr(0,63,hstr);
                  u8g2.drawStr(50,63,":");
                  u8g2.drawStr(67,63,mstr);
                  u8g2.sendBuffer();
                  rt_thread_mdelay(5000);
                  display_page = 0;
                  break;
        }
    }
}
MSH_CMD_EXPORT(oled_display, oled start);

