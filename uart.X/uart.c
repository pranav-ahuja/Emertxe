/* 
 * File:   uart.c
 * Author: Pranav Ahuja
 * DESC: 
 * Created on October 27, 2023, 2:39 PM
 */

#include "main.h"

void init_uart(unsigned long baud_rate) {
    
    //TRANSMITTER
    
    SPEN = 1;
    
    TXEN = 1;
    
    BRGH = 1;   //high(1) or low(0) speed baud rate
    
    //Receiver      
    
    CREN = 1;
    
    RCIE = 1;
    
    //baud rate
    
    SPBRG = (FOSC /(16 * baud_rate) - 1); 
}

//unsigned char getchar()
//{
//    while(RCIF != 1);
//    
//    RCIF = 0;
//    
//    return RCREG;
//}

void putchar(unsigned char ch)
{
    TXREG = ch;
    
    while(TXIF != 1);
    
    TXIF = 0;
}

void puts(const char *str)
{
    while(*str)
    {
        putchar(*str++);
    }
}