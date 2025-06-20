#include "stm32f401xe.h"  // Device header from CMSIS


int main(void) {
    // 1. Enable clock to GPIOA (bit 0 in AHB1ENR)
    RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN;

    // 2. Set PA5 to general purpose output mode (MODER = 01 for pin 5)
    GPIOA->MODER |=(1U<<10);   //set bit 10 to 1
    GPIOA->MODER &=~(1U<<11);    //set bit 11 to 0

    GPIOA->OTYPER &= ~(1U << 5);
      GPIOA->PUPDR  &= ~(3U << (2 * 5));
   
    // 4. Toggle PA5 in a loop
    while (1) {
        GPIOA->ODR ^= (1U << 5);  // Toggle pin 5
        for (int i=0;i<1000000;i++){}
    }
}
