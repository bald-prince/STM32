/*

*******************************************************************************
================================================================================
【平    台】stm32f103zet6_sumjess平台
【编    写】sumjess
【E-mail  】1371129880@qq.com
【软件版本】V2.0
【最后更新】2018年01月21日
【相关信息参考下列地址】
【网    站】http://www.openedv.com/
           http://www.stmcu.org/
					 http://www.firebbs.cn/forum.php
---------------------------------------------------------------------------------
【dev.env.】MDK5.14及以上版本
【Target  】stm32f103zet6
第一次修订：2017/11/09
第二次修订：2018/01/21
---------------------------------------------------------------------------------
没有完美的代码，只有不断的奉献，大家一起努力；
赠人玫瑰手留余香，欢迎大家反馈bug！
================================================================================
********************************************************************************




DMA步骤 

分布
①-②在void MYDMA_Config(DMA_Channel_TypeDef* DMA_CHx,u32 cpar,u32 cmar,u16 cndtr)
④在void MYDMA_Enable(DMA_Channel_TypeDef*DMA_CHx)



① 使能DMA时钟
   RCC_AHBPeriphClockCmd();
② 初始化DMA通道参数
   DMA_Init();
③使能串口DMA发送,串口DMA使能函数：
  USART_DMACmd();
④使能DMA1通道，启动传输。
   DMA_Cmd();
⑤查询DMA传输状态
  DMA_GetFlagStatus();
⑥获取/设置通道当前剩余数据量：
  DMA_GetCurrDataCounter();
  DMA_SetCurrDataCounter();


void MYDMA_Config(DMA_Channel_TypeDef* DMA_CHx,u32 cpar,u32 cmar,u16 cndtr)
{
 	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1, ENABLE);	//使能DMA传输
	
  DMA_DeInit(DMA_CHx);   //将DMA的通道1寄存器重设为缺省值
	DMA1_MEM_LEN=cndtr;
	DMA_InitStructure.DMA_PeripheralBaseAddr = cpar;  //DMA外设ADC基地址
	DMA_InitStructure.DMA_MemoryBaseAddr = cmar;  //DMA内存基地址
	DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralDST;  //数据传输方向，从内存读取发送到外设
	DMA_InitStructure.DMA_BufferSize = cndtr;  //DMA通道的DMA缓存的大小
	DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;  //外设地址寄存器不变
	DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;  //内存地址寄存器递增
	DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;  //数据宽度为8位
	DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte; //数据宽度为8位
	DMA_InitStructure.DMA_Mode = DMA_Mode_Normal;  //工作在正常缓存模式
	DMA_InitStructure.DMA_Priority = DMA_Priority_Medium; //DMA通道 x拥有中优先级 
	DMA_InitStructure.DMA_M2M = DMA_M2M_Disable;  //DMA通道x没有设置为内存到内存传输
	DMA_Init(DMA_CHx, &DMA_InitStructure);  //根据DMA_InitStruct中指定的参数初始化DMA的通道USART1_Tx_DMA_Channel所标识的寄存器
***第一个参数 DMA_PeripheralBaseAddr 用来设置 DMA 传输的外设基地址，比如要进行串口
DMA 传输，那么外设基地址为串口接受发送数据存储器 USART1->DR 的地址，表示方法为
&USART1->DR。
***第二个参数 DMA_MemoryBaseAddr为内存基地址，也就是我们存放 DMA传输数据的内存地址。
***第三个参数 DMA_DIR 设置数据传输方向，决定是从外设读取数据到内存还送从内存读取数
据发送到外设，也就是外设是源地还是目的地，这里我们设置为从内存读取数据发送到串口，
所以外设自然就是目的地了，所以选择值为 DMA_DIR_PeripheralDST。
***第四个参数 DMA_BufferSize 设置一次传输数据量的大小，这个很容易理解。
***第五个参数 DMA_PeripheralInc 设置传输数据的时候外设地址是不变还是递增。如果设置
为递增，那么下一次传输的时候地址加 1，这里因为我们是一直往固定外设地址&USART1->DR
发送数据，所以地址不递增，值为 DMA_PeripheralInc_Disable；
***第六个参 数 DMA_MemoryInc 设置传输数据时 候内存地址 是否递增。 这个参数和
DMA_PeripheralInc 意思接近，只不过针对的是内存。这里我们的场景是将内存中连续存储单
元的数据发送到串口，毫无疑问内存地址是需要递增的，所以值为 DMA_MemoryInc_Enable。
***第七个参数 DMA_PeripheralDataSize 用来设置外设的的数据长度是为字节传输（8bits），
半字传输 (16bits)还是字传输 (32bits)，这里我们是 8 位字节传输，所以值设置为
DMA_PeripheralDataSize_Byte。
***第八个参数 DMA_MemoryDataSize 是用来设置内存的数据长度，和第七个参数意思接近，这
里我们同样设置为字节传输 DMA_MemoryDataSize_Byte。
***第九个参数节发送到串口，如果设置为重复采集，那么它会在 64 个字节采集完成之后继续从内
存的第一个地址采集，如此循环。这里我们设置为一次连续采集完成之后不循环。所以设置值
为 DMA_Mode_Normal。在我们下面的实验中，如果设置此参数为循环采集，那么你会看到串口
不停的打印数据，不会中断，大家在实验中可以修改这个参数测试一下。
***第十个参数是设置 DMA 通道的优先级，有低，中，高，超高三种模式，这个在前面讲解过，
这里我们设置优先级别为中级，所以值为 DMA_Priority_Medium。如果要开启多个通道，那么
这个值就非常有意义。
***第 十 一 个 参 数 DMA_M2M 设 置 是 否 是 存 储 器 到 存 储 器 模 式 传 输 ， 这 里 我 们 选 择
DMA_M2M_Disable。  	
} 


//开启一次DMA传输
void MYDMA_Enable(DMA_Channel_TypeDef*DMA_CHx)
{ 
	DMA_Cmd(DMA_CHx, DISABLE );  //关闭USART1 TX DMA1 所指示的通道      
 	DMA_SetCurrDataCounter(DMA1_Channel4,DMA1_MEM_LEN);//DMA通道的DMA缓存的大小
 	DMA_Cmd(DMA_CHx, ENABLE);  //使能USART1 TX DMA1 所指示的通道 
}	  
③使能串口 DMA 发送
进行 DMA 配置之后，我们就要开启串口的 DMA 发送功能，使用的函数是：
USART_DMACmd(USART1,USART_DMAReq_Tx,ENABLE);
如果是要使能串口 DMA 接受，那么第二个参数修改为 USART_DMAReq_Rx 即可。


⑤查询 DMA 传输状态
在 DMA 传输过程中，我们要查询 DMA 传输通道的状态，使用的函数是：
FlagStatus DMA_GetFlagStatus(uint32_t DMAy_FLAG)
⑥比如我们要查询 DMA 通道 4 传输是否完成，方法是：
DMA_GetFlagStatus(DMA2_FLAG_TC4);
⑦这里还有一个比较重要的函数就是获取当前剩余数据量大小的函数：
uint16_t DMA_GetCurrDataCounter(DMA_Channel_TypeDef* DMAy_Channelx)
⑧比如我们要获取 DMA 通道 4 还有多少个数据没有传输，方法是：
DMA_GetCurrDataCounter(DMA1_Channel4);
 








#include "led.h"
#include "delay.h"
#include "sys.h"
#include "usart.h"
#include "key.h"
#include "dma.h"

//ALIENTEK Mini STM32开发板范例代码18
//DMA实验  
//技术支持：www.openedv.com
//广州市星翼电子科技有限公司
   	
const u8 TEXT_TO_SEND[]={"ALIENTEK Mini STM32 DMA 串口实验"};
#define TEXT_LENTH  sizeof(TEXT_TO_SEND)-1			//TEXT_TO_SEND字符串长度(不包含结束符)
u8 SendBuff[(TEXT_LENTH+2)*100];//最好是(TEXT_LENTH+2)的整数倍

 int main(void)
 { 
	u16 i;
	u8 t=0; 
	float pro=0;			//进度 
	delay_init();	    	 //延时函数初始化
	uart_init(9600);	 	//串口初始化为9600
	LED_Init();		  		//初始化与LED连接的硬件接口		   	//初始化LCD 
	KEY_Init();				//按键初始化		 	
 	MYDMA_Config(DMA1_Channel4,(u32)&USART1->DR,(u32)SendBuff,(TEXT_LENTH+2)*100);//DMA1通道4,外设为串口1,存储器为SendBuff,长(TEXT_LENTH+2)*100.
 //设置字体为红色 
	//显示提示信息	

							//for语句用来做换行符//  
	for(i=0;i<(TEXT_LENTH+2)*100;i++)//填充ASCII字符集数据
    {
		if(t>=TEXT_LENTH)//加入换行符
		{ 
			SendBuff[i++]=0x0d; 
			SendBuff[i]=0x0a; 
			t=0;
		}else SendBuff[i]=TEXT_TO_SEND[t++];//复制TEXT_TO_SEND语句    
    }		 //设置字体为蓝色	  
	i=0;
		
		
	while(1)
	{
		t=KEY_Scan(0);
		if(t==KEY0_PRES)//KEY0按下
		{
//显示百分号
			printf("\r\nDMA DATA:\r\n "); 	    
		  USART_DMACmd(USART1,USART_DMAReq_Tx,ENABLE); //????1?DMA??        
			MYDMA_Enable(DMA1_Channel4);//开始一次DMA传输！	  
		    //等待DMA传输完成，此时我们来做另外一些事，点灯
		    //实际应用中，传输数据期间，可以执行另外的任务
			LED1=!LED1;
		    while(1)
		    {
				if(DMA_GetFlagStatus(DMA1_FLAG_TC4)!=RESET)//等待通道4传输完成
				{
					DMA_ClearFlag(DMA1_FLAG_TC4);//清除通道4传输完成标志
					break; 
		        }
				pro=DMA_GetCurrDataCounter(DMA1_Channel4);//得到当前还剩余多少个数据
				pro=1-pro/((TEXT_LENTH+2)*100);//得到百分比	  
				pro*=100;      //扩大100倍
				//dayin pro  
		    }			    
//显示100%	  
//提示传送完成
		}
		i++;
		delay_ms(10);
		if(i==20)
		{
			LED0=!LED0;//提示系统正在运行	
			i=0;
		}		   
	}
}









*/


