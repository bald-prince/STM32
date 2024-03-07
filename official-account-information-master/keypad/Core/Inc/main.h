/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2021 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */

/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define KEY2_Pin GPIO_PIN_2
#define KEY2_GPIO_Port GPIOE
#define KEY1_Pin GPIO_PIN_3
#define KEY1_GPIO_Port GPIOE
#define KEY0_Pin GPIO_PIN_4
#define KEY0_GPIO_Port GPIOE
#define Key_ROW1_Pin GPIO_PIN_0
#define Key_ROW1_GPIO_Port GPIOF
#define Key_ROW2_Pin GPIO_PIN_1
#define Key_ROW2_GPIO_Port GPIOF
#define Key_ROW3_Pin GPIO_PIN_2
#define Key_ROW3_GPIO_Port GPIOF
#define Key_ROW4_Pin GPIO_PIN_3
#define Key_ROW4_GPIO_Port GPIOF
#define led1_Pin GPIO_PIN_9
#define led1_GPIO_Port GPIOF
#define led2_Pin GPIO_PIN_10
#define led2_GPIO_Port GPIOF
#define WK_UP_Pin GPIO_PIN_0
#define WK_UP_GPIO_Port GPIOA
#define Key_COL1_Pin GPIO_PIN_0
#define Key_COL1_GPIO_Port GPIOG
#define Key_COL2_Pin GPIO_PIN_1
#define Key_COL2_GPIO_Port GPIOG
#define Key_COL3_Pin GPIO_PIN_2
#define Key_COL3_GPIO_Port GPIOG
#define Key_COL4_Pin GPIO_PIN_3
#define Key_COL4_GPIO_Port GPIOG
#define LCD_DC_Pin GPIO_PIN_6
#define LCD_DC_GPIO_Port GPIOG
#define LCD_CS_Pin GPIO_PIN_7
#define LCD_CS_GPIO_Port GPIOG
#define LCD_RST_Pin GPIO_PIN_8
#define LCD_RST_GPIO_Port GPIOG
/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
