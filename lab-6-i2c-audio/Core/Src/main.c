#include "main.h"

#define CS43L22_I2C_ADDRESS 0x94
#define I2C_TIMEOUT 10

typedef enum {
    C4,
    C5,
    C6,
    D5,
    D6,
    E5,
    E6,
    F5,
    F6,
    G5,
    G6,
    A5,
    A6,
    B5,
    B6,
    C7
} Pitch;

I2C_HandleTypeDef hi2c1;

I2S_HandleTypeDef hi2s3;
DMA_HandleTypeDef hdma_spi3_tx;

int16_t dataI2S[100] = { 0 };

void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_DMA_Init(void);
static void MX_I2C1_Init(void);
static void MX_I2S3_Init(void);

void CS43L22_Init(void)
{

    HAL_GPIO_WritePin(GPIOD, GPIO_PIN_4, GPIO_PIN_SET);

    uint8_t TxBuffer[2];

    TxBuffer[0] = 0x0D;
    TxBuffer[1] = 0x01;
    HAL_I2C_Master_Transmit(
        &hi2c1, CS43L22_I2C_ADDRESS, (uint8_t*)&TxBuffer, 2, I2C_TIMEOUT);

    TxBuffer[0] = 0x00;
    TxBuffer[1] = 0x99;
    HAL_I2C_Master_Transmit(
        &hi2c1, CS43L22_I2C_ADDRESS, (uint8_t*)&TxBuffer, 2, I2C_TIMEOUT);

    TxBuffer[0] = 0x47;
    TxBuffer[1] = 0x80;
    HAL_I2C_Master_Transmit(
        &hi2c1, CS43L22_I2C_ADDRESS, (uint8_t*)&TxBuffer, 2, I2C_TIMEOUT);

    TxBuffer[0] = 0x32;
    TxBuffer[1] = 0xFF;
    HAL_I2C_Master_Transmit(
        &hi2c1, CS43L22_I2C_ADDRESS, (uint8_t*)&TxBuffer, 2, I2C_TIMEOUT);

    TxBuffer[0] = 0x32;
    TxBuffer[1] = 0x7F;
    HAL_I2C_Master_Transmit(
        &hi2c1, CS43L22_I2C_ADDRESS, (uint8_t*)&TxBuffer, 2, I2C_TIMEOUT);

    TxBuffer[0] = 0x00;
    TxBuffer[1] = 0x00;
    HAL_I2C_Master_Transmit(
        &hi2c1, CS43L22_I2C_ADDRESS, (uint8_t*)&TxBuffer, 2, I2C_TIMEOUT);

    TxBuffer[0] = 0x04;
    TxBuffer[1] = 0xAF;
    HAL_I2C_Master_Transmit(
        &hi2c1, CS43L22_I2C_ADDRESS, (uint8_t*)&TxBuffer, 2, I2C_TIMEOUT);

    TxBuffer[0] = 0x0D;
    TxBuffer[1] = 0x70;
    HAL_I2C_Master_Transmit(
        &hi2c1, CS43L22_I2C_ADDRESS, (uint8_t*)&TxBuffer, 2, I2C_TIMEOUT);

    TxBuffer[0] = 0x05;
    TxBuffer[1] = 0x81;
    HAL_I2C_Master_Transmit(
        &hi2c1, CS43L22_I2C_ADDRESS, (uint8_t*)&TxBuffer, 2, I2C_TIMEOUT);

    TxBuffer[0] = 0x06;
    TxBuffer[1] = 0x07;
    HAL_I2C_Master_Transmit(
        &hi2c1, CS43L22_I2C_ADDRESS, (uint8_t*)&TxBuffer, 2, I2C_TIMEOUT);

    TxBuffer[0] = 0x0A;
    TxBuffer[1] = 0x00;
    HAL_I2C_Master_Transmit(
        &hi2c1, CS43L22_I2C_ADDRESS, (uint8_t*)&TxBuffer, 2, I2C_TIMEOUT);

    TxBuffer[0] = 0x27;
    TxBuffer[1] = 0x00;
    HAL_I2C_Master_Transmit(
        &hi2c1, CS43L22_I2C_ADDRESS, (uint8_t*)&TxBuffer, 2, I2C_TIMEOUT);

    TxBuffer[0] = 0x1A;
    TxBuffer[1] = 0x0A;
    HAL_I2C_Master_Transmit(
        &hi2c1, CS43L22_I2C_ADDRESS, (uint8_t*)&TxBuffer, 2, I2C_TIMEOUT);

    TxBuffer[0] = 0x1B;
    TxBuffer[1] = 0x0A;
    HAL_I2C_Master_Transmit(
        &hi2c1, CS43L22_I2C_ADDRESS, (uint8_t*)&TxBuffer, 2, I2C_TIMEOUT);

    TxBuffer[0] = 0x1F;
    TxBuffer[1] = 0x0F;
    HAL_I2C_Master_Transmit(
        &hi2c1, CS43L22_I2C_ADDRESS, (uint8_t*)&TxBuffer, 2, I2C_TIMEOUT);

    TxBuffer[0] = 0x02;
    TxBuffer[1] = 0x9E;
    HAL_I2C_Master_Transmit(
        &hi2c1, CS43L22_I2C_ADDRESS, (uint8_t*)&TxBuffer, 2, I2C_TIMEOUT);
}

