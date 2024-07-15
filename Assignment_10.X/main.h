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

/*SWITCH*/

#define KEY_PORT                    PORTB
#define KEY_PORT_DDR                TRISB

#define STATE                       1
#define LEVEL                       0

#define INPUT_LINES                 0x3F
#define ALL_RELEASED                INPUT_LINES

#define DKS1                         0x3E
#define DKS2                         0x3D
#define DKS3                         0x3B
#define DKS4                         0x37
#define DKS5                         0x2F
#define DKS6                         0x1F

void init_digital_keypad();
unsigned char read_digital_keypad(unsigned char mode);

/*SSD*/
#define NUM_OF_SEG                  4

#define SSD_PORT                    PORTD
#define SSD_PORT_DDR                TRISD

#define SSD_CNTRL_PORT              PORTA
#define SSD_CNTRL_DDR               TRISA

#define ZERO                        0x3F
#define ONE                         0x06
#define TWO                         0x5B
#define THREE                       0x4F
#define FOUR                        0x66
#define FIVE                        0x6D
#define SIX                         0x7D
#define SEVEN                       0x07
#define EIGHT                       0x7F
#define NINE                        0x6F
#define BLANK                       0x08

void init_ssd();
void display_ssd(unsigned char data[]);



#endif	/* MAIN_H */

