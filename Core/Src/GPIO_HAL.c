	#include "GPIO_HAL.h"
	#include "GPIO.h"

	/*------------------------------------------------------------
	 * Function : LED_Init()
	 * Purpose  : Configure GPIO pin as Push-Pull Output
	 *-----------------------------------------------------------*/
	void LED_Init(GPIO_HAL * const led)
	{
		GPIO_InitTypeDef GPIO_InitStruct = {0};

		/* Check for NULL pointer */
		if (led != NULL)
		{
			/* Enable GPIOA peripheral clock */
			__HAL_RCC_GPIOA_CLK_ENABLE();

			/* Configure GPIO parameters */
			GPIO_InitStruct.Pin   = led->Pin;
			GPIO_InitStruct.Mode  = GPIO_MODE_OUTPUT_PP;
			GPIO_InitStruct.Pull  = GPIO_NOPULL;
			GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;

			/* Initialize GPIO */
			HAL_GPIO_Init(led->Port, &GPIO_InitStruct);

			/* Keep LED OFF initially */
			HAL_GPIO_WritePin(led->Port,
							  led->Pin,
							  GPIO_PIN_RESET);
		}
	}

	/*------------------------------------------------------------
	 * Function : LED_On()
	 * Purpose  : Set GPIO pin HIGH
	 *-----------------------------------------------------------*/
	void LED_On(GPIO_HAL * const led)
	{
		if (led != NULL)
		{
			HAL_GPIO_WritePin(led->Port,
							  led->Pin,
							  GPIO_PIN_SET);
		}
	}

	/*------------------------------------------------------------
	 * Function : LED_Off()
	 * Purpose  : Set GPIO pin LOW
	 *-----------------------------------------------------------*/
	void LED_Off(GPIO_HAL * const led)
	{
		if (led != NULL)
		{
			HAL_GPIO_WritePin(led->Port,
							  led->Pin,
							  GPIO_PIN_RESET);
		}
	}

	/*------------------------------------------------------------
	 * Function : LED_TogglePin()
	 * Purpose  : Toggle GPIO output state
	 *-----------------------------------------------------------*/
	void LED_TogglePin(GPIO_HAL * const led)
	{
		if (led != NULL)
		{
			HAL_GPIO_TogglePin(led->Port,
							   led->Pin);
		}
	}

	/*------------------------------------------------------------
	 * Function : Read_Pin()
	 * Purpose  : Read current GPIO pin state
	 * Return   : GPIO_PIN_SET / GPIO_PIN_RESET
	 *-----------------------------------------------------------*/
	GPIO_PinState Read_Pin(GPIO_HAL * const led)
	{
		GPIO_PinState state = GPIO_PIN_RESET;

		if (led != NULL)
		{
			state = HAL_GPIO_ReadPin(led->Port,
									 led->Pin);
		}

		return state;
	}



