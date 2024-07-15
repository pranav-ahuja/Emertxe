/* 
 * File:   matrix_keypad.c
 * Author: Pranav Ahuja
 * DESC: 
 * Created on October 26, 2023, 4:21 PM
 */

#include "main.h"

void init_matrix_keypad()
{
    ROWS_DDR = ROWS_DDR & 0xF0;
    COLS_DDR = COLS_DDR | 0x07;
    
    nRBPU = 0;
    
    ROW1 = 1;
    ROW2 = 1;
    ROW3 = 1;
    ROW4 = 1;
}

unsigned char read_matrix_key(unsigned char mode)
{
    static unsigned char once = 1;
    unsigned char key = scan_keypad();
    if(mode == LEVEL)
    {
        return key;
    }
    else if(mode == STATE)
    {
        if((key != ALL_RELEASED_MK) && once)
        {
            once = 0;
            return key;
        }
        else if(key == ALL_RELEASED_MK)
        {
            once = 1;
        }
    }
    
    return ALL_RELEASED_MK;
}

unsigned char scan_keypad()
{        
    ROW1 = 0;
    ROW2 = 1;
    ROW3 = 1;
    ROW4 = 1;
    
    for(int i = 100; i--; );
    
    if(COL1 == 0)
        return 1;
    else if(COL2 == 0)
        return 2;
    else if(COL3 == 0)
        return 3;        
    
    ROW1 = 1;
    ROW2 = 0;
    ROW3 = 1;
    ROW4 = 1;
    
    for(int i = 100; i--; );
    
    if(COL1 == 0)
        return 4;
    else if(COL2 == 0)
        return 5;
    else if(COL3 == 0)
        return 6;
    
    ROW1 = 1;
    ROW2 = 1;
    ROW3 = 0;
    ROW4 = 1;
    
    for(int i = 100; i--; );
    
    if(COL1 == 0)
        return 7;
    else if(COL2 == 0)
        return 8;
    else if(COL3 == 0)
        return 9;
    
    ROW1 = 1;
    ROW2 = 1;
    ROW3 = 1;
    ROW4 = 0;
    
    for(int i = 100; i--; );
    
    if(COL1 == 0)
        return '*';
    else if(COL2 == 0)
        return 0;
    else if(COL3 == 0)
        return '#';
    
    return ALL_RELEASED_MK;
}