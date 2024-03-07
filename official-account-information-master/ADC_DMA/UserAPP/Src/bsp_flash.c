#include "bsp_flash.h"
/************************************************************
  * @brief   ��ȡ2�ֽ�����
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
  * @brief   		 ��ȡn(uint16_t)�ֽ�����
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
		pBuffer[i]=BSP_FLASH_ReadHalfWord(ReadAddr);			//��ȡ2���ֽ�.
		ReadAddr+=2;																			//ƫ��2���ֽ�.	
	}
}

#if STM32_FLASH_WREN	//���ʹ����д   
/************************************************************
  * @brief   д��n(uint16_t)�ֽ�����
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
	  WriteAddr+=2;                                    //��ַ����2.
	}  
} 
/************************************************************
  * @brief   		д��n(uint16_t)�ֽ�����
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
	uint16_t sector_off;	   //������ƫ�Ƶ�ַ(16λ�ּ���)
	uint16_t sector_remain; //������ʣ���ַ(16λ�ּ���)	   
 	uint16_t i;    
	uint32_t secor_pos;	   //������ַ
	uint32_t offaddr;   //ȥ��0X08000000��ĵ�ַ
	
	if(WriteAddr<FLASH_BASE||(WriteAddr>=(FLASH_BASE+1024*STM32_FLASH_SIZE)))return;//�Ƿ���ַ
	
	HAL_FLASH_Unlock();									//����
	
	offaddr=WriteAddr-FLASH_BASE;				//ʵ��ƫ�Ƶ�ַ.
	secor_pos=offaddr/STM_SECTOR_SIZE;			//������ַ  0~127 for STM32F103RBT6
	sector_off=(offaddr%STM_SECTOR_SIZE)/2;		//�������ڵ�ƫ��(2���ֽ�Ϊ������λ.)
	sector_remain=STM_SECTOR_SIZE/2-sector_off;		//����ʣ��ռ��С   
	if(len<=sector_remain)sector_remain=len;//�����ڸ�������Χ
	
	while(1) 
	{	
		BSP_FLASH_Read(secor_pos*STM_SECTOR_SIZE+FLASH_BASE,STMFLASH_BUF,STM_SECTOR_SIZE/2);//������������������
				
		for(i=0;i<sector_remain;i++)//У������
		{
			if(STMFLASH_BUF[sector_remain+i]!=0XFFFF)
				break;//��Ҫ����  	  
		}
		if(i<sector_remain)//��Ҫ����
		{
			//�����������
      /* Fill EraseInit structure*/
      EraseInitStruct.TypeErase     = FLASH_TYPEERASE_PAGES;
      EraseInitStruct.PageAddress   = secor_pos*STM_SECTOR_SIZE+FLASH_BASE;
      EraseInitStruct.NbPages       = 1;
      HAL_FLASHEx_Erase(&EraseInitStruct, &SECTORError);
			for(i=0;i<sector_remain;i++)//����
			{
				STMFLASH_BUF[i+sector_off]=pBuffer[i];	  
			}
			BSP_FLASH_Write_NoCheck(secor_pos*STM_SECTOR_SIZE+FLASH_BASE,STMFLASH_BUF,STM_SECTOR_SIZE/2);//д����������  
		}
		else 
			BSP_FLASH_Write_NoCheck(WriteAddr,pBuffer,sector_remain);//д�Ѿ������˵�,ֱ��д������ʣ������. 				   
		if(len==sector_remain)
			break;//д�������
		else//д��δ����
		{
			secor_pos++;				//������ַ��1
			sector_off=0;				//ƫ��λ��Ϊ0 	 
		  pBuffer+=sector_remain;  	//ָ��ƫ��
			WriteAddr+=sector_remain;	//д��ַƫ��	   
		  len-=sector_remain;	//�ֽ�(16λ)���ݼ�
			
			if(len>(STM_SECTOR_SIZE/2))
				sector_remain=STM_SECTOR_SIZE/2;//��һ����������д����
			else 
				sector_remain=len;//��һ����������д����
		}	 
	};	
	HAL_FLASH_Lock();//����
}
#endif
