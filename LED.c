
#include <stdint.h>
void delay()
{
	volatile uint32_t i;
	for(i=0 ;i<4000000;i++);//dummy delay

}
int main(void)
{
	uint32_t *pAHB1ENR = (uint32_t*)(0x40023830);
	*pAHB1ENR |= 1<<0; //rcc clock to gpioa port

	uint32_t *gpioa_moder=(uint32_t*)(0x40020000);
	*gpioa_moder|=1<<14;// set as general output mode for port 7

	uint32_t *gpioa_odr =(uint32_t*)(0x40020014);
	 //set output @port7

	while(1)
	{
		*gpioa_odr|=(1<<7); // set bit
		delay();

		*gpioa_odr &= ~(1<<7);// clear bit
		delay();

	}

	return 0;

}
