#include "stdio.h"

#include "stm32f401xe.h"
#include "stdint.h"

#define SYS_FREQ 16000000U
#define APB1_CLK SYS_FREQ // USART2 is on APB1
#define UART_BAUDRATE 115200U

void uart2_rxtx_init(void);
void uart2_write(int ch);
void uart2_print(const char *str);
void uart_set_baudrate(USART_TypeDef *USART, uint32_t PeriphClk, uint32_t BaudRate);
uint32_t compute_uart_div(uint32_t PeriphClk, uint32_t BaudRate);
char uart2_read(void);

int __io_putchar(int ch)
{
    uart2_write(ch);
    return ch;
}

char key;
int main(void)
{
    for (volatile int i = 0; i < 2000000; ++i)
        ; // Delay
    uart2_rxtx_init();

    // Enable clock access and  Set PA5 as output pin
    RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN;
    GPIOA->MODER |= (1U << 10); // PA5 output
    GPIOA->MODER &= ~(1U << 11);

    while (1)
    {
        key = uart2_read();
        if (key == '1')
        {
            GPIOA->ODR |= (1U << 5);
        }
        else
        {
            GPIOA->ODR &= ~(1U << 5);
        }




    }
}

void uart2_rxtx_init(void)
{
    RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN;

    // PA2 = USART2_TX
    GPIOA->MODER &= ~(3U << 4);
    GPIOA->MODER |= (2U << 4);
    GPIOA->AFR[0] &= ~(0xF << 8);
    GPIOA->AFR[0] |= (7U << 8);

    // PA3 to alternate function mode
    GPIOA->MODER &= ~(1U << 6);
    GPIOA->MODER |= (1U << 7);
    // Set PA
    GPIOA->AFR[0] &= ~(0xF << 12);
    GPIOA->AFR[0] |= (7U << 12);

    RCC->APB1ENR |= RCC_APB1ENR_USART2EN;
    uart_set_baudrate(USART2, APB1_CLK, UART_BAUDRATE);

    // configure transfer direction
    USART2->CR1 = USART_CR1_TE | USART_CR1_RE;
    // enable uart module
    USART2->CR1 |= USART_CR1_UE;
}

char uart2_read(void)
{

    while (!(USART2->SR & USART_SR_RXNE))
    {

    }
    return USART2->DR;
}

void uart2_write(int ch)
{
    while (!(USART2->SR & USART_SR_TXE))
    {
    }
    USART2->DR = (ch & 0xFF);
    while (!(USART2->SR & USART_SR_TC))
    {
    }
}

void uart2_print(const char *str)
{
    while (*str)
    {
        uart2_write(*str++);
    }
}

void uart_set_baudrate(USART_TypeDef *USART, uint32_t PeriphClk, uint32_t BaudRate)
{
    USART->BRR = compute_uart_div(PeriphClk, BaudRate);
}

uint32_t compute_uart_div(uint32_t PeriphClk, uint32_t BaudRate)
{
    return ((PeriphClk + (BaudRate / 2U)) / BaudRate);
}
