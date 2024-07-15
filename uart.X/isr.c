/* 
 * File:   isr.c
 * Author: Pranav Ahuja
 * DESC: 
 * Created on October 27, 2023, 4:46 PM
 */

#include <xc.h>
extern unsigned char ch;
void __interrupt() isr(void) 
{
    if(RCIF == 1)
    {
        if(OERR == 1)
            OERR = 0;
        
        ch = RCREG;
        RCIF = 0;
    }
}
