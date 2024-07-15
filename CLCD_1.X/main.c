/*
 * File:   main.c
 * Author: Rakesh Ahuja
 *
 * Created on October 25, 2023, 11:58 PM
 */


#include "main.h"

#pragma config WDTE = OFF        // Watchdog Timer Enable bit (WDT disabled)

static void init_config(void) {
    init_clcd();
}

void main(void) {
    init_config();

    while (1) {
        clcd_putch('H', LINE1(5));
        clcd_print("Hello", LINE2(7));
    }
    return;
}
