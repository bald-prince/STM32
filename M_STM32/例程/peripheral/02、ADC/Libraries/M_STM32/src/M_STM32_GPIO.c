#include "M_STM32_GPIO.h"

/**
  * @brief  识别GPIOx
  * @param  hex 十六进制数 
  * @retval None
  */
GPIO_TypeDef* M_GPIOx_Recognizer(uint16_t hex)
{
	char H = 0; //十六进制高位
	
	H = hex >> 4; //分离高位
	
	//识别GPIOx
	switch(H){
		//GPIOA
		case 1:
			return GPIOA;
			
		//GPIOB
		case 2:
			return GPIOB;
			
		//GPIOC
		case 3:
			return GPIOC;
			
		//GPIOD
		case 4:
			return GPIOD;
			
		//GPIOE
		case 5:
			return GPIOE;
		
		//GPIOF
		case 6:
			return GPIOF;
		
		//GPIOG
		case 7:
			return GPIOG;
	}
	return 0; //ERROR
}

/**
  * @brief  识别GPIO_Pin_x
  * @param  hex 十六进制数 
  * @retval None
  */
uint16_t M_GPIO_Pin_Recognizer(uint16_t hex)
{
	char L; //十六进制低位
	
	L = hex & 0x0F; //分离低位
	
	switch(L){
		case 0:
			return GPIO_Pin_0;
		
		case 1:
			return GPIO_Pin_1;
		
		case 2:
			return GPIO_Pin_2;
		
		case 3:
			return GPIO_Pin_3;
		
		case 4:
			return GPIO_Pin_4;
		
		case 5:
			return GPIO_Pin_5;
		
		case 6:
			return GPIO_Pin_6;
		
		case 7:
			return GPIO_Pin_7;
		
		case 8:
			return GPIO_Pin_8;
		
		case 9:
			return GPIO_Pin_9;
		
		case 10:
			return GPIO_Pin_10;
		
		case 11:
			return GPIO_Pin_11;
		
		case 12:
			return GPIO_Pin_12;
		
		case 13:
			return GPIO_Pin_13;
		
		case 14:
			return GPIO_Pin_14;
		
		case 15:
			return GPIO_Pin_15;
	}
	return 0; //EEROR
	
}

/**
  * @brief  初始化引脚
  * @param  GPIOx: 端口
  * @param  GPIO_Pin: 引脚
  * @retval None
  * example:M_GPIO_Init(A1, GPIO_Mode_Out_PP);
  */
void M_GPIO_Init(uint16_t PTx, u8 GPIO_Mode)
{
	GPIO_InitTypeDef GPIO_InitStructure;		// 定义一个GPIO_InitTypeDef类型的结构体
	
	GPIO_TypeDef* GPIOx;    
    uint16_t      GPIO_Pin;
	GPIOx    = M_GPIOx_Recognizer(PTx);       //GPIOx
	GPIO_Pin = M_GPIO_Pin_Recognizer(PTx);    //GPIO_Pin_x
	
	//开启端口时钟
	if(GPIOx == GPIOA){
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	}
	else if(GPIOx == GPIOB){
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
	}
	else if(GPIOx == GPIOC){
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);
	}
	else if(GPIOx == GPIOD){
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD, ENABLE);
	}
	else if(GPIOx == GPIOE){
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOE, ENABLE);
	}
	else if(GPIOx == GPIOF){
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOF, ENABLE);
	}
	else if(GPIOx == GPIOG){
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOG, ENABLE);
	}

	GPIO_InitStructure.GPIO_Pin   = GPIO_Pin;				// 选择要控制的IO口
	GPIO_InitStructure.GPIO_Mode  = GPIO_Mode;      		// 设置引脚为推挽输出
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		//设置引脚速率为50MHz
	GPIO_Init(GPIOx, &GPIO_InitStructure);					//完成初始化
}

/**
  * @brief  设置引脚输出高低电平
  * @param  GPIOx: 端口
  * @param  GPIO_Pin: 引脚
  * @param  Data: 电平 (HIHG or LOW)
  * @retval None
  * example:M_GPIO_Set(A1, HIGH)
  */
void M_GPIO_Set(uint16_t PTx, char Data)
{
	GPIO_TypeDef* GPIOx;    
    uint16_t      GPIO_Pin;
	GPIOx    = M_GPIOx_Recognizer(PTx);    //GPIOx
	GPIO_Pin = M_GPIO_Pin_Recognizer(PTx); //GPIO_Pin_x
	
	switch(Data){
		case HIGH:GPIO_SetBits(GPIOx, GPIO_Pin);break;
		case LOW: GPIO_ResetBits(GPIOx, GPIO_Pin);break;
		default:break;
	}
}

/**
  * @brief  读取引脚数据
  * @param  GPIOx: 端口
  * @param  GPIO_Pin: 引脚
  * @retval None
  * example: M_READ_Data(A1)
  */
uint8_t M_READ_Data(uint16_t PTx)
{
	GPIO_TypeDef* GPIOx;    
    uint16_t      GPIO_Pin;
	GPIOx    = M_GPIOx_Recognizer(PTx);    //GPIOx
	GPIO_Pin = M_GPIO_Pin_Recognizer(PTx); //GPIO_Pin_x
	
	GPIO_SetBits(GPIOx, GPIO_Pin);
	return(GPIO_ReadInputDataBit(GPIOx, GPIO_Pin));
}
