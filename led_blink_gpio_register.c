
#include <stdint.h>
void delay()
{
	volatile uint32_t i;
	for(i=0 ;i<4000000;i++);//dummy delay
}

int main(void)
{
	// RCC and GPIO base addresses
	uint32_t *rcc_AHB1ENR = (uint32_t*)(0x40023830);//rcc 
	uint32_t *gpioa_moder=(uint32_t*)(0x40020000);
	uint32_t *gpioa_odr =(uint32_t*)(0x40020014);
	
	*rcc_AHB1ENR |= 1<<0;  // Enable clock for GPIOA
	*gpioa_moder|=1<<14;// Configure PA7 as output (MODER register: bits 14-15)

	while(1)
	{
		*gpioa_odr|=(1<<7); // Set PA7 high
		delay();

		*gpioa_odr &= ~(1<<7);//Set PA7 LOW
		delay();
	}
	return 0;
}
