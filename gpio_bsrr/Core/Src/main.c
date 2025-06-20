#include "stm32f401xe.h"

int main(void)
{
  RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN;

  GPIOA->MODER &= ~(3U << 10);
  GPIOA->MODER |= (1U << 10);

  while (1)
  {
    GPIOA->BSRR = (1U << 5);
    for (int i = 0; i < 1000000; i++)
    {
    }

    GPIOA->BSRR = (1U << 21);
    for (int i = 0; i < 100000; i++)
    {
    }
  }
}