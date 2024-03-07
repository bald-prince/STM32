#include "M_STM32_AD.h"

//ADC1采样结果(DMA方式，空间大小5000,一次采集5000个数据)
__IO uint16_t ADC1_ConvertedValue[5000]={0};

/**
  * @brief  ADCx引脚初始化
  * @param  ADCx:AD模块号
  * @param  ADC_Channel_x 通道号  
  * @retval None
  */
  void M_ADC_GPIO_Config(ADC_TypeDef* ADCx, uint8_t ADC_Channel_x)
  {
	  GPIO_InitTypeDef GPIO_InitStructure;
	  
	  if(ADCx == ADC1){
		  if(ADC_Channel_x == ADC_Channel_0){
			  //开启时钟和复用功能时钟
			  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_AFIO, ENABLE);
			  
			  GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_0;	//引脚配置
			  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN; //配置模式为模拟输入
			  GPIO_Init(GPIOA, &GPIO_InitStructure);        //初始化配置参数
		  }
		  else if(ADC_Channel_x == ADC_Channel_1){
			  //开启时钟和复用功能时钟
			  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_AFIO, ENABLE);
			  
			  GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_1;	//引脚配置
			  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN; //配置模式为模拟输入
			  GPIO_Init(GPIOA, &GPIO_InitStructure);        //初始化配置参数
		  }
		  else if(ADC_Channel_x == ADC_Channel_2){
			  //开启时钟和复用功能时钟
			  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_AFIO, ENABLE);
			  
			  GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_2;	//引脚配置
			  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN; //配置模式为模拟输入
			  GPIO_Init(GPIOA, &GPIO_InitStructure);        //初始化配置参数
		  }
		  else if(ADC_Channel_x == ADC_Channel_3){
			  //开启时钟和复用功能时钟
			  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_AFIO, ENABLE);
			  
			  GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_3;	//引脚配置
			  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN; //配置模式为模拟输入
			  GPIO_Init(GPIOA, &GPIO_InitStructure);        //初始化配置参数
		  }
		  else if(ADC_Channel_x == ADC_Channel_4){
			  //开启时钟和复用功能时钟
			  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_AFIO, ENABLE);
			  
			  GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_4;	//引脚配置
			  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN; //配置模式为模拟输入
			  GPIO_Init(GPIOA, &GPIO_InitStructure);        //初始化配置参数
		  }
		  else if(ADC_Channel_x == ADC_Channel_5){
			  //开启时钟和复用功能时钟
			  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_AFIO, ENABLE);
			  
			  GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_5;	//引脚配置
			  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN; //配置模式为模拟输入
			  GPIO_Init(GPIOA, &GPIO_InitStructure);        //初始化配置参数
		  }
		  else if(ADC_Channel_x == ADC_Channel_6){
			  //开启时钟和复用功能时钟
			  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_AFIO, ENABLE);
			  
			  GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_6;	//引脚配置
			  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN; //配置模式为模拟输入
			  GPIO_Init(GPIOA, &GPIO_InitStructure);        //初始化配置参数
		  }
		  else if(ADC_Channel_x == ADC_Channel_7){
			  //开启时钟和复用功能时钟
			  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_AFIO, ENABLE);
			  
			  GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_7;	//引脚配置
			  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN; //配置模式为模拟输入
			  GPIO_Init(GPIOA, &GPIO_InitStructure);        //初始化配置参数
		  }
		  else if(ADC_Channel_x == ADC_Channel_8){
			  //开启时钟和复用功能时钟
			  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB | RCC_APB2Periph_AFIO, ENABLE);
			  
			  GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_0;	//引脚配置
			  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN; //配置模式为模拟输入
			  GPIO_Init(GPIOB, &GPIO_InitStructure);        //初始化配置参数
		  }
		  else if(ADC_Channel_x == ADC_Channel_9){
			  //开启时钟和复用功能时钟
			  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB | RCC_APB2Periph_AFIO, ENABLE);
			  
			  GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_1;	//引脚配置
			  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN; //配置模式为模拟输入
			  GPIO_Init(GPIOB, &GPIO_InitStructure);        //初始化配置参数
		  }
		  else if(ADC_Channel_x == ADC_Channel_10){
			  //开启时钟和复用功能时钟
			  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);
			  
			  GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_0;	//引脚配置
			  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN; //配置模式为模拟输入
			  GPIO_Init(GPIOC, &GPIO_InitStructure);        //初始化配置参数
		  }
		  else if(ADC_Channel_x == ADC_Channel_11){
			  //开启时钟和复用功能时钟
			  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);
			  
			  GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_1;	//引脚配置
			  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN; //配置模式为模拟输入
			  GPIO_Init(GPIOC, &GPIO_InitStructure);        //初始化配置参数
		  }
		  else if(ADC_Channel_x == ADC_Channel_12){
			  //开启时钟和复用功能时钟
			  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);
			  
			  GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_2;	//引脚配置
			  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN; //配置模式为模拟输入
			  GPIO_Init(GPIOC, &GPIO_InitStructure);        //初始化配置参数
		  }
		  else if(ADC_Channel_x == ADC_Channel_13){
			  //开启时钟和复用功能时钟
			  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);
			  
			  GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_3;	//引脚配置
			  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN; //配置模式为模拟输入
			  GPIO_Init(GPIOC, &GPIO_InitStructure);        //初始化配置参数
		  }
		  else if(ADC_Channel_x == ADC_Channel_14){
			  //开启时钟和复用功能时钟
			  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);
			  
			  GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_4;	//引脚配置
			  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN; //配置模式为模拟输入
			  GPIO_Init(GPIOC, &GPIO_InitStructure);        //初始化配置参数
		  }
		  else if(ADC_Channel_x == ADC_Channel_15){
			  //开启时钟和复用功能时钟
			  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);
			  
			  GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_5;	//引脚配置
			  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN; //配置模式为模拟输入
			  GPIO_Init(GPIOC, &GPIO_InitStructure);        //初始化配置参数
		  }
	  }
	  else if(ADCx == ADC2){
		  if(ADC_Channel_x == ADC_Channel_0){
			  //开启时钟和复用功能时钟
			  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_AFIO, ENABLE);
			  
			  GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_0;	//引脚配置
			  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN; //配置模式为模拟输入
			  GPIO_Init(GPIOA, &GPIO_InitStructure);        //初始化配置参数
		  }
		  else if(ADC_Channel_x == ADC_Channel_1){
			  //开启时钟和复用功能时钟
			  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_AFIO, ENABLE);
			  
			  GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_1;	//引脚配置
			  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN; //配置模式为模拟输入
			  GPIO_Init(GPIOA, &GPIO_InitStructure);        //初始化配置参数
		  }
		  else if(ADC_Channel_x == ADC_Channel_2){
			  //开启时钟和复用功能时钟
			  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_AFIO, ENABLE);
			  
			  GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_2;	//引脚配置
			  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN; //配置模式为模拟输入
			  GPIO_Init(GPIOA, &GPIO_InitStructure);        //初始化配置参数
		  }
		  else if(ADC_Channel_x == ADC_Channel_3){
			  //开启时钟和复用功能时钟
			  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_AFIO, ENABLE);
			  
			  GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_3;	//引脚配置
			  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN; //配置模式为模拟输入
			  GPIO_Init(GPIOA, &GPIO_InitStructure);        //初始化配置参数
		  }
		  else if(ADC_Channel_x == ADC_Channel_4){
			  //开启时钟和复用功能时钟
			  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_AFIO, ENABLE);
			  
			  GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_4;	//引脚配置
			  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN; //配置模式为模拟输入
			  GPIO_Init(GPIOA, &GPIO_InitStructure);        //初始化配置参数
		  }
		  else if(ADC_Channel_x == ADC_Channel_5){
			  //开启时钟和复用功能时钟
			  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_AFIO, ENABLE);
			  
			  GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_5;	//引脚配置
			  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN; //配置模式为模拟输入
			  GPIO_Init(GPIOA, &GPIO_InitStructure);        //初始化配置参数
		  }
		  else if(ADC_Channel_x == ADC_Channel_6){
			  //开启时钟和复用功能时钟
			  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_AFIO, ENABLE);
			  
			  GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_6;	//引脚配置
			  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN; //配置模式为模拟输入
			  GPIO_Init(GPIOA, &GPIO_InitStructure);        //初始化配置参数
		  }
		  else if(ADC_Channel_x == ADC_Channel_7){
			  //开启时钟和复用功能时钟
			  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_AFIO, ENABLE);
			  
			  GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_7;	//引脚配置
			  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN; //配置模式为模拟输入
			  GPIO_Init(GPIOA, &GPIO_InitStructure);        //初始化配置参数
		  }
		  else if(ADC_Channel_x == ADC_Channel_8){
			  //开启时钟和复用功能时钟
			  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB | RCC_APB2Periph_AFIO, ENABLE);
			  
			  GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_0;	//引脚配置
			  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN; //配置模式为模拟输入
			  GPIO_Init(GPIOB, &GPIO_InitStructure);        //初始化配置参数
		  }
		  else if(ADC_Channel_x == ADC_Channel_9){
			  //开启时钟和复用功能时钟
			  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB | RCC_APB2Periph_AFIO, ENABLE);
			  
			  GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_1;	//引脚配置
			  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN; //配置模式为模拟输入
			  GPIO_Init(GPIOB, &GPIO_InitStructure);        //初始化配置参数
		  }
		  else if(ADC_Channel_x == ADC_Channel_10){
			  //开启时钟和复用功能时钟
			  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);
			  
			  GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_0;	//引脚配置
			  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN; //配置模式为模拟输入
			  GPIO_Init(GPIOC, &GPIO_InitStructure);        //初始化配置参数
		  }
		  else if(ADC_Channel_x == ADC_Channel_11){
			  //开启时钟和复用功能时钟
			  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);
			  
			  GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_1;	//引脚配置
			  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN; //配置模式为模拟输入
			  GPIO_Init(GPIOC, &GPIO_InitStructure);        //初始化配置参数
		  }
		  else if(ADC_Channel_x == ADC_Channel_12){
			  //开启时钟和复用功能时钟
			  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);
			  
			  GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_2;	//引脚配置
			  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN; //配置模式为模拟输入
			  GPIO_Init(GPIOC, &GPIO_InitStructure);        //初始化配置参数
		  }
		  else if(ADC_Channel_x == ADC_Channel_13){
			  //开启时钟和复用功能时钟
			  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);
			  
			  GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_3;	//引脚配置
			  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN; //配置模式为模拟输入
			  GPIO_Init(GPIOC, &GPIO_InitStructure);        //初始化配置参数
		  }
		  else if(ADC_Channel_x == ADC_Channel_14){
			  //开启时钟和复用功能时钟
			  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);
			  
			  GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_4;	//引脚配置
			  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN; //配置模式为模拟输入
			  GPIO_Init(GPIOC, &GPIO_InitStructure);        //初始化配置参数
		  }
		  else if(ADC_Channel_x == ADC_Channel_15){
			  //开启时钟和复用功能时钟
			  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);
			  
			  GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_5;	//引脚配置
			  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN; //配置模式为模拟输入
			  GPIO_Init(GPIOC, &GPIO_InitStructure);        //初始化配置参数
		  }
	  }
  }

 /**
  * @brief  ADCx工作模式配置
  * @param  ADCx:         AD模块号
  * @param  ADC_Channel_x 通道号
  * @param  ADC_Mode      工作模式
  * @param  ADC_ExternalTrigConv 触发模式
  * @param  ADC_NbrOfChannel     转换通道
  * @retval None
  */
  void M_ADC_Mode_Config(ADC_TypeDef* ADCx, 
	                     uint8_t      ADC_Channel_x, 
	                     uint32_t     ADC_Mode, 
                         uint32_t     ADC_ExternalTrigConv,
						 NbrOfChannel ADC_NbrOfChannel)
  {
	  ADC_InitTypeDef ADC_InitStructure;
	  
	  //开启ADC时钟
	  if(ADCx == ADC1){
		  RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1, ENABLE);
	  }
	  else if(ADCx == ADC2){
		  RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC2, ENABLE);
	  }
	  
	  //ADC模式配置
	  ADC_InitStructure.ADC_Mode               = ADC_Mode;             //工作模式配置，如独立模式ADC_Mode_Independent
	  ADC_InitStructure.ADC_ScanConvMode       = ENABLE;               //连续扫描
	  ADC_InitStructure.ADC_ContinuousConvMode = ENABLE;               //连续转换
	  ADC_InitStructure.ADC_ExternalTrigConv   = ADC_ExternalTrigConv; //触发源
	  ADC_InitStructure.ADC_DataAlign          = ADC_DataAlign_Right;  //数据右对齐
	  ADC_InitStructure.ADC_NbrOfChannel       = ADC_NbrOfChannel;     //转换通道个数
	  ADC_Init(ADCx, &ADC_InitStructure);                              //ADC初始化
  }
  
