/* 
 * File:   rtc.c
 * Author: Pranav Ahuja
 * DESC: 
 * Created on October 28, 2023, 3:22 PM
 */

#include "main.h"
#include "i2c.h"

void init_rtc(void) {
    unsigned char dummy;
    
    dummy = ds1307_read(SEC_ADDR);    
    dummy = dummy & 0x7F;  //CH = 0
    ds1307_write(SEC_ADDR, dummy);
}

unsigned char ds1307_read(unsigned char address)
{
    unsigned char data;
    
    i2c_start();            //send the start bit
    i2c_write(RTC_ADD_WRITE);   //send unique address of RTC with write intention 
    i2c_write(address);     //send the address from where the read has to be performed
    
    i2c_repeat_start();     //send the repeated start
    i2c_write(RTC_ADD_READ);    //send the unique address of RTC with read address
    data = i2c_read(0);     //read the data from the above mentioned address and get the data in the variable
    
    i2c_stop();     //send the stop bit
    
    return data;    //return the data
}

void ds1307_write(unsigned char address, unsigned char value)
{
    
    i2c_start();                //transmit the start bit
    i2c_write(RTC_ADD_WRITE);   //send the unique address with intention
    i2c_write(address);         //send the address where the data has to be written
    i2c_write(value);           //send the data to the specified register
    i2c_stop();                 //transmit the stop bit    
}
