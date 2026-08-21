#include <stdio.h>
#include "stm32f4xx.h"
#include <stdint.h>
#include "adc.h"

#define GPIOAEN (1U<<0)
#define ADC1EN (1U<<8)
#define ADC_CH1 (1U<<0)
#define ADC_SEQ_LEN_1 (0x00)
#define CR2_ADON (1U<<0)
#define CR2_SWSTART (1U<<30)
#define SR_EOC (1U<<1)

void pa1_adc_init(void)
{
	/*****configure ADC and GPIO pin*****/
	/*configure GPIO*/

	//We are going to use ADC1 and channel 1 of it.Channel 1 is connected to PA1

	//Enable clock access to GPIOA
	RCC->AHB1ENR |= GPIOAEN;
	//Set PA1 to analog mode
	GPIOA->MODER |=(1U<<2);
	GPIOA->MODER |=(1U<<3);

	/*configure ADC*/
	//Enable clock access
	RCC->APB2ENR |= ADC1EN;
	//Set the channel to be converted first. Since we are using CH1 of the ADC, we put binary value '1' in the SQ1 section of SQR3 register
	ADC1->SQR3 = ADC_CH1;
	//Set sequence length. There is a section in SQR1 register to set the length of the sequence. Sequence length is 1 because we are only using one channel
	ADC1->SQR1 = ADC_SEQ_LEN_1;
	//Enable ADC1, it can be done using ADC_CR2
	ADC1->CR2 |= CR2_ADON;

}

void start_conversion(void)
{
	/*start ADC conversion*/
	ADC1->CR2 |= CR2_SWSTART;
}

uint32_t adc_read(void)
{
	//wait for the conversion to finish
	while(!(ADC1->SR & SR_EOC)){}
	//read converted result
	return(ADC1->DR & 0xFF);
}

