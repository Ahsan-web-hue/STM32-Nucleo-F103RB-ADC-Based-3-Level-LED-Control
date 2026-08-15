/******************************************************************************
 * @file    ADC_HAL.c
 * @brief   ADC Hardware Abstraction Layer Source File.
 *
 * @details Implements ADC initialization and ADC read functions using
 *          STM32 HAL Library.
 ******************************************************************************/

#include "ADC_HAL.h"

/******************************************************************************
 * Function    : ADC_Init
 *
 * Description : Initializes ADC1 Channel 0 (PA0) for single conversion mode.
 *
 * Parameter   : adc - Pointer to ADC object.
 *
 * Return      : None
 ******************************************************************************/
void ADC_Init(ADC_HAL * const adc)
{
    GPIO_InitTypeDef GPIO_InitStruct = {0};
    ADC_ChannelConfTypeDef sConfig = {0};

    if (adc != NULL)
    {
        /* Enable GPIOA peripheral clock */
        __HAL_RCC_GPIOA_CLK_ENABLE();

        /* Enable ADC1 peripheral clock */
        __HAL_RCC_ADC1_CLK_ENABLE();

        /* Configure PA0 as Analog Input */
        GPIO_InitStruct.Pin  = GPIO_PIN_0;
        GPIO_InitStruct.Mode = GPIO_MODE_ANALOG;

        HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

        /* Configure ADC1 parameters */
        adc->hadc.Instance = ADC1;
        adc->hadc.Init.ScanConvMode = ADC_SCAN_DISABLE;
        adc->hadc.Init.ContinuousConvMode = DISABLE;
        adc->hadc.Init.DiscontinuousConvMode = DISABLE;
        adc->hadc.Init.ExternalTrigConv = ADC_SOFTWARE_START;
        adc->hadc.Init.DataAlign = ADC_DATAALIGN_RIGHT;
        adc->hadc.Init.NbrOfConversion = 1U;

        (void)HAL_ADC_Init(&adc->hadc);

        /* Configure ADC Regular Channel */
        sConfig.Channel = ADC_CHANNEL_0;
        sConfig.Rank = ADC_REGULAR_RANK_1;
        sConfig.SamplingTime = ADC_SAMPLETIME_55CYCLES_5;

        (void)HAL_ADC_ConfigChannel(&adc->hadc, &sConfig);

        /* Perform ADC Calibration */
        (void)HAL_ADCEx_Calibration_Start(&adc->hadc);
    }
}
/******************************************************************************
 * Function    : ADC_Read
 *
 * Description : Starts an ADC conversion, waits for conversion completion,
 *               reads the converted value, and stops the ADC.
 *
 * Parameter   : adc - Pointer to ADC object.
 *
 * Return      : ADC conversion value (0 - 4095).
 ******************************************************************************/
uint16_t ADC_Read(ADC_HAL * const adc)
{
    uint16_t value = 0U;

    if (adc != NULL)
    {
        /* Start ADC Conversion */
        (void)HAL_ADC_Start(&adc->hadc);

        /* Wait until conversion is complete */
        (void)HAL_ADC_PollForConversion(&adc->hadc, HAL_MAX_DELAY);

        /* Read converted ADC value */
        value = (uint16_t)HAL_ADC_GetValue(&adc->hadc);

        /* Stop ADC Conversion */
        (void)HAL_ADC_Stop(&adc->hadc);
    }

    return value;
}
