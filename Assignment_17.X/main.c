/* 
 * File:   main.c
 * Author: Pranav Ahuja
 * DESC: Implement a dynamic scrolling number marquee with rotation control
 * Created on: 30 Oct, 2023 
 */

#include <xc.h>
#include "clcd.h"
#include "matrix_keypad.h"
#include "timers.h"

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
    
    GIE = 1;
    init_clcd();
    init_matrix_keypad();
    init_timer0();
    clcd_print("enter the number", LINE1(0));
    
}

void main(void) {
    unsigned char key, cur_key;
    static char arr[16] = "";
    static int edit_key = 0, once = 1,count_letter = 0, scroll = 0,count,temp, pos = 0, char_pos;
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
        if(cur_key == 1 && scroll == 1)
        {
            /*logic for left scrolling*/
            clcd_write(CLEAR_DISP_SCREEN,INST_MODE);
            
            for(count = 0; count <= count_letter; count++)
            {
                char_pos = pos + count;
                if(char_pos < 0)
                    char_pos = 15;
                if(char_pos > 15)
                    char_pos = char_pos - 15;
                clcd_putch(arr[count],LINE2(char_pos));
            }
            pos--;
            if(pos < 0)
                pos = 15;
          
            for(unsigned long int i = 0; i<40000; i++);
        }
        if(cur_key == 2 && scroll == 1)
        {
            clcd_write(CLEAR_DISP_SCREEN,INST_MODE);
            
            for(count = 0; count <= count_letter; count++)
            {
                char_pos = pos + count;
                if(char_pos < 0)
                    char_pos = 15;
                if(char_pos > 15)
                    char_pos = char_pos - 15;
                clcd_putch(arr[count],LINE2(char_pos));
            }
            pos++;
            if(pos > 15)
                pos = 0;
            
            for(unsigned long int i = 0; i<40000; i++);
        }              
        /*increment the current position value*/
        if(key == 1 && edit_key == 1)
        {
            arr[count_letter] = arr[count_letter] + 1;
            if(arr[count_letter] > '9')
            {
                arr[count_letter] = '0';
            }
            if(arr[count_letter] < '0')
            {
                arr[count_letter] = '9';
            }
            clcd_putch(arr[count_letter], LINE2(5 + count_letter));
            SHIFT_CURSOR_LEFT1;
        }               
        /*decrement the current position value*/
        if(key == 2 && edit_key == 1)
        {
            arr[count_letter] = arr[count_letter] - 1;
            if(arr[count_letter] > '9')
            {
                arr[count_letter] = '0';
            }
            if(arr[count_letter] < '0')
            {
                arr[count_letter] = '9';
            }
           clcd_putch(arr[count_letter], LINE2(5 + count_letter));
            SHIFT_CURSOR_LEFT1;
        }
        /*logic for stop and start values */
        if(key == 3)
        {
            edit_key = !edit_key;
            
            scroll = !scroll;
            if(scroll == 1)
            {
                cur_key = 1;
            }
            DISP_ON_AND_CURSOR_OFF1;
            clcd_write(CLEAR_DISP_SCREEN,INST_MODE);
            clcd_print("Scrolling Marque", LINE1(0));
            clcd_print("Release stop key", LINE2(0));
        }
        /*logic for edit the value*/
        if(key == 4 || once)
        {
            edit_key = 1;
            scroll = 0;
            count_letter = 0;
            arr[count_letter] = '0';
            clcd_write(CLEAR_DISP_SCREEN,INST_MODE);
            clcd_print("Enter New Number", LINE1(0));
            clcd_print("Msg:", LINE2(0));
            clcd_putch(arr[0], LINE2(count_letter + 5));
            LCD_CURSOR_BLINK;
            SHIFT_CURSOR_LEFT1;
            
            once = 0;
        }
        /*logic for position changing and accept values*/
        if(key == 5 && edit_key == 1)
        {             
            count_letter++;               
            arr[count_letter] = '0';              
            if(count_letter > 10) 
            {
                count_letter = 10;
            }                
            clcd_putch(arr[count_letter], LINE2(5 + count_letter));                
            SHIFT_CURSOR_LEFT1;           
        }
        /*logic for delete the current position backspace */
        if(key == 6 && edit_key == 1)
        {
            arr[count_letter] = '0';
            clcd_putch(0x00, LINE2(5 + count_letter));
            count_letter--;
            if(count_letter < 0)
            {
                count_letter = 0;
            }
            SHIFT_CURSOR_LEFT1;
            SHIFT_CURSOR_LEFT1;
                    
        }
    }
    return;
}

