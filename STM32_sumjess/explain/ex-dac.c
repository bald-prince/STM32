/*
DAC步骤配置

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



1）开启 PA 口时钟，设置 PA4 为模拟输入。
STM32F103RCT6 的 DAC 通道 1 在 PA4 上，所以，我们先要使能 PORTA 的时钟，然
后设置 PA4 为模拟输入。 DAC 本身是输出，但是为什么端口要设置为模拟输入模式呢？因
为一但使能 DACx 通道之后，相应的 GPIO 引脚（PA4 或者 PA5）会自动与 DAC 的模拟输
出相连，设置为输入，是为了避免额外的干扰。
使能 GPIOA 时钟：
RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE ); //使能 PORTA
时钟
设置 PA1 为模拟输入只需要设置初始化参数即可：
GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN; //模拟输入


2）使能 DAC1 时钟。
同其他外设一样，要想使用，必须先开启相应的时钟。 STM32 的 DAC 模块时钟是由
APB1 提供的，所以我们调用函数 RCC_APB1PeriphClockCmd()设置 DAC 模块的时钟使能。
RCC_APB1PeriphClockCmd(RCC_APB1Periph_DAC, ENABLE ); //使能 DAC 通道时
钟



3） 初始化 DAC,设置 DAC 的工作模式。
该部分设置全部通过 DAC_CR 设置实现，包括： DAC 通道 1 使能、 DAC 通道 1 输出
缓存关闭、不使用触发、不使用波形发生器等设置。这里 DMA 初始化是通过函数 DAC_Init
完成的：
void DAC_Init(uint32_t DAC_Channel, DAC_InitTypeDef* DAC_InitStruct)
跟前面一样，首先我们来看看参数设置结构体类型 DAC_InitTypeDef 的定义：
typedef struct
{
uint32_t DAC_Trigger;ALIENTEK MiniSTM32 V3.0 开发板教程
310
STM32 不完全手册（库函数版）
uint32_t DAC_WaveGeneration;
uint32_t DAC_LFSRUnmask_TriangleAmplitude;
uint32_t DAC_OutputBuffer;
}DAC_InitTypeDef;
这个结构体的定义还是比较简单的，只有四个成员变量，下面我们一一讲解。
第一个参数 DAC_Trigger 用来设置是否使用触发功能，前面已经讲解过这个的含义，这里
我们不是用触发功能，所以值为 DAC_Trigger_None。
第二个参数 DAC_WaveGeneratio 用来设置是否使用波形发生，这里我们前面同样讲解过不
使用。所以值为 DAC_WaveGeneration_None。
第三个参数 DAC_LFSRUnmask_TriangleAmplitude 用来设置屏蔽/幅值选择器，这个变量只
在使用波形发生器的时候才有用，这里我们设置为 0 即可，值为 DAC_LFSRUnmask_Bit0。
第四个参数 DAC_OutputBuffer 是用来设置输出缓存控制位，前面讲解过，我们不使用输出
缓存，所以值为 DAC_OutputBuffer_Disable。到此四个参数设置完毕。看看我们的实例代码：
DAC_InitTypeDef DAC_InitType;
DAC_InitType.DAC_Trigger=DAC_Trigger_None; //不使用触发功能 TEN1=0
DAC_InitType.DAC_WaveGeneration=DAC_WaveGeneration_None;//不使用波形发生
DAC_InitType.DAC_LFSRUnmask_TriangleAmplitude=DAC_LFSRUnmask_Bit0;
DAC_InitType.DAC_OutputBuffer=DAC_OutputBuffer_Disable ; //DAC1 输出缓存关闭
DAC_Init(DAC_Channel_1,&DAC_InitType); //初始化 DAC 通道 1


4） 使能 DAC 转换通道
初始化 DAC 之后，理所当然要使能 DAC 转换通道，库函数方法是：
DAC_Cmd(DAC_Channel_1, ENABLE); //使能 DAC1


5） 设置 DAC 的输出值。
通过前面 4 个步骤的设置， DAC 就可以开始工作了，我们使用 12 位右对齐数据格式，
所以我们通过设置 DHR12R1，就可以在 DAC 输出引脚（PA4）得到不同的电压值了。库函
数的函数是：
DAC_SetChannel1Data(DAC_Align_12b_R, 0);
第一个参数设置对齐方式，可以为 12 位右对齐 DAC_Align_12b_R， 12 位左对齐
DAC_Align_12b_L 以及 8 位右对齐 DAC_Align_8b_R 方式。
第二个参数就是 DAC 的输入值了，这个很好理解，初始化设置为 0。
6)这里，还可以读出 DAC 的数值，函数是：
DAC_GetDataOutputValue(DAC_Channel_1);
设置和读出一一对应很好理解，这里就不多讲解了。
最后，再提醒一下大家， MiniSTM32 开发板的参考电压直接就是 VDDA，即 3.3V。
通过以上几个步骤的设置，我们就能正常的使用 STM32 的 DAC 通道 1 来输出不同的
模拟电压了。



<STM32不完全手册>321 / 600


*/


