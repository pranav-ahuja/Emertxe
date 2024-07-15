/* 
 * File:   timer.c
 * Author: Pranav Ahuja
 *  
 * Created on October 27, 2023, 12:27 PM
 */

#include <xc.h>

void init_timer0(void)
{
    /* Setting the internal clock source */
    T0CS = 0;
    
    /* Assinging the prescaler to Watchdog Timer */
    PSA = 1;

    TMR0 = 6;
    
    /* The timer interrupt is enabled */
    
}

