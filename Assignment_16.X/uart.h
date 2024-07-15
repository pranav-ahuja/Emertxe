/* 
 * File:   uart.h
 * Author: Pranav Ahuja
 * DESC: Implement a message display using UART and CLCD
 * Created on: 30 Oct, 2023 
 */

#ifndef UART_H
#define	UART_H

#define FOSC                20000000

void init_uart(unsigned long baud);
unsigned char getcharx(void);
void putchars(unsigned char data);
void putsx(const char *s);
void getsx(char *string);

#endif	/* UART_H */