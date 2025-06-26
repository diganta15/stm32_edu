/*
 * exti.c
 *
 *  Created on: Jun 26, 2025
 *      Author: digantadas
 */
#include "exti.h"

void pc13_exti_init(void){
    //disable global interrupts
    __disable_irq();
    //enable clock access for gpioc
    RCC->AHB1ENR |= RCC_AHB1ENR_GPIOCEN;

    //set PC13 as input
    GPIOC->MODER &=~(1U<<26);
    GPIOC->MODER &=~(1U<<27);

    //enable clock access to SYSCFG
    RCC->APB2ENR = RCC_APB2ENR_SYSCFGEN;
    //select PORTC for EXTI13
    SYSCFG->EXTICR[3] |=(1U<<5);
    //unmask EXTI13
    EXTI->IMR |=(1U<<13);
    //select falling edge trigger
    EXTI->FTSR |=(1U<<13);
    //enable exti13 line in NVIC
    NVIC_EnableIRQ(EXTI15_10_IRQn);

    //enable global interrupt
    __enable_irq();
}

