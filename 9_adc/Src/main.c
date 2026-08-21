#include <stdio.h>
#include "stm32f4xx.h"
#include <stdint.h>
#include "uart.h"
#include "adc.h"


#define GPIOAEN (1U<<10)
#define GPIOA_5 (1U<<5)
#define LED_PIN GPIOA_5

uint32_t sensor_value;

int main (void)
{

uart2_tx_init();
pa1_adc_init();


while(1)
	{
	start_conversion();
		sensor_value = adc_read();
		printf("sensor value : %d \n\r", (int)sensor_value);
}

}


