/*> This C program demonstrates how to initialize and use the USART2 peripheral on an STM32 microcontroller using **bare-metal register-level programming**.
It enables GPIOA and USART2 clocks, configures PA2 and PA3 as alternate functions for UART TX/RX, sets the baud rate, and transmits a string over UART using `printf`.
This example is ideal for understanding low-level peripheral configuration without using any HAL or library abstraction.
*/

/*if there any change please notify me*/

#include <stdint.h>//FIXED INT LENGTH 32 BIT
#include<stdio.h>

uint32_t *pAHB1ENR=(uint32_t*)0x40023830;   //GPIOA RCC EN
uint32_t *pAPB1ENR=(uint32_t*)0x40023840;  //UART RCC EN
uint32_t *pGPIOMODER=(uint32_t*)0x40020000;  //ALTERNATE MODE SET
uint32_t *pGPIOAFRL=(uint32_t*)0x40020020;   //ALTERNATE FUNCTION SET
uint32_t *pUSART2_CR1=(uint32_t*)0x4000440c;  //USART CONTROL REG
uint32_t *pUSART2_BRR=(uint32_t*)0x40004408;  // BAURD RATE REG
uint32_t *pUSART2_SR=(uint32_t*)0x40004400;  //STATUS REG
uint32_t *pUSART2_DR=(uint32_t*)0x40004404;   //DATA REG

void Uart_Init(void);
void Uart_Write(int ch);

void Uart_Init(void){//function for usart
	//*pAHB1ENR|=(1U<<0); 1U as unsigned int
	*pAHB1ENR|=(1<<0);//gpio a enable
	*pAPB1ENR|=(1<<17);//usart 2 enable

	//*pGPIOMODER&=~(1<<4);//0
	*pGPIOMODER|=(1<<5);//1   alt func PA 2

	//*pGPIOMODER&=~(1<<6);//0
	*pGPIOMODER|=(1<<7);//1   alt func PA 3
        // ALTERNATE FUNCTION MAPPING
	 *pGPIOAFRL|=(0x07<<8);  //AF7 0111
/*	*pGPIOAFRL|=(1<<8); //AF7 0111
	*pGPIOAFRL|=(1<<9);
	*pGPIOAFRL|=(1<<10);//AF7
	*pGPIOAFRL&=~(1<<11);
*/
	 /*USART (CLK+BR)
	  * BR=(CLK(BR/2))/BR;
	  * BR ->HEXA_DECIMAL
	  * */


	*pUSART2_BRR=0X683;//baudrate clk+baudrate usart

	*pUSART2_CR1|=0X2008;//  USART ENABLE=1 START TRANSMISSION=1

}

void Uart_Write(int ch){
	//W
	while(!(*pUSART2_SR & 0X0080)){  //1 - go inside the loop IF
		//NOT YET TRANSMITTED
	}
	//W-ASCII- to 8 bits MASKING
	*pUSART2_DR=(ch&0Xff);//only 8 bit//W

}

int __io_putchar(int ch){//one-one bit data send //We

	Uart_Write(ch);//W
	return ch;

}

int main(void)//entry point
{
	Uart_Init();

	while(1){//inifinte time loop will be run
		printf("Welcome to ARM cortex series\n");//data  TO arduino send

		//data through put char function send one by one
	}

	for(;;);
}
