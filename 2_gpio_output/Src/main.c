#include "stm32f4xx.h"



#define GPIOAEN (1U<<0)
#define GPIOCEN (1U<<2)

#define PIN5 (1U<<5)
#define PIN13 (1U<<13)

#define LED_PIN PIN5
#define BTN_PIN PIN13

int main (void)
{
	//enable clock access for GPIOA and GPIOC
	RCC->AHB1ENR |= GPIOAEN;
	RCC->AHB1ENR |= GPIOCEN;

	//Set GPIOC PC13 as input
	GPIOC->MODER &=~(1U<<26);
	GPIOC->MODER &=~(1U<<27);

	//Set GPIOA PA5 as input

	GPIOA->MODER |=(1U<<10);
	GPIOA->MODER &=~(1U<<11);

	while(1)
	{
//check if BTN (ACTIVE LOW) is pressed
		if (GPIOC->IDR & BTN_PIN)
		{
		GPIOA->BSRR =(1U<<21);
		}
		else
		{
GPIOA->BSRR =LED_PIN;
		}
	}
}
