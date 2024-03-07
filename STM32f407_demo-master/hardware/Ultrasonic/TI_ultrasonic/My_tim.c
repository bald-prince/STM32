#include "My_tim.h"
#include "driverlib.h"
#include "ultrasonic.h"
void T32_INT1_IRQHandler(void)
{
	ct++;
//	UL_Distance = Calc_ULS_Conclude_Tim(ct,&flag);
	ULS_Acquire(&ULS_Distance);
	Timer32_clearInterruptFlag(TIMER32_0_BASE);
	

//	Timer32_clearInterruptFlag(INT_T32_INT1);
}

void Tim_init()
{
//	  CS_setReferenceOscillatorFrequency(CS_MODOSC_SELECT);//24000000
//    CS_initClockSignal(CS_MCLK, CS_MODOSC_SELECT, CS_CLOCK_DIVIDER_1);
//    PCM_setPowerState(PCM_AM_LF_VCORE0);
	
	Timer32_initModule(TIMER32_0_BASE, TIMER32_PRESCALER_1, TIMER32_32BIT,
            TIMER32_PERIODIC_MODE);

	Interrupt_enableInterrupt(INT_T32_INT1);
	Timer32_enableInterrupt(INT_T32_INT1);
	
	MAP_Timer32_setCount(TIMER32_0_BASE,240);
  MAP_Timer32_enableInterrupt(TIMER32_0_BASE);
  MAP_Timer32_startTimer(TIMER32_0_BASE, 0);
	//Timer32_startTimer(TIMER32_BASE,0);
}
