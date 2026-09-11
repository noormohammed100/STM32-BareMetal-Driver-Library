#include <stdio.h>
#include "stm32f4xx.h"
#include <stdint.h>
#include "uart.h"
#include "adc.h"
#include "systick.h"
#include "timers.h"
#include "exti.h"

#define GPIOAEN (1U<<0)
#define PIN5 (1U<<5)
#define LED_PIN PIN5

static void exti_callback(void);

int main (void)
{

	RCC->AHB1ENR |= GPIOAEN;
	GPIOA->MODER |= (1U<<10);
	GPIOA->MODER &=~ (1U<<11);

	uart2_tx_init();
	pc13_exti_init();

while(1)
	{
	printf("BTN not Pressed ...\n\r");
	systickDelayMS(1000);

}
}

static void exti_callback(void)
{
	printf("BTN Pressed ...\n\r");
	GPIOA->ODR ^= PIN5;
}

void EXTI15_10_IRQHandler(void) //this function handles interrupt request for EXTI 10 to 15
{
	if((EXTI->PR & LINE13)!=0)
	{
		//clear PR flag
		EXTI->PR |= LINE13; //we set '1' in PR register bit, that's the way to reset. Because it is a set to clear register.
		//do what you want to do
		exti_callback();
	}
}
