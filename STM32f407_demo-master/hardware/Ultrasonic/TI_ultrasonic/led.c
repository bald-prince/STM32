#include "led.h"
/* DriverLib Includes */
#include "driverlib.h"

void LED_Init()
{
    P2DIR |= GPIO_PIN2|GPIO_PIN1|GPIO_PIN0;
    P1DIR |= GPIO_PIN0;
}



