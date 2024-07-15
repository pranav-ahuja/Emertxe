/* 
 * File:   main.c
 * Author: Pranav Ahuja
 * DESC: Implement a temperature sensor node with CLCD display
 * Created on: 30 Oct, 2023 
 */

#include <xc.h>
#include "main.h"
#include "adc.h"
#include "clcd.h"

#pragma config WDTE = OFF        // Watchdog Timer Enable bit (WDT disabled)

void display(unsigned short adc_reg_val)
{ 
    char buff[5];
    int i;

    i = 1; // buff: "1 0 2 3"
    do
    {               
        /*Convert volts to mv*/
        buff[i] = (adc_reg_val % 10) + '0';//10%10 -> 0 + '0' 
        /*convert mv to celcious*/
        adc_reg_val = adc_reg_val / 10; //0
    } while (i--); // 0
    buff[2] = '.';
    buff[3] = 'C';
    buff[4] = '\0';
    /*display the result  in clcd*/
    clcd_print(buff, LINE2(0));
}

static void init_config(void) {
    init_clcd();
    init_adc();
    
    clcd_print("TEMP SENSOR", LINE1(0));
}

void main(void) {
    unsigned short int adc_reg_val,x;
    
    init_config();

    while (1) {
        adc_reg_val = read_adc(CHANNEL2); 

        /*convert adc value to volts*/
        x = ((double)adc_reg_val * 0.488);
        display(x);
    }
    return;
}
