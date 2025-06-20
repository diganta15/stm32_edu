#include "stm32f401xe.h"

int main(void){
  RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN;
  RCC->AHB1ENR |= RCC_AHB1ENR_GPIOCEN;

  GPIOA->MODER &= ~(3U<<10);
  GPIOA->MODER |= (1U<<10);

  GPIOC->MODER &=~(1U<<26);
  GPIOC->MODER &=~(1u<<27);


  while (1)
  {
    if(GPIOC->IDR & (1u<<13)){
      GPIOA->BSRR = (1U<<5);
    }
    else GPIOA->BSRR = (1U<<21);
  }
  
  
}