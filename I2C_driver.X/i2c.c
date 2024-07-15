/* 
 * File:   i2c.c
 * Author: Pranav Ahuja
 * DESC: 
 * Created on October 28, 2023, 12:40 PM
 */

#include "i2c.h"

void i2c_init(unsigned long int baud_rate)
{
    //initialize the i2c module -> SSPCON1 reg
    SSPEN = 1;
    
    //Select master mode -> SSPCON1 reg
    SSPM3 = 1;
    
    //SSPADD will act as a baud rate generator. The formula is given in the data sheet
    SSPADD = (FOSC / baud_rate * 4) - 1;    
    
}

void i2c_wait_for_idle()
{
    //wait till the R_nW || (SEN || RCEN || ACKEN || PEN || RSEN) is 0. Once it is 0, the bus become idle and ready to transfer
    while(R_nW || (SSPCON2 & 0x1F));
}

void i2c_start()
{
    //wait till the bus gets idle, if it gets idle then send the start bit
    i2c_wait_for_idle();
    SEN = 1;
}

void i2c_repeat_start()
{
    //wait till the bus gets idle, if it gets idle then activate the repeated start condition
//    i2c_stop();
//    i2c_start();
    i2c_wait_for_idle();
    RSEN = 1;
}

void i2c_stop()
{
    //wait till the bus gets idle, if it gets idle then activate the repeated start condition
    i2c_wait_for_idle();
    PEN = 1;
}

unsigned char i2c_write(unsigned char data)
{
    //wait till the bus gets idle, one it is idle write the data to buffer register
    i2c_wait_for_idle();
    SSPBUF = data;
    
    //return the acknowledge status from the slave
    return !ACKSTAT;
}

unsigned char i2c_read(unsigned char ack)
{
    unsigned char data;
    
    i2c_wait_for_idle();
    RCEN = 1;   //set to receive the data
    
    i2c_wait_for_idle();
    data = SSPBUF;
    
    if(ack == 1)
    {
        ACKDT = 1; //no acknowledge required
    }
    else if(ack == 0)
    {
        ACKDT = 0;  //acknowledge needed
    }
    
    ACKEN = 1;
    
    return data;                        
}

