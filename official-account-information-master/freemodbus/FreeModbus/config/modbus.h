/*
************************************************************************************************
主要的包含文件

文 件: INCLUDES.C ucos包含文件
作 者: Jean J. Labrosse
************************************************************************************************
*/

#ifndef __MODBUS_H__
#define __MODBUS_H__
/* ----------------------- Modbus includes ---------------------------------------------------*/
#include "mb.h"

/* ----------------------- modbus reg lengh Defines ------------------------------------------*/
/* ----------------------- modbus 各个寄存器数据长度，允许用户调用的数据----------------------*/
#define DISCRETE_INPUT_START        1
#define DISCRETE_INPUT_NDISCRETES   96
#define COIL_START                  1
#define COIL_NCOILS                 96
#define REG_INPUT_START             1
#define REG_INPUT_NREGS             100
#define REG_HOLDING_START           1
#define REG_HOLDING_NREGS           100
/* ----------------------- modbus Static variables defines------------------------------------*/
extern USHORT   usDiscreteInputStart                             ;
extern UCHAR    usDiscreteInputBuf[DISCRETE_INPUT_NDISCRETES/8]  ;
extern USHORT   usCoilStart                                      ;
extern UCHAR    usCoilBuf[COIL_NCOILS/8]                         ;
extern USHORT   usRegInputStart                                  ;
extern USHORT   usRegInputBuf[REG_INPUT_NREGS]                   ;
extern USHORT   usRegHoldingStart                                ;
extern USHORT   usRegHoldingBuf[REG_HOLDING_NREGS]               ;
/* -------------------------------------------------------------------------------------------*/
extern eMBErrorCode	
eMBRegInputCB( UCHAR * pucRegBuffer, USHORT usAddress, USHORT usNRegs );

extern eMBErrorCode
eMBRegHoldingCB( UCHAR * pucRegBuffer, USHORT usAddress, USHORT usNRegs, eMBRegisterMode eMode );

eMBErrorCode
eMBRegCoilsCB( UCHAR * pucRegBuffer, USHORT usAddress, USHORT usNCoils, eMBRegisterMode eMode );

extern eMBErrorCode
eMBRegDiscreteCB( UCHAR * pucRegBuffer, USHORT usAddress, USHORT usNDiscrete );
void User_eMBRegCoilsWriteCB(void);
void User_eMBRegHoldingWriteCB(void);
//////////////////////////////////////////////////////////////////////////////////////////////// 	
#endif
