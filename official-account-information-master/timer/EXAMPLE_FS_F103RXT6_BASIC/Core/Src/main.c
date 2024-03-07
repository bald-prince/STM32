/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
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
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "tim.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
/*
 * * change record:-->1
 * * time and author:21.10.4 lanxin
 * * what changed:������ʼ�汾��
 * * point:1.���� FS_STM32F103RX_BoardV1.3  git----> git@gitee.com:lanxin980210/fs-share.git -->FS_BOARD-->FS_STM32F103RXT6_BOARD V1.3
 * * point:2.�����ļ��е�stm32f1xx_it.c������soft_timer�Ĳ����ļ�������δ���޸ġ�
 * * point:3.main.c�����Ӳ��Դ��룬����δ���޸ġ�
 * * point:4.led 1000ms��˸һ�Σ������Ϩ�� 
 * * point:5.����/ɾ����ʱ��  ����/�رն�ʱ��
 * * point:6. ���ģ��ʹ��tim_ops->timer_stop()Ҳ�ǿ��Թرյģ�֮��ʹ��tim_ops->timer_start();�������¿���
 */
#include "fs_soft_timer_driver.h"

c_soft_timer_t *my_timer_1 = 0x00;
c_soft_timer_t *my_timer_2 = 0x00;

void test(void *para);
void test2(void *para);

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_TIM6_Init();
  /* USER CODE BEGIN 2 */
  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_2, GPIO_PIN_RESET); //��ʼ��led gpio
                                                        /* ʹ��hard timer 6 */
  __HAL_TIM_ENABLE(&htim6);
  __HAL_TIM_ENABLE_IT(&htim6, TIM_IT_UPDATE);
  /* soft timer init */
  if (fs_soft_timer_module_init() != SOFT_TIMER_STATE_OK)
  {
    return 0; //��ʾsoft timer module ������
  }

  my_timer_1 = tim_ops->add_new_timer(SOFT_TIMER_WORK_PERIOD, 1000, 0, test);                   //��ӵ�һ��timer
  my_timer_2 = tim_ops->add_new_timer(SOFT_TIMER_WORK_PERIOD, 5000, (void *)my_timer_1, test2); //ͨ���ڶ���timer�ѵ�һ��timerɾ��,�رյڶ�����ʱ��

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
    tim_ops->timer_handle();
  }
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.HSEPredivValue = RCC_HSE_PREDIV_DIV1;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL9;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_SYSCLK | RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK)
  {
    Error_Handler();
  }
}

/* USER CODE BEGIN 4 */
/*
 * *@ author:lanxin
 * *@ brief:my_timer_1������жϴ�����
 * *@ note:��תled��״̬
 * *@ param:NONE
 * *@ retval:NONE
 */
void test(void *para)
{
  HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_2);
}
/*
 * *@ author:lanxin
 * *@ brief:my_timer_2������жϴ�����
 * *@ note:�ѵ�һ��timer��ɾ����
 * *@ note:��Ȼ���õ��������Զ�ʱ���������������͹ر��˸ö�ʱ��������ֻ�����һ��
 * *@ param:NONE
 * *@ retval:NONE
 */
void test2(void *para)
{
  c_soft_timer_t *tim = (c_soft_timer_t *)para; //ת������Ĳ���
  tim_ops->delete_timer(tim);
  tim_ops->timer_disable(my_timer_2);
  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_2, GPIO_PIN_SET);
}
/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}

#ifdef USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
