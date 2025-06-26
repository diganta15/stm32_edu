/*
 * tim.c
 *
 *  Created on: Jun 25, 2025
 *      Author: digantadas
 */


#include "tim.h"

void tim2_1hz_init(void){
    //enable clock access to tim2
    RCC->APB1ENR |= RCC_APB1ENR_TIM2EN;

    //set prescaler value
    TIM2->PSC = 1600-1;
    //set auto reload value
    TIM2->ARR = 10000-1;
    //clear counter
    TIM2->CNT = 0;

    //enable timer
    TIM2->CR1 = TIM_CR1_CEN;
}

void tim2_output_compare(void){
    //enable clock access to GPIOA
    RCC->AHB1ENR = RCC_AHB1ENR_GPIOAEN;

    //set PA5 to alternate function mode
    GPIOA->MODER &=~(1U<<10);
    GPIOA->MODER |=(1U<<11);

    //set PA5 alternate function type to TIM2_CH1 (AF01)
    GPIOA->AFR[0] = (1U<<20);
     //enable clock access to tim2
    RCC->APB1ENR |= RCC_APB1ENR_TIM2EN;

    //set prescaler value
    TIM2->PSC = 1600-1;
    //set auto reload value
    TIM2->ARR = 10000-1;

    //set output compare toggle mode
    TIM2->CCMR1 = (1U<<4)|(1U<<5);

    //enable tim2 ch1 in compare mode
    TIM2->CCER = TIM_CCER_CC1E;

    //clear counter
    TIM2->CNT = 0;

    //enable timer
    TIM2->CR1 = TIM_CR1_CEN;
}