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

#define LD3320_SPI_DEVICE_NAME "spi40"

rt_uint32_t nMp3Size = 0;           // mp3 size
rt_uint32_t nMp3Pos = 0;            // mp3 current pos
rt_uint8_t *nMp3name;               // mp3 playing status
rt_uint8_t nAsrStatus = 0;          // Record the status of the ASR
rt_uint8_t nLD_Mode = LD_MODE_IDLE; // Record the status of LD3320(ASR or Play Sound)
rt_uint8_t bMp3Play = 0;            // Record the status of audio player
rt_uint8_t ucRegVal;                // Interrupt request number
rt_uint8_t ucHighInt;               // Intterrupt enable status
rt_uint8_t ucLowInt;                // Intterrupt enable status
rt_uint8_t ucStatus;                // FIFO status
rt_uint8_t ucSPVol = 15;            // Speaker volume, MAX=31 MIN=0
volatile rt_uint8_t ld3320_flag = 0;



static rt_uint8_t rt_LD_AsrAddKey(void);
static void rt_LD_Init_Common(void);
static void rt_LD_ReloadMp3Data(void);
static rt_uint8_t rt_LD_Check_ASRBusyFlag(void);
static void rt_LD_WriteReg(rt_uint8_t data1, rt_uint8_t data2);
static rt_uint8_t rt_LD_ReadReg(rt_uint8_t reg_add);
static void rt_LD_Init_ASR(void);
static rt_uint8_t rt_LD_AsrRun(void);

struct rt_spi_device *spi_dev_ld3320; /* SPI 锟借备锟斤拷锟�? */

void rt_ld3320_isr(void *args)
{
    ld3320_flag=1;
  //  rt_kprintf("---------------ASR---------------\r\n");
}
void rt_ProcessInt()
{
    rt_uint8_t nAsrResCount = 0;
    ucRegVal = rt_LD_ReadReg(0x2B);
    ucHighInt = rt_LD_ReadReg(0x29); // interrupt enable flag
    ucLowInt = rt_LD_ReadReg(0x02); // interrupt enable flag
    rt_LD_WriteReg(0x29, 0);// interrupt disenable
    rt_LD_WriteReg(0x02, 0);// interrupt disenable

    if(nLD_Mode == LD_MODE_ASR_RUN) {
        //rt_kprintf("---------------ASR---------------\r\n");
        //The interruption caused by speech recognition
        //(There is sound input, and there is interruption whether the recognition is successful or failed)
        if((ucRegVal & 0x10) && rt_LD_ReadReg(0xb2)==0x21 && rt_LD_ReadReg(0xbf)==0x35) {
            nAsrResCount = rt_LD_ReadReg(0xba);
            if(nAsrResCount>0 && nAsrResCount<=4) {
                rt_kprintf("ASR SUCCESSFUL \r\n");
                nAsrStatus = LD_ASR_FOUNDOK;
            }
            else {
                rt_kprintf("ASR UNSUCCESSFUL \r\n");
                nAsrStatus = LD_ASR_FOUNDZERO;
            }
        }
        else {
            //rt_kprintf("No ASR \r\n");
            nAsrStatus = LD_ASR_FOUNDZERO;
        }
        rt_LD_WriteReg(0x2b, 0);
        rt_LD_WriteReg(0x1c, 0);
        return;
    }
    rt_kprintf("--------------PLAY MP3--------------\r\n");
    // Play MP3 to produce 3 kinkd of intterupt
    // A. play over
    // B. data send over
    // C. Data will be used up and sent
    if(rt_LD_ReadReg(0xBA) & CAUSE_MP3_SONG_END) {
        // A. play over
        rt_LD_WriteReg(0x2B, 0);
        rt_LD_WriteReg(0xBA, 0);
        rt_LD_WriteReg(0xBC, 0);
        rt_LD_WriteReg(0x08, 1);
        rt_LD_WriteReg(0x08, 0);
        rt_LD_WriteReg(0x33, 0);
        rt_kprintf("play over \r\n");
        bMp3Play = 0;                   // play status
        return;
    }
    if(nMp3Pos >= nMp3Size) {
        // B. data send over
        rt_LD_WriteReg(0xBC, 0x01);//data voer
        rt_LD_WriteReg(0x29, 0x10);
        return;
    }
    // C. Data will be used up and sent
    rt_LD_ReloadMp3Data();
    rt_LD_WriteReg(0x29, ucHighInt);
    rt_LD_WriteReg(0x02, ucLowInt);
}

