/*
 * gpio.c
 *
 *  Created on: Nov 16, 2022
 *      Author: carlos
 */
#include "gpio.h"

void GPIO_Config(void)
{
	/*
	* Set pin direction
	* 7.4.1 | pg. 187
	*/
	// GPIO Port A
		// OUTPUTS
		GPIOA->MODER |= (1 << GPIO_MODER_MODER5_Pos); // Set PA5 as OUTPUT -> On-Board LED

		// INPUTS
		GPIOA->MODER &= ~(GPIO_MODER_MODER6); // Set PA6 as INPUT -> DOWN button
		GPIOA->MODER &= ~(GPIO_MODER_MODER7); // Set PA7 as INPUT -> LEFT button
		GPIOA->MODER &= ~(GPIO_MODER_MODER8); // Set PA8 as INPUT -> REVERSE button
		GPIOA->MODER &= ~(GPIO_MODER_MODER11); // Set PA11 as INPUT -> STOP button

	// GPIO Port B
		GPIOB->MODER &= ~(GPIO_MODER_MODER4); // Set PB4 as INPUT -> Button IRQ

	// GPIO Port C
		//INPUTS
		GPIOC->MODER &= ~(GPIO_MODER_MODER6); // Set PC6 as INPUT -> BACK button
		GPIOC->MODER &= ~(GPIO_MODER_MODER7); // Set PC7 as INPUT -> START button
		GPIOC->MODER &= ~(GPIO_MODER_MODER8); // Set PC8 as INPUT -> SELECT button
		GPIOC->MODER &= ~(GPIO_MODER_MODER9); // Set PC9 as INPUT -> RIGHT button
		GPIOC->MODER &= ~(GPIO_MODER_MODER13); // Set PC13 as INPUT -> UP button


	/*
	* Configure pin output mode
	* 7.4.2, 7.4.3, 7.4.4 | pg.188/9
	*/
	// GPIO Port A
		// OUTPUTS
		GPIOA->OTYPER &= ~(GPIO_OTYPER_OT5); // Push-Pull
		GPIOA->OSPEEDR |= (2 << GPIO_OSPEEDR_OSPEED5_Pos); // Fast speed
		GPIOA->PUPDR &= ~(GPIO_PUPDR_PUPD5); // No pull up/down

		// INPUTS
		GPIOA->PUPDR |= GPIO_PUPDR_PUPD6_0; // Enable pull up on pin PA6
		GPIOA->PUPDR |= GPIO_PUPDR_PUPD7_0; // Enable pull up on pin PA7
		GPIOA->PUPDR |= GPIO_PUPDR_PUPD8_0; // Enable pull up on pin PA8
		GPIOA->PUPDR |= GPIO_PUPDR_PUPD11_0; // Enable pull up on pin PA11

	// GPIO Port B
		// INPUTS
		GPIOB->PUPDR |= GPIO_PUPDR_PUPD4_0; // Enable pull up on PB4

	// GPIO Port C
		// INPUTS
		GPIOC->PUPDR |= GPIO_PUPDR_PUPD6_0; // Enable pull up on pin PC6
		GPIOC->PUPDR |= GPIO_PUPDR_PUPD7_0; // Enable pull up on pin PC7
		GPIOC->PUPDR |= GPIO_PUPDR_PUPD8_0; // Enable pull up on pin PC8
		GPIOC->PUPDR |= GPIO_PUPDR_PUPD9_0; // Enable pull up on pin PC9
		GPIOC->PUPDR |= GPIO_PUPDR_PUPD13_0; // Enable pull up on pin PC13
}
