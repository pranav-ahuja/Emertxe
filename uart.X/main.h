/* 
 * File:   main.h
 * Author: Pranav Ahuja
 *
 * Created on October 27, 2023, 2:25 PM
 */

#ifndef MAIN_H
#define	MAIN_H

#include<xc.h>

#define FOSC                20000000
#define LED                 RD1

void init_uart(unsigned long baud_rate);
//unsigned char getchar();
void putchar(unsigned char ch);
void puts(const char *str);
#endif	/* MAIN_H */

