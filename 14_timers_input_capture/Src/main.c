#include <stdio.h>
#include "stm32f4xx.h"
#include <stdint.h>
#include "uart.h"
#include "adc.h"
#include "systick.h"
#include "timers.h"

#define GPIOAEN (1U<<0)
#define PIN5 (1U<<5)
#define LED_PIN PIN5


int timestamp = 0;
/*setup : connect a jumper wire from PA5 to PA6*/
int main (void)
{

tim2_output_compare();
tim3_input_capture();

while(1)
	{
//wait until edge is captures
		while(!(TIM3->SR & SR_CC1IF)){}
	timestamp = TIM3->CCR1;
	}

}


