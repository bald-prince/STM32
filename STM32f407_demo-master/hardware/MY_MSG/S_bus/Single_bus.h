#ifndef _Single_bus_H
#define _Single_bus_H
#include "sys.h"
#include "delay.h"

#define S_bus PBout(9)
#define S_bus_Enable PAout(1)

void S_bus_Init();
void S_bus_TX(float Data);


#endif