/**
  * @brief  ADCx时钟配置
  * @param  ADCx:          AD模块号
  * @param  ADC_Channel_x  通道号
  * @param  ADC_PCLK_DIVx  时钟分频
  * @param  Rank           转换顺序
  * @param  ADC_SampleTime 采样时间
  * @retval None
  */
void M_ADC_Clock_Config(ADC_TypeDef* ADCx, uint8_t ADC_Channel_x, uint32_t ADC_PCLK_DIVx, RANK Rank, uint8_t ADC_SampleTime)
{
	//配置ADC时钟分频
	if(ADCx == ADC1){
		RCC_ADCCLKConfig(ADC_PCLK_DIVx);
	}
	else if(ADCx == ADC2){
		RCC_ADCCLKConfig(ADC_PCLK_DIVx);
	}
	
	//配置ADC通道的转换顺序及采样时间
	ADC_RegularChannelConfig(ADCx, ADC_Channel_x, Rank, ADC_SampleTime); 
	
	//若是ADC1的话默认开启DMA请求
	if(ADCx == ADC1){
		ADC_DMACmd(ADC1, ENABLE);
	}
	
	//开启ADC，并开始转换
	ADC_Cmd(ADCx, ENABLE);
	
	//ADC校准
	ADC_ResetCalibration(ADCx);
	while(ADC_GetResetCalibrationStatus(ADCx));
	ADC_StartCalibration(ADCx);
	while(ADC_GetCalibrationStatus(ADCx));
}

