/* ����ͷ�ļ� ----------------------------------------------------------------*/
#include "bsp_iap.h"
#include "bsp_flash.h"
#include "user_uartdma.h"

extern UserUartDMA_Typedef UserUartDma;


struct STRUCT_IAP_RECIEVE strAppBin  __attribute__((at(0x20001000)))={{0},0};

static uint16_t ulBuf_Flash_App[1024];
uint16_t APP_UPDATE_FLAG = 0x5AA5;



/******************************************************
* Brief     : IAP_WriteBin_Init
* Parameter : 
*           *None
* Return    : None.
*******************************************************/
void IAP_WriteBin_Init(void)
{
		UserUartDma.Cur_WriteAddr = APP_Temp_ADDR;
}
/******************************************************
* Brief     : ����APP��
* Parameter : 
*           *startaddr��APP��ʼ��ַ
*						*pages		��Ҫ������page = APPSIZE/PAGESIZE
* Return    :None.
*******************************************************/
void APPReigion_Erase(uint32_t startaddr,uint16_t pages)
{
		uint32_t SECTORError = 0;

		//����APP��
		/* Fill EraseInit structure*/
		EraseInitStruct.TypeErase     = FLASH_TYPEERASE_PAGES;
		EraseInitStruct.PageAddress   = startaddr;
		EraseInitStruct.NbPages       = pages;
		HAL_FLASHEx_Erase(&EraseInitStruct, &SECTORError);
}

/******************************************************
* Brief     : ����APP��
* Parameter : 
*           *startaddr��APP��ʼ��ַ
*						*pages		��Ҫ������page = APPSIZE/PAGESIZE
* Return    :None.
*******************************************************/
void APP_UpdateFlag_Write(uint32_t addr,uint16_t *pdata)
{
		//uint16_t flag_temp = APP_UPDATE_FLAG;
		BSP_FLASH_Write(addr,pdata,1);
}

uint16_t APP_UpdateFlag_Read(uint32_t addr)
{
		uint16_t flag_temp;
		BSP_FLASH_Read(addr,&flag_temp,1);
	
		return flag_temp;
}

/******************************************************
* Brief     : ����APP��
* Parameter : 
*           *startaddr��APP��ʼ��ַ
*						*pages		��Ҫ������page = APPSIZE/PAGESIZE
* Return    :None.
*******************************************************/

/******************************************************
* Brief     : Bin�ļ�д��app������
* Parameter : 
*           StartAddr: ��ʼ��ַ
*           *pBin_DataBuf: Ҫ���������
*           packBufLength���������ݳ���
* Return    : None.
*******************************************************/
void IAP_WriteBin(uint32_t StartAddr,uint8_t * pBin_DataBuf,uint32_t packBufLength)
{
	uint16_t pack_len, packlen_Ctr=0, dataTemp;
	uint8_t * pData = pBin_DataBuf;
	 
	for (pack_len = 0; pack_len < packBufLength; pack_len += 2 )
	{						    
		dataTemp =  ( uint16_t ) pData[1]<<8;
		dataTemp += ( uint16_t ) pData[0];	  
		pData += 2;                                                      //ƫ��2���ֽ�
		ulBuf_Flash_App [ packlen_Ctr ++ ] = dataTemp;	    
	}	

			BSP_FLASH_Write ( UserUartDma.Cur_WriteAddr, ulBuf_Flash_App, packlen_Ctr );	
			UserUartDma.Cur_WriteAddr += (packlen_Ctr*2);                                           //ƫ��packlen_Ctr  16=2*8.����Ҫ����2.
			packlen_Ctr = 0;
}
/******************************************************
* Brief     : Bin�ļ�д��ap��
* Parameter : 
*           SrcStartAddr: app��������ʼ��ַ
*           DstStartAddr: APP����ʼ��ַ
*           BinLength��bin�ļ�����

* Return    : None.
*******************************************************/
void IAP_WriteBinToAPPReigon(uint32_t SrcStartAddr,uint32_t DstStartAddr,uint32_t BinLength)
{
	uint16_t data_temp = 0;
	uint32_t count=0;
	
	
	HAL_FLASH_Unlock();									//����
	
	APPReigion_Erase(APP_START_ADDR,APPSIZE/PAGESIZE);
	HAL_Delay(10);
	
	for(count=0;count<BinLength;count=count+2)
	{
			BSP_FLASH_Read (SrcStartAddr, &data_temp, 1);
			BSP_FLASH_Write_NoCheck(DstStartAddr, &data_temp,1);
			SrcStartAddr+=2;
			DstStartAddr+=2;
	}
	
	//BSP_FLASH_Write_NoCheck(DstStartAddr, ,1);
	HAL_FLASH_Lock();//����
}

/******************************************************
* Brief     : DMA���亯��
* Parameter : 
*           *pData: Ҫ���������
* Return    : None.
*******************************************************/

__asm void MSR_MSP ( uint32_t ulAddr ) 
{
    MSR MSP, r0 			                   //set Main Stack value
    BX r14
}

/******************************************************
* Brief     : DMA���亯��
* Parameter : 
*           *pData: Ҫ���������
* Return    : None.
*******************************************************/
void IAP_ExecuteApp ( uint32_t ulAddr_App )
{
	pIapFun_TypeDef pJump2App; 
	
	if ( ( ( * ( __IO uint32_t * ) ulAddr_App ) & 0x2FFE0000 ) == 0x20000000 )	  //���ջ����ַ�Ƿ�Ϸ�.
	{ 
		pJump2App = ( pIapFun_TypeDef ) * ( __IO uint32_t * ) ( ulAddr_App + 4 );	//�û��������ڶ�����Ϊ����ʼ��ַ(��λ��ַ)		
		MSR_MSP( * ( __IO uint32_t * ) ulAddr_App ); //��ʼ��APP��ջָ��(�û��������ĵ�һ�������ڴ��ջ����ַ)
		pJump2App ();								                                    	//��ת��APP.
	}
}		

