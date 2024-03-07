#ifndef __BSP_IAP_H__
#define	__BSP_IAP_H__

/* ����ͷ�ļ� ----------------------------------------------------------------*/
#include "stm32f1xx_hal.h"

/* ���Ͷ��� ------------------------------------------------------------------*/
/************************** IAP �������Ͷ���********************************/
typedef  void ( * pIapFun_TypeDef ) ( void ); //����һ���������͵Ĳ���.

#define APP_Len_ADDR	0x807BFFE
#define APP_UpdateFlag_ADDR	0x807C000
/* �궨�� --------------------------------------------------------------------*/
/************************** IAP ���������********************************/
 //�Ƿ���� APP �� FLASH��������µ� RAM
#define User_Flash                                        

#define APPSIZE			224*1024			//224K


#ifdef User_Flash
#define APP_START_ADDR       	0x800C000//0x8010000  	//Ӧ�ó�����ʼ��ַ(�����FLASH APP������)
#define APP_Temp_ADDR       	0x8044000//0x8010000  	//Ӧ�ó�����ʼ��ַ(�����FLASH APP������)
#define Flash_UNUSED					0x807C000

#else
  #define APP_START_ADDR       	0x20001000  						//Ӧ�ó�����ʼ��ַ(�����RAM)
#endif

#define APP_Update_FlagAddr 		0x807BFFE								//2�ֽ�������־
#
/************************** IAP �ⲿ����********************************/
//#define APP_FLASH_LEN  			   56320u       					//���� APP �̼����������55kB=55*1024=56320
#define APP_FLASH_LEN  			   	 1000u
/* ��չ���� ------------------------------------------------------------------*/
extern struct  STRUCT_IAP_RECIEVE      									//��������֡�Ĵ���ṹ��
{
	uint8_t   ucDataBuf[APP_FLASH_LEN];
	uint16_t  usLength;
} strAppBin;

/* �������� ------------------------------------------------------------------*/
void IAP_WriteBin_Init(void);
void IAP_WriteBin(uint32_t StartAddr,uint8_t * pBin_DataBuf,uint32_t packBufLength);
void IAP_ExecuteApp( uint32_t appxaddr );			                              //ִ��flash�����app����
void IAP_WriteBinToAPPReigon(uint32_t SrcStartAddr,uint32_t DstStartAddr,uint32_t BinLength);
void APP_UpdateFlag_Write(uint32_t addr,uint16_t *pdata);
uint16_t APP_UpdateFlag_Read(uint32_t addr);
void APPReigion_Erase(uint32_t startaddr,uint16_t pages);

#endif /* __BSP_IAP_H__ */

/******************* (C) COPYRIGHT 2015-2020 ӲʯǶ��ʽ�����Ŷ� *****END OF FILE****/