void CS43L22_Beep(Pitch pitch, uint32_t duration_ms)
{
    uint8_t TxBuffer[2];

    TxBuffer[0] = 0x1D;
    TxBuffer[1] = 0x00;
    HAL_I2C_Master_Transmit(
        &hi2c1, CS43L22_I2C_ADDRESS, (uint8_t*)&TxBuffer, 2, I2C_TIMEOUT);

    TxBuffer[0] = 0x1C;
    switch (pitch) {
    case C4:
        TxBuffer[1] = 0x00;
        break;
    case C5:
        TxBuffer[1] = 0x10;
        break;
    case C6:
        TxBuffer[1] = 0x80;
        break;
    case D5:
        TxBuffer[1] = 0x20;
        break;
    case D6:
        TxBuffer[1] = 0x90;
        break;
    case E5:
        TxBuffer[1] = 0x30;
        break;
    case E6:
        TxBuffer[1] = 0xA0;
        break;
    case F5:
        TxBuffer[1] = 0x40;
        break;
    case F6:
        TxBuffer[1] = 0xB0;
        break;
    case G5:
        TxBuffer[1] = 0x50;
        break;
    case G6:
        TxBuffer[1] = 0xC0;
        break;
    case A5:
        TxBuffer[1] = 0x60;
        break;
    case A6:
        TxBuffer[1] = 0xD0;
        break;
    case B5:
        TxBuffer[1] = 0x70;
        break;
    case B6:
        TxBuffer[1] = 0xE0;
        break;
    case C7:
        TxBuffer[1] = 0xF0;
        break;
    default:
        TxBuffer[1] = 0x00;
        break;
    }
    HAL_I2C_Master_Transmit(
        &hi2c1, CS43L22_I2C_ADDRESS, (uint8_t*)&TxBuffer, 2, I2C_TIMEOUT);

    TxBuffer[0] = 0x1E;
    TxBuffer[1] = 0xC0;
    HAL_I2C_Master_Transmit(
        &hi2c1, CS43L22_I2C_ADDRESS, (uint8_t*)&TxBuffer, 2, I2C_TIMEOUT);

    HAL_Delay(duration_ms);

    TxBuffer[0] = 0x1E;
    TxBuffer[1] = 0x00;
    HAL_I2C_Master_Transmit(
        &hi2c1, CS43L22_I2C_ADDRESS, (uint8_t*)&TxBuffer, 2, I2C_TIMEOUT);
}

int main(void)
{
    HAL_Init();

    SystemClock_Config();

    MX_GPIO_Init();
    MX_DMA_Init();
    MX_I2C1_Init();
    MX_I2S3_Init();

    CS43L22_Init();

    HAL_I2S_Transmit_DMA(&hi2s3, (uint16_t*)dataI2S, 100);

    const Pitch pitches[]
        = { C4, C5, D5, E5, F5, G5, A5, B5, C6, D6, E6, F6, G6, A6, B6, C7 };

    int pitchesCount = sizeof(pitches) / sizeof(pitches[0]);

    for (int i = 0; i < 2 * pitchesCount - 1; i++) {
        int index = (i < pitchesCount) ? i : 2 * pitchesCount - 1 - i;
        CS43L22_Beep(pitches[index], 100);
        HAL_Delay(50);
    }

    HAL_Delay(1000);

    const Pitch melody[] = { C5, E5, G5, E5, F5, A5, C6, A5, G5, B5, D6, B5, A5,
        C6, E6, C6, D5, F5, A5, F5, G5, B5, D6, B5, C5, E5, G5, E5, F5, A5, C6,
        A5, G5, B5, D6, B5, A5, C6, E6, C6, D5, F5, A5, F5, G5, B5, D6, B5, C5,
        E5, G5, E5, F5, A5, C6, A5, G5, B5, D6, B5, A5, C6, E6, C6 };

    int durations[] = { 500, 250, 250, 500, 250, 500, 250, 500, 250, 500, 250,
        500, 250, 500, 500, 500, 500, 250, 250, 500, 250, 500, 250, 500, 250,
        500, 250, 500, 250, 500, 500, 500, 500, 250, 250, 500, 250, 500, 250,
        500, 250, 500, 250, 500, 250, 500, 500, 500, 500, 250, 250, 500, 250,
        500, 250, 500, 250, 500, 250, 500, 250, 500, 500, 500 };

    while (1)
    {
        for (int i = 0; i < sizeof(melody) / sizeof(melody[0]); i++)
        {
            CS43L22_Beep(melody[i], durations[i]);
            HAL_Delay(durations[i] / 2);
        }
    }
}

