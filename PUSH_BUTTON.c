//in-build push_button PC13 with in-build led PA5 config
#include <stdint.h>

void delay()
{
    volatile uint32_t i;
    for (i = 0; i < 300000; i++); // Adjusted for reasonable delay
}

int main(void)
{
    // RCC and GPIO base addresses
    uint32_t *rcc_AHB1ENR = (uint32_t*)(0x40023830);  // RCC AHB1 peripheral clock enable register
    uint32_t *gpioa_moder = (uint32_t*)(0x40020000);  // GPIOA mode register
    uint32_t *gpioc_moder = (uint32_t*)(0x40020800);  // GPIOC mode register
    uint32_t *gpioc_idr   = (uint32_t*)(0x40020810);  // GPIOC input data register
    uint32_t *gpioa_odr   = (uint32_t*)(0x40020014);  // GPIOA output data register

    // Enable clocks for GPIOA and GPIOC
    *rcc_AHB1ENR |= (1 << 0);  // GPIOA
    *rcc_AHB1ENR |= (1 << 2);  // GPIOC

    // Set PA5 as output (MODER5 = 01)
    *gpioa_moder &= ~(3 << 10); // Clear bits first
    *gpioa_moder |=  (1 << 10); // Set MODER5 to 01 (output)

    // Set PC13 as input (MODER13 = 00)
    *gpioc_moder &= ~(3 << 26); // Clear bits 27:26 for PC13

    while (1)
    {
        // Read PC13 input and mask bit 13
        uint8_t value = ((*gpioc_idr >> 13) & 0x1);

        // PC13 has a internal pull-up resistor, so default is HIGH (1)
        // When button pressed, PC13 is LOW (0)
        if (value == 0)
        {
            *gpioa_odr ^= (1 << 5); // Toggle PA5
            delay();                // Debounce delay
        }
    }

    return 0;
}

