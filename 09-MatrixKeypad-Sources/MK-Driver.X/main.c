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
    if (key != ALL_RELEASED)
    {
       // key 1 pressed
        clcd_print("Key  ", LINE2(0)); // Key 
        
        switch (key) //'*' '#' 
        {
            case '*':
            case '#':
                clcd_putch(key, LINE2(5)); //* #
                break;
            default: // 0 1 2 3 .. 9
                clcd_putch(key + '0', LINE2(5)); // 1 + '0' -> '1'
        }
        
        clcd_print("   Pressed", LINE2(6));
    }
    else
    {
        clcd_print(" No Key Pressed ", LINE2(0));
    }
}

static void init_config(void) {
    init_clcd();
    init_matrix_keypad();
    
    clcd_print(" Matrix  Keypad ", LINE1(0));
}

void main(void) {
    unsigned char key;
    
    init_config();

    while (1) {
        key = read_matrix_keypad(LEVEL);  // 0 1 2 3 4 5 6 7 8 9 '*' '#'  ALL_RELEASED
        display(key);
    }
    return;
}

// Matrix keypad
// No Key Pressed