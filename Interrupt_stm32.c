/*

### 🛠️ STM32 External Interrupt Handling (PC13 - Onboard Button)

This project demonstrates **external interrupt configuration** on an **STM32 microcontroller (e.g., STM32F4)** using the onboard **user push button connected to pin PC13**.

#### 📌 Key Concepts Implemented:

* Enabling RCC clocks for **GPIOC** and **SYSCFG**.
* Configuring **EXTI13** (external interrupt line for PC13).
* Setting up **falling edge trigger** to detect button press.
* **Unmasking the interrupt line** in the EXTI Interrupt Mask Register (IMR).
* Enabling interrupt in **NVIC (Interrupt Controller)**.
* Handling the interrupt using the **EXTI15\_10\_IRQHandler()** function.
* Clearing the interrupt pending bit in **EXTI\_PR**.

#### 🧾 Flow:

1. Enable clocks for GPIOC and SYSCFG.
2. Map PC13 to EXTI13 using `SYSCFG_EXTICR4`.
3. Configure falling edge detection.
4. Unmask EXTI13 to allow interrupt generation.
5. Enable NVIC interrupt at position 40 (`NVIC_ISER1` bit 8).
6. Write an ISR (Interrupt Service Routine) to handle the interrupt.

#### 🧪 Test:

* When the blue push button on the STM32 board is pressed, a falling edge is detected on PC13.
* This triggers the `EXTI15_10_IRQHandler()`, which prints `"button pressed"` and clears the pending flag.

#### 📄 Note:

* This is a **bare-metal implementation**, using direct register-level programming without any HAL/LL libraries.
*/



#include <stdint.h>//fixed integer datatype headerfile
#include <stdio.h>//input and output


uint32_t volatile *pAHB1ENR=(uint32_t*)0x40023830;//	RCC clock to gpioa
uint32_t volatile *pAPB2ENR=(uint32_t*)0x40023844;//   rcc clock to interrupt
uint32_t volatile *pSYSCFG_EXTICR4=(uint32_t*)0x40013814;  //external interrupt sysconfig
uint32_t volatile *pEXTI_FTSR=(uint32_t*)0x40013c0c; 
uint32_t volatile *pEXTI_IMR=(uint32_t*)0x40013c00;
uint32_t volatile *pNVIC_ISER1=(uint32_t*)0xe000e104;
uint32_t volatile *pEXTI_PR=(uint32_t*)0x40013c14;

void Button_Init(void){//function definition

	*pAHB1ENR|=(1<<2);//GPIOC CLOCK
	*pAPB2ENR|=(1<<14);//EXTERNAL INTRPT CLOCK
	*pSYSCFG_EXTICR4|=(1<<5);//EXT INT PC13 0010
	*pEXTI_FTSR|=(1<<13);//FALLING EDGE
	*pEXTI_IMR|=(1<<13);//INTERRUPT MASKING
	*pNVIC_ISER1|=(1<<8);//nvic position 40
}

int main(void)
{
	Button_Init();//function call
	while(1){

	}

}

void EXTI15_10_IRQHandler(void){
	printf("button pressed");
	*pEXTI_PR|=(1<<13);//clear


}

