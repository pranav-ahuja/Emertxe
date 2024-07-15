/* 
 * File:   main.c
 * Author: Pranav Ahuja
 * DESC: Implement a right scrolling message marquee
 * Created on: 26 Oct, 2023 
 */


#include "main.h"

#pragma config WDTE = OFF        // Watchdog Timer Enable bit (WDT disabled)

static void init_config(void) {
    //Initialize the peripherals
    init_display();        
}

void main(void) {
    init_config();    
    char str[] = "__Good Morning__";   
    char temp;
    int wait=0;
    unsigned char key, prekey;

    while (1) {
        //write the loop code  
        if(wait++ == 5000)
        {
            wait = 0;
            clcd_putstr("Right Scrolling", LINE1(0));
            temp = str[15];
            for(int i = 15; i >0; i--)
            {
                str[i] = str[i-1];
            }
            str[0] = temp;  
            
            clcd_putstr(str, LINE2(0));    
        }                  
                
    }
    return;
}
