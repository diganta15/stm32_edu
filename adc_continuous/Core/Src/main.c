#include "stm32f401xe.h"
#include "uart.h"

#include "adc.h"

int __io_putchar(int ch){
    uart2_write(ch);
    return ch;
}

uint32_t sensor_value;

int main(){
    uart2_tx_init();
    pa1_adc_init();
    start_conversion();

    while(1){
        sensor_value = adc_read();
        printf("Sensor value: %d \n\r",(int)sensor_value);
    }
}
