#include "M_STM32_AD.h"

//ADC1�������(DMA��ʽ���ռ��С5000,һ�βɼ�5000������)
__IO uint16_t ADC1_ConvertedValue[5000]={0};

/**
  * @brief  ADCx���ų�ʼ��
  * @param  ADCx:ADģ���
  * @param  ADC_Channel_x ͨ����  
  * @retval None
  */
  void M_ADC_GPIO_Config(ADC_TypeDef* ADCx, uint8_t ADC_Channel_x)
  {
	  GPIO_InitTypeDef GPIO_InitStructure;
	  
	  if(ADCx == ADC1){
		  if(ADC_Channel_x == ADC_Channel_0){
			  //����ʱ�Ӻ͸��ù���ʱ��
			  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_AFIO, ENABLE);
			  
			  GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_0;	//��������
			  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN; //����ģʽΪģ������
			  GPIO_Init(GPIOA, &GPIO_InitStructure);        //��ʼ�����ò���
		  }
		  else if(ADC_Channel_x == ADC_Channel_1){
			  //����ʱ�Ӻ͸��ù���ʱ��
			  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_AFIO, ENABLE);
			  
			  GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_1;	//��������
			  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN; //����ģʽΪģ������
			  GPIO_Init(GPIOA, &GPIO_InitStructure);        //��ʼ�����ò���
		  }
		  else if(ADC_Channel_x == ADC_Channel_2){
			  //����ʱ�Ӻ͸��ù���ʱ��
			  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_AFIO, ENABLE);
			  
			  GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_2;	//��������
			  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN; //����ģʽΪģ������
			  GPIO_Init(GPIOA, &GPIO_InitStructure);        //��ʼ�����ò���
		  }
		  else if(ADC_Channel_x == ADC_Channel_3){
			  //����ʱ�Ӻ͸��ù���ʱ��
			  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_AFIO, ENABLE);
			  
			  GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_3;	//��������
			  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN; //����ģʽΪģ������
			  GPIO_Init(GPIOA, &GPIO_InitStructure);        //��ʼ�����ò���
		  }
		  else if(ADC_Channel_x == ADC_Channel_4){
			  //����ʱ�Ӻ͸��ù���ʱ��
			  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_AFIO, ENABLE);
			  
			  GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_4;	//��������
			  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN; //����ģʽΪģ������
			  GPIO_Init(GPIOA, &GPIO_InitStructure);        //��ʼ�����ò���
		  }
		  else if(ADC_Channel_x == ADC_Channel_5){
			  //����ʱ�Ӻ͸��ù���ʱ��
			  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_AFIO, ENABLE);
			  
			  GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_5;	//��������
			  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN; //����ģʽΪģ������
			  GPIO_Init(GPIOA, &GPIO_InitStructure);        //��ʼ�����ò���
		  }
		  else if(ADC_Channel_x == ADC_Channel_6){
			  //����ʱ�Ӻ͸��ù���ʱ��
			  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_AFIO, ENABLE);
			  
			  GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_6;	//��������
			  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN; //����ģʽΪģ������
			  GPIO_Init(GPIOA, &GPIO_InitStructure);        //��ʼ�����ò���
		  }
		  else if(ADC_Channel_x == ADC_Channel_7){
			  //����ʱ�Ӻ͸��ù���ʱ��
			  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_AFIO, ENABLE);
			  
			  GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_7;	//��������
			  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN; //����ģʽΪģ������
			  GPIO_Init(GPIOA, &GPIO_InitStructure);        //��ʼ�����ò���
		  }
		  else if(ADC_Channel_x == ADC_Channel_8){
			  //����ʱ�Ӻ͸��ù���ʱ��
			  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB | RCC_APB2Periph_AFIO, ENABLE);
			  
			  GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_0;	//��������
			  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN; //����ģʽΪģ������
			  GPIO_Init(GPIOB, &GPIO_InitStructure);        //��ʼ�����ò���
		  }
		  else if(ADC_Channel_x == ADC_Channel_9){
			  //����ʱ�Ӻ͸��ù���ʱ��
			  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB | RCC_APB2Periph_AFIO, ENABLE);
			  
			  GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_1;	//��������
			  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN; //����ģʽΪģ������
			  GPIO_Init(GPIOB, &GPIO_InitStructure);        //��ʼ�����ò���
		  }
		  else if(ADC_Channel_x == ADC_Channel_10){
			  //����ʱ�Ӻ͸��ù���ʱ��
			  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);
			  
			  GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_0;	//��������
			  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN; //����ģʽΪģ������
			  GPIO_Init(GPIOC, &GPIO_InitStructure);        //��ʼ�����ò���
		  }
		  else if(ADC_Channel_x == ADC_Channel_11){
			  //����ʱ�Ӻ͸��ù���ʱ��
			  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);
			  
			  GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_1;	//��������
			  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN; //����ģʽΪģ������
			  GPIO_Init(GPIOC, &GPIO_InitStructure);        //��ʼ�����ò���
		  }
		  else if(ADC_Channel_x == ADC_Channel_12){
			  //����ʱ�Ӻ͸��ù���ʱ��
			  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);
			  
			  GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_2;	//��������
			  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN; //����ģʽΪģ������
			  GPIO_Init(GPIOC, &GPIO_InitStructure);        //��ʼ�����ò���
		  }
		  else if(ADC_Channel_x == ADC_Channel_13){
			  //����ʱ�Ӻ͸��ù���ʱ��
			  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);
			  
			  GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_3;	//��������
			  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN; //����ģʽΪģ������
			  GPIO_Init(GPIOC, &GPIO_InitStructure);        //��ʼ�����ò���
		  }
		  else if(ADC_Channel_x == ADC_Channel_14){
			  //����ʱ�Ӻ͸��ù���ʱ��
			  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);
			  
			  GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_4;	//��������
			  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN; //����ģʽΪģ������
			  GPIO_Init(GPIOC, &GPIO_InitStructure);        //��ʼ�����ò���
		  }
		  else if(ADC_Channel_x == ADC_Channel_15){
			  //����ʱ�Ӻ͸��ù���ʱ��
			  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);
			  
			  GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_5;	//��������
			  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN; //����ģʽΪģ������
			  GPIO_Init(GPIOC, &GPIO_InitStructure);        //��ʼ�����ò���
		  }
	  }
	  else if(ADCx == ADC2){
		  if(ADC_Channel_x == ADC_Channel_0){
			  //����ʱ�Ӻ͸��ù���ʱ��
			  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_AFIO, ENABLE);
			  
			  GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_0;	//��������
			  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN; //����ģʽΪģ������
			  GPIO_Init(GPIOA, &GPIO_InitStructure);        //��ʼ�����ò���
		  }
		  else if(ADC_Channel_x == ADC_Channel_1){
			  //����ʱ�Ӻ͸��ù���ʱ��
			  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_AFIO, ENABLE);
			  
			  GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_1;	//��������
			  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN; //����ģʽΪģ������
			  GPIO_Init(GPIOA, &GPIO_InitStructure);        //��ʼ�����ò���
		  }
		  else if(ADC_Channel_x == ADC_Channel_2){
			  //����ʱ�Ӻ͸��ù���ʱ��
			  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_AFIO, ENABLE);
			  
			  GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_2;	//��������
			  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN; //����ģʽΪģ������
			  GPIO_Init(GPIOA, &GPIO_InitStructure);        //��ʼ�����ò���
		  }
		  else if(ADC_Channel_x == ADC_Channel_3){
			  //����ʱ�Ӻ͸��ù���ʱ��
			  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_AFIO, ENABLE);
			  
			  GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_3;	//��������
			  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN; //����ģʽΪģ������
			  GPIO_Init(GPIOA, &GPIO_InitStructure);        //��ʼ�����ò���
		  }
		  else if(ADC_Channel_x == ADC_Channel_4){
			  //����ʱ�Ӻ͸��ù���ʱ��
			  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_AFIO, ENABLE);
			  
			  GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_4;	//��������
			  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN; //����ģʽΪģ������
			  GPIO_Init(GPIOA, &GPIO_InitStructure);        //��ʼ�����ò���
		  }
		  else if(ADC_Channel_x == ADC_Channel_5){
			  //����ʱ�Ӻ͸��ù���ʱ��
			  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_AFIO, ENABLE);
			  
			  GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_5;	//��������
			  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN; //����ģʽΪģ������
			  GPIO_Init(GPIOA, &GPIO_InitStructure);        //��ʼ�����ò���
		  }
		  else if(ADC_Channel_x == ADC_Channel_6){
			  //����ʱ�Ӻ͸��ù���ʱ��
			  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_AFIO, ENABLE);
			  
			  GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_6;	//��������
			  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN; //����ģʽΪģ������
			  GPIO_Init(GPIOA, &GPIO_InitStructure);        //��ʼ�����ò���
		  }
		  else if(ADC_Channel_x == ADC_Channel_7){
			  //����ʱ�Ӻ͸��ù���ʱ��
			  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_AFIO, ENABLE);
			  
			  GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_7;	//��������
			  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN; //����ģʽΪģ������
			  GPIO_Init(GPIOA, &GPIO_InitStructure);        //��ʼ�����ò���
		  }
		  else if(ADC_Channel_x == ADC_Channel_8){
			  //����ʱ�Ӻ͸��ù���ʱ��
			  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB | RCC_APB2Periph_AFIO, ENABLE);
			  
			  GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_0;	//��������
			  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN; //����ģʽΪģ������
			  GPIO_Init(GPIOB, &GPIO_InitStructure);        //��ʼ�����ò���
		  }
		  else if(ADC_Channel_x == ADC_Channel_9){
			  //����ʱ�Ӻ͸��ù���ʱ��
			  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB | RCC_APB2Periph_AFIO, ENABLE);
			  
			  GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_1;	//��������
			  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN; //����ģʽΪģ������
			  GPIO_Init(GPIOB, &GPIO_InitStructure);        //��ʼ�����ò���
		  }
		  else if(ADC_Channel_x == ADC_Channel_10){
			  //����ʱ�Ӻ͸��ù���ʱ��
			  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);
			  
			  GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_0;	//��������
			  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN; //����ģʽΪģ������
			  GPIO_Init(GPIOC, &GPIO_InitStructure);        //��ʼ�����ò���
		  }
		  else if(ADC_Channel_x == ADC_Channel_11){
			  //����ʱ�Ӻ͸��ù���ʱ��
			  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);
			  
			  GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_1;	//��������
			  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN; //����ģʽΪģ������
			  GPIO_Init(GPIOC, &GPIO_InitStructure);        //��ʼ�����ò���
		  }
		  else if(ADC_Channel_x == ADC_Channel_12){
			  //����ʱ�Ӻ͸��ù���ʱ��
			  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);
			  
			  GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_2;	//��������
			  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN; //����ģʽΪģ������
			  GPIO_Init(GPIOC, &GPIO_InitStructure);        //��ʼ�����ò���
		  }
		  else if(ADC_Channel_x == ADC_Channel_13){
			  //����ʱ�Ӻ͸��ù���ʱ��
			  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);
			  
			  GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_3;	//��������
			  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN; //����ģʽΪģ������
			  GPIO_Init(GPIOC, &GPIO_InitStructure);        //��ʼ�����ò���
		  }
		  else if(ADC_Channel_x == ADC_Channel_14){
			  //����ʱ�Ӻ͸��ù���ʱ��
			  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);
			  
			  GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_4;	//��������
			  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN; //����ģʽΪģ������
			  GPIO_Init(GPIOC, &GPIO_InitStructure);        //��ʼ�����ò���
		  }
		  else if(ADC_Channel_x == ADC_Channel_15){
			  //����ʱ�Ӻ͸��ù���ʱ��
			  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);
			  
			  GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_5;	//��������
			  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN; //����ģʽΪģ������
			  GPIO_Init(GPIOC, &GPIO_InitStructure);        //��ʼ�����ò���
		  }
	  }
  }

 /**
  * @brief  ADCx����ģʽ����
  * @param  ADCx:         ADģ���
  * @param  ADC_Channel_x ͨ����
  * @param  ADC_Mode      ����ģʽ
  * @param  ADC_ExternalTrigConv ����ģʽ
  * @param  ADC_NbrOfChannel     ת��ͨ��
  * @retval None
  */
  void M_ADC_Mode_Config(ADC_TypeDef* ADCx, 
	                     uint8_t      ADC_Channel_x, 
	                     uint32_t     ADC_Mode, 
                         uint32_t     ADC_ExternalTrigConv,
						 NbrOfChannel ADC_NbrOfChannel)
  {
	  ADC_InitTypeDef ADC_InitStructure;
	  
	  //����ADCʱ��
	  if(ADCx == ADC1){
		  RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1, ENABLE);
	  }
	  else if(ADCx == ADC2){
		  RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC2, ENABLE);
	  }
	  
	  //ADCģʽ����
	  ADC_InitStructure.ADC_Mode               = ADC_Mode;             //����ģʽ���ã������ģʽADC_Mode_Independent
	  ADC_InitStructure.ADC_ScanConvMode       = ENABLE;               //����ɨ��
	  ADC_InitStructure.ADC_ContinuousConvMode = ENABLE;               //����ת��
	  ADC_InitStructure.ADC_ExternalTrigConv   = ADC_ExternalTrigConv; //����Դ
	  ADC_InitStructure.ADC_DataAlign          = ADC_DataAlign_Right;  //�����Ҷ���
	  ADC_InitStructure.ADC_NbrOfChannel       = ADC_NbrOfChannel;     //ת��ͨ������
	  ADC_Init(ADCx, &ADC_InitStructure);                              //ADC��ʼ��
  }
  
