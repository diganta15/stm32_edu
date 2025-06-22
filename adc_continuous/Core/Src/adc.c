/*
 * adc.c
 *
 *  Created on: Jun 22, 2025
 *      Author: digantadas
 */
#include "adc.h"

void pa1_adc_init(void){
    //enable clock access to GPIOA
    RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN;
    //set the mode of PA1 to analog
    GPIOA->MODER |=(1U<<2);
    GPIOA->MODER |=(1U<<3);
    //enable clock access to ADC
    RCC->APB2ENR |= RCC_APB2ENR_ADC1EN;
    //clock conversion sequence start
    ADC1->SQR3 = (1U<<0);
    //conversion sequence length
    ADC1->SQR1 = 0x00;
    //enable ADC module
    ADC1->CR2 = ADC_CR2_ADON;

}

void start_conversion(void){
    //enable continous conversion
    ADC1->CR2 |= ADC_CR2_CONT;
    //start adc conversion
    ADC1->CR2 |= ADC_CR2_SWSTART;
}

uint32_t adc_read(void){
    //wait for conversion to be completed
    while(!(ADC1->SR & ADC_SR_EOC)){}

    return ADC1->DR;
}