/* 
 * File:   %<%NAME%>%.%<%EXTENSION%>%
 * Author: Pranav Ahuja
 * DESC: 
 * Created on %<%DATE%>%, %<%TIME%>%
 */

#include "main.h"

#pragma config WDTE = OFF        // Watchdog Timer Enable bit (WDT disabled)

static void init_config(void) {
    //Initialize the peripherals
    init_display();
    init_digital_keypad();
        
}

void main(void) {
    init_config();
    clcd_putstr("Select DKP SW", LINE1(0));
    clcd_putstr("S0-Left S1-Right", LINE2(0));
    char str[] = "CLCD_Demo_Code_$";   
    char temp;
    unsigned char key, prekey;

    while (1) {
        //write the loop code
        key = read_digital_keypad(LEVEL);    
        
        if(key != ALL_RELEASED)
        {
            prekey = key;
        }
        
        if(prekey == SW0)
        {               
            clcd_putstr("Left Scroll", LINE1(0));
            temp = str[0];
            for(int i = 0; i < 15; i++)
            {
                str[i] = str[i+1];
            }
            str[15] = temp;
            
            clcd_putstr(str, LINE2(0));            
        }
        
        else if(prekey == SW1)
        {            
            clcd_putstr("Right Scroll", LINE1(0));
            temp = str[15];
            for(int i = 15; i >0; i--)
            {
                str[i] = str[i-1];
            }
            str[0] = temp;  
            
            clcd_putstr(str, LINE2(0));
        }
    }
    return;
}