/**
  * @brief  ADCxʱ������
  * @param  ADCx:          ADģ���
  * @param  ADC_Channel_x  ͨ����
  * @param  ADC_PCLK_DIVx  ʱ�ӷ�Ƶ
  * @param  Rank           ת��˳��
  * @param  ADC_SampleTime ����ʱ��
  * @retval None
  */
void M_ADC_Clock_Config(ADC_TypeDef* ADCx, uint8_t ADC_Channel_x, uint32_t ADC_PCLK_DIVx, RANK Rank, uint8_t ADC_SampleTime)
{
	//����ADCʱ�ӷ�Ƶ
	if(ADCx == ADC1){
		RCC_ADCCLKConfig(ADC_PCLK_DIVx);
	}
	else if(ADCx == ADC2){
		RCC_ADCCLKConfig(ADC_PCLK_DIVx);
	}
	
	//����ADCͨ����ת��˳�򼰲���ʱ��
	ADC_RegularChannelConfig(ADCx, ADC_Channel_x, Rank, ADC_SampleTime); 
	
	//����ADC1�Ļ�Ĭ�Ͽ���DMA����
	if(ADCx == ADC1){
		ADC_DMACmd(ADC1, ENABLE);
	}
	
	//����ADC������ʼת��
	ADC_Cmd(ADCx, ENABLE);
	
	//ADCУ׼
	ADC_ResetCalibration(ADCx);
	while(ADC_GetResetCalibrationStatus(ADCx));
	ADC_StartCalibration(ADCx);
	while(ADC_GetCalibrationStatus(ADCx));
}

