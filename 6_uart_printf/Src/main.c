#include <stdio.h>
#include "stm32f4xx.h"
#include <stdint.h>


#define GPIOAEN (1U<<0)
#define USART2_EN (1U<<17)
#define SYS_FREQ 16000000
#define APB1_CLK SYS_FREQ
#define USART_BAUDRATE 115200
#define CR1_CE (1U<<3)
#define CR1_UE (1U<<13)
#define SR_TXE (1U<<7)

static void uart_set_baudrate (USART_TypeDef *USArtx, uint32_t PeriphClk, uint32_t BaudRate);
static uint16_t compute_uart_bd(uint32_t PeriphClk, uint32_t BaudRate);
void uart2_write(int ch);
void uart2_tx_init (void);

int __io_putchar(int ch);
int main (void)
{
	uart2_tx_init();
	while(1)
	{
printf("Printf is working...\n\r");
	}
}


void uart2_tx_init (void)
{
	/*Configure UART GPIO pin*/
	//give clock access to GPIOA
	RCC->AHB1ENR |= GPIOAEN;
	//set PA2 to alternate function
	GPIOA->MODER &=~ (1U<<4);
	GPIOA->MODER  |= (1U<<5);
	//set function type of PA3 to UART_TX (AF07). Use AFRL register and set the designated bits of PA2 to AF07.
	GPIOA->AFR[0] |= (1U<<8);
	GPIOA->AFR[0] |= (1U<<9);
	GPIOA->AFR[0] |= (1U<<10);
	GPIOA->AFR[0] &=~ (1U<<11);
	/*Configure UART*/
	//Enable clock access to UART2 module
	RCC->APB1ENR |= USART2_EN;
	//set baud rate
	uart_set_baudrate(USART2,APB1_CLK, USART_BAUDRATE);
	//set transfer direction
	USART2->CR1 = CR1_CE; //no need to configure stop bit in CR2 because it is already set to 0 by default
	//enable USART module
	USART2->CR1 |= CR1_UE; //i used | becuase i dont want to clear everything
}

void uart2_write(int ch)
{
	/*make sure transmit data register is empty*/
	//write to transmit data register (simply data register)
	while (!(USART2->SR & SR_TXE)){}
	USART2->DR = (ch & 0xFF);

}

static void uart_set_baudrate (USART_TypeDef *USARTx, uint32_t PeriphClk, uint32_t BaudRate)
{
	USARTx->BRR = compute_uart_bd(PeriphClk,BaudRate);
}

static uint16_t compute_uart_bd(uint32_t PeriphClk, uint32_t BaudRate)
		{
	return ((PeriphClk + (BaudRate/2U))/BaudRate);
		}
int __io_putchar(int ch)
{
	uart2_write(ch);
	return ch;
}
