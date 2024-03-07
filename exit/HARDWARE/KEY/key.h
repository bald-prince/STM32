#ifndef _KEY_H
#define _KEY_H
#include "sys.h"

#define KEY0        PGin(13) 			//KEY0按键PG13
#define KEY1        PGin(11) 			//KEY1按键PG11
#define KEY2        PGin(10)			//KEY2按键PG10
#define KEY3        PGin(9)
#define WEKEUP       	PAin(0) 			//WKUP按键PG9

#define KEY0_PRES 	1
#define KEY1_PRES		2
#define KEY2_PRES		3
#define KEY3_PRES		4
#define WEKEUP_PRES   5

void KEY_Init(void);
u8 KEY_Scan(u8 mode);
#endif
