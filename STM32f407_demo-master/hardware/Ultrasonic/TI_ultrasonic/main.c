/* DriverLib Includes */
#include "driverlib.h"

/* Standard Includes */
#include <stdint.h>
#include <stdbool.h>
#include "HAL_usart.h"
#include "HAL_timer.h"
#include <stdio.h>
#include "led.h"
#include "ultrasonic.h"
#include "My_tim.h"
#include "S_bus_Reci.h"
void MCU_Init(void);
double UL_Distance = 0;
int tim_n = 0;
int tim_o = 0;
//ULS ULS_Distance;
	 int tim_rem=0;
	 int tim_new=0;
	 int tim_pass;
	 int ct = 0;
	 int flag=1;
	 int a = 0;
int main(void)
{
    MCU_Init();
		//UL_Init();
//		Tim_init();
		S_bus_init();
    while(1)
    {
			  tim_n = GetSysTime_us();
			  S_Reci();
//			  UL_Distance = Calc_Barrier_Distance();
		   	//ULS_Acquire(&ULS_Distance);
//			  if(flag)
//				{
//					GPIO_setOutputHighOnPin(GPIO_PORT_P5, GPIO_PIN4);
//			    Delay_us(12);
//			    GPIO_setOutputLowOnPin(GPIO_PORT_P5, GPIO_PIN4);
//    		  flag = 0;
//				}
//				a++;
			  tim_o = GetSysTime_us() - tim_n;
    }
}

void MCU_Init(void)
{
    //ֹͣ���Ź�
    MAP_WDT_A_holdTimer();

    //�����ں�ʱ��
    SystemCoreClockUpdate();

    //���õδ��ʱ��
    SysTick_Configuration();

    //���ڳ�ʼ��
    USART_Init();

    //100ms��ʱ
    Delay_ms(100);

    //ʹ���ж�
    MAP_Interrupt_enableMaster();  
}