/**
  * @brief  ADC_DMA����
  * @param  ADCx:ADģ���
  * @retval None
  */
void M_ADC_DMA_Config(ADC_TypeDef* ADCx)
{
	DMA_InitTypeDef DMA_InitStructure;
	
	//����DMAʱ��
	if(ADCx == ADC1){
		RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1, ENABLE);
	}
	
	DMA_DeInit(DMA1_Channel1); //��λDMA
	
	//DMA������ʽ����
	DMA_InitStructure.DMA_PeripheralBaseAddr = (u32)(&(ADCx->DR));              //�������ַ
	DMA_InitStructure.DMA_MemoryBaseAddr     = (u32)ADC1_ConvertedValue;        //�洢����ַ
	DMA_InitStructure.DMA_DIR                = DMA_DIR_PeripheralSRC;           //����Դ
	DMA_InitStructure.DMA_BufferSize         = 5000;                  //��������С
	DMA_InitStructure.DMA_PeripheralInc      = DMA_PeripheralInc_Disable;       //�����ַ������
	DMA_InitStructure.DMA_MemoryInc          = DMA_MemoryInc_Enable;            //�ڴ��ַ����
	DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_HalfWord; //�����ַ��λ
	DMA_InitStructure.DMA_MemoryDataSize     = DMA_MemoryDataSize_HalfWord;     //�ڴ��ַ��λ
	DMA_InitStructure.DMA_Mode               = DMA_Mode_Circular;               //ѭ������
	DMA_InitStructure.DMA_Priority           = DMA_Priority_Medium;             //���ȼ�
	DMA_InitStructure.DMA_M2M                = DMA_M2M_Disable;                 //��ֹ�ڴ浽�ڴ�Ĵ���
	DMA_Init(DMA1_Channel1, &DMA_InitStructure);                                //��ʼ������
	DMA_Cmd(DMA1_Channel1, ENABLE);                                             //ʹ��DMA
}

