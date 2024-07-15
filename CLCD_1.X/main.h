/* 
 * File:   main.h
 * Author: Rakesh Ahuja
 *
 * Created on October 25, 2023, 11:26 PM
 */

#ifndef MAIN_H
#define	MAIN_H

#include <xc.h>

#define _XTAL_FREQ          20000000
#define CLCD_PORT           PORTD
#define CLCD_PORT_DDR       TRISD

#define RS_PIN              RE2
#define EN_PIN              RE1
#define RS_PIN_DDR          TRISE2
#define EN_PIN_DDR          TRISE1

#define INSTRUCTION         0
#define DATA                1

#define EIGHT_BIT_MODE              0x33
#define TWO_LINES_5x8_8_BIT_MODE    0x38
#define CLEAR_DISP_SCREEN           0x01
#define DISP_ON_AND_CURSOR_OFF      0x0C

#define HI                  1
#define LO                  0

#define LINE1(x)            (0x80 + x)
#define LINE2(x)            (0xC0 + x)

void init_clcd();
static void init_display_controller();

static void clcd_write(unsigned char , unsigned char);

void clcd_putch(char, char);
void clcd_print(char *, char);
#endif	/* MAIN_H */

