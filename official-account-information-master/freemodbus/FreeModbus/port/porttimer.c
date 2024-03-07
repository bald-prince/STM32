/*
 * FreeModbus Libary: LPC214X Port
 * Copyright (C) 2007 Tiago Prado Lone <tiago@maxwellbohr.com.br>
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
 *
 * File: $Id: porttimer.c,v 1.1 2007/04/24 23:15:18 wolti Exp $
 */
/* ----------------------- Platform includes --------------------------------*/
#include "port.h"

/* ----------------------- Modbus includes ----------------------------------*/
#include "mb.h"
#include "mbport.h"

/* ----------------------- Start implementation -----------------------------*/
BOOL
xMBPortTimersInit( USHORT usTim1Timerout50us )
{
 __HAL_TIM_SET_AUTORELOAD(&htim7, 50 * usTim1Timerout50us-1);
  return TRUE;
}


void
vMBPortTimersEnable(  )
{	
	__HAL_TIM_SET_COUNTER(&htim7,0);
	HAL_TIM_Base_Start_IT(&htim7);
}

void
vMBPortTimersDisable(  )
{
	__HAL_TIM_SET_COUNTER(&htim7,0);
	HAL_TIM_Base_Stop_IT(&htim7);
}


void
TIMERExpiredISR( void )
{
    (void)pxMBPortCBTimerExpired();
}
