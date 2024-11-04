/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2024 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "stdio.h"

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
UART_HandleTypeDef huart2;

/* USER CODE BEGIN PV */
char keypad[4][3] = {
    {'1', '2', '3'},
    {'4', '5', '6'},
    {'7', '8', '9'},
    {'*', '0', '#'}
};

char pressed_key = 0;
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_USART2_UART_Init(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
int _write(int file, char *ptr, int len)
{
  (void)file;
  int DataIdx;

  for (DataIdx = 0; DataIdx < len; DataIdx++)
  {
    ITM_SendChar(*ptr++);
  }
  return len;
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
  MX_USART2_UART_Init();
  /* USER CODE BEGIN 2 */

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
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
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE3);

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
  RCC_OscInitStruct.PLL.PLLM = 16;
  RCC_OscInitStruct.PLL.PLLN = 336;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV4;
  RCC_OscInitStruct.PLL.PLLQ = 2;
  RCC_OscInitStruct.PLL.PLLR = 2;
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
}

/**
  * @brief USART2 Initialization Function
  * @param None
  * @retval None
  */
static void MX_USART2_UART_Init(void)
{

  /* USER CODE BEGIN USART2_Init 0 */

  /* USER CODE END USART2_Init 0 */

  /* USER CODE BEGIN USART2_Init 1 */

  /* USER CODE END USART2_Init 1 */
  huart2.Instance = USART2;
  huart2.Init.BaudRate = 115200;
  huart2.Init.WordLength = UART_WORDLENGTH_8B;
  huart2.Init.StopBits = UART_STOPBITS_1;
  huart2.Init.Parity = UART_PARITY_NONE;
  huart2.Init.Mode = UART_MODE_TX_RX;
  huart2.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart2.Init.OverSampling = UART_OVERSAMPLING_16;
  if (HAL_UART_Init(&huart2) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN USART2_Init 2 */

  /* USER CODE END USART2_Init 2 */

}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOH_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOC, R1_Pin|R2_Pin|R3_Pin|R4_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(LD2_GPIO_Port, LD2_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOB, A_Pin|B_Pin|C_Pin|G_Pin
                          |F_Pin|E_Pin|D_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin : B1_Pin */
  GPIO_InitStruct.Pin = B1_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_IT_FALLING;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(B1_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pins : R1_Pin R2_Pin R3_Pin R4_Pin */
  GPIO_InitStruct.Pin = R1_Pin|R2_Pin|R3_Pin|R4_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

  /*Configure GPIO pin : LD2_Pin */
  GPIO_InitStruct.Pin = LD2_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(LD2_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pins : C1_Pin C2_Pin C3_Pin */
  GPIO_InitStruct.Pin = C1_Pin|C2_Pin|C3_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_IT_FALLING;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pins : A_Pin B_Pin C_Pin G_Pin
                           F_Pin E_Pin D_Pin */
  GPIO_InitStruct.Pin = A_Pin|B_Pin|C_Pin|G_Pin
                          |F_Pin|E_Pin|D_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /* EXTI interrupt init*/
  HAL_NVIC_SetPriority(EXTI9_5_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(EXTI9_5_IRQn);

}

/* USER CODE BEGIN 4 */
void scan_keypad(void)
{
    // Set all row pins high initially
    HAL_GPIO_WritePin(GPIOC, R1_Pin | R2_Pin | R3_Pin | R4_Pin, GPIO_PIN_SET);

    // Scan each row
    for (int row = 0; row < 4; row++)
    {
        // Set the current row pin to low
        HAL_GPIO_WritePin(GPIOC, (R1_Pin << row), GPIO_PIN_RESET);

        //printf("Scanning Row: %d\n", row);  // Debug print to indicate current row being scanned

        // Check each column
        for (int col = 0; col < 3; col++)
        {
            int pinState = HAL_GPIO_ReadPin(GPIOA, (C1_Pin << col));  // Read pin state for debugging

            // Debug print to show the pin state of each column
           // printf("Checking Column: %d, Pin State: %d\n", col, pinState);

            if (pinState == GPIO_PIN_RESET)
            {
                // Key is pressed in this row and column
                pressed_key = keypad[row][col];
                display_number(pressed_key); // Display the key number
                printf("Pressed Key: %c\n", pressed_key);
                printf("Detected at Row: %d, Column: %d\n", row, col);

                // Restore the row pin to high
                HAL_GPIO_WritePin(GPIOC, (R1_Pin << row), GPIO_PIN_SET);

                return; // Exit as soon as a pressed key is found
            }
        }

        // Restore the row pin to high
        HAL_GPIO_WritePin(GPIOC, (R1_Pin << row), GPIO_PIN_SET);

    }
}

void display_number(char key) {
    uint8_t number = key - '0'; // Convert char to integer
    switch (number) {
        case 0:
            HAL_GPIO_WritePin(GPIOB, A_Pin, GPIO_PIN_RESET);
            HAL_GPIO_WritePin(GPIOB, B_Pin, GPIO_PIN_RESET);
            HAL_GPIO_WritePin(GPIOB, C_Pin, GPIO_PIN_RESET);
            HAL_GPIO_WritePin(GPIOB, D_Pin, GPIO_PIN_RESET);
            HAL_GPIO_WritePin(GPIOB, E_Pin, GPIO_PIN_RESET);
            HAL_GPIO_WritePin(GPIOB, F_Pin, GPIO_PIN_RESET);
            HAL_GPIO_WritePin(GPIOB, G_Pin, GPIO_PIN_SET);
            break;
        case 1:
            HAL_GPIO_WritePin(GPIOB, A_Pin, GPIO_PIN_SET);
            HAL_GPIO_WritePin(GPIOB, B_Pin, GPIO_PIN_RESET);
            HAL_GPIO_WritePin(GPIOB, C_Pin, GPIO_PIN_RESET);
            HAL_GPIO_WritePin(GPIOB, D_Pin, GPIO_PIN_SET);
            HAL_GPIO_WritePin(GPIOB, E_Pin, GPIO_PIN_SET);
            HAL_GPIO_WritePin(GPIOB, F_Pin, GPIO_PIN_SET);
            HAL_GPIO_WritePin(GPIOB, G_Pin, GPIO_PIN_SET);
            break;
        case 2:
            HAL_GPIO_WritePin(GPIOB, A_Pin, GPIO_PIN_RESET);
            HAL_GPIO_WritePin(GPIOB, B_Pin, GPIO_PIN_RESET);
            HAL_GPIO_WritePin(GPIOB, C_Pin, GPIO_PIN_SET);
            HAL_GPIO_WritePin(GPIOB, D_Pin, GPIO_PIN_RESET);
            HAL_GPIO_WritePin(GPIOB, E_Pin, GPIO_PIN_RESET);
            HAL_GPIO_WritePin(GPIOB, F_Pin, GPIO_PIN_SET);
            HAL_GPIO_WritePin(GPIOB, G_Pin, GPIO_PIN_RESET);
            break;
        case 3:
            HAL_GPIO_WritePin(GPIOB, A_Pin, GPIO_PIN_RESET);
            HAL_GPIO_WritePin(GPIOB, B_Pin, GPIO_PIN_RESET);
            HAL_GPIO_WritePin(GPIOB, C_Pin, GPIO_PIN_RESET);
            HAL_GPIO_WritePin(GPIOB, D_Pin, GPIO_PIN_RESET);
            HAL_GPIO_WritePin(GPIOB, E_Pin, GPIO_PIN_SET);
            HAL_GPIO_WritePin(GPIOB, F_Pin, GPIO_PIN_SET);
            HAL_GPIO_WritePin(GPIOB, G_Pin, GPIO_PIN_RESET);
            break;
        case 4:
            HAL_GPIO_WritePin(GPIOB, A_Pin, GPIO_PIN_SET);
            HAL_GPIO_WritePin(GPIOB, B_Pin, GPIO_PIN_RESET);
            HAL_GPIO_WritePin(GPIOB, C_Pin, GPIO_PIN_RESET);
            HAL_GPIO_WritePin(GPIOB, D_Pin, GPIO_PIN_SET);
            HAL_GPIO_WritePin(GPIOB, E_Pin, GPIO_PIN_SET);
            HAL_GPIO_WritePin(GPIOB, F_Pin, GPIO_PIN_RESET);
            HAL_GPIO_WritePin(GPIOB, G_Pin, GPIO_PIN_RESET);
            break;
        case 5:
            HAL_GPIO_WritePin(GPIOB, A_Pin, GPIO_PIN_RESET);
            HAL_GPIO_WritePin(GPIOB, B_Pin, GPIO_PIN_SET);
            HAL_GPIO_WritePin(GPIOB, C_Pin, GPIO_PIN_RESET);
            HAL_GPIO_WritePin(GPIOB, D_Pin, GPIO_PIN_RESET);
            HAL_GPIO_WritePin(GPIOB, E_Pin, GPIO_PIN_SET);
            HAL_GPIO_WritePin(GPIOB, F_Pin, GPIO_PIN_RESET);
            HAL_GPIO_WritePin(GPIOB, G_Pin, GPIO_PIN_RESET);
            break;
        case 6:
            HAL_GPIO_WritePin(GPIOB, A_Pin, GPIO_PIN_RESET);
            HAL_GPIO_WritePin(GPIOB, B_Pin, GPIO_PIN_SET);
            HAL_GPIO_WritePin(GPIOB, C_Pin, GPIO_PIN_RESET);
            HAL_GPIO_WritePin(GPIOB, D_Pin, GPIO_PIN_RESET);
            HAL_GPIO_WritePin(GPIOB, E_Pin, GPIO_PIN_RESET);
            HAL_GPIO_WritePin(GPIOB, F_Pin, GPIO_PIN_RESET);
            HAL_GPIO_WritePin(GPIOB, G_Pin, GPIO_PIN_RESET);
            break;
        case 7:
            HAL_GPIO_WritePin(GPIOB, A_Pin, GPIO_PIN_RESET);
            HAL_GPIO_WritePin(GPIOB, B_Pin, GPIO_PIN_RESET);
            HAL_GPIO_WritePin(GPIOB, C_Pin, GPIO_PIN_RESET);
            HAL_GPIO_WritePin(GPIOB, D_Pin, GPIO_PIN_SET);
            HAL_GPIO_WritePin(GPIOB, E_Pin, GPIO_PIN_SET);
            HAL_GPIO_WritePin(GPIOB, F_Pin, GPIO_PIN_SET);
            HAL_GPIO_WritePin(GPIOB, G_Pin, GPIO_PIN_SET);
            break;
        case 8:
            HAL_GPIO_WritePin(GPIOB, A_Pin, GPIO_PIN_RESET);
            HAL_GPIO_WritePin(GPIOB, B_Pin, GPIO_PIN_RESET);
            HAL_GPIO_WritePin(GPIOB, C_Pin, GPIO_PIN_RESET);
            HAL_GPIO_WritePin(GPIOB, D_Pin, GPIO_PIN_RESET);
            HAL_GPIO_WritePin(GPIOB, E_Pin, GPIO_PIN_RESET);
            HAL_GPIO_WritePin(GPIOB, F_Pin, GPIO_PIN_RESET);
            HAL_GPIO_WritePin(GPIOB, G_Pin, GPIO_PIN_RESET);
            break;
        case 9:
            HAL_GPIO_WritePin(GPIOB, A_Pin, GPIO_PIN_RESET);
            HAL_GPIO_WritePin(GPIOB, B_Pin, GPIO_PIN_RESET);
            HAL_GPIO_WritePin(GPIOB, C_Pin, GPIO_PIN_RESET);
            HAL_GPIO_WritePin(GPIOB, D_Pin, GPIO_PIN_RESET);
            HAL_GPIO_WritePin(GPIOB, E_Pin, GPIO_PIN_SET);
            HAL_GPIO_WritePin(GPIOB, F_Pin, GPIO_PIN_RESET);
            HAL_GPIO_WritePin(GPIOB, G_Pin, GPIO_PIN_RESET);
            break;
        default:
            // If key is not a valid digit, turn off all segments
            HAL_GPIO_WritePin(GPIOB, A_Pin | B_Pin | C_Pin | D_Pin | E_Pin | F_Pin | G_Pin, GPIO_PIN_SET);
            break;
    }
}


void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
    if (GPIO_Pin == C1_Pin || GPIO_Pin == C2_Pin || GPIO_Pin == C3_Pin)
    {
        scan_keypad();
    }
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