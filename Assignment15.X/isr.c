/* 
 * File:   isr.c
 * Author: Pranav Ahuja
 * DESC: Implement system sleep and wake up while Interrupt on change
 * Created on: 30 Oct, 2023 
 */

#include <xc.h>
#include "main.h"
#include "ssd.h"

int count1;
void __interrupt() isr(void)
{
    static unsigned int count = 0;
    if (TMR0IF == 1)
    {
        TMR0 = TMR0 + 6 + 2;
        if (++count == 15000)
        {
            if(INTF == 1)
            {
                count1 = 0;
                INTF = 0;
                TMR0IE = 1;
                
            }
            count1++;
            
            count = 0;
            LED1 = !LED1;  
        }
        
        TMR0IF = 0;
    }
    
}