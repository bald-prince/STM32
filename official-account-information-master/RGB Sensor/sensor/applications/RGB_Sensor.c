/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2021-07-28     Administrator       the first version
 */
#include "RGB_Sensor.h"
#include <rtthread.h>
#include <rtdevice.h>
#include <math.h>
#include "stdbool.h"
#include "drv_common.h"

#define sensor_ledpin GET_PIN(A,8)

COLOR_RGBC rgb;
COLOR_HSL  hsl;

static struct rt_i2c_bus_device *i2c_bus = RT_NULL;     /* I2C总线设备句柄 */
static rt_bool_t initialized = RT_FALSE;                /* 传感器初始化状态 */

/* 写传感器寄存器 */
static rt_err_t write_reg(struct rt_i2c_bus_device *bus, rt_uint8_t reg, rt_uint32_t *data)
{
    rt_uint8_t buf[3];
    struct rt_i2c_msg msgs;
    rt_uint32_t buf_size = 1;

    buf[0] = TCS34725_COMMAND_BIT | reg;                   //cmd
    if (data != RT_NULL)
    {
        buf[1] = data[0];
        buf[2] = data[1];
        buf_size = 3;
    }

    msgs.addr = TCS34725_ADDRESS;
    msgs.flags = RT_I2C_WR;
    msgs.buf = buf;
    msgs.len = buf_size;

    /* 调用I2C设备接口传输数据 */
    if (rt_i2c_transfer(bus, &msgs, 1) == 1)
    {
        return RT_EOK;
    }
    else
    {
        return -RT_ERROR;
    }
}

/* 读传感器寄存器数据 */
static rt_err_t read_regs(struct rt_i2c_bus_device *bus,rt_uint8_t reg,rt_uint8_t len, rt_uint8_t *buf)
{
    struct rt_i2c_msg msgs;
    write_reg(i2c_bus,reg, RT_NULL);

    msgs.addr = TCS34725_ADDRESS;
    msgs.flags = RT_I2C_RD;
    msgs.buf = buf;
    msgs.len = len;

    /* 调用I2C设备接口传输数据 */
    if (rt_i2c_transfer(bus, &msgs, 1) == 1)
    {
        return RT_EOK;
    }
    else
    {
        return -RT_ERROR;
    }
}

/*========================================================================*/
/*                          PRIVATE FUNCTIONS                             */
/*========================================================================*/

/**************************************************************************/
/*!
    @brief  Implements missing powf function
*/
/**************************************************************************/
float powf(const float x, const float y)
{
  return (float)(pow((double)x, (double)y));
}


rt_uint16_t convertRGB24toRGB565(rt_uint8_t r,rt_uint8_t g,rt_uint8_t b)
{
  return ((r/8)<<11)|((g/4)<<5)|(b/8);
}

/**************************************************************************/
/*!
    Enables the device
*/
/**************************************************************************/
void RT_enable(void)
{
  write_reg(i2c_bus,TCS34725_ENABLE,TCS34725_ENABLE_PON);
  //stm32_udelay(3);
  write_reg(i2c_bus,TCS34725_ENABLE,(TCS34725_ENABLE_PON | TCS34725_ENABLE_AEN));
  rt_thread_delay(5);

}

/**************************************************************************/
/*!
    Disables the device (putting it in lower power sleep mode)
*/
/**************************************************************************/
void RT_disable(void)
{
  /* Turn the device off to save power */
  rt_uint8_t reg = 0;

  read_regs(i2c_bus,TCS34725_ENABLE,1,&reg);
  write_reg(i2c_bus,TCS34725_ENABLE, (reg & ~(TCS34725_ENABLE_PON | TCS34725_ENABLE_AEN)));
}

/**************************************************************************/
/*!
    Initializes I2C and configures the sensor (call this function before
    doing anything else)
*/
/**************************************************************************/
rt_uint8_t begin(void)
{
   rt_uint8_t sensor_id = 0;
  /* Make sure we're actually connected */
  read_regs(i2c_bus,TCS34725_ID,1,&sensor_id);

  if ((sensor_id != 0x4d) && (sensor_id != 0x10))
  {
     rt_kprintf("find sensor failed!\n");
    return 0;
  }
  rt_kprintf("sensor ID is:%0x!\n",sensor_id);
  rt_kprintf("find sensor success!\n");


  /* Set default integration time and gain */
  RT_setIntegrationTime(TCS34725_INTEGRATIONTIME_2_4MS);
  RT_setGain(TCS34725_GAIN_60X);
  rt_thread_delay(5);
  /* Note: by default, the device is in power down mode on bootup */
  RT_enable();

  return 1;
}


