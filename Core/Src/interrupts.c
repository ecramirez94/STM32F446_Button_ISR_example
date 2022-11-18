/*
 * interrupts.c
 *
 *  Created on: Nov 16, 2022
 *      Author: carlos
 */
#include "interrupts.h"
#include "globals.h"

void interrupts_config(void)
{
	/*
	 * Disable the EXTI Mask(s)
	 * 10.3.1 | pg.247
	 */
	EXTI->IMR |= EXTI_IMR_MR4; // Un-mask interrupt request on line 4

	/*
	 * Configure Rising/falling edge trigger
	 * 10.3.3/4 | pg.248
	 */
	// EXTI Line 4
	EXTI->RTSR &= ~(EXTI_RTSR_TR4); // Disable RISING edge interrupt trigger
	EXTI->FTSR |= EXTI_FTSR_TR4; // Enable FALLING edge to trigger interrupt

	/*
	 * Configure the EXTI configuration Register in the SYSCFG
	 * 8.2.5 | pg.199
	 */
	SYSCFG->EXTICR[1] |= SYSCFG_EXTICR2_EXTI4_PB;

	/*
	 * Set Interrupt Priority
	 */
	NVIC_SetPriority(EXTI4_IRQn, 0);

	/*
	 * Enable the Interrupt
	 */
	NVIC_EnableIRQ(EXTI4_IRQn);
}


void EXTI4_IRQHandler(void)
{
	/*
	 * EXTI4 is dedicated to UI button pushes.
	 * Each button is assigned a GPIO pin whose state
	 * is read at the beginning if the ISR. The EXTI4
	 * interrupt is triggered by the press of any button
	 * as they are "wire-OR'd" to pin PB4 using 1N4148
	 * small signal diodes. All buttons and PB4 are
	 * Active LOW signals.
	 *
	 * *** Routine***
	 * 1. Read the GPIO Port Input Data Register(s) for all buttons
	 * 2. Mask and clear un-related Input Data (the state of pins who
	 * don't have a button attached)
	 * 3. Sort remaining values to determine which button was pressed.
	 */

	// 1. Read GPIO Port Input Data Register(s)
	uint32_t ulGPIO_port_A = GPIOA->IDR;
	uint32_t ulGPIO_port_C = GPIOC->IDR;

	// 2. Mask and clear un-related data for each button
	// If expression evaluates to a '1', that is the pushed button
	// Port A
	uint8_t ucDOWN_button = !((ulGPIO_port_A & GPIO_IDR_ID6) >> GPIO_IDR_ID6_Pos); // PA6 -> DOWN
	uint8_t ucLEFT_button = !((ulGPIO_port_A & GPIO_IDR_ID7) >> GPIO_IDR_ID7_Pos); // PA7 -> LEFT
	uint8_t ucREVERSE_button = !((ulGPIO_port_A & GPIO_IDR_ID8) >> GPIO_IDR_ID8_Pos); // PA8 -> REVERSE
	uint8_t ucSTOP_button = !((ulGPIO_port_A & GPIO_IDR_ID11) >> GPIO_IDR_ID11_Pos); // PA11 -> STOP
	// Port C
	uint8_t ucBACK_button = !((ulGPIO_port_C & GPIO_IDR_ID6) >> GPIO_IDR_ID6_Pos); // PC6 -> BACK
	uint8_t ucSTART_button = !((ulGPIO_port_C & GPIO_IDR_ID7) >> GPIO_IDR_ID7_Pos); // PC7 -> START
	uint8_t ucSELECT_button = !((ulGPIO_port_C & GPIO_IDR_ID8) >> GPIO_IDR_ID8_Pos); // PC8 -> SELECT
	uint8_t ucRIGHT_button = !((ulGPIO_port_C & GPIO_IDR_ID9) >> GPIO_IDR_ID9_Pos); // PC9 -> RIGHT
	uint8_t ucUP_button = !((ulGPIO_port_C & GPIO_IDR_ID13) >> GPIO_IDR_ID13_Pos); // PC13 -> UP

	// 3. Check and sort button press
	if ((ucDOWN_button + ucLEFT_button + ucREVERSE_button + ucSTOP_button +
			ucBACK_button + ucSTART_button + ucSELECT_button + ucRIGHT_button +
				ucUP_button) == 1) // Make sure not more than one button is pressed.
	{
		/*
		 * GPIO port bit set/reset
		 * 7.4.7 | pg. 190
		 */
		if (ucDOWN_button == TRUE)
		{
			GPIOA->BSRR |= GPIO_BSRR_BS5;
		}

		else if (ucLEFT_button == TRUE)
		{
			GPIOA->BSRR |= GPIO_BSRR_BS5;
		}

		else if (ucREVERSE_button == TRUE)
		{
			GPIOA->BSRR |= GPIO_BSRR_BS5;
		}

		else if (ucSTOP_button == TRUE)
		{
			GPIOA->BSRR |= GPIO_BSRR_BS5;
		}

		else if (ucBACK_button == TRUE)
		{
			GPIOA->BSRR |= GPIO_BSRR_BR5;
		}

		else if (ucSTART_button == TRUE)
		{
			GPIOA->BSRR |= GPIO_BSRR_BS5;
		}

		else if (ucSELECT_button == TRUE)
		{
			GPIOA->BSRR |= GPIO_BSRR_BS5;
		}

		else if (ucRIGHT_button == TRUE)
		{
			GPIOA->BSRR |= GPIO_BSRR_BS5;
		}

		else if (ucUP_button == TRUE)
		{
			GPIOA->BSRR |= GPIO_BSRR_BS5;
		}
	}

	/*
	 * Clear Interrupt flag in EXTI Pending Register on ISR exit.
	 * 10.3.6 | pg.249
	 */
	EXTI->PR |= EXTI_PR_PR4;
}
//void EXTI9_5_IRQHandler(void)
//{
//	/*
//	* Clear Interrupt flag in EXTI Pending Register after each
//	* interrupt is handled.
//	* Example: EXTI->PR |= EXTI_PR_PRx; | x = interrupt #
//	* 10.3.6 | pg.249
//	*/
//	uint32_t val = EXTI->PR;
//
//	switch (val)
//	{
//		case EXTI_PR_PR5: // Not yet implemented
//
//			// Clear Interrupt Flag
//			EXTI->PR |= EXTI_PR_PR5;
//		break;
//
//		case EXTI_PR_PR6: // BACK Button
//
//			// Clear Interrupt Flag
//			EXTI->PR |= EXTI_PR_PR6;
//		break;
//
//		case EXTI_PR_PR7: // START Button
//
//			// Clear Interrupt Flag
//			EXTI->PR |= EXTI_PR_PR7;
//		break;
//
//		case EXTI_PR_PR8: // SELECT Button
//			if (states == TRUE)
//			{
//				GPIOA->BSRR |= GPIO_BSRR_BR5;
//				states = FALSE;
//			}
//			else
//			{
//				GPIOA->BSRR |= GPIO_BSRR_BS5;
//				states = TRUE;
//			}
//
//			// Clear Interrupt Flag
//			EXTI->PR |= EXTI_PR_PR8;
//		break;
//
//		case EXTI_PR_PR9:
//
//			// Clear Interrupt Flag
//			EXTI->PR |= EXTI_PR_PR9;
//		break;
//		default:
//		break;
//	}
//}


