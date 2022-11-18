#include "clocks.h"
#include "constants.h"
#include "globals.h"
#include "gpio.h"
#include "interrupts.h"
#include "main.h"
#include "stm32f446xx.h"

int main (void)
{
	systemClockConfig();
	GPIO_Config();
	interrupts_config();

	while (1){}
}


