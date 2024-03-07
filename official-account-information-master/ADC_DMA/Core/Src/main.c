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
#include "adc.h"
#include "dma.h"
#include "tim.h"
#include "usart.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "stdio.h"
#include "string.h"

#include "userUart.h"
#include "scheduler.h"
#include "bsp_iap.h"
#include "button.h"
#include "user_json.h"
#include "bsp_flash.h"
#include "alg_sha1.h"
#include "user_uartdma.h"


/* FreeRTOS头文件 */
#include "FreeRTOS.h"
#include "task.h"

#include "freertos_task.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */
extern UserUartDMA_Typedef UserUartDma;
extern uint16_t APP_UPDATE_FLAG;
/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
#define KEY_ON 0
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */
Button_t Button1;
Button_t Button2; 

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */
static void Systick_Config(void);
uint32_t Key_ScanTask(void);
uint32_t Task_02(void);

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
void Btn1_Dowm_CallBack(void *btn)
{
  PRINT_INFO("Button1 单击!");
}

void Btn1_Double_CallBack(void *btn)
{
  PRINT_INFO("Button1 双击!");
}

void Btn1_Long_CallBack(void *btn)
{
  PRINT_INFO("Button1 长按!");
}

void Btn1_Continuos_CallBack(void *btn)
{
  PRINT_INFO("Button1 连按!");
}
void Btn1_ContinuosFree_CallBack(void *btn)
{
  PRINT_INFO("Button1 连按释放!");
}


void Btn2_Dowm_CallBack(void *btn)
{
  PRINT_INFO("Button2 单击!");
}

void Btn2_Double_CallBack(void *btn)
{
  PRINT_INFO("Button2 双击!");
}

void Btn2_Long_CallBack(void *btn)
{
  PRINT_INFO("Button2 长按!");
}

void Btn2_Continuos_CallBack(void *btn)
{
  PRINT_INFO("Button2 连按!");
}
void Btn2_ContinuosFree_CallBack(void *btn)
{
  PRINT_INFO("Button2 连按释放!");
}

uint8_t Read_KEY1_Level(void)
{
	
	return HAL_GPIO_ReadPin(Usr_Key_GPIO_Port,Usr_Key_Pin);
}
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
  MX_TIM2_Init();
  MX_DMA_Init();
  MX_USART1_UART_Init();
  MX_ADC1_Init();
  /* USER CODE BEGIN 2 */
  Systick_Config();