/********************************************************************************
function:
                Run ASR
********************************************************************************/
rt_uint8_t rt_LD_ASR(void)
{
    rt_uint8_t i = 0;
    rt_uint8_t asrflag = 0;
    for (i = 0; i < 5; i++)
    {                     //run ASR try 5 times
        rt_LD_Init_ASR(); //init ASR
        rt_thread_delay(100);
        if (rt_LD_AsrAddKey() == 0)
        { //Add fixed to LD3320
            rt_kprintf("ERROR!!! LD_AsrAddKey\r\n");
            rt_LD_init(); //ERROR,Reset LD3320
            rt_thread_delay(50);
            continue;
        }
        rt_thread_delay(10);
        if (rt_LD_AsrRun() == 0)
        { //start ASR
            rt_kprintf("ERROR!!! LD_AsrRun\r\n");
            rt_LD_init(); //ERROR,Reset LD3320
            rt_thread_delay(50);
            continue;
        }
        asrflag = 1;
        break;
    }
    //rt_kprintf("RunASR\r\n");
    return asrflag;
}

/********************************************************************************
function:
                Start play
********************************************************************************/
void rt_LD_play(rt_uint8_t *mp3name)
{
    nMp3Pos = 0;
    bMp3Play = 1;
    nMp3name = mp3name;
    if (nMp3Pos >= nMp3Size)
        return;

    rt_LD_ReloadMp3Data();

    rt_LD_WriteReg(0xBA, 0x00);
    rt_LD_WriteReg(0x17, 0x48); //activate DSP
    rt_LD_WriteReg(0x33, 0x01); //play mp3
    rt_LD_WriteReg(0x29, 0x04); //FIFO interrupt allowed
    rt_LD_WriteReg(0x02, 0x01); //FIFO_DATA interrupt allowed
    rt_LD_WriteReg(0x85, 0x5A);
}

/********************************************************************************
function:
                Adjust headset volume
note:
                MAX=15 MIN=0
********************************************************************************/
void rt_LD_Adjust_Volume(rt_uint8_t val)
{
    val = ((15 - val) & 0x0f) << 2;
    rt_LD_WriteReg(0x8e, val | 0xc1); //volume
    rt_LD_WriteReg(0x87, 0x78);       //accept adjust
}

/********************************************************************************
function:
                Get LD3320 return value
********************************************************************************/
rt_uint8_t rt_LD_GetResult(void)
{
    return rt_LD_ReadReg(0xc5);
}

/********************************************************************************
function:
                LD3320 hardware init
********************************************************************************/
void rt_LD_init(void)
{
    LD3320_RST_Func(1);
    rt_thread_delay(100);
    LD3320_RST_Func(0);
    rt_thread_delay(100);
    LD3320_RST_Func(1);

    rt_thread_delay(100);
    LD3320_CS_Func(0);
    rt_thread_delay(100);
    LD3320_CS_Func(1);
    rt_thread_delay(100);

    //rt_ld3320_irq_pin_init();

    //  rt_LD_ReadReg(06);
    //  rt_LD_WriteReg(0x35, 0x33);
    //  rt_LD_WriteReg(0x1b, 0x55);
    //  rt_LD_WriteReg(0xb3, 0xaa);
    //  printf(" %x \n", rt_LD_ReadReg(0x35));
    //  printf(" %x \n", rt_LD_ReadReg(0x1b));
    //  printf(" %x \n", rt_LD_ReadReg(0xb3));
    //
    //  printf(" %x \n", rt_LD_ReadReg(0x06));
    //  printf(" %x \n", rt_LD_ReadReg(0x06));
    //  printf(" %x \n", rt_LD_ReadReg(0x35));
    //  printf(" %x \n", rt_LD_ReadReg(0xb3));
}

