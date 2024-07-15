/* 
 * File:   AT24C04.h
 * Author: Pranav Ahuja
 * DESC: Implement a 4 digit key press counter with persistence using external EEPROM
 * Created on: 30 Oct, 2023 
 */


#ifndef AT24C04_H
#define	AT24C04_H
#define SLAVE_WRITE             0b10100000 // 0xD0
#define SLAVE_READ              0b10100001 // 0xD1

#define SEC_ADDR                0x00


void init_AT24C04(void);
unsigned char read_AT24C04(unsigned char addr);
void write_AT24C04(unsigned char addr, unsigned char data);

#endif	/* AT24C04_H */

