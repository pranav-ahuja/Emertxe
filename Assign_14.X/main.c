/* 
 * File:   main.c
 * Author: Pranav Ahuja
 * DESC: Implement a 4 digit key press counter with persistence using external EEPROM
 * Created on: 30 Oct, 2023 
 */


#include <xc.h>
#include "ssd.h"
#include "digital_keypad.h"
#include "i2c.h"
#include "AT24C04.h"
#pragma config WDTE = OFF

/*configuring display and ssd*/
void init_config(void)
{
	init_ssd();
	init_digital_keypad();
    init_i2c(100000);
    init_AT24C04();
}


void main(void)
{
    init_config();
    static unsigned char ssd[MAX_SSD_CNT]={ZERO,ZERO,ZERO,ZERO};
    static unsigned char digit[] = {ZERO, ONE,TWO, THREE, FOUR, FIVE, SIX, SEVEN, EIGHT, NINE, UNDERSCORE, UNDERSCORE};
	static unsigned long int count = 0, flag = 0 ;
	unsigned char key ;
	while(1)
	{
		key = read_digital_keypad(STATE);
        
        
		/* if switch 1 pressed increment counter by 1 */
		if ( key == SW1 )
		{
            if(flag == 0)
            {
                count++;
                if (count > 9) 
                {
                    count = 0;
                }
               
            }
            flag=0;
            /*giving digit to ssd */
			ssd[3] = digit[count % 10];
			ssd[2] = digit[(count % 100)/10];
			ssd[1] = digit[(count % 1000)/100];
			ssd[0] = digit[count / 1000];
            
            
		}
        else if (key == SW2)
        {
            /*writing every digit in eeprom*/
            write_AT24C04(0x04, (count % 10));
            write_AT24C04(0x03, ((count % 100)/10));
            write_AT24C04(0x02, ((count % 1000)/100));
            write_AT24C04(0x01, (count / 1000));
        }
        
		/* if switch 1 pressed for long than reset counter */
		else if ( key == LPSW1 )
		{
            /*reading the stored count value*/
            count = 1000*read_AT24C04(0x01) + 100*read_AT24C04(0x02) + 10*read_AT24C04(0x03) + read_AT24C04(0x04);
			flag = 1;  
            /*giving digit to ssd */
			ssd[3] = ZERO;
			ssd[2] = ZERO;
			ssd[1] = ZERO;
			ssd[0] = ZERO;
            
		}
        /*displaying the digit in ssd */
        display(ssd);
		
	}
}