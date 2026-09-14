#include <stdio.h>
#include "stm32f4xx.h"
#include <stdint.h>
#include "uart.h"
#include "adc.h"


#define GPIOAEN (1U<<10)
#define GPIOA_5 (1U<<5)
#define LED_PIN GPIOA_5

uint32_t sensor_value;
static void adc_callback(void);
void ADC_IRQHandler(void);
int main (void)
{

uart2_tx_init();
pa1_adc_interrupt_init();
start_conversion();

while(1)
	{



}
}

void ADC_IRQHandler(void)
{
	//check for EOC in SR register
	if((ADC1->SR & SR_EOC)!=0)
		{
			//clear EOC flg
			ADC1->SR &=~ SR_EOC;
			//do the desired action
			adc_callback();
		}
}

static void adc_callback(void)
{
	sensor_value = ADC1->DR;
			printf("sensor value : %d \n\r", (int)sensor_value);
	}



