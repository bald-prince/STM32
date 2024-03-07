/*
 * Copyright (c) 2006-2020, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2020-09-02     RT-Thread    first version
 */

#include <rtthread.h>
#include <rtdevice.h>
#include "drv_common.h"

#include "drv_pwm.h"
#define DBG_TAG "main"
#define DBG_LVL DBG_LOG


#define LED_PIN GET_PIN(I, 8)





int main(void)
{
    rt_uint32_t count = 1;

    rt_pin_mode(LED_PIN, PIN_MODE_OUTPUT);


                                  //²ÉÑùÆµÂÊ
    UserPWM_Init();

    while(count++)
    {

        rt_pin_write(LED_PIN, count%2);
        rt_thread_mdelay(200);
    }
    return RT_EOK;
}

#include "stm32h7xx.h"
static int vtor_config(void)
{
    /* Vector Table Relocation in Internal QSPI_FLASH */
    SCB->VTOR = QSPI_BASE;
    return 0;
}
INIT_BOARD_EXPORT(vtor_config);


