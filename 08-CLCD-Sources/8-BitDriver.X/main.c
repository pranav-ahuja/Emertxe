/*
 * File:   main.c
 */

#include <xc.h>
#include "clcd.h"

#pragma config WDTE = OFF        // Watchdog Timer Enable bit (WDT disabled)

static void init_config(void) {
    init_clcd();
}

void main(void) {
    init_config();

    while (1) {
        clcd_putch('H', LINE1(0));
        clcd_print("Hello", LINE2(0));
    }
    return;
}
