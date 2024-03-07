#ifndef __M_STM32_TIMER_H
#define __M_STM32_TIMER_H

#include "stm32f10x.h"
/*The table below gives the allowed values of the pre-emption priority and subpriority according
 to the Priority Grouping configuration performed by NVIC_PriorityGroupConfig function
  ============================================================================================================================
    NVIC_PriorityGroup   | NVIC_IRQChannelPreemptionPriority | NVIC_IRQChannelSubPriority  | Description
  ============================================================================================================================
   NVIC_PriorityGroup_0  |                0                  |            0-15             |   0 bits for pre-emption priority
                         |                                   |                             |   4 bits for subpriority
  ----------------------------------------------------------------------------------------------------------------------------
   NVIC_PriorityGroup_1  |                0-1                |            0-7              |   1 bits for pre-emption priority
                         |                                   |                             |   3 bits for subpriority
  ----------------------------------------------------------------------------------------------------------------------------    
   NVIC_PriorityGroup_2  |                0-3                |            0-3              |   2 bits for pre-emption priority
                         |                                   |                             |   2 bits for subpriority
  ----------------------------------------------------------------------------------------------------------------------------    
   NVIC_PriorityGroup_3  |                0-7                |            0-1              |   3 bits for pre-emption priority
                         |                                   |                             |   1 bits for subpriority
  ----------------------------------------------------------------------------------------------------------------------------    
   NVIC_PriorityGroup_4  |                0-15               |            0                |   4 bits for pre-emption priority
                         |                                   |                             |   0 bits for subpriority                       
  ============================================================================================================================
  */
//****************************中断分组**************************************
//NVIC_PriorityGroup_0	所有4位用于指定响应优先级
//NVIC_PriorityGroup_1	最高1位用于指定抢占式优先级，最低3位用于指定响应优先级
//NVIC_PriorityGroup_2	最高2位用于指定抢占式优先级，最低2位用于指定响应优先级
//NVIC_PriorityGroup_4	所有4位用于指定抢占式优先级
//***************************中断优先级*************************************
//NVIC_PriorityGroup_3	最高3位用于指定抢占式优先级，最低1位用于指定响应优先级
#define LEVEL_0    0
#define LEVEL_1    1
#define LEVEL_2    2
#define LEVEL_3    3
#define LEVEL_4    4
#define LEVEL_5    5
#define LEVEL_6    6
#define LEVEL_7    7
#define LEVEL_8    8
#define LEVEL_9    9
#define LEVEL_10  10
#define LEVEL_11  11
#define LEVEL_12  12
#define LEVEL_13  13
#define LEVEL_14  14
#define LEVEL_15  15

//**************************************************************************
void M_TIMx_NVIC_Configuration(TIM_TypeDef* TIMx,                                              //配置TIM中断
                               uint32_t     NVIC_PriorityGroup_x, 
							   uint8_t      Pre_LEVEL_x, 
							   uint8_t      Sub_LEVEL_x);

void M_TIMx_Init(TIM_TypeDef* TIMx, u16 CK_time);										       //TIMx通道初始化
void M_TIMx_Switch(TIM_TypeDef* TIMx, FunctionalState NewState);					           //TIMx中断开关

#endif

