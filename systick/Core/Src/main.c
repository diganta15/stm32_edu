#include "stm32f401xe.h"
#include "systick.h"
#include "uart.h"


int __io_putchar(int ch){
    uart2_write(ch);
    return ch;
}


int main(void){
  //enable GPIOA clock access
  RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN;

  //set PA5 as output pin
  GPIOA->MODER &= ~(3U << 10); // Clear bits 11 and 10
    GPIOA->MODER |= (1U << 10);  // Set bit 10 to 1 (Output mode)

    uart2_tx_init();

  while(1){
    
	  printf("a second just passed !! \n\r");
    GPIOA->ODR ^= (1U<<5);
     systickDelayMs(1000);
  }


}