/********************************************************************************
function:
                Add ASR Keyword
********************************************************************************/
static rt_uint8_t rt_LD_AsrAddKey(void)
{
    rt_uint8_t k, flag;
    rt_uint8_t nAsrAddLength;
#define DATE_A 5
#define DATE_B 20

    rt_uint8_t sRecog[DATE_A][DATE_B] = {
        //add commond,use pinying
        "ni hao",
        "ni lai zi na li",
        "bei yi shou shi",
        "shi jie zhe me da"

    };
    rt_uint8_t pCode[DATE_A] = {
        //add commond code to do the commond
        CODE_RUN,
        CODE_KEY,
        CODE_FLASH,
        CODE_PLAY,

    };
    flag = 1;
    for (k = 0; k < DATE_A; k++)
    { //write data to LD3320
        if (rt_LD_Check_ASRBusyFlag() == 0)
        {
            flag = 0;
            break;
        }
        rt_LD_WriteReg(0xc1, pCode[k]);
        rt_LD_WriteReg(0xc3, 0);
        rt_LD_WriteReg(0x08, 0x04);
        rt_thread_delay(1);
        rt_LD_WriteReg(0x08, 0x00);
        rt_thread_delay(1);
        for (nAsrAddLength = 0; nAsrAddLength < DATE_B; nAsrAddLength++)
        {
            if (sRecog[k][nAsrAddLength] == 0)
                break;
            rt_LD_WriteReg(0x5, sRecog[k][nAsrAddLength]);
        }
        rt_LD_WriteReg(0xb9, nAsrAddLength);
        rt_LD_WriteReg(0xb2, 0xff);
        rt_LD_WriteReg(0x37, 0x04);
    }
    return flag;
}

/********************************************************************************
function:
                Reload mp3 data
********************************************************************************/
static void rt_LD_ReloadMp3Data()
{
    rt_uint8_t val;
    ucStatus = rt_LD_ReadReg(0x06);
    while (!(ucStatus & MASK_FIFO_STATUS_AFULL) && (nMp3Pos < nMp3Size))
    {
        //printf("ucStatus is %x, write mp3 data: %x\r\n", ucStatus, val);
        val = nMp3name[nMp3Pos++];
        rt_LD_WriteReg(0x01, val);
        ucStatus = rt_LD_ReadReg(0x06);
    }
}

/********************************************************************************
function:
                Begin to ASR
********************************************************************************/
static rt_uint8_t rt_LD_AsrRun(void)
{
    rt_LD_WriteReg(0x35, MIC_VOL);
    rt_LD_WriteReg(0x1C, 0x09);
    rt_LD_WriteReg(0xBD, 0x20);
    rt_LD_WriteReg(0x08, 0x01);
    rt_thread_delay(20);
    rt_LD_WriteReg(0x08, 0x00);
    rt_thread_delay(20);

    if (rt_LD_Check_ASRBusyFlag() == 0)
        return 0;

    rt_LD_WriteReg(0xB2, 0xff);
    rt_LD_WriteReg(0x37, 0x06);
    rt_LD_WriteReg(0x37, 0x06);
    rt_thread_delay(20);
    rt_LD_WriteReg(0x1C, 0x0b);
    rt_LD_WriteReg(0x29, 0x10);
    rt_LD_WriteReg(0xBD, 0x00);
    return 1;
}

/********************************************************************************
function:
                Check ASR state
********************************************************************************/
static rt_uint8_t rt_LD_Check_ASRBusyFlag(void)
{
    rt_uint8_t j;
    rt_uint8_t flag = 0;
    for (j = 0; j < 10; j++)
    {
        if (rt_LD_ReadReg(0xb2) == 0x21)
        {
            flag = 1;
            //rt_kprintf("success!!! ASR OK\r\n");
            break;
        }
        rt_thread_delay(10);
        //printf("ERROR!!! ASR Busy\r\n");
    }
    return flag;
}

