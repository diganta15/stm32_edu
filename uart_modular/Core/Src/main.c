
#include "stdio.h"

#include "stm32f401xe.h"

int main(void) {
    for (volatile int i = 0; i < 2000000; ++i); // Delay
    uart2_tx_init();

    // LED init
    RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN;
    GPIOA->MODER |= (1U << 10); // PA5 output

    while (1) {
        GPIOA->ODR ^= (1U << 5); // Toggle LED
        printf("Hello from STM32F4.......\n\r");
        for (volatile int i = 0; i < 1000000; ++i);
    }
}