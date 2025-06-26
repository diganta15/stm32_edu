/*
 * systick.c
 *
 *  Created on: Jun 25, 2025
 *      Author: digantadas
 */

#include "systick.h"

#define SYSTICK_LOAD_VAL    16000
#define CTRL_ENABLE         (1U<<0)
#define CTRL_CLKSRC         (1U<<2)
#define CTRL_COUNTFLAG      (1U<<16)

void systickDelayMs(int delay){
    //configure systick
    SysTick->LOAD = SYSTICK_LOAD_VAL;

    //clear systick current value register
    SysTick->VAL = 0;
    //enable systick and select internal clk src
    SysTick->CTRL = SysTick_CTRL_ENABLE_Msk | SysTick_CTRL_CLKSOURCE_Msk;
    
    for(int i=0; i<delay; i++){
        //wait until the countflag is set
        while((SysTick->CTRL & SysTick_CTRL_COUNTFLAG_Msk)==0){

        }
    }
    SysTick->CTRL = 0;

}
