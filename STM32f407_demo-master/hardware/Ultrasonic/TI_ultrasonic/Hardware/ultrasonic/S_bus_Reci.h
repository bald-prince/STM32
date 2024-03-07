#ifndef _S_BUS_RECI_H
#define _S_BUS_RECI_H

#include "driverlib.h"
#include "HAL_timer.h"
//Port9 PIN2 -> S_bus
//Port8 PIN2 -> Enable

extern int S_bus_flag;
extern int En[2];
extern uint8_t Data;


void S_bus_init();
uint8_t S_Reci();
#endif