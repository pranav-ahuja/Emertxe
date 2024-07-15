/* 
 * File:   main.c
 * Author: Pranav Ahuja
 * DESC: Implement a scrolling number marquee with direction control
 * Created on: 26 Oct, 2023 
 */

#include "main.h"

#pragma config WDTE = OFF        // Watchdog Timer Enable bit (WDT disabled)

unsigned int num = 1234;
static void init_config(void) {
    //Initialize the peripherals
    init_ssd();
//    TRISD = 0x00;
//    PORTD = 0x00;
    init_digital_keypad();        
}

void main(void) {
    init_config();
    int wait = 0, i = 0;
    static unsigned char once = 0, hold = 0, left=0, right =0;
    unsigned char ssd[NUM_OF_SEG], key, prekey = ALL_RELEASED;
    unsigned char vals[12] = {ZERO, ONE, TWO, THREE, FOUR, FIVE, SIX, SEVEN, EIGHT, NINE, BLANK, BLANK};

    while (1) 
    {
        key = read_digital_keypad(LEVEL);
        
        if(key != ALL_RELEASED)
            prekey = key;
        
        
//        ssd[0] = vals[num / 1000];
//        ssd[1] = vals[(num/100) % 10];
//        ssd[2] = vals[(num/10) %10];
//        ssd[3] = vals[num % 10];
        if(wait++ == 200)
        {
            wait = 0;
            if((prekey == DKS1 || prekey == ALL_RELEASED) && hold == 0)
            {             
                left = 1;
                right = 0;
                if(once)
                {
                    i = i-3;
                    once = 0;
                }
                ssd[0] = vals[i%12];
                ssd[1] = vals[(i+1) % 12];
                ssd[2] = vals[(i+2) % 12];
                ssd[3] = vals[(i+3) % 12];
                i++;
                
                PORTD = 0x02;
            }
            
            else if((prekey == DKS2) && (hold == 0))
            {
                right = 1;
                left = 0;
                if(once == 0)
                {
                    i = i+3;
                    once = 1;
                }
                ssd[0] = vals[(12+ ((i-3) % 12)) %12];
                ssd[1] = vals[(12+ ((i-2) % 12)) %12];
                ssd[2] = vals[(12+ ((i-1) % 12)) %12];
                ssd[3] = vals[(12+ (i % 12)) %12];
                i--;                
            }
            
            else if(key == DKS3)
            {
//                prekey = ALL_RELEASED; 
                if(hold == 0)
                {
                    if(right)
                    {
                        i = i - 3;
                    }
                    hold = 1;
                    ssd[0] = vals[i];
                    ssd[1] = vals[i+1];
                    ssd[2] = vals[i+2];
                    ssd[3] = vals[i+3];
                }
                else if(hold == 1)
                {
                    hold = 0;
                    prekey == ALL_RELEASED;
                }
            }
        }
        
        display_ssd(ssd);
    }
        
    return;
}

