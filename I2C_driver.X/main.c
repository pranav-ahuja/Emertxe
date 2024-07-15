/* 
 * File:   main.c
 * Author: Pranav Ahuja
 * DESC: 
 * Created on October 28, 2023, 12:39 PM
 */

#include "i2c.h"
#include "main.h"
#include "clcd.h"

#pragma config WDTE = OFF        // Watchdog Timer Enable bit (WDT disabled)

static void init_config(void) {
    //Initialize the peripherals
    i2c_init(100000);
    init_clcd();
    init_rtc(); //Initialization of RTC - ds1307
    clcd_print("HH:MM:SS", LINE1(2));
}

void main(void) {
    init_config();
    unsigned char clock_reg[3]; //{hr, min, sec}

    while (1) {
        //write the loop code
        get_time(clock_reg);
        display_time(clock_reg);//we cannot display bcd directly on LCD. So we have top call this function to change the bcd to characters
    }
    return;
}

void get_time(unsigned char clock_reg[])
{
    clock_reg[0] = ds1307_read(HR_ADD);
    clock_reg[1] = ds1307_read(MIN_ADD);
    clock_reg[2] = ds1307_read(SEC_ADDR);
}

void display_time(unsigned char clock_reg[])
{
    char time[9];
    
    //hour digits
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
    
    clcd_print(time, LINE2(3));          
}