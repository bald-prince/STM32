#include "HAL_timer.h"
#include "driverlib.h"
#include "HAL_usart.h"

volatile uint32_t usTicks = 0;
volatile uint32_t msTicks = 0;                                    

void SysTick_Handler(void)
{
    msTicks++;
    PollingUSART();
}

void SysTick_Configuration(void)
{
    usTicks = SystemCoreClock / 1000000;		//48
    SysTick_Config(SystemCoreClock / 1000);       /* Systick interrupt each 1ms */
}

uint32_t GetSysTime_us(void) //两次获取若大于u32/1000(us),则两次差值溢出，不可取
{
    register uint32_t ms;
    uint32_t time_us;
    
    do
    {
        ms = sysTickUptime;

        time_us = ms * 1000 + (usTicks * 1000 - SysTick->VAL) / usTicks;
    } while (ms != sysTickUptime);
        
    return (time_us);
}

void Delay_us(uint32_t nTime)
{ 
	uint32_t now;
	now = GetSysTime_us();
	while(GetSysTime_us()-now<nTime);
}

void Delay_ms(uint32_t nTime)
{ 
    uint16_t i;
    
    for(i=0;i<nTime;i++)
    {
        Delay_us(1000);
    }
}

void Delay(uint32_t nCount)
{
    for(; nCount!= 0;nCount--);
}
