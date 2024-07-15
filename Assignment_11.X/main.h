/* 
 * File:   main.h
 * Author: Rakesh Ahuja
 *
 * Created on October 26, 2023, 11:04 AM
 */

#ifndef MAIN_H
#define	MAIN_H

#include <xc.h>
#include <string.h>

/*CLCD*/
#define _XTAL_FREQ                  20000000
#define CLCD_PORT                   PORTD
#define CLCD_PORT_DDR               TRISD

#define RS_PIN                      RE2
#define RS_PIN_DDR                  TRISE2
#define EN_PIN                      RE1
#define EN_PIN_DDR                  TRISE1

#define CLEAR_DISPLAY               0x01
#define FOUR_BIT_MODE               0x02
#define DISPLAY_ON_CURSOR_OFF       0x0C
#define EIGHT_BIT_MODE              0x33
#define TWO_LINES_5x8_8_BIT_MODE    0x38
#define TWO_LINES_5x8_4_BIT_MODE    0x28

#define LINE1(x)                    (0x80 + x)
#define LINE2(x)                    (0xC0 + x)

#define DATA_MODE                   1
#define INST_MODE                   0

#define HI                          1
#define LO                          0

void init_display();
void init_display_controller();
void clcd_write(char, char);
void clcd_putch(char, char);
void clcd_putstr(char *, char);

#endif	/* MAIN_H */

