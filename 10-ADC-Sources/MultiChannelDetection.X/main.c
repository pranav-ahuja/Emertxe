/*
 * File:   main.c
 */

#include <xc.h>
#include "main.h"
#include "adc.h"
#include "clcd.h"

#pragma config WDTE = OFF        // Watchdog Timer Enable bit (WDT disabled)

void display(unsigned short adc_reg_val_1, unsigned short adc_reg_val_2)
{ 
    char buff[5];
    int i;
    
    clcd_print("C0:", LINE2(0));  
    // adc_reg_val_1 = 0 to 1023

    i = 3; // buff: "1 0 2 3"
    do
    {
        buff[i] = (adc_reg_val_1 % 10) + '0';//10%10 -> 0 + '0' 
        adc_reg_val_1 = adc_reg_val_1 / 10; //0
    } while (i--); // 0
    buff[4] = '\0';
    
    clcd_print(buff, LINE2(3));
    
    clcd_print("C1:", LINE2(9));
    
    i = 3;
    do
    {
        buff[i] = (adc_reg_val_2 % 10) + '0'; // 1024
        adc_reg_val_2 = adc_reg_val_2 / 10;
    } while (i--);
    buff[4] = '\0';
    
    clcd_print(buff, LINE2(12));
}

static void init_config(void) {
    init_clcd();
    init_adc();
    
    clcd_print("ADC Test", LINE1(4));
}

void main(void) {
    unsigned short adc_reg_val_1,adc_reg_val_2;
    
    init_config();

    while (1) {
        adc_reg_val_1 = read_adc(CHANNEL0); // pot1
        
        
        adc_reg_val_2 = read_adc(CHANNEL1); // pot2
        
        display(adc_reg_val_1, adc_reg_val_2);
    }
    return;
}
