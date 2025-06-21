#include "stdio.h"

#include "stm32f401xe.h"
#include "stdint.h"

#define SYS_FREQ       16000000U
#define APB1_CLK       SYS_FREQ       // USART2 is on APB1
#define UART_BAUDRATE  115200U

void uart2_tx_init(void);
void uart2_write(int ch);
void uart2_print(const char *str);
void uart_set_baudrate(USART_TypeDef *USART, uint32_t PeriphClk, uint32_t BaudRate);
uint32_t compute_uart_div(uint32_t PeriphClk, uint32_t BaudRate);



int __io_putchar(int ch){
    uart2_write(ch);
    return ch;
}
int main(void) {
    for (volatile int i = 0; i < 2000000; ++i); // Delay
    uart2_tx_init();

    // LED init
    RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN;
    GPIOA->MODER |= (1U << 10); // PA5 output

    while (1) {
        GPIOA->ODR ^= (1U << 5); // Toggle LED
        printf("Hello from STM32F4.......\n\r");
        for (volatile int i = 0; i < 1000000; ++i);
    }
}

void uart2_tx_init(void) {
    RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN;

    // PA2 = USART2_TX
    GPIOA->MODER &= ~(3U << 4);
    GPIOA->MODER |=  (2U << 4);
    GPIOA->AFR[0] &= ~(0xF << 8);
    GPIOA->AFR[0] |=  (7U << 8);

    RCC->APB1ENR |= RCC_APB1ENR_USART2EN;
    uart_set_baudrate(USART2, APB1_CLK, UART_BAUDRATE);

    USART2->CR1 = USART_CR1_TE;
    USART2->CR1 |= USART_CR1_UE;
}

void uart2_write(int ch) {
    while (!(USART2->SR & USART_SR_TXE)) {}
    USART2->DR = (ch & 0xFF);
    while (!(USART2->SR & USART_SR_TC)) {}
}

void uart2_print(const char *str) {
    while (*str) {
        uart2_write(*str++);
    }
}

void uart_set_baudrate(USART_TypeDef *USART, uint32_t PeriphClk, uint32_t BaudRate) {
    USART->BRR = compute_uart_div(PeriphClk, BaudRate);
}

uint32_t compute_uart_div(uint32_t PeriphClk, uint32_t BaudRate) {
    return ((PeriphClk + (BaudRate / 2U)) / BaudRate);
}