void SystemClock_Config(void)
{
    RCC_OscInitTypeDef RCC_OscInitStruct = { 0 };
    RCC_ClkInitTypeDef RCC_ClkInitStruct = { 0 };

    __HAL_RCC_PLL_PLLM_CONFIG(16);

    __HAL_RCC_PLL_PLLSOURCE_CONFIG(RCC_PLLSOURCE_HSI);

    __HAL_RCC_PWR_CLK_ENABLE();
    __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);

    RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
    RCC_OscInitStruct.HSIState = RCC_HSI_ON;
    RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
    RCC_OscInitStruct.PLL.PLLState = RCC_PLL_NONE;
    RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
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

static void MX_I2C1_Init(void)
{

    hi2c1.Instance = I2C1;
    hi2c1.Init.ClockSpeed = 100000;
    hi2c1.Init.DutyCycle = I2C_DUTYCYCLE_2;
    hi2c1.Init.OwnAddress1 = 0;
    hi2c1.Init.AddressingMode = I2C_ADDRESSINGMODE_7BIT;
    hi2c1.Init.DualAddressMode = I2C_DUALADDRESS_DISABLE;
    hi2c1.Init.OwnAddress2 = 0;
    hi2c1.Init.GeneralCallMode = I2C_GENERALCALL_DISABLE;
    hi2c1.Init.NoStretchMode = I2C_NOSTRETCH_DISABLE;
    if (HAL_I2C_Init(&hi2c1) != HAL_OK) {
        Error_Handler();
    }
}

static void MX_I2S3_Init(void)
{

    hi2s3.Instance = SPI3;
    hi2s3.Init.Mode = I2S_MODE_MASTER_TX;
    hi2s3.Init.Standard = I2S_STANDARD_PHILIPS;
    hi2s3.Init.DataFormat = I2S_DATAFORMAT_16B;
    hi2s3.Init.MCLKOutput = I2S_MCLKOUTPUT_ENABLE;
    hi2s3.Init.AudioFreq = I2S_AUDIOFREQ_48K;
    hi2s3.Init.CPOL = I2S_CPOL_LOW;
    hi2s3.Init.ClockSource = I2S_CLOCK_PLL;
    hi2s3.Init.FullDuplexMode = I2S_FULLDUPLEXMODE_DISABLE;
    if (HAL_I2S_Init(&hi2s3) != HAL_OK) {
        Error_Handler();
    }
}

static void MX_DMA_Init(void)
{

    __HAL_RCC_DMA1_CLK_ENABLE();

    HAL_NVIC_SetPriority(DMA1_Stream5_IRQn, 0, 0);
    HAL_NVIC_EnableIRQ(DMA1_Stream5_IRQn);
}

static void MX_GPIO_Init(void)
{
    GPIO_InitTypeDef GPIO_InitStruct = { 0 };

    __HAL_RCC_GPIOA_CLK_ENABLE();
    __HAL_RCC_GPIOC_CLK_ENABLE();
    __HAL_RCC_GPIOD_CLK_ENABLE();
    __HAL_RCC_GPIOB_CLK_ENABLE();

    HAL_GPIO_WritePin(GPIOD, GPIO_PIN_4, GPIO_PIN_RESET);

    GPIO_InitStruct.Pin = GPIO_PIN_4;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
    HAL_GPIO_Init(GPIOD, &GPIO_InitStruct);
}

void Error_Handler(void)
{

    __disable_irq();
    while (1)
        ;
}

#ifdef USE_FULL_ASSERT
void assert_failed(uint8_t* file, uint32_t line) { }
#endif