/********************************************************************************
function:
                Common init
********************************************************************************/
static void rt_LD_Init_Common(void)
{
    bMp3Play = 0;

    rt_LD_ReadReg(0x06);
    rt_LD_WriteReg(0x17, 0x35);
    rt_thread_delay(20);
    rt_LD_ReadReg(0x06);

    rt_LD_WriteReg(0x89, 0x03);
    rt_thread_delay(20);
    rt_LD_WriteReg(0xCF, 0x43);
    rt_thread_delay(20);
    rt_LD_WriteReg(0xCB, 0x02);

    /*PLL setting*/
    rt_LD_WriteReg(0x11, LD_PLL_11);
    if (nLD_Mode == LD_MODE_MP3)
    {
        rt_LD_WriteReg(0x1E, 0x00);
        rt_LD_WriteReg(0x19, LD_PLL_MP3_19);
        rt_LD_WriteReg(0x1B, LD_PLL_MP3_1B);
        rt_LD_WriteReg(0x1D, LD_PLL_MP3_1D);
    }
    else
    {
        rt_LD_WriteReg(0x1E, 0x00);
        rt_LD_WriteReg(0x19, LD_PLL_ASR_19);
        rt_LD_WriteReg(0x1B, LD_PLL_ASR_1B);
        rt_LD_WriteReg(0x1D, LD_PLL_ASR_1D);
    }
    rt_thread_delay(20);
    rt_LD_WriteReg(0xCD, 0x04);
    rt_LD_WriteReg(0x17, 0x4c);
    rt_thread_delay(20);
    rt_LD_WriteReg(0xB9, 0x00);
    rt_LD_WriteReg(0xCF, 0x4F);
    rt_LD_WriteReg(0x6F, 0xFF);
}

/********************************************************************************
function:
                ASR init
********************************************************************************/
static void rt_LD_Init_ASR(void)
{
    nLD_Mode = LD_MODE_ASR_RUN;
    rt_LD_Init_Common();

    rt_LD_WriteReg(0xBD, 0x00);
    rt_LD_WriteReg(0x17, 0x48);
    rt_thread_delay(20);

    rt_LD_WriteReg(0x3C, 0x80);
    rt_LD_WriteReg(0x3E, 0x07);
    rt_LD_WriteReg(0x38, 0xff);
    rt_LD_WriteReg(0x3A, 0x07);
    rt_thread_delay(20);

    rt_LD_WriteReg(0x40, 0);
    rt_LD_WriteReg(0x42, 8);
    rt_LD_WriteReg(0x44, 0);
    rt_LD_WriteReg(0x46, 8);
    rt_thread_delay(20);
}

/********************************************************************************
function:
                MP3 player init
********************************************************************************/
void rt_LD_Init_MP3()
{
    nLD_Mode = LD_MODE_MP3;
    rt_LD_Init_Common();

    rt_LD_WriteReg(0xBD, 0x02);
    rt_LD_WriteReg(0x17, 0x48);
    rt_thread_delay(20);

    rt_LD_WriteReg(0x85, 0x52);
    rt_LD_WriteReg(0x8F, 0x00);
    rt_LD_WriteReg(0x81, 0x00);
    rt_LD_WriteReg(0x83, 0x00);
    rt_LD_WriteReg(0x8E, 0xff);
    rt_LD_WriteReg(0x8D, 0xff);
    rt_thread_delay(20);
    rt_LD_WriteReg(0x87, 0xff);
    rt_LD_WriteReg(0x89, 0xff);
    rt_thread_delay(20);
    rt_LD_WriteReg(0x22, 0x00);
    rt_LD_WriteReg(0x23, 0x00);
    rt_LD_WriteReg(0x20, 0xef);
    rt_LD_WriteReg(0x21, 0x07);
    rt_LD_WriteReg(0x24, 0x77);
    rt_LD_WriteReg(0x25, 0x03);
    rt_LD_WriteReg(0x26, 0xbb);
    rt_LD_WriteReg(0x27, 0x01);
}

void rt_ld3320_irq_pin_init()
{
    rt_pin_mode(LD3320_IRQ, PIN_MODE_INPUT_PULLUP);

    rt_pin_attach_irq(LD3320_IRQ, PIN_IRQ_MODE_FALLING, rt_ld3320_isr, RT_NULL);
    rt_pin_irq_enable(LD3320_IRQ, PIN_IRQ_ENABLE);
}

