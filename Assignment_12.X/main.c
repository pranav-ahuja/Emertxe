/*
 * File:   main.c
 */

#include <xc.h>
#include "clcd.h"
#include "matrix_keypad.h"

#pragma config WDTE = OFF        // Watchdog Timer Enable bit (WDT disabled)

//Matrix  Keypad 
//key 01 pressed


void display(unsigned char key)
{
    static unsigned char pos = 1;
    
    if (key != ALL_RELEASED)
    {
        if(key == 1)
        {
            clcd_print("*", LINE2(pos)); // Key 
            pos++;
        }       
        else if(key == 0)
        {
            clcd_print("#", LINE2(pos)); // Key 
            pos++;
        }                          
    }   
    else
    {
        clcd_write(0xC0, INST_MODE);
        clcd_write(0x0F, INST_MODE);
    }        
     
}

static void init_config(void) {
    init_clcd();
    init_matrix_keypad();
    
    clcd_print(" Enter Password ", LINE1(0));
}

void main(void) {
    unsigned char key, prekey, wait = 0;
    
    init_config();

    while (1) {
        key = read_matrix_keypad(STATE);  // 0 1 2 3 4 5 6 7 8 9 '*' '#'  ALL_RELEASED
        
        if(wait++ == 0)
        {
            wait = 0;
            if(key != ALL_RELEASED)
            {
                prekey = key;
                display(prekey);
            }
            display(key);
        }
        
    }
    return;
}

// Matrix keypad
// No Key Pressed