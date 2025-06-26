#include "tim.h"

int main(void){
  RCC->AHB1ENR = RCC_AHB1ENR_GPIOAEN;

  GPIOA->MODER |= (1U<<10);
  GPIOA->MODER &=~(1U<<11);

  tim2_1hz_init();

  while(1){
    while(!(TIM2->SR & TIM_SR_UIF)){}

    //clear UIF
    TIM2->SR &=~TIM_SR_UIF;

    GPIOA->ODR ^= (1U<<5);

  }
}