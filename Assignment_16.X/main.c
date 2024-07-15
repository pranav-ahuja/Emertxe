/* 
 * File:   main.c
 * Author: Pranav Ahuja
 * DESC: Implement a message display using UART and CLCD
 * Created on: 30 Oct, 2023 
 */

#include <xc.h>
#include <string.h>
#include "uart.h"
#include "clcd.h"

#pragma config WDTE = OFF        // Watchdog Timer Enable bit (WDT disabled)

extern unsigned char ch;
static void clcd_write(unsigned char byte, unsigned char mode)
{
    CLCD_RS = mode;
    
    CLCD_DATA_PORT = byte & 0xF0;
    CLCD_EN = HI;
    __delay_us(100);
    CLCD_EN = LOW;

    CLCD_DATA_PORT = (byte & 0x0F) << 4;
    CLCD_EN = HI;
    __delay_us(100);
    CLCD_EN = LOW;
    
    __delay_us(4100);
}
static void init_config(void) {

    init_clcd();
    init_uart(9600);
    
    putsx("UART Test Code\n");
    
    /* Enabling peripheral interrupt */
    PEIE = 1;
    
    /* Enabling global interrupt */
    GIE = 1;
}

void main(void) {
    unsigned long int wait = 0;
    char ch, str[90]="", str1[17]="",str2[17]="";
    unsigned int i = 0, count = 0;
    init_config();

    while (1) {
    
        /* To get the char string value in cute-com
         * STR1 is based on cute com value to print the results in LINE1
         * And then continues value STR2-LINE2 also 
         * finally STR2-LINE2 characters is completed.Then LINE2 value printed in LINE1 
         * And finally STR1-LINE1 is output shown STR2-LINE2 is clear the screen   
         */
        getsx(str); // function call
        for(i = 0; i < strlen(str); i++)
        {
            count++;
            if(count > 32)
            {
                count = 17;
               strncpy(str1,"",strlen(str1));
                for(i = 0; i < 16; i++)
                {
                    str1[i] = str2[i];
                }
                strncpy(str2,"",strlen(str2));
                 
            }
            if(count > 16)
            {
                str2[count-17] = str[i];               
            }
            else if(count <= 16)
            {
                str1[count-1] =str[i];
            }
        }
        str1[16] = '\0';
        str2[16] = '\0';
        strncpy(str,"",strlen(str));
        CLEAR_DISP_SCREEN1;
        /*display the result in clcd*/
        clcd_print(str1,LINE1(0));
        clcd_print(str2,LINE2(0));            
    }
    
    return;
}

