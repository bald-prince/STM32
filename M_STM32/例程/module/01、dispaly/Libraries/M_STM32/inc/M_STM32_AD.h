#ifndef __M_STM32_AD_H
#define __M_STM32_AD_H

#include "stm32f10x.h"

//***************************ADC 通道定义***********************************
#define ADC_CH0_Pin	  ADC_Channel_0			//PA0
#define ADC_CH1_Pin	  ADC_Channel_1	        //PA1
#define ADC_CH2_Pin	  ADC_Channel_2         //PA2
#define ADC_CH3_Pin	  ADC_Channel_3         //PA3
#define ADC_CH4_Pin	  ADC_Channel_4         //PA4
#define ADC_CH5_Pin   ADC_Channel_5         //PA5
#define ADC_CH6_Pin	  ADC_Channel_6         //PA6
#define ADC_CH7_Pin	  ADC_Channel_7         //PA7
#define ADC_CH8_Pin   ADC_Channel_8         //PB0
#define ADC_CH9_Pin	  ADC_Channel_9         //PB1
#define ADC_CH10_Pin  ADC_Channel_10        //PC0
#define ADC_CH11_Pin  ADC_Channel_11        //PC1
#define ADC_CH12_Pin  ADC_Channel_12        //PC2
#define ADC_CH13_Pin  ADC_Channel_13        //PC3
#define ADC_CH14_Pin  ADC_Channel_14        //PC4
#define ADC_CH15_Pin  ADC_Channel_15        //PC5                       

//定义使用的通道数
typedef enum NumOfChannel{
	Channel_1  = 1 ,
	Channel_2  = 2 ,
	Channel_3  = 3 ,
	Channel_4  = 4 ,
	CHannel_5  = 5 ,
	Channel_6  = 6 ,
	Channel_7  = 7 ,
	Channel_8  = 8 ,
	Channel_9  = 9 ,
	Channel_10 = 10,
	Channel_11 = 11,
	Channel_12 = 12,
	Channel_13 = 13,
	Channel_14 = 14,
	Channel_15 = 15,
	Channel_16 = 16
}NbrOfChannel;

//定义采样的顺序
typedef enum RANK{
	Rank_1  = 1 ,
	Rank_2  = 2 ,
	Rank_3  = 3 ,
	Rank_4  = 4 ,
	Rank_5  = 5 ,
	Rank_6  = 6 ,
	Rank_7  = 7 ,
	Rank_8  = 8 ,
	Rank_9  = 9 ,
	Rank_10 = 10,
	Rank_11 = 11,
	Rank_12 = 12,
	Rank_13 = 13,
	Rank_14 = 14,
	Rank_15 = 15,
	Rank_16 = 16
	
}RANK;

void M_ADC_Init(  ADC_TypeDef* ADCx,                                //ADC初始化
				  uint8_t      ADC_Channel_x, 
				  uint32_t     ADC_ExternalTrigConv, 
				  NbrOfChannel ADC_NbrOfChannel,
				  RANK         Rank);

uint16_t M_ADCx_GetValue(ADC_TypeDef* ADCx);                        //ADC采样
void M_ADC_SwitchConvert(ADC_TypeDef* ADCx, FunctionalState State); //触发采样开关

#endif
