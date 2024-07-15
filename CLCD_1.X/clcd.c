/*
 * File:   clcd.c
 * Author: Rakesh Ahuja
 *
 * Created on October 26, 2023, 12:02 AM
 */


#include "main.h"

void init_clcd()
{
    CLCD_PORT_DDR = 0x00;
    RS_PIN_DDR = 0;
    EN_PIN_DDR = 0;
    
    init_display_controller();
            
}

static void init_display_controller()
{
    __delay_ms(30);
    
    clcd_write(EIGHT_BIT_MODE, INSTRUCTION);
    
    __delay_us(4100);
    
    clcd_write(EIGHT_BIT_MODE, INSTRUCTION);
    
    __delay_us(4100);
    
    clcd_write(EIGHT_BIT_MODE, INSTRUCTION);
    
    __delay_us(4100);
    
    clcd_write(TWO_LINES_5x8_8_BIT_MODE, INSTRUCTION);
    
    __delay_us(4100);
    
    clcd_write(CLEAR_DISP_SCREEN, INSTRUCTION);
    
    __delay_us(4100);
    
    clcd_write(DISP_ON_AND_CURSOR_OFF, INSTRUCTION);
    
    __delay_us(4100);
}

static void clcd_write(unsigned char byte, unsigned char mode)
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
    clcd_write(addr, INSTRUCTION);        
    
    clcd_write(data, DATA);
}

void clcd_print(char *str, char addr)
{
    clcd_write(addr, INSTRUCTION);
    
    while(*str != '\0')
    {
        clcd_write(*str, DATA);
        str++;
    }
}