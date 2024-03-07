#ifndef __BSP_IAP_H__
#define	__BSP_IAP_H__

/* 包含头文件 ----------------------------------------------------------------*/
#include "stm32f1xx_hal.h"

/* 类型定义 ------------------------------------------------------------------*/
/************************** IAP 数据类型定义********************************/
typedef  void ( * pIapFun_TypeDef ) ( void ); //定义一个函数类型的参数.

#define APP_Len_ADDR	0x807BFFE
#define APP_UpdateFlag_ADDR	0x807C000
/* 宏定义 --------------------------------------------------------------------*/
/************************** IAP 宏参数定义********************************/
 //是否更新 APP 到 FLASH，否则更新到 RAM
#define User_Flash                                        

#define APPSIZE			224*1024			//224K


#ifdef User_Flash
#define APP_START_ADDR       	0x800C000//0x8010000  	//应用程序起始地址(存放在FLASH APP缓冲区)
#define APP_Temp_ADDR       	0x8044000//0x8010000  	//应用程序起始地址(存放在FLASH APP缓冲区)
#define Flash_UNUSED					0x807C000

#else
  #define APP_START_ADDR       	0x20001000  						//应用程序起始地址(存放在RAM)
#endif

#define APP_Update_FlagAddr 		0x807BFFE								//2字节升级标志
#
/************************** IAP 外部变量********************************/
//#define APP_FLASH_LEN  			   56320u       					//定义 APP 固件最大容量，55kB=55*1024=56320
#define APP_FLASH_LEN  			   	 1000u
/* 扩展变量 ------------------------------------------------------------------*/
extern struct  STRUCT_IAP_RECIEVE      									//串口数据帧的处理结构体
{
	uint8_t   ucDataBuf[APP_FLASH_LEN];
	uint16_t  usLength;
} strAppBin;

/* 函数声明 ------------------------------------------------------------------*/
void IAP_WriteBin_Init(void);
void IAP_WriteBin(uint32_t StartAddr,uint8_t * pBin_DataBuf,uint32_t packBufLength);
void IAP_ExecuteApp( uint32_t appxaddr );			                              //执行flash里面的app程序
void IAP_WriteBinToAPPReigon(uint32_t SrcStartAddr,uint32_t DstStartAddr,uint32_t BinLength);
void APP_UpdateFlag_Write(uint32_t addr,uint16_t *pdata);
uint16_t APP_UpdateFlag_Read(uint32_t addr);
void APPReigion_Erase(uint32_t startaddr,uint16_t pages);

#endif /* __BSP_IAP_H__ */

/******************* (C) COPYRIGHT 2015-2020 硬石嵌入式开发团队 *****END OF FILE****/
