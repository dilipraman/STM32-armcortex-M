/* STM32F4 ADC Interface with Potentiometer

This project demonstrates how to interface a potentiometer with the STM32F4 microcontroller using the ADC (Analog-to-Digital Converter) peripheral. The analog value is read from a GPIO pin (PA0) configured in analog mode, converted to a digital value using ADC1, and sent to the console using ITM (Instrumentation Trace Macrocell) via SWO for debugging.

 📌 Features

- Configures PA1 as analog input
- Initializes ADC1 and performs continuous conversions
- Uses ITM to output the result of the ADC to the SWV ITM console
- Supports 12-bit ADC resolution (values range from 0 to 4095)

🔧 Tools Used

- **Microcontroller**: STM32F4 series
- **IDE**: STM32CubeIDE
- **Debugger**: ST-Link with SWO output
- **Language**: Embedded C
- **Console Output**: ITM (SWV ITM Console in STM32CubeIDE)

🧪 Circuit Setup

- **Potentiometer**:
  - One end to **3.3V**
  - One end to **GND**
  - Middle pin (wiper) to **PA1 (Pin A1)**
- Ensure `Vref+` is connected to 3.3V and `Vref-` to GND.
*/



#include <stdint.h>

uint32_t *p_AHB1ENR = (uint32_t*)(0x40023830);
uint32_t *p_APB2ENR = (uint32_t*)(0x40023844);
uint32_t *gpioa_moder=(uint32_t*)(0x40020000);
uint32_t *ADC_CR=(uint32_t*)(0x40012008);// adc control register
uint32_t *ADC_SQR3=(uint32_t*)(0x40012034);//channel select
uint32_t *ADC_SR=(uint32_t*)(0x40012000);//status register
uint32_t *ADC_DR=(uint32_t*)(0x4001204c);//data register


void ADC_INIT(void)
{
	*p_AHB1ENR|=1<<0;//Enable GPIOA clock
	*p_APB2ENR |= 0X100;// Enable ADC1 clock
	*gpioa_moder|=0X0C; //GPIOA  ANALOGMODE PA1
	 *ADC_CR =0; //CLEAR
	 *ADC_SQR3 |=1;//CHANNEL 1
	 *ADC_CR|=1;// PERIPHERAL EN ADON
}
void delay(void)
{
	for(uint32_t i=0;i<300000;i++);
}

uint16_t analog_value=0;
int main(void)
{
	ADC_INIT();
	while(1)
	{
		*ADC_CR |=0x40000000;//start conversion in regular mode
		while(!(*ADC_SR &2));// Wait for end of conversion check (analog to digital)
		analog_value=(uint16_t)*ADC_DR;//after EOC ,read  adc result 

		printf("ADC VALUE:%d",analog_value);
		delay();

	}

}

/* update in syscall.c file*/
/*using ITM (Instrumentation Trace Macrocell) to redirect printf output via SWO (Single Wire Output)*/
/*check reference manual for armv7 */
#define DEMCR                        *((volatile uint32_t *) 0xE000EDFC)
#define ITM_STIMULUS_PORT0           *((volatile uint32_t *) 0xE0000000)
#define ITM_TRACE_EN                 *((volatile uint32_t *) 0xE0000E00)

void ITM_Sendchar(uint8_t ch)
{
	DEMCR|=1<<24;// Enable TRCENA in DEMCR (Debug Exception and Monitor Control Register)
	ITM_TRACE_EN =1<<0; // Enable stimulus port 0
	while(!(ITM_STIMULUS_PORT0 &1));// Wait until STIM0 is  fifo ready
	ITM_STIMULUS_PORT0=ch;
}

