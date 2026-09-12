/*
 * uart.h
 *
 *  Created on: 3 Aug 2026
 *      Author: noork
 */

#ifndef UART_H_
#define UART_H_

#include <stdint.h>
#include "stm32f4xx.h"
#define CR1_RXNEIE (1U<<5)
#define SR_RXNE (1U << 5)  /* Read Data Register Not Empty (Bit 5) */
void uart2_tx_init (void);
char uart2_read(void);
void uart2_rxtx_init(void);
void uart2_write(int ch);
void uart2_rxtx_interrupt_init(void);

#endif /* UART_H_ */
