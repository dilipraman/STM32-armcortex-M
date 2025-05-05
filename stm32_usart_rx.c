#include <stdint.h>

uint32_t *pAHB1ENR=(uint32_t*)0x40023830; //RCC GPIO
uint32_t *pAPB1ENR=(uint32_t*)0x40023840;  // RCC USART
uint32_t *pGPIOAMODER=(uint32_t*)0x40020000; //MODE FUNCTION
uint32_t *pGPIOAODR=(uint32_t*)0x40020014;   //OUTPUT MODE FOR  LED
uint32_t *pGPIOAAFRL=(uint32_t*)0x40020020;//AF MAPPING


uint32_t *pUSART2_BRR=(uint32_t*)0x40004408;//BAURD RATE
uint32_t *pUSART2_CR1=(uint32_t*)0x4000440c;//USART CONTROL REG
uint32_t *pUSART2_SR=(uint32_t*)0x40004400;//STATUS REG
uint32_t *pUSART2_DR=(uint32_t*)0x40004404;// DATA HOLD REG
void Uart_Init(void){

	*pAHB1ENR|=(1<<0);//GPIOA
	*pAPB1ENR|=(1<<17);//usart2 enable
	*pGPIOAMODER&=~(1<<4);
	*pGPIOAMODER|=(1<<5);  //pa2

	*pGPIOAMODER&=~(1<<6);
	*pGPIOAMODER|=(1<<7);  //pa3

	*pGPIOAMODER|=(1<<10);
	*pGPIOAMODER&=~(1<<11);//pa 5
	//PA2 alternative mapping
	*pGPIOAAFRL|=(1<<8);/*0111*/
	*pGPIOAAFRL|=(1<<9);
	*pGPIOAAFRL|=(1<<10);
	*pGPIOAAFRL&=~(1<<11);
	//PA3 alternative mapping
	*pGPIOAAFRL|=(1<<12);
	*pGPIOAAFRL|=(1<<13);
	*pGPIOAAFRL|=(1<<14);
	*pGPIOAAFRL&=~(1<<15);

	*pUSART2_BRR=0X0683;//baudrate

	*pUSART2_CR1|=(1<<13);//usart2 peripheral enable

	*pUSART2_CR1|=(1<<3);//TX
	*pUSART2_CR1|=(1<<2);//RX

}
/*TX FUNCTION*/
void Uart_Write(char ch){

	while(!(*pUSART2_SR & (1<<7))){// TXE: Transmit Data Register Empty
	}

	*pUSART2_DR=(ch&0Xff);

}
/*RX FUNCTION*/
char Uart_Read(void){
	while(!(*pUSART2_SR & (1<<5))){// RXNE: Read Data Register Not Empty
		}
	return *pUSART2_DR;
}
/*printf -> io_putchar ITM Syscall */
int __io_putchar(int ch){
	Uart_Write(ch);
	return ch;
}

int main(void)
{
	char ch;
	Uart_Init();
	printf("STM32 LEARNING \n");

	while(1){
		ch=Uart_Read();
		if(ch=='a')/*IF A RX then ledon*/
		{
			*pGPIOAODR|=(1<<5);//led on
		}
		else
		{
			*pGPIOAODR&=~(1<<5);//led off
		}

		printf("Data is %c\n",ch);//for debug ITM
	}


	for(;;);
}
