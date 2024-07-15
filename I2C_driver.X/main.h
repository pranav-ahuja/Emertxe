/* 
 * File:   main.h
 * Author: Rakesh Ahuja
 *
 * Created on October 28, 2023, 12:39 PM
 */

#ifndef MAIN_H
#define	MAIN_H

#include <xc.h>

#define SEC_ADDR            0x00
#define MIN_ADD             0x01
#define HR_ADD              0x02

#define RTC_ADD_WRITE       0xD0    //1101 0000
#define RTC_ADD_READ        0xD1    //1101 0001


void init_rtc();
void ds1307_write(unsigned char address, unsigned char value);
unsigned char ds1307_read(unsigned char address);
void get_time(unsigned char clock_reg[]);
void display_time(unsigned char clock_reg[]);
#endif	/* MAIN_H */

