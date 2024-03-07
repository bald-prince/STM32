/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2021-08-22     Administrator       the first version
 */

#include <rtthread.h>
#include <rtdevice.h>
#include "drv_soft_i2c.h"
#include <board.h>

#include <string.h>
#include <stdio.h>

#include "sensor_inven_mpu6xxx.h"
#include "mpu6xxx.h"

#include "inv_mpu_dmp_motion_driver.h"
#include "mpu6xxx.h"
#include <mpu6050_drv.h>

#define THREAD_STACK_SIZE   1024
#define THREAD_PRIORITY     20
#define THREAD_TIMESLICE    10

struct mpu6xxx_device *i2c_bus;                     //6050控制句柄
struct mpu6xxx_3axes accel, gyro;

float pitch, roll, yaw;           //欧拉角

char str[32];

static void thread1_entry(void* parameter)
{
   i2c_bus = (struct mpu6xxx_device *) mpu6xxx_init(MPU6050_I2C_BUS_NAME, MPU6050_ADDR); //初始化MPU6050，测量单位为角速度，加速度    while(count++)
    while (mpu_dmp_init())
    {
        rt_thread_mdelay(100);
        rt_kprintf("\r\nMPU6050 DMP init Error\r\n");
    }
    rt_kprintf("\r\nMPU6050 DMP init OK\r\n");
    while (1)
    {
        MPU6050_DataGet();
    }
}

void MPU6050_DataGet(void)
{
    if (mpu_dmp_get_data(&pitch, &roll, &yaw) == 0)
    {
        mpu6xxx_get_accel_raw(i2c_bus,&accel);
        mpu6xxx_get_gyro_raw(i2c_bus,&gyro);

/*
        sprintf(str,"pitch=%d\r\n",(int)pitch);
        rt_kprintf(str);

        sprintf(str,"roll=%d\r\n",(int)roll);
        rt_kprintf(str);

        sprintf(str,"yaw=%d\r\n",(int)yaw);
        rt_kprintf(str);


        mpu6xxx_get_accel_raw(i2c_bus, &gyro);
        sprintf(str,"gyro.x=%d\r\n",gyro.x);
        rt_kprintf(str);

        sprintf(str,"gyro.y=%d\r\n",gyro.y);
        rt_kprintf(str);

        sprintf(str,"gyro.z=%d\r\n",gyro.z);
        rt_kprintf(str);


        mpu6xxx_get_gyro_raw(i2c_bus,&accel);

        sprintf(str,"accel.x=%d\r\n",accel.x);
        rt_kprintf(str);
        sprintf(str,"accel.y=%d\r\n",accel.y);
        rt_kprintf(str);
        sprintf(str,"accel.z=%d\r\n",accel.z);
        rt_kprintf(str);
*/

    }



}

int mpu6050_sample(void)
{
    static rt_thread_t tid1 = RT_NULL;

    /* 创建线程  */
    tid1 = rt_thread_create("thread1", thread1_entry,
    RT_NULL,
    THREAD_STACK_SIZE,
    THREAD_PRIORITY, THREAD_TIMESLICE);
    /* 如果获得线程控制块，启动这个线程 */
    if (tid1 != RT_NULL)
        rt_thread_startup(tid1);

    /* 创建线程  */

    return 0;
}
/* 导出到 msh 命令列表中 */
//MSH_CMD_EXPORT(mpu6050_sample, mpu6050 sample);
INIT_COMPONENT_EXPORT(mpu6050_sample);

