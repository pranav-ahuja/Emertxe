/* 
 * File:   timers.c
 * Author: Pranav Ahuja
 * DESC: Implement system sleep and wake up while Interrupt on change
 * Created on: 30 Oct, 2023 
 */

#include <xc.h>
#include "timers.h"
void init_timer0(void)
{
    /* Setting the internal clock source */
    T0CS = 0;
    
    /* Assinging the prescaler to Watchdog Timer */
    PSA = 1;

    TMR0 = 6;
    
    /* The timer interrupt is enabled */
    TMR0IE = 1;
}