static error_t rt_hw_ld3320_init(void)
{
    __HAL_RCC_GPIOH_CLK_ENABLE();
    __HAL_RCC_GPIOE_CLK_ENABLE();
    __HAL_RCC_GPIOB_CLK_ENABLE();

    rt_pin_mode(LD3320_WR, PIN_MODE_OUTPUT);
    rt_pin_mode(LD3320_RST, PIN_MODE_OUTPUT);
    rt_pin_mode(LD3320_CS, PIN_MODE_OUTPUT);

    if (RT_EOK == rt_hw_spi_device_attach("spi4", "spi40", GPIOE, GPIO_PIN_4))
    {
        return RT_EOK;
    }
    return RT_ERROR;
}

/********************************************************************************
function:
                Write data to LD3320 reg
********************************************************************************/
static void rt_LD_WriteReg(rt_uint8_t data1, rt_uint8_t data2)
{
    rt_uint8_t buf[3];

    struct rt_spi_message msg;

    LD3320_WR_Func(0);

    buf[0] = 0x04;
    buf[1] = data1;
    buf[2] = data2;

    msg.send_buf = buf;
    msg.recv_buf = RT_NULL;
    msg.length = 3;
    msg.cs_take = 1;
    msg.cs_release = 1;
    msg.next = RT_NULL;

    rt_spi_transfer_message(spi_dev_ld3320, &msg);
}
/********************************************************************************
function:
                Read data from LD3320 reg
********************************************************************************/
static rt_uint8_t rt_LD_ReadReg(rt_uint8_t reg_addr)
{
    rt_uint8_t ret_byte;

    LD3320_WR_Func(0);

    struct rt_spi_message msg1, msg2;

    rt_uint8_t buf[3];

    buf[0] = 0x05;
    buf[1] = reg_addr;
    buf[2] = 0x00;

    msg1.send_buf = buf;
    msg1.recv_buf = RT_NULL;
    msg1.length = 2;
    msg1.cs_take = 1;
    msg1.cs_release = 0;
    msg1.next = &msg2;

    msg2.send_buf = RT_NULL;
    msg2.recv_buf = &ret_byte;
    msg2.length = 1;
    msg2.cs_take = 0;
    msg2.cs_release = 1;
    msg2.next = RT_NULL;

    rt_spi_transfer_message(spi_dev_ld3320, &msg1);

    return (ret_byte);
}

void rt_ld3320_init(int argc, char *argv[])
{
    char name[RT_NAME_MAX];

    if (argc == 2)
    {
        rt_strncpy(name, argv[1], RT_NAME_MAX);
    }
    else
    {
        rt_strncpy(name, LD3320_SPI_DEVICE_NAME, RT_NAME_MAX);
    }
    rt_hw_ld3320_init();

    spi_dev_ld3320 = (struct rt_spi_device *)rt_device_find(name);
    if (!spi_dev_ld3320)
    {
        rt_kprintf("spi sample run failed! can't find %s device!\n", name);
    }
    else
    {
        rt_kprintf("spi sample run success!find %s device!\n", name);
    }

    struct rt_spi_configuration cfg;
    cfg.data_width = 8;
    cfg.mode = RT_SPI_MSB | RT_SPI_MASTER | RT_SPI_MODE_2;
    cfg.max_hz = 6 * 1000 * 100; /* 6M */

    if (rt_spi_configure(spi_dev_ld3320, &cfg) == RT_ERROR)
    {
        rt_kprintf("spi4 config error\r\n");
    }
    rt_kprintf("spi4 config success\r\n");

    rt_LD_init();
}

rt_uint8_t  ld3320_statusCheck(void)
{
    if(rt_LD_ReadReg(0xb2)==0x21)
    {
        //rt_kprintf("---------------ASR---------------\r\n");
        return RT_EOK;
    }
    return RT_ERROR;
}

INIT_COMPONENT_EXPORT(rt_ld3320_init);



