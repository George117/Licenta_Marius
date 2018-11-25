/*
 * File:   main.c
 * Author: georg
 *
 * Created on October 27, 2018, 10:59 AM
 */

#define _XTAL_FREQ 64000000
#include <xc.h>
#include "bit_settings.h"
#include "config.h"
#include "i2c_display.h"


void main(void) {
    config();
    
    while(1)
    {
        LATDbits.LATD0=1;
        __delay_ms(10);
        LATDbits.LATD0=0;
        __delay_ms(10);
        Lcd_Clear();
        for(int i=0x41;i<0x5A;i++)
        {
            Lcd_Set_Cursor(1,1);       
            Lcd_Write_Char(i);
            __delay_ms(500);
        }
        
        __delay_ms(1);
    }
    
    return;
}
