/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  ** This notice applies to any and all portions of this file
  * that are not between comment pairs USER CODE BEGIN and
  * USER CODE END. Other portions of this file, whether 
  * inserted by the user or by software development tools
  * are owned by their respective copyright owners.
  *
  * COPYRIGHT(c) 2021 STMicroelectronics
  *
  * Redistribution and use in source and binary forms, with or without modification,
  * are permitted provided that the following conditions are met:
  *   1. Redistributions of source code must retain the above copyright notice,
  *      this list of conditions and the following disclaimer.
  *   2. Redistributions in binary form must reproduce the above copyright notice,
  *      this list of conditions and the following disclaimer in the documentation
  *      and/or other materials provided with the distribution.
  *   3. Neither the name of STMicroelectronics nor the names of its contributors
  *      may be used to endorse or promote products derived from this software
  *      without specific prior written permission.
  *
  * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
  * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
  * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
  * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
  * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
  * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
  * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
  * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
  * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
  * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "tim.h"
#include "usart.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "user_key.h"
#include "user_delay.h"
#include "hcsr04.h"
#include "HLINK_voice.h"
#include "common_interrupt.h"
#include "HW_Remote.h"
#include "stdio.h"
#include "string.h"
#include "SEGGER_RTT.h"

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

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */
	uint8_t key = 0,t=0,HW_KeyValue = 0;
	float distant = 0;
	int val = 0;
	char *keystr = NULL;
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
  MX_USART2_UART_Init();
  MX_TIM3_Init();
  MX_USART1_UART_Init();
  MX_TIM2_Init();
  MX_TIM7_Init();
  MX_TIM4_Init();
  /* USER CODE BEGIN 2 */
  HAL_Delay_us_init(168);
  HCSR_TRIG_LOW();
  HAL_GPIO_WritePin(Relay_Ctr_GPIO_Port, Relay_Ctr_Pin, GPIO_PIN_RESET);
  Voice_RecUartInit();
  HAL_TIM_Base_Start(&htim3);
//  HAL_TIM_PWM_Start(&htim3,TIM_CHANNEL_1);
  HAL_TIM_PWM_Start(&htim3,TIM_CHANNEL_3);
//  HAL_TIM_PWM_Start(&htim3,TIM_CHANNEL_2);
	RemoteInit();

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
	
		
		/*********************************************
		//以下是超声波测试代码
		**********************************************/
		//distant =  Distance(5);
		/**********************************************/
		
		/*********************************************
		//以下是按键控制舵机测试代码
		**********************************************/
//		key=KEY_Scan(0);
//		switch (key)
//		{
//			case WKUP_PRES:			//
//				PWM_Output(4,1);
//				printf("rotate -90度\r\n");
//				break;
//			case KEY2_PRES:			//
//				PWM_Output(4,2);
//				printf("rotate -45度\r\n");

//				break;
//			case KEY1_PRES:			// 
//				PWM_Output(4,4);
//				printf("rotate 45度\r\n");
//				break;
//			case KEY0_PRES:			//
//				PWM_Output(4,5);
//				printf("rotate 90度\r\n");	
//				break;
//		}
//		t++;
//		if(t%50==0)
//		{
//			t=0;
//			//printf("\r\n\r\n---------------start--------------------\r\n\r\n");
//			//printf("The Mesure Distant is:%.2f cm\r\n",distant);
//			//printf("\r\n\r\n----------------stop--------------------\r\n\r\n");
//			HAL_GPIO_TogglePin(led_run_GPIO_Port,led_run_Pin);
//		}
//		/**********************************************/
//		
//		/*********************************************
//		//以下是离线语音控制测试代码
//		**********************************************/
//		//Voice_DataFrame();
//		/*********************************************
//		
//		
//		//以下是红外控制舵机测试代码
//		**********************************************/
//		HW_KeyValue=Remote_Scan();
//		
//		if(HW_KeyValue)
//		{
//			keystr = KeyValueConvert(HW_KeyValue);
//			
//			if(!memcmp(keystr,"*",strlen("*")))
//			{
//				PWM_Stop();
//				printf("\r\nrotate stop\r\n");
//			}
//			else if(!memcmp(keystr,"UP",strlen("UP")))
//			{
//				PWM_Output(1,0);
//				PWM_Output(2,0);
//				PWM_Output(3,0);
//				PWM_Output(4,0);
//				printf("\r\nrotate 45度\r\n");
//			}
//			else if(!memcmp(keystr,"RIGHT",strlen("RIGHT")))
//			{
//				PWM_Output(1,45);
//				PWM_Output(2,45);
//				PWM_Output(3,45);
//				PWM_Output(4,45);
//				printf("\r\nrotate 90度\r\n");	
//			}	
//			else if(!memcmp(keystr,"DOWN",strlen("DOWN")))
//			{
//				PWM_Output(1,90);
//				PWM_Output(2,90);
//				PWM_Output(3,90);
//				PWM_Output(4,90);
//				printf("\r\nrotate -45度\r\n");
//			}
//			else if(!memcmp(keystr,"LEFT",strlen("LEFT")))
//			{
//				PWM_Output(1,135);
//				PWM_Output(2,135);
//				PWM_Output(3,135);
//				PWM_Output(4,135);
//				printf("\r\nrotate -90度\r\n");
//			}
//			else if(!memcmp(keystr,"OK",strlen("OK")))
//			{
//				PWM_Output(1,180);
//				PWM_Output(2,180);
//				PWM_Output(3,180);
//				PWM_Output(4,180);
//				printf("\r\nrotate 90度\r\n");
//			}	
//			printf("\r\nThe Key Value is %s \r\n",(char *)(keystr));
//		}
//		/**********************************************/
//		HAL_Delay(10);

	
		SEGGER_RTT_printf(0, RTT_CTRL_TEXT_RED"\r\n欢迎关注小飞哥玩嵌入式\r\n\r\n");
		SEGGER_RTT_printf(0, RTT_CTRL_TEXT_BRIGHT_GREEN"\r\nwelcome Embedded-party\r\n\r\n");
		SEGGER_RTT_printf(0, RTT_CTRL_TEXT_BRIGHT_BLUE"data print test:%f\r\n",12.34);	
		HAL_Delay(500);
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

  /** Configure the main internal regulator output voltage
  */
  __HAL_RCC_PWR_CLK_ENABLE();
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);
  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLM = 4;
  RCC_OscInitStruct.PLL.PLLN = 168;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = 4;
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
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV4;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV2;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_5) != HAL_OK)
  {
    Error_Handler();
  }
}

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */

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
     tex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
