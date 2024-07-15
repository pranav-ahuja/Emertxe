/* 
 * File:   main.c
 * Author: Pranav Ahuja
 * DESC: Implement system sleep and wake up while Interrupt on change
 * Created on: 30 Oct, 2023 
 */

#include <xc.h>
#include "main.h"
#include "timers.h"
#include "ssd.h"

#pragma config WDTE = OFF        // Watchdog Timer Enable bit (WDT disabled)

extern int count1;
static void init_config(void) {
    
    LED_ARRAY1_DDR7 = 0;
    init_ssd();
    init_timer0();
    LED1 = 0;    

    /* Enable all the Global Interrupts */
    GIE = 1;
    
    INTE = 1;
 
}

void main(void) {
    
    static unsigned char ssd[]={ONE, TWO, THREE, FOUR};
    init_config();

    while (1) {
               
        if( count1 >= 5)           
        {            
            TMR0IE = 0;          
            /*turning off led arrays*/
            LED_ARRAY1 = 0x00;
            LED_ARRAY2 = 0x00;                         
            
        }
        if(count1 < 5)           
        {
            /*display 1 2 3 4 on ssd*/  
            display(ssd);             
        }                                 
          
    }
    return;
}