/*******************************************************************************
 * @brief TCS34725ÉèÖÃ»ý·ÖÊ±¼ä
 *
 * @return None
*******************************************************************************/
void RT_setIntegrationTime(rt_uint8_t time)
{
  /* Update the timing register */
  write_reg(i2c_bus,TCS34725_ATIME, &time);
  /* Update value placeholders */
}

/**************************************************************************/
/*!
    Adjusts the gain on the TCS34725 (adjusts the sensitivity to light)
*/
/**************************************************************************/
void RT_setGain(rt_uint8_t gain)
{
  /* Update the timing register */
  write_reg(i2c_bus,TCS34725_CONTROL, &gain);
  /* Update value placeholders */
}


/**************************************************************************/
/*!
    @brief  Converts the raw R/G/B values to color temperature in degrees
            Kelvin
*/
/**************************************************************************/
uint16_t RT_calculateColorTemperature(uint16_t r, uint16_t g, uint16_t b)
{
  float X, Y, Z;      /* RGB to XYZ correlation      */
  float xc, yc;       /* Chromaticity co-ordinates   */
  float n;            /* McCamy's formula            */
  float cct;

  /* 1. Map RGB values to their XYZ counterparts.    */
  /* Based on 6500K fluorescent, 3000K fluorescent   */
  /* and 60W incandescent values for a wide range.   */
  /* Note: Y = Illuminance or lux                    */
  X = (-0.14282F * r) + (1.54924F * g) + (-0.95641F * b);
  Y = (-0.32466F * r) + (1.57837F * g) + (-0.73191F * b);
  Z = (-0.68202F * r) + (0.77073F * g) + ( 0.56332F * b);

  /* 2. Calculate the chromaticity co-ordinates      */
  xc = (X) / (X + Y + Z);
  yc = (Y) / (X + Y + Z);

  /* 3. Use McCamy's formula to determine the CCT    */
  n = (xc - 0.3320F) / (0.1858F - yc);

  /* Calculate the final CCT */
  cct = (449.0F * powf(n, 3)) + (3525.0F * powf(n, 2)) + (6823.3F * n) + 5520.33F;

  /* Return the results in degrees Kelvin */
  return (uint16_t)cct;
}

/**************************************************************************/
/*!
    @brief  Converts the raw R/G/B values to lux
*/
/**************************************************************************/
uint16_t RT_calculateLux(uint16_t r, uint16_t g, uint16_t b)
{
  float illuminance;

  /* This only uses RGB ... how can we integrate clear or calculate lux */
  /* based exclusively on clear since this might be more reliable?      */
  illuminance = (-0.32466F * r) + (1.57837F * g) + (-0.73191F * b);

  return (uint16_t)illuminance;
}


void RT_setInterrupt(rt_bool_t i) {
  uint8_t r = 0;

  read_regs(i2c_bus,TCS34725_ENABLE,1,&r);
  if (i) {
    r |= TCS34725_ENABLE_AIEN;
  } else {
    r &= ~TCS34725_ENABLE_AIEN;
  }
  write_reg(i2c_bus,TCS34725_ENABLE, r);
}

void RT_clearInterrupt(void) {
  write_reg(i2c_bus,0x66,RT_NULL);
}

void RT_setIntLimits(uint16_t low, uint16_t high) {
   write_reg(i2c_bus,0x04,(low & 0xFF));
   write_reg(i2c_bus,0x05, (low >> 8));
   write_reg(i2c_bus,0x06,(high & 0xFF));
   write_reg(i2c_bus,0x07, (high >> 8));
}

