/*
 * clocks.c
 *
 *  Created on: Nov 16, 2022
 *      Author: carlos
 */
#include "clocks.h"

void systemClockConfig(void)
{
	/************************************************
	 * ***** General System Clock Configuration *****
	 * **********************************************
	 */
	/*
	* Enable the HSI and wait for it to become ready
	* 6.3.1 |pg.127
	*/
	RCC->CR |= RCC_CR_HSION;
	while (!(RCC->CR & RCC_CR_HSIRDY));

	/*
	* Set the Power Enable Clock and Voltage Regulator scaling
	* 6.3.13 | pg. 147 and 5.4.1 | pg. 111
	*/
	RCC->APB1ENR |= RCC_APB1ENR_PWREN;
	PWR->CR |= PWR_CR_VOS; // Voltage scale mode 1

	/*
	* Configure the Flash data cache, instruction cache, prefetch buffer and, flash latency
	* 3.8.1 | pg.80
	*/
	FLASH->ACR |= FLASH_ACR_DCEN;
	FLASH->ACR |= FLASH_ACR_ICEN;
	FLASH->ACR |= FLASH_ACR_PRFTEN;
	FLASH->ACR |= FLASH_ACR_LATENCY_5WS;

	/*
	* Configure the main PLL
	* 6.3.2 | pg.129
	*/
	RCC->PLLCFGR = 0x00000000; // Reset the register values
	RCC->PLLCFGR |= RCC_PLLCFGR_PLLSRC_HSI; // HSI clk selected as clk source
	RCC->PLLCFGR |= 0x00000000; // VCO freq / 2
	RCC->PLLCFGR |= 180 << RCC_PLLCFGR_PLLN_Pos; // N = 180
	RCC->PLLCFGR |= 8 << RCC_PLLCFGR_PLLM_Pos; // M = 8

	/*
	* Configure the main clock pre-scalers
	* 6.3.3 | pg.131
	*/
	RCC->CFGR |= RCC_CFGR_PPRE2_DIV2; // AHB clk divided by 2
	RCC->CFGR |= RCC_CFGR_PPRE1_DIV4; // AHB clk divided by 4
	RCC->CFGR |= RCC_CFGR_HPRE_DIV1; // System clk not divided


	/*
	* Enable PLL and wait for it to become ready
	* 6.3.1 | pg.127
	*/
	RCC->CR |= RCC_CR_PLLON; // Enable PLL
	while(!(RCC->CR & RCC_CR_PLLRDY));

	/*
	* Select clock source and wait for it to be set
	* 6.3.3 | pg. 131
	*/
	RCC->CFGR |= RCC_CFGR_SW_PLL; // PLL_P Selected as system clk
	while((RCC->CFGR & RCC_CFGR_SWS_Msk) != RCC_CFGR_SWS_PLL);


	/*
	* Enable GPIO Clock(s)
	* 6.3.10 | pg.144
	*/
	RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN; // Enable clock for I/O port A
	RCC->AHB1ENR |= RCC_AHB1ENR_GPIOCEN; // Enable clock for I/O port C


	/************************************************
	 * ***** SYSCFG Clock Configuration *****
	 * Used for interrupts
	 * ***********************************************
	 */

	/*
	 * Enable System Configuration Controller Clk
	 * 6.3.14 | pg.149
	 */
	RCC->APB2ENR |= RCC_APB2ENR_SYSCFGEN;
}

