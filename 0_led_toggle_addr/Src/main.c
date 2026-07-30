//Where is the led connected?
//port: A
//pin: 5

#define PERIPH_BASE  (0x40000000UL)
//after checking the diagram, it is evident that the PORT A is connected to AHB1 Bus
#define AHB1PERIPH_OFFSET (0x00020000UL) //address of AHB1 bus is (0x4002000) found from the memory map
#define AHB1PERIPH_BASE   (PERIPH_BASE + AHB1PERIPH_OFFSET) //i wrote this like how the professionals write it
#define GPIOA_OFFSET (0x0000U) //0x0000 0000 = 0x0 = 0

#define GPIOA_BASE (AHB1PERIPH_BASE + GPIOA_OFFSET)
//now that i found the required address, i need to give the port clock access to activate it. it is done using AHB1ENR register situated inside RCC peripheral
#define RCC_OFFSET (0x00003800UL) //got using data sheet
#define RCC_BASE (AHB1PERIPH_BASE + RCC_OFFSET)
#define AHB1EN_R_OFFSET (0x30UL) //Now that we got RCC's address, we need to access AHB1ENR register located inside RCC
#define RCC_AHB1EN_R (*(volatile unsigned int *)(RCC_BASE + AHB1EN_R_OFFSET))
#define GPIOAEN (1U<<0) //0b 0000 0000 0000 0000 0000 0000 0000 0001
// we need to set 0x1 to AHB1ENR register to enable PORTA
//After enabling it, we need to set it's behaviour
#define MODE_R_OFFSET (0x00UL)
#define GPIOA_MODE_R (*(volatile unsigned int *)(GPIOA_BASE + MODE_R_OFFSET))
//lets find address of the output register
#define GPIOA_OD_R_OFFSET (0x14UL)
#define GPIOA_OD_R (*(volatile unsigned int *)(GPIOA_BASE + GPIOA_OD_R_OFFSET))

#define PIN5 (1U<<5)
#define LED_PIN PIN5
//Now we set MODER5 to 01 to set PA05 to output



int main (void)
{
	//enable clock access to GPIOA
	RCC_AHB1EN_R |= GPIOAEN;
	//set PA5 as output pin
	GPIOA_MODE_R |= (1U<<10); //set bit 10 1
	GPIOA_MODE_R &=~ (1U<<11);//set bit 11 0
	while(1)
	{
		//Set PA5 high
		GPIOA_OD_R ^= LED_PIN;
		for(int i=0; i<1000000; i++);
	}

	}

