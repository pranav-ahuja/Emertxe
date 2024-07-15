/* 
 * File:   ssd.c
 * Author: Pranav Ahuja
 * DESC: Implement a scrolling number marquee with direction control
 * Created on: 26 Oct, 2023 
 */

#include <xc.h>

#include "main.h"

void init_ssd() {
    SSD_PORT_DDR = 0x00;
    SSD_PORT = 0x00;
    
    SSD_CNTRL_DDR = SSD_CNTRL_DDR & 0x03;
    SSD_CNTRL_PORT &= 0x03;
}

void display_ssd(unsigned char data[])
{
    unsigned char digit;
    
    for(digit = 0; digit< NUM_OF_SEG; digit++)
    {
        SSD_PORT = data[digit];
        SSD_CNTRL_PORT = (SSD_CNTRL_PORT & 0x03) | (0x04 << digit);
        
        for(int i = 400; i--;);
    }
}