/**
  * @brief  ADCx��ʼ��
  * @param  ADCx:                ADģ���
  * @param  ADC_Channel_x        ͨ��
  * @param  ADC_ExternalTrigConv ����Դ(���ò���ADC_ExternalTrigConv_None�����������)
  * @param  ADC_NbrOfChannel     ͨ����Ŀ(���ò���Channel_1������ͨ��)
  * @param  Rank                 ����˳�򣨳��ò���Rank_1,��˳��1��
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
	//�����ADC1Ĭ�Ͽ���DMA���� 
	if(ADCx == ADC1){
		M_ADC_DMA_Config(ADCx); 
	}
	M_ADC_Mode_Config(ADCx, ADC_Channel_x, ADC_Mode_Independent, ADC_ExternalTrigConv, ADC_NbrOfChannel);
	M_ADC_Clock_Config(ADCx, ADC_Channel_x, RCC_PCLK2_Div8, Rank, ADC_SampleTime_55Cycles5);
	//ʹ���������ʱĬ��ʹ��
	if(ADC_ExternalTrigConv == ADC_ExternalTrigConv_None){
		ADC_SoftwareStartConvCmd(ADCx, ENABLE);
	}
}

/**
  * @brief  ��ȡADCx�ɼ����
  * @param  ADCx ADCģ���
  * @retval None
  * example:M_ADCx_GetValue(ADC2);
  */
  uint16_t M_ADCx_GetValue(ADC_TypeDef* ADCx)
  {
	  return ADC_GetConversionValue(ADCx);
  }
