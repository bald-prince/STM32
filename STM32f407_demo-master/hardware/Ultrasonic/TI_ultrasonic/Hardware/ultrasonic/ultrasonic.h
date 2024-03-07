#ifndef _ULTRASONIC_H
#define _ULTRASONIC_H

#include "stdint.h"
#include "HAL_timer.h"
#include "driverlib.h"

//#define TRIG	0	//5.0
//#define ECHO	2	//5.2
 typedef struct U{
	double dis_front;
	double dis_left;
	double dis_right;
}ULS;

extern ULS ULS_Distance;
extern double UL_Distance;
extern int flag;
void UL_Init(void);
double Calc_Barrier_Distance(void);
double Calc_ULS_Conclude(void);
void ULS_Acquire(ULS *Dir);
double Calc_ULS_Conclude_Tim(int usT,int *flag);
#endif
