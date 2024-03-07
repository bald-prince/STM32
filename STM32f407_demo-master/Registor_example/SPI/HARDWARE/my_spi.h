#ifndef __MY_SPI_H
#define __MY_SPI_H
#include "sys.h"
/* define */
/* 4ÏßSPI */
#define SDO PBout(8)
#define SDI PBin(9)
#define SCK PBout(10)
#define CS PBout(11)

/* extern */
void my_spi_init(void);
u8 SPI_TR_BYTE(u8 date);
#endif





