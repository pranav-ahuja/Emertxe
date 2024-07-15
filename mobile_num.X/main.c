/* 
 * File:   %<%NAME%>%.%<%EXTENSION%>%
 * Author: Pranav Ahuja
 * DESC: 
 * Created on %<%DATE%>%, %<%TIME%>%
 */

#include "main.h"

#pragma config WDTE = OFF        // Watchdog Timer Enable bit (WDT disabled)

static void init_config(void) {
    //Initialize the peripherals
    init_display();
    init_matrix_keypad();
        
}

void main(void) {
    init_config();
    clcd_putstr("Enter Mobile Num", LINE1(0));
        
    unsigned char key, prekey;

    while (1) {
        //write the loop code
//        key = read_digital_keypad(LEVEL);    
        
        key = read_matrix_key(STATE);
        if(key != ALL_RELEASED_MK)
        {
            prekey = key;
            
        }
        display(prekey);
//        else{
//            display(key);            
//        }                    
    }
    return;
}

void display(unsigned char key)
{
    if(key != ALL_RELEASED_MK)
    {
        clcd_putstr("Key : ", LINE2(0));
        
        switch(key)
        {
            case '*':
            case'#':
                clcd_putstr(CLR_LINE, LINE2(0));
                clcd_putch(key, LINE2(8));
                break;
            default:
                clcd_putstr(CLR_LINE, LINE2(0));
                clcd_putch(key + '0', LINE2(8));
        }
        
    }
    else{
        clcd_putstr("No key pressed", LINE2(0));
    }
}
