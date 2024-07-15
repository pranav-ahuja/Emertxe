/* 
 * File:   i2c.h
 * Author: Rakesh Ahuja
 *
 * Created on October 28, 2023, 12:39 PM
 */

#ifndef I2C_H
#define	I2C_H

#include <xc.h>
#include "main.h"

#define FOSC            20000000
void i2c_init(unsigned long int baud_rate);
void i2c_wait_for_idle();
void i2c_start();
void i2c_repeat_start();
void i2c_stop();

unsigned char i2c_write(unsigned char data);
unsigned char i2c_read(unsigned char ack);
#endif	/* I2C_H */

