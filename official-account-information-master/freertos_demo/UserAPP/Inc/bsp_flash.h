#ifndef __BSP_FLASH_H
#define __BSP_FLASH_H

#include "stm32f1xx_hal.h"

#define STM32_FLASH_SIZE        512  // STM32的FLASH容量大小(单位为K)
#define STM32_FLASH_WREN        1    // 0-disable  1-enable 


#if STM32_FLASH_SIZE < 256
  #define STM_SECTOR_SIZE  1024 //字节
#else 
  #define STM_SECTOR_SIZE	 2048
#endif

#if STM32_FLASH_WREN	
static uint16_t STMFLASH_BUF [ STM_SECTOR_SIZE / 2 ];
static FLASH_EraseInitTypeDef EraseInitStruct;
#endif

void BSP_FLASH_Write(uint32_t WriteAddr,uint16_t * pBuffer,uint16_t len );
void BSP_FLASH_Read (uint32_t ReadAddr, uint16_t *pBuffer, uint16_t len );   	
void BSP_FLASH_Write_NoCheck ( uint32_t WriteAddr, uint16_t * pBuffer, uint16_t len ) ;  
uint16_t BSP_FLASH_ReadHalfWord(uint32_t raddr);

#endif
