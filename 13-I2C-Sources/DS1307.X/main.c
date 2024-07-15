/*
 * File:   main.c
 */

#include <xc.h>
#include "i2c.h"
#include"ds1307.h"
#include "clcd.h"

#pragma config WDTE = OFF        // Watchdog Timer Enable bit (WDT disabled)

static void display_time(unsigned char *clock_reg)
{
    //BCD Format 
    //clock_reg[0] = HH
    //clock_reg[1] = MM
    //clock_reg[2] = SS
   
    /* To store the time in HH:MM:SS format */
    char time[9];  // "HH:MM:SS"
    // HH -> 
    time[0] = ((clock_reg[0] >> 4) & 0x03) + '0';
    time[1] = (clock_reg[0] & 0x0F) + '0';
    
    time[2] = ':';
    // MM 
    time[3] = ((clock_reg[1] >> 4) & 0x07) + '0';
    time[4] = (clock_reg[1] & 0x0F) + '0';
    
    time[5] = ':';
    // SS
    time[6] = ((clock_reg[2] >> 4) & 0x07) + '0';
    time[7] = (clock_reg[2] & 0x0F) + '0';
    time[8] = '\0';
    
    clcd_print(time, LINE2(4)); // HH:MM:SS 
}

static void get_time(unsigned char *clock_reg)
{
    clock_reg[0] = read_ds1307(HOUR_ADDR); // HH -> BCD 
    clock_reg[1] = read_ds1307(MIN_ADDR); // MM -> BCD 
    clock_reg[2] = read_ds1307(SEC_ADDR); // SS -> BCD 
}

static void init_config(void) {
    init_i2c(100000); //100K
    init_ds1307();
    
    init_clcd();
    clcd_print("  DS1307  TEST  ", LINE1(0));
}

void main(void) {
    unsigned char clock_reg[3]; // HH MM SS
                               // 0   1  2 
    
    init_config();

    while (1) {
        get_time(clock_reg); // HH MM SS
        
        display_time(clock_reg); // HH:MM:SS --> 13:14:15
    }
    
    return;
}
