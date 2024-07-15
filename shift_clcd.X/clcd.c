/* 
 * File:   clcd.c
 * Author: Pranav Ahuja
 * DESC: 
 * Created on October 26, 2023, 11:53 AM
 */

#include "main.h"

void init_display() 
{
    CLCD_PORT_DDR = 0x00;
    RS_PIN_DDR = 0;
    EN_PIN_DDR = 0;
    
    init_display_controller();
}

void init_display_controller()
{
    __delay_ms(30);
    
    clcd_write(INST_MODE, EIGHT_BIT_MODE);
    __delay_us(4100);
    
    clcd_write(INST_MODE, EIGHT_BIT_MODE);
    __delay_us(200);
    
    clcd_write(INST_MODE, EIGHT_BIT_MODE);
    __delay_us(1);
    
    clcd_write(INST_MODE, TWO_LINES_5x8_8_BIT_MODE);
    __delay_us(100);
    
    clcd_write(INST_MODE, CLEAR_DISPLAY);
    __delay_us(500);
    
    clcd_write(INST_MODE, DISPLAY_ON_CURSOR_OFF);
    __delay_us(100);
}

void clcd_write(char mode, char byte)
{
    RS_PIN = mode;
   
    CLCD_PORT = byte;
    
    EN_PIN = HI;
    __delay_us(100);
    EN_PIN = LO;
    __delay_us(4100);
    
}

void clcd_putch(char data, char addr)
{
    
    clcd_write(INST_MODE, addr);
    clcd_write(DATA_MODE, data);
}

void clcd_putstr(char *str, char addr)
{
    clcd_write(INST_MODE, addr);
    
    while(*str != '\0')
    {
        clcd_write(DATA_MODE, *str);
        str++;
    }
}