/*
 * exti.c
 *
 *  Created on: 11 Aug 2026
 *      Author: noork
 */
#include "exti.h"
#include "stm32f4xx.h"

#define GPIOCEN (1U<<2)
#define SYSCFGEN (1U<<14)


void pc13_exti_init(void)
{
	//disable global interrupts
	__disable_irq();
	//enable clock access to port C
	RCC->AHB1ENR |= GPIOCEN;
	//set port c to input mode (for the switch)
	GPIOC->MODER &=~ (1U<<26);
	GPIOC->MODER &=~ (1U<<27);
	//enable clock access to SYSCFG
	RCC->APB2ENR |= SYSCFGEN;
	//select port c for SYSCFG
	SYSCFG->EXTICR[3] |= (1U<<5);//we only need to set 1 on that particular bit because the reset value is 0
	//unmask EXTI13
	EXTI->IMR |= (1U<<13);
	//select falling edge trigger using
	EXTI->FTSR |= (1U<<13);
	//Enable EXTI13 line in NVIC
	NVIC_EnableIRQ(EXTI15_10_IRQn);
	//enable global interrupts
	__enable_irq();
}

