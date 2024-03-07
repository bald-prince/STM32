/*

*******************************************************************************
================================================================================
【平    台】stm32f103zet6_sumjess平台
【编    写】sumjess
【E-mail  】1371129880@qq.com
【软件版本】V2.0
【最后更新】2018年09月06日
【相关信息参考下列地址】
【网    站】
           https://blog.csdn.net/qq_38351824
           http://www.openedv.com/
           http://www.stmcu.org/
					 http://www.firebbs.cn/forum.php
---------------------------------------------------------------------------------
【dev.env.】MDK5.14及以上版本
【Target  】stm32f103zet6
第一次修订：2017/11/09
第二次修订：2018/01/21
第三次修订：2018/09/06
【problem 】
    （1）库内补充的不全面；
    （2）库内解释部分不全面；
    （3）库内还存在一定的bug；
【direction】
      下一步的目标就是把库继续集成！
【explain 】
      本库是根据正点原子、中景园电子、优信电子等商家改编而成，
      同时为了方便使用，我也自己写了很多的库，和优化了算法和表示方式！
【warning】
      目前程序中暂无警告 ！   
---------------------------------------------------------------------------------
没有完美的代码，只有不断的奉献，大家一起努力；
赠人玫瑰手留余香，欢迎大家反馈bug！
================================================================================
********************************************************************************




实验目的：ADC1的通道1（PA1)进行单次转化



①开启PA口时钟和ADC1时钟，设置PA1为模拟输入。
      GPIO_Init();如下
			************************************************************
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;		//模拟输入引脚
	GPIO_Init(GPIOA, &GPIO_InitStructure); 
      *************************************************************	
     APB2PeriphClockCmd();如下
	****RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA |RCC_APB2Periph_ADC1	, ENABLE );	  //使能ADC1通道时钟***
****************************************************************************************************************************
②复位ADC1，同时设置ADC1分频因子。
      RCC_ADCCLKConfig(RCC_PCLK2_Div6);
			
		*******RCC_ADCCLKConfig(RCC_PCLK2_Div6);   //设置ADC分频因子6 72M/6=12,ADC最大时间不能超过14M*******

      ADC_DeInit(ADC1);
			
		********ADC_DeInit(ADC1);  //复位ADC1,将外设 ADC1 的全部寄存器重设为缺省值********

③初始化ADC1参数，设置ADC1的工作模式以及规则序列的相关信息。
     void ADC_Init(ADC_TypeDef* ADCx, ADC_InitTypeDef* ADC_InitStruct)；
		 
****************************************************************************************************
	ADC_InitStructure.ADC_Mode = ADC_Mode_Independent;	//ADC工作模式:ADC1和ADC2工作在独立模式
	ADC_InitStructure.ADC_ScanConvMode = DISABLE;	//模数转换工作在单通道模式
	ADC_InitStructure.ADC_ContinuousConvMode = DISABLE;	//模数转换工作在单次转换模式
	ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;	//转换由软件而不是外部触发启动
	ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;	//ADC数据右对齐
	ADC_InitStructure.ADC_NbrOfChannel = 1;	//顺序进行规则转换的ADC通道的数目
	ADC_Init(ADC1, &ADC_InitStructure);	//根据ADC_InitStruct中指定的参数初始化外设ADCx的寄存器
******************************************************************************************************	 
④使能ADC并校准。
     	ADC_Cmd(ADC1, ENABLE);
			
******ADC_Cmd(ADC1, ENABLE);	//使能指定的ADC1********

⑤配置规则通道参数：
     ADC_RegularChannelConfig();
		 
⑥开启软件转换：ADC_SoftwareStartConvCmd(ADC1);

⑦等待转换完成，读取ADC值。
   ADC_GetConversionValue(ADC1);
*****************************************************************************************************
************************************ADC初级阶段直接使用即可********************************************
*********************************以下为测电压**********************************************************
*****************************************************************************************************
	  int main(void)
 { 
	u16 adcx;
	float temp;
	delay_init();	    	 //延时函数初始化	  
	uart_init(9600);	 	//串口初始化为9600
 	Adc_Init();		  		//ADC初始化	    
	while(1)
	{
		adcx=Get_Adc_Average(ADC_Channel_1,10);
		temp=(float)adcx*(3.3/4096);*******************************该处为数据处理，根据外设需要改变**********
		printf("%f",temp);
		delay_ms(250);	
	}											    
}	


















*/