/**
  * @brief  ADC_DMA配置
  * @param  ADCx:AD模块号
  * @retval None
  */
void M_ADC_DMA_Config(ADC_TypeDef* ADCx)
{
	DMA_InitTypeDef DMA_InitStructure;
	
	//开启DMA时钟
	if(ADCx == ADC1){
		RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1, ENABLE);
	}
	
	DMA_DeInit(DMA1_Channel1); //复位DMA
	
	//DMA工作方式配置
	DMA_InitStructure.DMA_PeripheralBaseAddr = (u32)(&(ADCx->DR));              //外设基地址
	DMA_InitStructure.DMA_MemoryBaseAddr     = (u32)ADC1_ConvertedValue;        //存储器地址
	DMA_InitStructure.DMA_DIR                = DMA_DIR_PeripheralSRC;           //数据源
	DMA_InitStructure.DMA_BufferSize         = 5000;                  //缓冲区大小
	DMA_InitStructure.DMA_PeripheralInc      = DMA_PeripheralInc_Disable;       //外设地址不自增
	DMA_InitStructure.DMA_MemoryInc          = DMA_MemoryInc_Enable;            //内存地址自增
	DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_HalfWord; //外设地址单位
	DMA_InitStructure.DMA_MemoryDataSize     = DMA_MemoryDataSize_HalfWord;     //内存地址单位
	DMA_InitStructure.DMA_Mode               = DMA_Mode_Circular;               //循环传输
	DMA_InitStructure.DMA_Priority           = DMA_Priority_Medium;             //优先级
	DMA_InitStructure.DMA_M2M                = DMA_M2M_Disable;                 //禁止内存到内存的传输
	DMA_Init(DMA1_Channel1, &DMA_InitStructure);                                //初始化配置
	DMA_Cmd(DMA1_Channel1, ENABLE);                                             //使能DMA
}

