/*******************************************************************************
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
********************************************************************************/	
//内存占用 驱动代码

#include "sumjess_malloc.h"	    

//内存池(4字节对齐)
#if SRAMEX==1
		__align(32) u8 membase[MEM_MAX_SIZE]  __attribute__((at(0X68000000)));					     //外部SRAM内存池
		u16 memmapbase[MEM_ALLOC_TABLE_SIZE] __attribute__((at(0X68000000+MEM_MAX_SIZE))); //外部SRAM内存池MAP
#else
		__align(32) u8 membase[MEM_MAX_SIZE];			   //SRAM内存池
		u16 memmapbase[MEM_ALLOC_TABLE_SIZE];			   //SRAM内存池MAP
#endif	



//内存管理参数	   
const u32 memtblsize=MEM_ALLOC_TABLE_SIZE;		//内存表大小
const u32 memblksize=MEM_BLOCK_SIZE;			    //内存分块大小
const u32 memsize   =MEM_MAX_SIZE;					  //内存总大小


//内存管理控制器
struct _m_mallco_dev mallco_dev=
{
	mem_init,			//内存初始化
	mem_perused,		//内存使用率
	membase,			//内存池
	memmapbase,			//内存管理状态表
	0,  				//内存管理未就绪
};

//复制内存
//*des:目的地址
//*src:源地址
//n:需要复制的内存长度(字节为单位)
void mymemcpy(void *des,void *src,u32 n)  
{  
    u8 *xdes=des;
	  u8 *xsrc=src; 
    while(n--)*xdes++=*xsrc++;  
}  
//设置内存
//*s:内存首地址
//c :要设置的值
//count:需要设置的内存大小(字节为单位)
void mymemset(void *s,u8 c,u32 count)  
{  
    u8 *xs = s;  
    while(count--)*xs++=c;  
}	   
//内存管理初始化  
void mem_init(void)  
{  
#if SRAMEX==1
		FSMC_SRAM_Init();			//初始化外部SRAM 
#endif
		mymemset(mallco_dev.memmap, 0,memtblsize*2);//内存状态表数据清零  
		mymemset(mallco_dev.membase, 0,memsize);	//内存池所有数据清零  
		mallco_dev.memrdy=1;						//内存管理初始化OK  
}  
//获取内存使用率
//返回值:使用率(0~100)
u8 mem_perused(void)  
{  
    u32 used=0,i;  
    for(i=0;i<memtblsize;i++)  
        if(mallco_dev.memmap[i])used++; 
    return (used*100)/(memtblsize);  
}  
//内存分配(内部调用)
//memx:所属内存块
//size:要分配的内存大小(字节)
//返回值:0XFFFFFFFF,代表错误;其他,内存偏移地址 
u32 mem_malloc(u32 size)  
{  
    signed long offset=0;  
    u16 nmemb;	//需要的内存块数  
	  u16 cmemb=0;//连续空内存块数
    u32 i;  
    if(!mallco_dev.memrdy)mallco_dev.init();	//未初始化,先执行初始化 
    if(size==0)return 0XFFFFFFFF;				//不需要分配
    nmemb=size/memblksize;  					//获取需要分配的连续内存块数
    if(size%memblksize)nmemb++;  
    for(offset=memtblsize-1;offset>=0;offset--)	//搜索整个内存控制区  
    {     
				if(!mallco_dev.memmap[offset])cmemb++;	//连续空内存块数增加
				else cmemb=0;							//连续内存块清零
				if(cmemb==nmemb)						//找到了连续nmemb个空内存块
				{
								for(i=0;i<nmemb;i++)  				//标注内存块非空  
										mallco_dev.memmap[offset+i]=nmemb;  
								return (offset*memblksize);			//返回偏移地址  
				}
    }  
    return 0XFFFFFFFF;//未找到符合分配条件的内存块  
}  
//释放内存(内部调用) 
//offset:内存地址偏移
//返回值:0,释放成功;1,释放失败;  
u8 mem_free(u32 offset)  
{  
    int i;  
    if(!mallco_dev.memrdy)//未初始化,先执行初始化
	  {
		    mallco_dev.init();    
        return 1;//未初始化  
    }  
    if(offset<memsize)//偏移在内存池内. 
    {  
        int index=offset/memblksize;		//偏移所在内存块号码  
        int nmemb=mallco_dev.memmap[index];	//内存块数量
        for(i=0;i<nmemb;i++)  				//内存块清零
            mallco_dev.memmap[index+i]=0;  
        return 0;  
    }else return 2;//偏移超区了.  
}  
//释放内存(外部调用) 
//ptr:内存首地址 
void myfree(void *ptr)  
{  
	  u32 offset;  
    if(ptr==NULL)return;//地址为0.  
 	  offset=(u32)ptr-(u32)mallco_dev.membase;  
    mem_free(offset);	//释放内存     
}  
//分配内存(外部调用)
//size:内存大小(字节)
//返回值:分配到的内存首地址.
void *mymalloc(u32 size)  
{  
    u32 offset;  									      
	  offset=mem_malloc(size);  	   				   
    if(offset==0XFFFFFFFF)return NULL;  
    else return (void*)((u32)mallco_dev.membase+offset);  
}  
//重新分配内存(外部调用)
//*ptr:旧内存首地址
//size:要分配的内存大小(字节)
//返回值:新分配到的内存首地址.
void *myrealloc(void *ptr,u32 size)  
{  
    u32 offset;  
    offset=mem_malloc(size);  
    if(offset==0XFFFFFFFF)return NULL;     
    else  
    {  									   
	      mymemcpy((void*)((u32)mallco_dev.membase+offset),ptr,size);	//拷贝旧内存内容到新内存   
        myfree(ptr);  											  	//释放旧内存
        return (void*)((u32)mallco_dev.membase+offset);  			//返回新内存首地址
    }  
}

