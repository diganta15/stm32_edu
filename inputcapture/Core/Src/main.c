#include "tim.h"
#include "stm32f401xe.h"
#include <stdint.h>

int timestamp = 0;


//setup connection between pa5 to pa6
int main(void){
  tim2_output_compare();
  tim_pa6_input_capture();

  while(1){
    //wait until edge is captured
    while(!(TIM3->SR & TIM_SR_CC1IF)){}
    //read value
    timestamp = TIM3->CCR1;

    //clear capture flag
//    TIM3->SR &= ~TIM_SR_CC1IF;
  }

}
