#include "bsp_flash.h"
/************************************************************
  * @brief   读取2字节数据
	* @param[in]   uint32_t faddr
  * @return  NULL
  * @github  
  * @date    2021-xx-xx
  * @version v1.0
  * @note    NULL
  ***********************************************************/
uint16_t BSP_FLASH_ReadHalfWord(uint32_t raddr)
{
	return *(__IO uint16_t*)raddr; 
}
/************************************************************
  * @brief   		 读取n(uint16_t)字节数据
	* @param[in]   uint32_t ReadAddr
	* @param[out]  uint16_t *pBuffer
	* @param[in]   uint16_t len
  * @return  NULL
  * @github  
  * @date    2021-xx-xx
  * @version v1.0
  * @note    NULL
  ***********************************************************/
void BSP_FLASH_Read (uint32_t ReadAddr, uint16_t *pBuffer, uint16_t len )   	
{
	uint16_t i;
	
	for(i=0;i<len;i++)
	{
		pBuffer[i]=BSP_FLASH_ReadHalfWord(ReadAddr);			//读取2个字节.
		ReadAddr+=2;																			//偏移2个字节.	
	}
}

#if STM32_FLASH_WREN	//如果使能了写   
/************************************************************
  * @brief   写入n(uint16_t)字节数据
	* @param[in]   uint32_t ReadAddr
	* @param[out]   uint16_t *pBuffer
	* @param[in]   uint16_t len
  * @return  NULL
  * @github  
  * @date    2021-xx-xx
  * @version v1.0
  * @note    NULL
  ***********************************************************/
void BSP_FLASH_Write_NoCheck ( uint32_t WriteAddr, uint16_t * pBuffer, uint16_t len )   
{ 			 		 
	uint16_t i;	
	
	for(i=0;i<len;i++)
	{
		HAL_FLASH_Program(FLASH_TYPEPROGRAM_HALFWORD,WriteAddr,pBuffer[i]);
	  WriteAddr+=2;                                    //地址增加2.
	}  
} 
/************************************************************
  * @brief   		写入n(uint16_t)字节数据
	* @param[in]  uint32_t WriteAddr
	* @param[in]  uint16_t *pBuffer
	* @param[in]  uint16_t len
  * @return  NULL
  * @github  
  * @date    2021-xx-xx
  * @version v1.0
  * @note    NULL
  ***********************************************************/
void BSP_FLASH_Write(uint32_t WriteAddr,uint16_t * pBuffer,uint16_t len )	
{
  uint32_t SECTORError = 0;
	uint16_t sector_off;	   //扇区内偏移地址(16位字计算)
	uint16_t sector_remain; //扇区内剩余地址(16位字计算)	   
 	uint16_t i;    
	uint32_t secor_pos;	   //扇区地址
	uint32_t offaddr;   //去掉0X08000000后的地址
	
	if(WriteAddr<FLASH_BASE||(WriteAddr>=(FLASH_BASE+1024*STM32_FLASH_SIZE)))return;//非法地址
	
	HAL_FLASH_Unlock();									//解锁
	
	offaddr=WriteAddr-FLASH_BASE;				//实际偏移地址.
	secor_pos=offaddr/STM_SECTOR_SIZE;			//扇区地址  0~127 for STM32F103RBT6
	sector_off=(offaddr%STM_SECTOR_SIZE)/2;		//在扇区内的偏移(2个字节为基本单位.)
	sector_remain=STM_SECTOR_SIZE/2-sector_off;		//扇区剩余空间大小   
	if(len<=sector_remain)sector_remain=len;//不大于该扇区范围
	
	while(1) 
	{	
		BSP_FLASH_Read(secor_pos*STM_SECTOR_SIZE+FLASH_BASE,STMFLASH_BUF,STM_SECTOR_SIZE/2);//读出整个扇区的内容
				
		for(i=0;i<sector_remain;i++)//校验数据
		{
			if(STMFLASH_BUF[sector_remain+i]!=0XFFFF)
				break;//需要擦除  	  
		}
		if(i<sector_remain)//需要擦除
		{
			//擦除这个扇区
      /* Fill EraseInit structure*/
      EraseInitStruct.TypeErase     = FLASH_TYPEERASE_PAGES;
      EraseInitStruct.PageAddress   = secor_pos*STM_SECTOR_SIZE+FLASH_BASE;
      EraseInitStruct.NbPages       = 1;
      HAL_FLASHEx_Erase(&EraseInitStruct, &SECTORError);
			for(i=0;i<sector_remain;i++)//复制
			{
				STMFLASH_BUF[i+sector_off]=pBuffer[i];	  
			}
			BSP_FLASH_Write_NoCheck(secor_pos*STM_SECTOR_SIZE+FLASH_BASE,STMFLASH_BUF,STM_SECTOR_SIZE/2);//写入整个扇区  
		}
		else 
			BSP_FLASH_Write_NoCheck(WriteAddr,pBuffer,sector_remain);//写已经擦除了的,直接写入扇区剩余区间. 				   
		if(len==sector_remain)
			break;//写入结束了
		else//写入未结束
		{
			secor_pos++;				//扇区地址增1
			sector_off=0;				//偏移位置为0 	 
		  pBuffer+=sector_remain;  	//指针偏移
			WriteAddr+=sector_remain;	//写地址偏移	   
		  len-=sector_remain;	//字节(16位)数递减
			
			if(len>(STM_SECTOR_SIZE/2))
				sector_remain=STM_SECTOR_SIZE/2;//下一个扇区还是写不完
			else 
				sector_remain=len;//下一个扇区可以写完了
		}	 
	};	
	HAL_FLASH_Lock();//上锁
}
#endif
