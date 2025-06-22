#include "stm32f401xe.h"
#include <stdint.h>
#define ADC_CH1         (1U<<0)
#define ADC_SEQ_LEN_1   0x00


void pa1_adc_init(void){
    //enable clock access
    RCC->AHB1ENR = RCC_AHB1ENR_GPIOAEN;

    //set modwer of pa1 to analog
    GPIOA->MODER |=(1U<<2);
    GPIOA->MODER |=(1U<<3);

    //configure adc

    //enable clock access
    RCC->APB2ENR = RCC_APB2ENR_ADC1EN;

    //conversion system start
    ADC1->SQR3 = ADC_CH1;
    
    //conversion sequence length
    ADC1->SQR1 = ADC_SEQ_LEN_1;

    //enable ADC module
    ADC1->CR2 |= ADC_CR2_ADON;


}

void start_conversion(void){
    ADC1->CR2 |= ADC_CR2_SWSTART;
}

uint32_t adc_read(void){
    //wait for conversion to be complete
    while(!(ADC1->SR & ADC_SR_EOC)){

    }
    return ADC1->DR;
}