/*******************************************************************************
 * @brief TCS34725获取各个通道数据
 *
 * @return 1 - 转换完成，数据可用
 *         0 - 转换未完成，数据不可用
*******************************************************************************/
rt_uint8_t RT_getRawData (COLOR_RGBC *rgbc)
{
    rt_uint8_t data[2] = {0};
    rt_uint8_t status = TCS34725_STATUS_AVALID;

    read_regs(i2c_bus,TCS34725_STATUS,1,&status);

    if(status & TCS34725_STATUS_AVALID)
    {
        read_regs(i2c_bus,TCS34725_CDATAL,2,data);
        rgbc->c = (data[1]<<8)|data[0];

        read_regs(i2c_bus,TCS34725_RDATAL,2,data);
        rgbc->r = (data[1]<<8)|data[0];

        read_regs(i2c_bus,TCS34725_GDATAL,2,data);
        rgbc->g = (data[1]<<8)|data[0];

        read_regs(i2c_bus,TCS34725_BDATAL,2,data);
        rgbc->b = (data[1]<<8)|data[0];

        return 1;
    }
    return 0;
}
/******************************************************************************/
//RGB转HSL
void RT_RGBtoHSL(COLOR_RGBC *Rgb, COLOR_HSL *Hsl)
{
    rt_uint8_t maxVal,minVal,difVal;
    rt_uint8_t r = Rgb->r*100/Rgb->c;   //[0-100]
    rt_uint8_t g = Rgb->g*100/Rgb->c;
    rt_uint8_t b = Rgb->b*100/Rgb->c;

    maxVal = max3v(r,g,b);
    minVal = min3v(r,g,b);
    difVal = maxVal-minVal;

    //计算亮度
    Hsl->l = (maxVal+minVal)/2;   //[0-100]

    if(maxVal == minVal)//若r=g=b,灰度
    {
        Hsl->h = 0;
        Hsl->s = 0;
    }
    else
    {
        //计算色调
        if(maxVal==r)
        {
            if(g>=b)
                Hsl->h = 60*(g-b)/difVal;
            else
                Hsl->h = 60*(g-b)/difVal+360;
        }
        else
            {
                if(maxVal==g)Hsl->h = 60*(b-r)/difVal+120;
                else
                    if(maxVal==b)Hsl->h = 60*(r-g)/difVal+240;
            }

        //计算饱和度
        if(Hsl->l<=50)Hsl->s=difVal*100/(maxVal+minVal);  //[0-100]
        else
            Hsl->s=difVal*100/(200-(maxVal+minVal));
    }
}

static void rgbSensor_init(const char *name)
{
    /* 查找I2C总线设备，获取I2C总线设备句柄 */
    i2c_bus = (struct rt_i2c_bus_device *)rt_device_find(name);

    if (i2c_bus == RT_NULL)
    {
        rt_kprintf("can't find %s device failed!\n", name);
    }
    else
    {
        rt_kprintf("find %s device success!\n", name);
        rt_pin_mode(sensor_ledpin, PIN_MODE_OUTPUT);
        begin();
    }
}

static void i2c_rgbSensor_sample(int argc, char *argv[])
{
    rt_uint8_t led_status = 1;
    rt_uint16_t timecount=0;
    char name[RT_NAME_MAX];

    if (argc == 2)
    {
        rt_strncpy(name, argv[1], RT_NAME_MAX);
    }
    else
    {
        rt_strncpy(name, "i2c3", RT_NAME_MAX);
    }
    rgbSensor_init(name);

    while(1)
    {
        timecount++;
        if(timecount%200==0)
        {
            rt_pin_write(sensor_ledpin, led_status);
            //led_status= ~led_status;
        }

        if(timecount%1000==0)
        {
            /* 传感器初始化 */
            RT_getRawData(&rgb);  //读两次，实际测试时发现读到的颜色总是上一次的颜色
            RT_RGBtoHSL(&rgb,&hsl);
            rt_kprintf("R=%d G=%d B=%d C=%d\r\n",rgb.r,rgb.g,rgb.b,rgb.c);
            rt_kprintf("H=%d S=%d L=%d\r\n",hsl.h,hsl.s,hsl.l);
       /*   RGB565 =  convertRGB24toRGB565(R,G,B);
            rt_kprintf("RGB565 = %0x\n\n\n",RGB565);*/
            timecount = 0;
        }
        rt_thread_delay(1);

    }

}
/* 导出到 msh 命令列表中 */
//MSH_CMD_EXPORT(i2c_rgbSensor_sample, i2c rgbSensor sample);
INIT_COMPONENT_EXPORT(i2c_rgbSensor_sample);

