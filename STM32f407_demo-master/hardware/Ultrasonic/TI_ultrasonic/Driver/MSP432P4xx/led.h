#ifndef _LED_H
#define _LED_H

#include "stdint.h"

#define LED_BLUE_ON     P2OUT |= GPIO_PIN2
#define LED_BLUE_OFF    P2OUT &= ~GPIO_PIN2

#define LED_GREEN_ON    P2OUT |= GPIO_PIN1
#define LED_GREEN_OFF   P2OUT &= ~GPIO_PIN1

#define LED_RED_ON      P2OUT |= GPIO_PIN0
#define LED_RED_OFF     P2OUT &= ~GPIO_PIN0

#define LED_MAIN_ON     P1OUT |= GPIO_PIN0
#define LED_MAIN_OFF    P1OUT &= ~GPIO_PIN0

void LED_Init(void);


#endif
