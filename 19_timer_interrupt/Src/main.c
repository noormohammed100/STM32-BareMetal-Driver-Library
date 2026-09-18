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
tim2_1hz_interrupt();

while(1)
	{


	}

}
static void callback_timer2(void)
{

			printf("A second just passed \n\r");
			GPIOA->ODR ^= LED_PIN;
			//systickDelayMS(1000);
}

void TIM2_IRQHandler(void)
		{
	//clear UPDATE INETRRUPT FLAG (UIE)
	TIM2->SR &=~ SR_UIF;
	//do something
	callback_timer2();
		}
