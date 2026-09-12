#include <stdio.h>
#include "stm32f4xx.h"
#include <stdint.h>
#include "uart.h"


#define GPIOAEN (1U<<0)
#define GPIOA_5 (1U<<5)
#define LED_PIN GPIOA_5
static void uart_callback(void);

char key;
int main (void)
{
	//enable clock access to GPIOA
	RCC->AHB1ENR |= GPIOAEN;
	//set PA5 as output pin
	GPIOA->MODER |= (1U<<10);
	GPIOA->MODER &=~ (1U<<11);
	uart2_rxtx_interrupt_init();

	while(1)
	{

	}
}

static void uart_callback(void)
{
	key = USART2->DR;
	//Do something
	uart2_write(key);
	if (key == '1')
{
GPIOA->ODR |= LED_PIN;
}
else
{
GPIOA->ODR &=~ LED_PIN;
}
}

void USART2_IRQHandler(void)
{
	// Clear Overrun Error (ORE) if set to prevent RX interrupt lockup
	if (USART2->SR & (1U << 3))
	{
		(void)USART2->SR;
		(void)USART2->DR;
	}

	// Check if RXNE (Read Data Register Not Empty) flag is set
	if ((USART2->SR & SR_RXNE) != 0)
	{
		uart_callback();
	}
}
