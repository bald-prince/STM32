/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2021-08-14     Administrator       the first version
 */

#include <rtthread.h>
#include <rtdevice.h>
#include "drv_spi.h"
#include <board.h>

#include "ld3320_drv.h"
#include "mp3.h"


#define THREAD_STACK_SIZE   1024
#define THREAD_PRIORITY     20
#define THREAD_TIMESLICE    10

extern rt_uint8_t nAsrStatus;
extern rt_uint32_t nMp3Size;
extern rt_uint8_t bMp3Play;
extern rt_uint8_t nLD_Mode;

/********************************************************************************
function:
                LD3320 test demo main function
********************************************************************************/
void rt_LD3320_test(void)
{
    rt_uint8_t nAsrRes = 0;
    while (1)
    {
        if (bMp3Play)
        {
            rt_kprintf("*********playing*********\r\n");
            continue;
        }
        //      printf("nAsrStatus is %x, nLD_Mode is %x \r\n", nAsrStatus, nLD_Mode);
        switch (nAsrStatus)
        {
        case LD_ASR_RUNING:
        case LD_ASR_ERROR:
            break;
        case LD_ASR_NONE:
            nAsrStatus = LD_ASR_RUNING;
            if (rt_LD_ASR() == 0) //Start the ASR process once
                nAsrStatus = LD_ASR_ERROR;
            break;
        case LD_ASR_FOUNDOK:
            nAsrRes = rt_LD_GetResult(); //once ASR process end, get the result
            switch (nAsrRes)
            { //show the commond
            case CODE_RUN:
                rt_kprintf("waterfall led\r\n");
                break;
            case CODE_KEY:
                rt_kprintf("reversal led\r\n");
                break;
            case CODE_FLASH:
                rt_kprintf("flash led\r\n");
                break;
            case CODE_PLAY:
                rt_kprintf("play mp3\r\n");
                break;
            default:
                break;
            }
            nAsrStatus = LD_ASR_NONE;
            break;
        case LD_ASR_FOUNDZERO:
        default:
            nAsrStatus = LD_ASR_NONE;
            break;
        }
        rt_Board_text(nAsrRes); //do the commond
        nAsrRes = 0;
    }
}
/********************************************************************************
function:
                LED waterfall
********************************************************************************/
void rt_LED_run(void)
{
    rt_kprintf("你好，欢迎关注嵌入式实验基地，遇见的都是最帅的人\r\n");
}

/********************************************************************************
function:
                LED flash
********************************************************************************/
void rt_LED_flash(void)
{
    rt_kprintf("人生得意须尽欢，\r\n莫使金樽空对月。\r\n天生我材必有用，\r\n千金散尽还复来。\r\n");
}
/********************************************************************************
function:
                LED reversal
********************************************************************************/
void rt_LED_key(void)
{
    rt_kprintf("我来自伟大的中华人民共和国，我爱中国\r\n");
}
/********************************************************************************
function:
                Play_mp3
********************************************************************************/
void rt_Play_demo()
{
/*    bMp3Play = 1;
    nMp3Size = size_sound_1 - 1;
    rt_LD_Init_MP3();
    rt_LD_Adjust_Volume(1);
    rt_LD_play(sound_1);*/
    rt_kprintf("我想去看看,你想和我一起吗\r\n");
}
/********************************************************************************
function:
                Do the corresponding operation on the board
********************************************************************************/
void rt_Board_text(rt_uint8_t Code_Val)
{
    switch (Code_Val)
    {
    case CODE_RUN: //Commond "liu shui deng"
        rt_LED_run();
        break;
    case CODE_KEY: //Commond "an jian"
        rt_LED_key();
        break;
    case CODE_FLASH: //Commond "shan shuo"
        rt_LED_flash();
        break;
    case CODE_PLAY: //Commond "bo fang"
        rt_Play_demo();
        break;
    default:
        break;
    }
}

extern volatile rt_uint8_t ld3320_flag;
/* 线程入口 */
static void thread1_entry(void* parameter)
{

    int i;
    while(1)
    {
/*      rt_kprintf("success!!! thread1_entry OK\r\n");
        rt_thread_delay(500);*/
        if(ld3320_flag)
        {
            ld3320_flag=0;
            rt_ProcessInt();
        }
        else {
            ld3320_flag=0;
            i++;
            if(i%500==0){

                rt_kprintf("\r\n\rvoice checking,please speak...\r\n");
                i=0;
            }
            rt_thread_delay(1);
        }
    }
}

/* 线程入口 */
static void thread2_entry(void* parameter)
{
   rt_uint8_t nAsrRes = 0;

  while (1)
  {
      if (bMp3Play)
      {
          rt_kprintf("*********playing*********\r\n");
          continue;
      }
      switch (nAsrStatus)
      {
      case LD_ASR_RUNING:
      case LD_ASR_ERROR:
          break;
      case LD_ASR_NONE:
          nAsrStatus = LD_ASR_RUNING;
          if (rt_LD_ASR() == 0) //Start the ASR process once
              nAsrStatus = LD_ASR_ERROR;
          break;
      case LD_ASR_FOUNDOK:
          nAsrRes = rt_LD_GetResult(); //once ASR process end, get the result
          switch (nAsrRes)
          { //show the commond
          case CODE_RUN:
              rt_kprintf("voice control system is runing.....\r\n");
              break;
          case CODE_KEY:
              rt_kprintf("voice control system is runing.....\r\n");
              break;
          case CODE_FLASH:
              rt_kprintf("voice control system is runing.....\r\n");
              break;
          case CODE_PLAY:
              rt_kprintf("voice control system is runing.....\r\n");
              break;
          default:
              break;
          }
          nAsrStatus = LD_ASR_NONE;
          break;
      case LD_ASR_FOUNDZERO:
      default:
          nAsrStatus = LD_ASR_NONE;
          break;
      }
      rt_Board_text(nAsrRes); //do the commond
      nAsrRes = 0;

  }
/*      rt_kprintf("success!!! thread2_entry OK\r\n");
        rt_thread_delay(500);*/
}

int ld3320_sample(void)
{

    static rt_thread_t tid1 = RT_NULL,tid2 = RT_NULL;

    rt_ld3320_irq_pin_init();
    /* 创建线程  */
    tid1=rt_thread_create(
                   "thread1",
                   thread1_entry,
                   RT_NULL,
                   THREAD_STACK_SIZE,
                   THREAD_PRIORITY, THREAD_TIMESLICE);
    /* 如果获得线程控制块，启动这个线程 */
    if (tid1 != RT_NULL)
        rt_thread_startup(tid1);

    /* 创建线程  */
    tid2=rt_thread_create(
                   "thread2",
                   thread2_entry,
                   RT_NULL,
                   THREAD_STACK_SIZE,
                   THREAD_PRIORITY, THREAD_TIMESLICE);
    /* 如果获得线程控制块，启动这个线程 */
    if (tid2 != RT_NULL)
        rt_thread_startup(tid2);

    return 0;
}
/* 导出到 msh 命令列表中 */
//MSH_CMD_EXPORT(ld3320_sample, ld3320 sample);
INIT_COMPONENT_EXPORT(ld3320_sample);



