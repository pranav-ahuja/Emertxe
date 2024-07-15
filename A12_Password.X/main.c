/* 
 * File:   main.c
 * Author: Pranav Ahuja
 *  
 * Created on October 27, 2023, 12:26 PM
 */

#include <xc.h>
#include "clcd.h"
#include "timer.h"
#include "matrix_keypad.h"
#include "main.h"

#pragma config WDTE = OFF        // Watchdog Timer Enable bit (WDT disabled)

/*global variable to reduce led light blink time*/
int sigma;
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
/*intialization of clcd,matrix keypad and timer zero*/
static void init_config(void) {
    LED_ARRAY1_DDR = 0;
    LED_ARRAY1 = LED_ARRAY1 & 0x7F;
    GIE = 1;
    init_clcd();
    init_matrix_keypad();
    init_timer0();
    
}

void main(void) {
    unsigned char key,cur_key;
    static char password[] = {0,0,0,0,0,0,0,0};
    static int flag1 = 0, count = 0, count1 = 0, attempt, once = 1;
    char ptr[]= "1";
    static char pwd[8];
    
    init_config();

    while (1) {
        /*reading keys*/
        key = read_matrix_keypad(STATE);  // 0 1 2 3 4 5 6 7 8 9 '*' '#'  ALL_RELEASED
        /* assigning key to the cur_key*/
        if(key != ALL_RELEASED)
        {
            cur_key = key;
        }
        
        /*checking if correct or wrong password entered previously*/
        if(flag1 == 0)
        {
            /*checking key is pressed 8 times and less*/
            if (key != ALL_RELEASED && count < 8)
            {
                pwd[count] = key;
                    /*clearing the display for the first time*/
               
                    
                    clcd_putch('*', LINE2(count));
                    
                    /*increasing the count for matched character*/
                if(pwd[count] == password[count])
                {
                    count1++;
                }
                count++;
            }
            /*checking the correct password is entered*/
            else if(count == 8 && count1 == count)
            {
                DISP_ON_AND_CURSOR_OFF1;
                /*clearing the display*/
                clcd_write(CLEAR_DISP_SCREEN, INST_MODE);
          
                clcd_print("Excellent! You",LINE1(1));
                clcd_print("Cracked the Code",LINE2(0));

                flag1 = 1;
                if(TMR0IE == 1)
                {
                    TMR0IE = 0;
                    LED7 = 0;
                }
            }
            /*checking if wrong password is entered*/
            else if(count == 8 && count1 != count)
            {
                sigma = sigma + 2;
                /*turning on timer to glow led at different speed*/
                if(TMR0IE == 0)
                    TMR0IE = 1;

                ++attempt;
                count1 = 0;
                count = 0;
                once = 1;
                
                /*clearing the display and showing number of attempts*/
                
                clcd_write(CLEAR_DISP_SCREEN, INST_MODE);
                DISP_ON_AND_CURSOR_OFF1;
                clcd_print("Attempt",LINE1(0));
                clcd_print(ptr,LINE1(9));
                ptr[0] = ptr[0] + 1;
                for(unsigned long int i = 0; i < 500; i++);

            }
            /*checking if 5 attempts are done*/
            else if(attempt == 5)
            {
                /*clearing the display and blocking the user to enter password*/
                DISP_ON_AND_CURSOR_OFF1;
                clcd_write(CLEAR_DISP_SCREEN, INST_MODE);            
                clcd_print("Password Failed",LINE1(0));
                clcd_print("Reset your board",LINE2(0));
                flag1 = 1;
                
            }
            /*blinking the _ till the password is entered*/
            else if(key == ALL_RELEASED && count == 0 && once)
            {
                once = 0;
                clcd_write(CLEAR_DISP_SCREEN, INST_MODE);
                clcd_print("Enter Password", LINE1(0));
                LCD_CURSOR_LINE2;
                LCD_CURSOR_BLINK;
            }
        }
    }
    return;
}