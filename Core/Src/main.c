/******************************************************************************
 * @file    main.c
 * @brief   ADC Based LED Control using STM32F103RB
 *
 * @details
 * This application reads the analog voltage from a potentiometer connected
 * to ADC1 Channel 0 (PA0). According to the converted ADC value, one of
 * three LEDs is turned ON.
 *
 * LED1 (PA5) : Low ADC Range
 * LED2 (PA6) : Medium ADC Range
 * LED3 (PA7) : High ADC Range
 *
 * MCU        : STM32F103RB
 * IDE        : STM32CubeIDE
 * Library    : STM32 HAL Driver
 *
 * @author    Ahsan Basharat
 * @date      2026
 ******************************************************************************/

#include "main.h"
#include "GPIO_HAL.h"
#include "ADC_HAL.h"

/******************************************************************************
 *                              Macro Definitions
 ******************************************************************************/

/* ADC Threshold Values */
#define ADC_LOW_THRESHOLD      (1365U)
#define ADC_HIGH_THRESHOLD     (2730U)

/* Delay between ADC Samples (ms) */
#define ADC_SAMPLE_DELAY_MS    (10U)

/******************************************************************************
 *                        Function Prototypes
 ******************************************************************************/

void SystemClock_Config(void);

/******************************************************************************
 *                         Global LED Objects
 ******************************************************************************/

/* LED connected to GPIOA Pin 5 */
GPIO_HAL LED =
{
    GPIOA,
    GPIO_PIN_5
};

/* LED connected to GPIOA Pin 6 */
GPIO_HAL LED1 =
{
    GPIOA,
    GPIO_PIN_6
};

/* LED connected to GPIOA Pin 7 */
GPIO_HAL LED2 =
{
    GPIOA,
    GPIO_PIN_7
};

/******************************************************************************
 *                         Global ADC Object
 ******************************************************************************/

ADC_HAL ADC1_Driver;

/******************************************************************************
 *                         Global Variables
 ******************************************************************************/

/* Stores ADC Conversion Result */
static uint16_t ADC_Value = 0U;

/******************************************************************************
 * Function    : main
 *
 * Description :
 *      Main program entry point.
 *
 *      1. Initializes HAL Library.
 *      2. Configures the System Clock.
 *      3. Initializes GPIO LEDs.
 *      4. Initializes ADC Peripheral.
 *      5. Continuously reads ADC value.
 *      6. Controls LEDs according to ADC range.
 *
 * Parameters :
 *      None
 *
 * Return :
 *      int
 ******************************************************************************/
int main(void)
{
    /* Initialize HAL Library */
    HAL_Init();

    /* Configure System Clock */
    SystemClock_Config();

    /* Initialize LED GPIOs */
    LED_Init(&LED);
    LED_Init(&LED1);
    LED_Init(&LED2);

    /* Initialize ADC Peripheral */
    ADC_Init(&ADC1_Driver);

    /* Infinite Loop */
    while (1)
    {
        /* Read Potentiometer Value */
        ADC_Value = ADC_Read(&ADC1_Driver);

        /* Low ADC Range */
        if (ADC_Value < ADC_LOW_THRESHOLD)
        {
            LED_On(&LED);
            LED_Off(&LED1);
            LED_Off(&LED2);
        }
        /* Medium ADC Range */
        else if (ADC_Value < ADC_HIGH_THRESHOLD)
        {
            LED_Off(&LED);
            LED_On(&LED1);
            LED_Off(&LED2);
        }
        /* High ADC Range */
        else
        {
            LED_Off(&LED);
            LED_Off(&LED1);
            LED_On(&LED2);
        }

        /* Wait before next ADC conversion */
        HAL_Delay(ADC_SAMPLE_DELAY_MS);
    }
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
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI_DIV2;
  RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL2;
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

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_0) != HAL_OK)
  {
    Error_Handler();
  }
  PeriphClkInit.PeriphClockSelection = RCC_PERIPHCLK_ADC;
  PeriphClkInit.AdcClockSelection = RCC_ADCPCLK2_DIV2;
  if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInit) != HAL_OK)
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
