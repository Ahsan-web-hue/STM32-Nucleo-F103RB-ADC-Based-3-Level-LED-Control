#ifndef GPIO_HAL_H
#define GPIO_HAL_H

/* Include STM32 HAL library */
#include "stm32f1xx_hal.h"

/* GPIO object structure */
typedef struct
{
    GPIO_TypeDef *Port;    /* GPIO Port (GPIOA, GPIOB, etc.) */
    uint16_t Pin;          /* GPIO Pin Number */

} GPIO_HAL;


/* Initialize GPIO pin */
void LED_Init(GPIO_HAL * const led);

/* Turn LED ON */
void LED_On(GPIO_HAL * const led);

/* Turn LED OFF */
void LED_Off(GPIO_HAL * const led);

/* Toggle LED state */
void LED_TogglePin(GPIO_HAL * const led);

/* Read GPIO pin state */
GPIO_PinState Read_Pin(GPIO_HAL * const led);

#endif
