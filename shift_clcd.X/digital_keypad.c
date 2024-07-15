/* 
 * File:   digital_keypad.c
 * Author: Pranav Ahuja
 * DESC: 
 * Created on October 26, 2023, 11:36 AM
 */

#include "main.h"

void init_digital_keypad()
{
    KEY_PORT_DDR = KEY_PORT_DDR | INPUT_LINES;
}

unsigned char read_digital_keypad(unsigned char mode)
{
    static unsigned char once = 1;
    if(mode == LEVEL)
    {
        return KEY_PORT & INPUT_LINES;
    }
    else if(mode == STATE)
    {
        if(((KEY_PORT & INPUT_LINES) != ALL_RELEASED) && once)
        {
            once = 0;
            return KEY_PORT & INPUT_LINES;
        }       
        else if((KEY_PORT && INPUT_LINES) == ALL_RELEASED)
        {
            once = 1;
        }        
    }
    return ALL_RELEASED;
}
