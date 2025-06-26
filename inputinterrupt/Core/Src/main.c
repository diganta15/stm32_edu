#include "exti.h"
#include "uart.h"
static void exti_callback(void);

int __io_putchar(int ch) {
    uart2_write(ch);  // Your UART function
    return ch;
}

int main(void){
  RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN;

  GPIOA->MODER |=(1U<<10);
  GPIOA->MODER &=~(1U<<11);

  

  pc13_exti_init();
  uart2_tx_init();

  while(1){

  }
}

static void exti_callback(void){
  printf("BTN Pressed...\n\r");
  GPIOA->ODR ^= (1U<<5);
}

void EXTI15_10_IRQHandler(void){
	 if((EXTI->PR & (1U << 13)) != 0){
    EXTI->PR |= (1U<<13);

    exti_callback();
  }
}
