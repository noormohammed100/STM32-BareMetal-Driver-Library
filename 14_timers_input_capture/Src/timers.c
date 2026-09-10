#include "stm32f4xx.h"
 /** timers.c
 *
 *  Created on: 10 Aug 2026
 *      Author: noork
 */
#define CR1_CEN (1U<<0)
#define CR1_CEN (1U<<0)
#define TIM2EN_APB1 (1U<<0)
#define TIM3EN_APB1 (1U<<1)
#define CCER_CC1E   (1U<<0)
#define GPIOAEN (1U<<0)
#define CCR1_CC1S (1U<<0)


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
	TIM2->ARR = 10000 - 1; //(10000/10000) = 1hz
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

void tim3_input_capture(void)
{
	//enable clock access to PA6
		RCC->AHB1ENR |= GPIOAEN;
		//set PA6 to alternate function mode
		GPIOA->MODER &=~ (1U<<12);
		GPIOA->MODER |= (1U<<13);
		//Set PA6 alternate function type to TIMER3 CHANNEL 1
		GPIOA->AFR[0] &=~ (1U<<24);
		GPIOA->AFR[0] |= (1U<<25);
		GPIOA->AFR[0] &=~ (1U<<26);
		GPIOA->AFR[0] &=~ (1U<<27);
		//Enable clock access to TIMER 3
		RCC->APB1ENR |= TIM3EN_APB1;
		//Set pre-scaler
		TIM3->PSC = 16000 - 1; //16000000 - 16000
		//Set CH1 to input capture mode
		TIM3->CCMR1 = CCR1_CC1S; //we dont need to configure anything else. the CC1S bit should be '01'
		//Hence we only set the first bit as 1
		//Enable CH1 to capture rising edge using TIMx_CCER2 (not TIM1) register
		TIM3->CCER = CCER_CC1E; //we only need to set bit 1 and the rest can be left 0, this will result in capture at rising edge
		//Enable TIMER 3
		TIM3->CR1 = CR1_CEN;
}