#if SRAMEX==1
//使用NOR/SRAM的 BANK 4,地址位HADDR[27,26]=10 
//对IS61LV25616/IS62WV25616,地址线范围为A0~A17 
//对IS61LV51216/IS62WV51216,地址线范围为A0~A18
#define Bank1_SRAM3_ADDR    ((u32)(0x60000000 | 0x08000000))	
  						   
//初始化外部SRAM
void FSMC_SRAM_Init(void)
{	
	FSMC_NORSRAMInitTypeDef  FSMC_NORSRAMInitStructure;
	FSMC_NORSRAMTimingInitTypeDef  readWriteTiming;
	GPIO_InitTypeDef  GPIO_InitStructure;
 
 	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD|RCC_APB2Periph_GPIOE|RCC_APB2Periph_GPIOF|RCC_APB2Periph_GPIOG,ENABLE);
  RCC_AHBPeriphClockCmd(RCC_AHBPeriph_FSMC,ENABLE);
  
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;


	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0  | GPIO_Pin_1  | GPIO_Pin_4  | GPIO_Pin_5
	                            | GPIO_Pin_8  | GPIO_Pin_9  | GPIO_Pin_10 | GPIO_Pin_11 
						                  | GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15;
								
	GPIO_Init(GPIOD, &GPIO_InitStructure);

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0  | GPIO_Pin_1  | GPIO_Pin_7  | GPIO_Pin_8
	                            | GPIO_Pin_9  | GPIO_Pin_10 | GPIO_Pin_11 | GPIO_Pin_12 
						                  | GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15;
								
	GPIO_Init(GPIOE, &GPIO_InitStructure);

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0  | GPIO_Pin_1  | GPIO_Pin_2  | GPIO_Pin_3
	                            | GPIO_Pin_4  | GPIO_Pin_5  | GPIO_Pin_12 
						                  | GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15; 
	
  GPIO_Init(GPIOF, &GPIO_InitStructure);

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0  | GPIO_Pin_1  | GPIO_Pin_2  | GPIO_Pin_3 
	                             | GPIO_Pin_4 | GPIO_Pin_5 |  GPIO_Pin_10; 

	GPIO_Init(GPIOG, &GPIO_InitStructure);
 
	 			  	  
	readWriteTiming.FSMC_AddressSetupTime = 0x00;	 //地址建立时间（ADDSET）为1个HCLK 1/36M=27ns
	readWriteTiming.FSMC_AddressHoldTime = 0x00;	 //地址保持时间（ADDHLD）模式A未用到	
	readWriteTiming.FSMC_DataSetupTime = 0x03;		 //数据保持时间（DATAST）为3个HCLK 4/72M=55ns(对EM的SRAM芯片)	 
	readWriteTiming.FSMC_BusTurnAroundDuration = 0x00;
	readWriteTiming.FSMC_CLKDivision = 0x00;
	readWriteTiming.FSMC_DataLatency = 0x00;
	readWriteTiming.FSMC_AccessMode = FSMC_AccessMode_A;	 //模式A 



	FSMC_NORSRAMInitStructure.FSMC_Bank = FSMC_Bank1_NORSRAM3;//  这里我们使用NE3 ，也就对应BTCR[4],[5]。
	FSMC_NORSRAMInitStructure.FSMC_DataAddressMux = FSMC_DataAddressMux_Disable; 
	FSMC_NORSRAMInitStructure.FSMC_MemoryType =FSMC_MemoryType_SRAM;// FSMC_MemoryType_SRAM;  //SRAM   
	FSMC_NORSRAMInitStructure.FSMC_MemoryDataWidth = FSMC_MemoryDataWidth_16b;//存储器数据宽度为16bit  
	FSMC_NORSRAMInitStructure.FSMC_BurstAccessMode =FSMC_BurstAccessMode_Disable;// FSMC_BurstAccessMode_Disable; 
	FSMC_NORSRAMInitStructure.FSMC_WaitSignalPolarity = FSMC_WaitSignalPolarity_Low;
	FSMC_NORSRAMInitStructure.FSMC_AsynchronousWait=FSMC_AsynchronousWait_Disable;
	FSMC_NORSRAMInitStructure.FSMC_WrapMode = FSMC_WrapMode_Disable;   
	FSMC_NORSRAMInitStructure.FSMC_WaitSignalActive = FSMC_WaitSignalActive_BeforeWaitState;  
	FSMC_NORSRAMInitStructure.FSMC_WriteOperation = FSMC_WriteOperation_Enable;	//存储器写使能 
	FSMC_NORSRAMInitStructure.FSMC_WaitSignal = FSMC_WaitSignal_Disable;  
	FSMC_NORSRAMInitStructure.FSMC_ExtendedMode = FSMC_ExtendedMode_Disable; // 读写使用相同的时序
	FSMC_NORSRAMInitStructure.FSMC_WriteBurst = FSMC_WriteBurst_Disable;  
	FSMC_NORSRAMInitStructure.FSMC_ReadWriteTimingStruct = &readWriteTiming;
	FSMC_NORSRAMInitStructure.FSMC_WriteTimingStruct = &readWriteTiming; //读写同样时序

	FSMC_NORSRAMInit(&FSMC_NORSRAMInitStructure);  //初始化FSMC配置

	FSMC_NORSRAMCmd(FSMC_Bank1_NORSRAM3, ENABLE);  // 使能BANK3										  
											
}
	  														  
