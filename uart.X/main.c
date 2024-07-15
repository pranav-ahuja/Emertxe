/* 
 * File:   main.c
 * Author: Pranav Ahuja
 * DESC: 
 * Created on October 27, 2023, 2:38 PM
 */

#include "main.h"

#pragma config WDTE = OFF        // Watchdog Timer Enable bit (WDT disabled)
unsigned char ch;
static void init_config(void) {
    //Initialize the peripherals
    TRISD = 0x00;
    TRISB = 0x00;
    LED = 0;
    
    init_uart(9600);
    
    GIE = 1;
    PEIE = 1;
    
    puts("UART TEST CODE\n\r");
}

void main(void) {
    init_config();    
    unsigned long int wait = 0;
    
    while (1) {
        //write the loop code
        if(ch != '\0')
        {
            putchar(ch);   
            putchar('\n');
            ch = '\0';
        }
            
        
        if(wait++ == 100000)
        {
            wait = 0;
            LED = !LED;
        }
        
    }
    return;
}
