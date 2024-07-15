/*
 * File:   main.c
 */

#include <xc.h>
#include "ssd.h"

#pragma config WDTE = OFF        // Watchdog Timer Enable bit (WDT disabled)

static void init_config(void) {
    init_ssd();
}

void main(void) {
    unsigned char ssd[MAX_SSD_CNT];
    
    init_config();

    while (1) {
        ssd[0] = ONE;
        ssd[1] = TWO;
        ssd[2] = THREE;
        ssd[3] = FOUR;
        
        display(ssd);
    }
    return;
}