//在指定地址开始,连续写入n个字节.
//pBuffer:字节指针
//WriteAddr:要写入的地址
//n:要写入的字节数
void FSMC_SRAM_WriteBuffer(u8* pBuffer,u32 WriteAddr,u32 n)
{
	for(;n!=0;n--)  
	{										    
		*(vu8*)(Bank1_SRAM3_ADDR+WriteAddr)=*pBuffer;	  
		WriteAddr++; 
		pBuffer++;
	}   
}																			    
//在指定地址开始,连续读出n个字节.
//pBuffer:字节指针
//ReadAddr:要读出的起始地址
//n:要写入的字节数
void FSMC_SRAM_ReadBuffer(u8* pBuffer,u32 ReadAddr,u32 n)
{
	for(;n!=0;n--)  
	{											    
		*pBuffer++=*(vu8*)(Bank1_SRAM3_ADDR+ReadAddr);    
		ReadAddr++; 
	}  
} 
////////////////////////////////////////////////////////////////////////////////////////
//测试函数
//在指定地址写入1个字节
//addr:地址
//data:要写入的数据
void fsmc_sram_test_write(u8 data,u32 addr)
{			   
	FSMC_SRAM_WriteBuffer(&data,addr,1);//写入1个字节
}
//读取1个字节
//addr:要读取的地址
//返回值:读取到的数据
u8 fsmc_sram_test_read(u32 addr)
{
	u8 data;
	FSMC_SRAM_ReadBuffer(&data,addr,1);
	return data;
}	
#endif	






