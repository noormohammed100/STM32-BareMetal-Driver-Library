/*
 * uart.c
 *
 *  Created on: 3 Aug 2026
 *      Author: noork
 */
#include "uart.h"

#define GPIOAEN     (1U << 0)
#define USART2_EN   (1U << 17)

#define SYS_FREQ       16000000U
#define APB1_CLK       SYS_FREQ
#define USART_BAUDRATE 115200U

/* Correct USART_CR1 bit masks */
#define CR1_RE  (1U << 2)  /* Receiver Enable (Bit 2) */
#define CR1_TE  (1U << 3)  /* Transmitter Enable (Bit 3) */
#define CR1_UE  (1U << 13) /* USART Enable (Bit 13) */

/* USART_SR bit masks */
#define SR_ORE  (1U << 3)  /* Overrun Error (Bit 3) */
#define SR_RXNE (1U << 5)  /* Read Data Register Not Empty (Bit 5) */
#define SR_TXE  (1U << 7)  /* Transmit Data Register Empty (Bit 7) */

static void uart_set_baudrate(USART_TypeDef *USARTx, uint32_t PeriphClk, uint32_t BaudRate);
static uint16_t compute_uart_bd(uint32_t PeriphClk, uint32_t BaudRate);

void uart2_write(int ch)
{
	/* Make sure transmit data register is empty */
	while (!(USART2->SR & SR_TXE)) {}
	USART2->DR = (ch & 0xFF);
}

char uart2_read(void)
{
	/* Handle and clear Overrun Error (ORE) if set to prevent RX lockup */
	if (USART2->SR & SR_ORE)
	{
		(void)USART2->SR;
		(void)USART2->DR;
	}

	/* Wait until receive data register is not empty */
	while (!(USART2->SR & SR_RXNE)) {}

	return (char)(USART2->DR & 0xFF);
}

static void uart_set_baudrate(USART_TypeDef *USARTx, uint32_t PeriphClk, uint32_t BaudRate)
{
	USARTx->BRR = compute_uart_bd(PeriphClk, BaudRate);
}

static uint16_t compute_uart_bd(uint32_t PeriphClk, uint32_t BaudRate)
{
	return ((PeriphClk + (BaudRate / 2U)) / BaudRate);
}

int __io_putchar(int ch)
{
	uart2_write(ch);
	return ch;
}

void uart2_tx_init(void)
{
	/* 1. Clock access to GPIOA */
	RCC->AHB1ENR |= GPIOAEN;

	/* 2. Configure PA2 as Alternate Function (10) */
	GPIOA->MODER &= ~(3U << 4);  /* Clear MODER2 (bits 5:4) */
	GPIOA->MODER |=  (2U << 4);  /* Set AF mode */

	/* 3. Configure PA2 AF07 (USART2_TX) in AFRL */
	GPIOA->AFR[0] &= ~(0xFU << 8); /* Clear bits 11:8 */
	GPIOA->AFR[0] |=  (7U << 8);   /* Set AF07 */

	/* 4. Clock access to USART2 module */
	RCC->APB1ENR |= USART2_EN;

	/* 5. Set baud rate */
	uart_set_baudrate(USART2, APB1_CLK, USART_BAUDRATE);

	/* 6. Enable Transmitter and USART module */
	USART2->CR1 = CR1_TE;
	USART2->CR1 |= CR1_UE;
}

void uart2_rxtx_init(void)
{
	/* 1. Clock access to GPIOA */
	RCC->AHB1ENR |= GPIOAEN;

	/* 2. Configure PA2 (TX) & PA3 (RX) as Alternate Function (10) */
	GPIOA->MODER &= ~((3U << 4) | (3U << 6)); /* Clear MODER2 & MODER3 */
	GPIOA->MODER |=  ((2U << 4) | (2U << 6)); /* Set AF mode */

	/* 3. Configure PA2 & PA3 to AF07 (USART2) in AFRL */
	GPIOA->AFR[0] &= ~((0xFU << 8) | (0xFU << 12)); /* Clear bits 11:8 and 15:12 */
	GPIOA->AFR[0] |=  ((7U << 8)  | (7U << 12));   /* Set AF07 for PA2 & PA3 */

	/* 4. Clock access to USART2 module */
	RCC->APB1ENR |= USART2_EN;

	/* 5. Set baud rate */
	uart_set_baudrate(USART2, APB1_CLK, USART_BAUDRATE);

	/* 6. Enable Transmitter, Receiver, and USART module */
	USART2->CR1 = CR1_TE | CR1_RE;
	USART2->CR1 |= CR1_UE;
}
