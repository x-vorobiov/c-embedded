#include "main.h"
#include <stdio.h>
#include <string.h>

void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_USART3_UART_Init(void);

UART_HandleTypeDef huart3;

#define PIN(name) GPIO_PIN_##name

const uint16_t GPIOS[] = {
  PIN(12),
  PIN(13),
  PIN(14),
  PIN(15),
  PIN(12) | PIN(13) | PIN(14) | PIN(15),
};

const char* COLOR_NAMES[] = {
  "Green",
  "Orange",
  "Red",
  "Blue",
  "All colors",
};

int main(void)
{
  HAL_Init();

  SystemClock_Config();

  MX_GPIO_Init();
  MX_USART3_UART_Init();

  while (1) {
    uint8_t buf[1];
    HAL_StatusTypeDef result = HAL_UART_Receive(&huart3, buf, 1, 10);
    if (result == HAL_OK) {
      if (!(buf[0] >= '0' && buf[0] <= '9')) {
        HAL_UART_Transmit(&huart3,
            (uint8_t*)"Numeric input required!\r\n", 26, 100);
        continue;
      }
      const int COMMAND = buf[0] - '0';
      // NOTE: 1-2 are for green, 3-4 for orange, 5-6 for red, 7-8 for
      // blue, 9-0 for all colors. On/off depends on even/odd.
      const int i = (COMMAND == 0) * 5 + ((COMMAND + 1) >> 1) - 1;
      char displayText[20];
      sprintf(displayText, "%s %s %s!\r\n", COLOR_NAMES[i],
          (i == 4 ? "are" : "is"), (COMMAND % 2 ? "on" : "off"));
      HAL_UART_Transmit(
          &huart3, (uint8_t*)displayText, strlen(displayText), 100);
      HAL_GPIO_WritePin(
          GPIOD, GPIOS[i], COMMAND % 2 ? GPIO_PIN_SET : GPIO_PIN_RESET);
    }
  }
}

void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = { 0 };
  RCC_ClkInitTypeDef RCC_ClkInitStruct = { 0 };

  __HAL_RCC_PWR_CLK_ENABLE();
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);

  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_NONE;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK) {
    Error_Handler();
  }

  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_SYSCLK
      | RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_HSI;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_0) != HAL_OK) {
    Error_Handler();
  }
}

static void MX_USART3_UART_Init(void)
{
  huart3.Instance = USART3;
  huart3.Init.BaudRate = 115200;
  huart3.Init.WordLength = UART_WORDLENGTH_8B;
  huart3.Init.StopBits = UART_STOPBITS_1;
  huart3.Init.Parity = UART_PARITY_NONE;
  huart3.Init.Mode = UART_MODE_TX_RX;
  huart3.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart3.Init.OverSampling = UART_OVERSAMPLING_16;
  if (HAL_UART_Init(&huart3) != HAL_OK) {
    Error_Handler();
  }
}

static void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = { 0 };

  __HAL_RCC_GPIOD_CLK_ENABLE();

  HAL_GPIO_WritePin(GPIOD,
      GPIO_PIN_12 | GPIO_PIN_13 | GPIO_PIN_14 | GPIO_PIN_15, GPIO_PIN_RESET);

  GPIO_InitStruct.Pin = GPIO_PIN_12 | GPIO_PIN_13 | GPIO_PIN_14 | GPIO_PIN_15;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOD, &GPIO_InitStruct);
}

void Error_Handler(void)
{
  __disable_irq();
  while (1) { }
}

#ifdef USE_FULL_ASSERT

void assert_failed(uint8_t* file, uint32_t line) { }
#endif
