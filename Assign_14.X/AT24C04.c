/* 
 * File:   AT24C04.c
 * Author: Pranav Ahuja
 * DESC: Implement a 4 digit key press counter with persistence using external EEPROM
 * Created on: 30 Oct, 2023 
 */


#include "i2c.h"
#include "AT24C04.h"

void init_AT24C04(void)
{
    unsigned char dummy;
    
    dummy = read_AT24C04(SEC_ADDR);
    dummy = dummy & 0x7F;
    write_AT24C04(SEC_ADDR, dummy);
}

unsigned char read_AT24C04(unsigned char addr)
{
    unsigned char data;
    
    i2c_start();
    i2c_write(SLAVE_WRITE);
    i2c_write(addr);
    i2c_rep_start();
    i2c_write(SLAVE_READ);
    data = i2c_read(0);
    i2c_stop();
    
    return data;
}

void write_AT24C04(unsigned char addr, unsigned char data)
{
    i2c_start();
    i2c_write(SLAVE_WRITE);
    i2c_write(addr);
    i2c_write(data);
    i2c_stop();
}
