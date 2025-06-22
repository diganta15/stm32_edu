/*
 * adc.h
 *
 *  Created on: Jun 22, 2025
 *      Author: digantadas
 */

#ifndef INC_ADC_H_
#define INC_ADC_H_
#include "stm32f401xe.h"
void pa1_adc_init(void);
void start_conversion(void);
uint32_t adc_read(void);


#endif /* INC_ADC_H_ */
