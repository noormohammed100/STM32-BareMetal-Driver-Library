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

static void callback_timer2(void);

int main (void)
{
RCC->AHB1ENR = GPIOAEN;
GPIOA->MODER |= (1U<<10);
GPIOA->MODER &=~ (1U<<11);

uart2_tx_init();
tim2_1hz_init();

while(1)
	{
while(!=(TIM2->SR & SR_UIF)){}
//clear the flag
TIM2->SR &=~ SR_UIF;
	printf("A second just passed \n\r");
				GPIOA->ODR ^= LED_PIN;
				systickDelayMS(1000);
	}

}
