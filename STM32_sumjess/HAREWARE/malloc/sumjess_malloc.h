#ifndef __SUMJESS_MALLOC_H
#define __SUMJESS_MALLOC_H
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

#include "sys.h"

#define SRAMEX    1		//外部内存池 
 

//内存参数设定.
#if SRAMEX==0
		#define MEM_BLOCK_SIZE			32  	  						//内存块大小为32字节
		#define MEM_MAX_SIZE			  10*1024  						//最大管理内存 10K
		#define MEM_ALLOC_TABLE_SIZE	MEM_MAX_SIZE/MEM_BLOCK_SIZE 	//内存表大小
#else	
		#define MEM_BLOCK_SIZE			32  	  						//内存块大小为32字节
		#define MEM_MAX_SIZE			  960 *1024           //最大管理内存960K(963.76)    x*1024+x*1024/32*2=1024*1024 x=963.765
		#define MEM_ALLOC_TABLE_SIZE	MEM_MAX_SIZE/MEM_BLOCK_SIZE 	//内存表大小 
#endif	




#ifndef NULL
#define NULL 0
#endif	

//内存管理控制器
struct _m_mallco_dev
{
	void (*init)(void);				//初始化
	u8 (*perused)(void);		  	//内存使用率
	u8 	*membase;					//内存池 
	u16 *memmap; 					//内存管理状态表
	u8  memrdy; 					//内存管理是否就绪
};
extern struct _m_mallco_dev mallco_dev;	//在mallco.c里面定义

void mymemset(void *s,u8 c,u32 count);	//设置内存
void mymemcpy(void *des,void *src,u32 n);//复制内存     
void mem_init(void);					 //内存管理初始化函数(外/内部调用)
u32 mem_malloc(u32 size);		 		//内存分配(内部调用)
u8 mem_free(u32 offset);		 		//内存释放(内部调用)
u8 mem_perused(void);					//得内存使用率(外/内部调用) 


//用户调用函数
void myfree(void *ptr);  				//内存释放(外部调用)
void *mymalloc(u32 size);				//内存分配(外部调用)
void *myrealloc(void *ptr,u32 size);	//重新分配内存(外部调用)
#if SRAMEX==1
		void FSMC_SRAM_Init(void);
		void FSMC_SRAM_WriteBuffer(u8* pBuffer,u32 WriteAddr,u32 NumHalfwordToWrite);
		void FSMC_SRAM_ReadBuffer(u8* pBuffer,u32 ReadAddr,u32 NumHalfwordToRead);
		void fsmc_sram_test_write(u8 data,u32 addr);
		u8 fsmc_sram_test_read(u32 addr);
#endif	


#endif