// UserUartInit();
	User_uartdma_Init();
	IAP_WriteBin_Init();
	
	
	SCH_Add_Task(Key_ScanTask, 1, 20);
  SCH_Add_Task(Task_02, 10, 10);
	
	
	Button_Create("Button1",
              &Button1, 
              Read_KEY1_Level, 
              KEY_ON);
  Button_Attach(&Button1,BUTTON_DOWM,Btn1_Dowm_CallBack);                       //单击
  Button_Attach(&Button1,BUTTON_DOUBLE,Btn1_Double_CallBack);                   //双击
  Button_Attach(&Button1,BUTTON_CONTINUOS,Btn1_Continuos_CallBack);             //连按  
  Button_Attach(&Button1,BUTTON_CONTINUOS_FREE,Btn1_ContinuosFree_CallBack);    //连按释放  
  Button_Attach(&Button1,BUTTON_LONG,Btn1_Long_CallBack);                       //长按

  Get_Button_Event(&Button1);
	PRINT_INFO("\n");

	PRINT_INFO("-----IAP Menu--------------\n");
	PRINT_INFO("-----Download APP BIN------\n");
	PRINT_INFO("-----Restart To RUN APP----\n");	
	PRINT_INFO("\n\n\n");
	
	if(0x5aa5==APP_UpdateFlag_Read(APP_UpdateFlag_ADDR))
	{
		PRINT_INFO("-----Restart.....5-------\n");
		HAL_Delay(1000);
		PRINT_INFO("-----Restart.....4-------\n");
		HAL_Delay(1000);
		PRINT_INFO("-----Restart.....3-------\n");
		HAL_Delay(1000);
		PRINT_INFO("-----Restart.....2-------\n");
		HAL_Delay(1000);
		PRINT_INFO("-----Restart.....1-------\n");
		HAL_Delay(1000);
		
		PRINT_INFO("the device need update\n");
		IAP_WriteBinToAPPReigon(APP_Temp_ADDR,APP_START_ADDR,APP_UpdateFlag_Read(APP_Len_ADDR));	
		PRINT_INFO("firmware write OK\n");
		PRINT_INFO("please double click the button the execute the application\n");
	
		HAL_FLASH_Unlock();									//解锁
		APPReigion_Erase(APP_Temp_ADDR,APPSIZE/PAGESIZE);		//擦除APP缓冲区
		APPReigion_Erase(Flash_UNUSED,1);										//清除APP更新标志					
		HAL_FLASH_Lock();										//上锁
		
		PRINT_INFO ( "开始执行 APP\n" ); 
		//执行FLASH APP代码
		IAP_ExecuteApp(APP_START_ADDR);
	}	
	
	UserAPP_TaskCreate();
	vTaskStartScheduler();

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
    //SCH_Dispatch_Tasks();
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
  RCC_PeriphCLKInitTypeDef PeriphClkInit = {0};

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
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK)
  {
    Error_Handler();
  }
  PeriphClkInit.PeriphClockSelection = RCC_PERIPHCLK_ADC;
  PeriphClkInit.AdcClockSelection = RCC_ADCPCLK2_DIV6;
  if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInit) != HAL_OK)
  {
    Error_Handler();
  }
}

/* USER CODE BEGIN 4 */
static void Systick_Config(void)
{
  HAL_SYSTICK_Config(HAL_RCC_GetHCLKFreq() / 10000); //10ms
  HAL_SYSTICK_CLKSourceConfig(SYSTICK_CLKSOURCE_HCLK);
  HAL_NVIC_SetPriority(SysTick_IRQn, 0, 0);
}

void HAL_SYSTICK_Callback(void)
{
//	UserUartDma.DMA_TIMCNT++;
//	if(UserUartDma.DMA_TIMCNT>2000)
//	{
//		UserUartDma.Binrec_endFlag = 1;
//		UserUartDma.DMA_TIMCNT = 0;
//	}
//  TIMX_IRQHandler_user(); //10ms调用一次
}
uint32_t Key_ScanTask(void)
{
	Button_Process();     //需要周期调用按键处理函数
	
	return 0;	//无实际意义
}



uint32_t Task_02(void)
{
	
	if(UserUartDma.rec_endFlag)
	{
		PRINT_INFO("update firmware\n");
		PRINT_INFO("APP 长度：%d字节\n", UserUartDma.RecDat_len);		
		
		UserUartDma.rec_endFlag = 0;
		IAP_WriteBin(UserUartDma.Cur_WriteAddr,UserUartDma.RxBuffer,UserUartDma.RecDat_len);
		
		memset(UserUartDma.RxBuffer,0,UserUartDma.RecDat_len);
		UserUartDma.RecDat_len = 0;
	}
	if(UserUartDma.BinLen!=0)
	{
		if(UserUartDma.Binrec_endFlag)
		{
			 UserUartDma.Binrec_endFlag = 0;
			 
			 APP_UpdateFlag_Write(APP_Len_ADDR,&UserUartDma.BinLen);			//写入升级标志
			 APP_UpdateFlag_Write(APP_UpdateFlag_ADDR,&APP_UPDATE_FLAG);			//写入升级标志
			 UserUartDma.BinLen = 0;		
			 IAP_ExecuteApp(FLASH_BASE);
			 HAL_Delay(2000);
		}
	
	}
	return 0;
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

#ifdef  USE_FULL_ASSERT
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
