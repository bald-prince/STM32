/*
DAC��������

*******************************************************************************
================================================================================
��ƽ    ̨��stm32f103zet6_sumjessƽ̨
����    д��sumjess
��E-mail  ��1371129880@qq.com
������汾��V2.0
�������¡�2018��09��06��
�������Ϣ�ο����е�ַ��
����    վ��
           https://blog.csdn.net/qq_38351824
           http://www.openedv.com/
           http://www.stmcu.org/
					 http://www.firebbs.cn/forum.php
---------------------------------------------------------------------------------
��dev.env.��MDK5.14�����ϰ汾
��Target  ��stm32f103zet6
��һ���޶���2017/11/09
�ڶ����޶���2018/01/21
�������޶���2018/09/06
��problem ��
    ��1�����ڲ���Ĳ�ȫ�棻
    ��2�����ڽ��Ͳ��ֲ�ȫ�棻
    ��3�����ڻ�����һ����bug��
��direction��
      ��һ����Ŀ����ǰѿ�������ɣ�
��explain ��
      �����Ǹ�������ԭ�ӡ��о�԰���ӡ����ŵ��ӵ��̼Ҹı���ɣ�
      ͬʱΪ�˷���ʹ�ã���Ҳ�Լ�д�˺ܶ�Ŀ⣬���Ż����㷨�ͱ�ʾ��ʽ��
��warning��
      Ŀǰ���������޾��� ��   
---------------------------------------------------------------------------------
û�������Ĵ��룬ֻ�в��ϵķ��ף����һ��Ŭ����
����õ���������㣬��ӭ��ҷ���bug��
================================================================================
********************************************************************************



1������ PA ��ʱ�ӣ����� PA4 Ϊģ�����롣
STM32F103RCT6 �� DAC ͨ�� 1 �� PA4 �ϣ����ԣ�������Ҫʹ�� PORTA ��ʱ�ӣ�Ȼ
������ PA4 Ϊģ�����롣 DAC ���������������Ϊʲô�˿�Ҫ����Ϊģ������ģʽ�أ���
Ϊһ��ʹ�� DACx ͨ��֮����Ӧ�� GPIO ���ţ�PA4 ���� PA5�����Զ��� DAC ��ģ����
������������Ϊ���룬��Ϊ�˱������ĸ��š�
ʹ�� GPIOA ʱ�ӣ�
RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE ); //ʹ�� PORTA
ʱ��
���� PA1 Ϊģ������ֻ��Ҫ���ó�ʼ���������ɣ�
GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN; //ģ������


2��ʹ�� DAC1 ʱ�ӡ�
ͬ��������һ����Ҫ��ʹ�ã������ȿ�����Ӧ��ʱ�ӡ� STM32 �� DAC ģ��ʱ������
APB1 �ṩ�ģ��������ǵ��ú��� RCC_APB1PeriphClockCmd()���� DAC ģ���ʱ��ʹ�ܡ�
RCC_APB1PeriphClockCmd(RCC_APB1Periph_DAC, ENABLE ); //ʹ�� DAC ͨ��ʱ
��



3�� ��ʼ�� DAC,���� DAC �Ĺ���ģʽ��
�ò�������ȫ��ͨ�� DAC_CR ����ʵ�֣������� DAC ͨ�� 1 ʹ�ܡ� DAC ͨ�� 1 ���
����رա���ʹ�ô�������ʹ�ò��η����������á����� DMA ��ʼ����ͨ������ DAC_Init
��ɵģ�
void DAC_Init(uint32_t DAC_Channel, DAC_InitTypeDef* DAC_InitStruct)
��ǰ��һ�������������������������ýṹ������ DAC_InitTypeDef �Ķ��壺
typedef struct
{
uint32_t DAC_Trigger;ALIENTEK MiniSTM32 V3.0 ������̳�
310
STM32 ����ȫ�ֲᣨ�⺯���棩
uint32_t DAC_WaveGeneration;
uint32_t DAC_LFSRUnmask_TriangleAmplitude;
uint32_t DAC_OutputBuffer;
}DAC_InitTypeDef;
����ṹ��Ķ��廹�ǱȽϼ򵥵ģ�ֻ���ĸ���Ա��������������һһ���⡣
��һ������ DAC_Trigger ���������Ƿ�ʹ�ô������ܣ�ǰ���Ѿ����������ĺ��壬����
���ǲ����ô������ܣ�����ֵΪ DAC_Trigger_None��
�ڶ������� DAC_WaveGeneratio ���������Ƿ�ʹ�ò��η�������������ǰ��ͬ���������
ʹ�á�����ֵΪ DAC_WaveGeneration_None��
���������� DAC_LFSRUnmask_TriangleAmplitude ������������/��ֵѡ�������������ֻ
��ʹ�ò��η�������ʱ������ã�������������Ϊ 0 ���ɣ�ֵΪ DAC_LFSRUnmask_Bit0��
���ĸ����� DAC_OutputBuffer ��������������������λ��ǰ�潲��������ǲ�ʹ�����
���棬����ֵΪ DAC_OutputBuffer_Disable�������ĸ�����������ϡ��������ǵ�ʵ�����룺
DAC_InitTypeDef DAC_InitType;
DAC_InitType.DAC_Trigger=DAC_Trigger_None; //��ʹ�ô������� TEN1=0
DAC_InitType.DAC_WaveGeneration=DAC_WaveGeneration_None;//��ʹ�ò��η���
DAC_InitType.DAC_LFSRUnmask_TriangleAmplitude=DAC_LFSRUnmask_Bit0;
DAC_InitType.DAC_OutputBuffer=DAC_OutputBuffer_Disable ; //DAC1 �������ر�
DAC_Init(DAC_Channel_1,&DAC_InitType); //��ʼ�� DAC ͨ�� 1


4�� ʹ�� DAC ת��ͨ��
��ʼ�� DAC ֮��������ȻҪʹ�� DAC ת��ͨ�����⺯�������ǣ�
DAC_Cmd(DAC_Channel_1, ENABLE); //ʹ�� DAC1


5�� ���� DAC �����ֵ��
ͨ��ǰ�� 4 ����������ã� DAC �Ϳ��Կ�ʼ�����ˣ�����ʹ�� 12 λ�Ҷ������ݸ�ʽ��
��������ͨ������ DHR12R1���Ϳ����� DAC ������ţ�PA4���õ���ͬ�ĵ�ѹֵ�ˡ��⺯
���ĺ����ǣ�
DAC_SetChannel1Data(DAC_Align_12b_R, 0);
��һ���������ö��뷽ʽ������Ϊ 12 λ�Ҷ��� DAC_Align_12b_R�� 12 λ�����
DAC_Align_12b_L �Լ� 8 λ�Ҷ��� DAC_Align_8b_R ��ʽ��
�ڶ����������� DAC ������ֵ�ˣ�����ܺ���⣬��ʼ������Ϊ 0��
6)��������Զ��� DAC ����ֵ�������ǣ�
DAC_GetDataOutputValue(DAC_Channel_1);
���úͶ���һһ��Ӧ�ܺ���⣬����Ͳ��ི���ˡ�
���������һ�´�ң� MiniSTM32 ������Ĳο���ѹֱ�Ӿ��� VDDA���� 3.3V��
ͨ�����ϼ�����������ã����Ǿ���������ʹ�� STM32 �� DAC ͨ�� 1 �������ͬ��
ģ���ѹ�ˡ�



<STM32����ȫ�ֲ�>321 / 600


*/


