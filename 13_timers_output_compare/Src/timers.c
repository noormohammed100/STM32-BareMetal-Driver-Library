#include "stm32f4xx.h"
 /** timers.c
 *
 *  Created on: 10 Aug 2026
 *      Author: noork
 */
#define CR1_CEN (1U<<0)
#define TIM2EN_APB1 (1U<<0)
#define CCER_CC1E   (1U<<0)
#define GPIOAEN (1U<<0)

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

void tim2_output_compare(void)
{
	//enable clock access to PA5
	RCC->AHB1ENR |= GPIOAEN;
	//set PA5 to alternate function mode
	GPIOA->MODER &=~ (1U<<10);
	GPIOA->MODER |= (1U<<11);
	//Set PA5 alternate function type to TIMER2 CHANNEL 1
	GPIOA->AFR[0] |= (1U<<20);
	GPIOA->AFR[0] &=~ (1U<<21);
	GPIOA->AFR[0] &=~ (1U<<22);
	GPIOA->AFR[0] &=~ (1U<<23);
	//enable clock access
	RCC->APB1ENR |= TIM2EN_APB1;
	//prescaler value
	TIM2->PSC = 1600-1; //will be 1600 because we start from 0.
	//Also, [(16000000/1600 = 10000)]
	//set auto reload value
	TIM2->ARR = 30000 - 1; //(10000/10000) = 1hz
	/*set output compare toggle mode*/
	TIM2->CCMR1 |= (1U<<4);
	TIM2->CCMR1 |= (1U<<5);
	TIM2->CCMR1 &=~ (1U<<6);
	//enable timer2 channel1 in compare mode
	TIM2->CCER |= CCER_CC1E;

	//clear the timer counter
			TIM2->CNT = 0;
	//enable the timer
	TIM2->CR1 = CR1_CEN;

}
