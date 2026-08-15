/******************************************************************************
 * @file    ADC_HAL.h
 * @brief   Header file for ADC Hardware Abstraction Layer (HAL).
 *
 * @details This module provides APIs to initialize the ADC peripheral and
 *          read analog values from the configured ADC channel.
 *
 * @author  Ahsan Basharat
 * @date    2026
 ******************************************************************************/

#ifndef ADC_HAL_H
#define ADC_HAL_H

#include "stm32f1xx_hal.h"
#include <stdint.h>

/* ADC Handle Structure */
typedef struct
{
    ADC_HandleTypeDef hadc;
} ADC_HAL;

/******************************************************************************
 * Function    : ADC_Init
 *
 * Description : Initializes ADC1 peripheral and configures PA0 as
 *               analog input.
 *
 * Parameter   : adc - Pointer to ADC object.
 *
 * Return      : None
 ******************************************************************************/
void ADC_Init(ADC_HAL * const adc);

/******************************************************************************
 * Function    : ADC_Read
 *
 * Description : Starts ADC conversion and returns converted value.
 *
 * Parameter   : adc - Pointer to ADC object.
 *
 * Return      : 12-bit ADC conversion result (0 - 4095).
 ******************************************************************************/
uint16_t ADC_Read(ADC_HAL * const adc);

#endif /* ADC_HAL_H */
