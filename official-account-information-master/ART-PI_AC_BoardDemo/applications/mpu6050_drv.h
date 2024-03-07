/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2021-12-04     wyffw       the first version
 */
#ifndef APPLICATIONS_MPU6050_DRV_H_
#define APPLICATIONS_MPU6050_DRV_H_

#define MPU6050_I2C_BUS_NAME          "i2c3"        //i2c总线设备名
#define MPU6050_ADDR                  0x68           //MPU6050地址,与AD0引脚接法有关系，AD0接GND为0X68

void MPU6050_DataGet(void);


#endif /* APPLICATIONS_MPU6050_DRV_H_ */