/**
  * @brief  ADCx初始化
  * @param  ADCx:                AD模块号
  * @param  ADC_Channel_x        通道
  * @param  ADC_ExternalTrigConv 触发源(常用参数ADC_ExternalTrigConv_None，即软件触发)
  * @param  ADC_NbrOfChannel     通道数目(常用参数Channel_1，即单通道)
  * @param  Rank                 采样顺序（常用参数Rank_1,即顺序1）
  * @retval None
  * example:M_ADC_Init(ADC1, ADC_Channel_0, ADC_ExternalTrigConv_None, Channel_1, Rank_1)
  */
void M_ADC_Init(ADC_TypeDef* ADCx, 
			  uint8_t        ADC_Channel_x, 
			  uint32_t       ADC_ExternalTrigConv, 
			  NbrOfChannel   ADC_NbrOfChannel,
			  RANK           Rank)
{
	M_ADC_GPIO_Config(ADCx, ADC_Channel_x);
	//如果是ADC1默认开启DMA传输 
	if(ADCx == ADC1){
		M_ADC_DMA_Config(ADCx); 
	}
	M_ADC_Mode_Config(ADCx, ADC_Channel_x, ADC_Mode_Independent, ADC_ExternalTrigConv, ADC_NbrOfChannel);
	M_ADC_Clock_Config(ADCx, ADC_Channel_x, RCC_PCLK2_Div8, Rank, ADC_SampleTime_55Cycles5);
	//使用软件触发时默认使能
	if(ADC_ExternalTrigConv == ADC_ExternalTrigConv_None){
		ADC_SoftwareStartConvCmd(ADCx, ENABLE);
	}
}

/**
  * @brief  获取ADCx采集结果
  * @param  ADCx ADC模块号
  * @retval None
  * example:M_ADCx_GetValue(ADC2);
  */
  uint16_t M_ADCx_GetValue(ADC_TypeDef* ADCx)
  {
	  return ADC_GetConversionValue(ADCx);
  }
