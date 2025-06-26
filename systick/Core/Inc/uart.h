/*
 * uart.h
 *
 *  Created on: Jun 22, 2025
 *      Author: digantadas
 */


#ifndef INC_UART_H_
#define INC_UART_H_

#include "stm32f401xe.h"
#include <stdint.h>


#define SYS_FREQ 16000000U
#define APB1_CLK SYS_FREQ // USART2 is on APB1
#define UART_BAUDRATE 115200U


void uart2_tx_init(void);
void uart2_write(int ch);
void uart2_print(const char *str);
void uart_set_baudrate(USART_TypeDef *USART, uint32_t PeriphClk, uint32_t BaudRate);
uint32_t compute_uart_div(uint32_t PeriphClk, uint32_t BaudRate);


#endif /* INC_UART_H_ */
