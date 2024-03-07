#ifndef _HLINK_VOICE_H
#define _HLINK_VOICE_H

#include "stm32f4xx.h"

#define Relay_Ctrl_OPEN	1
#define Relay_Ctrl_CLOSE	0

enum rev_status{
	Err_None,
	Err_Head

};

void Voice_RecUartCallBack(void);	
void Voice_RecTimCallBack(uint16_t timeout);
void Voice_RecUartInit(void);
int Voice_DataFrame(void);
void Relay_Ctrl(uint8_t Switch);
void RedLed_Ctrl(uint8_t Switch);


#endif


