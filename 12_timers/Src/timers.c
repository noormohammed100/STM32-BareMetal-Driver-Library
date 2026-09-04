#include "stm32f4xx.h"
 /** timers.c
 *
 *  Created on: 10 Aug 2026
 *      Author: noork
 */
#define CR1_CEN (1U<<0)
#define TIM2EN_APB1 (1U<<0)


void tim2_1hz_init(void)
{
	//enable clock access
	RCC->APB1ENR |= TIM2EN_APB1;
	//prescaler value
	TIM2->PSC = 1600-1; //will be 1600 because we start from 0.
	//Also, [(16000000/1600 = 10000)]
	//set auto reload value
	TIM2->ARR = 10000 - 1; //(10000/10000) = 1hz
	//clear the timer counter
			TIM2->CNT = 0;
	//enable the timer
	TIM2->CR1 = CR1_CEN;

}

void tim2_1hz_interrupt(void)
{
	//enable clock access
	RCC->APB1ENR |= TIM2EN_APB1;
	//prescaler value
	TIM2->PSC = 1600-1; //will be 1600 because we start from 0.
	//Also, [(16000000/1600 = 10000)]
	//set auto reload value
	TIM2->ARR = 10000 - 1; //(10000/10000) = 1hz
	//clear the timer counter
			TIM2->CNT = 0;
	//enable the timer
	TIM2->CR1 = CR1_CEN;

}
