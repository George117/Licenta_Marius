/*
 * File:   config.c
 * Author: georg
 *
 * Created on January 1, 2017, 1:37 PM
 */

#define _XTAL_FREQ 16000000
#include <xc.h>
#include <pic18f46k22.h>
#include "bit_settings.h"
#include "i2c_display.h"


void config()
{

    int cor;
    OSCCONbits.IRCF0=1;
    OSCCONbits.IRCF1=1;//16Mhz
    OSCCONbits.IRCF2=1;
    OSCTUNEbits.PLLEN = 0; // turn on the PLL 64 MHz
    INTCONbits.GIE=0;

    ANSELA=0X00;
    ANSELB=0X00;
    ANSELC=0X00;
    ANSELD=0X00;
    ANSELE=0X00;
    TRISA=0X00;
    TRISB=0X00;
    TRISC=0X00;
    TRISD=0X00;
    TRISE=0X00;
    PORTA=0X00;
    PORTB=0X00;
    PORTC=0X00;
    PORTD=0X00;
    PORTE=0X00;
    LATA=0X00;
    LATB=0X00;
    LATC=0X00;
    LATD=0X00;
    LATE=0X00;
    
    TRISCbits.TRISC3=1;//i2c
    TRISCbits.TRISC4=1;//i2c
    I2C_Master_Init(100000);
    __delay_ms(100);
    Lcd_Init();
    Lcd_Clear();
    Cursor_Off();
    Lcd_Set_Cursor(1,1);
    Lcd_Write_String("Test");
    __delay_ms(100);
    
        ////tmr1 config/////////
    T1CON=0x30;
    T1GCON=0x40;
    ///////////////////////
    
    
    TRISBbits.TRISB4=1;
    TRISBbits.TRISB5=1;
    TRISBbits.TRISB6=1;
    ///int config
    RCONbits.IPEN=0;//CU NIVELE DE INTRERUPERI
    INTCONbits.GIE=1;//INT GENERALE
    INTCONbits.PEIE=1;//INT PERIFERICE

    ////////IOCB/////////////
    INTCONbits.RBIE=0;//IOC INT
    INTCON2bits.RBIP=0;//IOCB HIGH INT PRIORITY
    cor=PORTB;
    INTCONbits.RBIF=0;//IOCB FLAG CLEAR

    IOCBbits.IOCB4=1;//RB4==IOCB
    IOCBbits.IOCB5=1;//RB5==IOCB
    IOCBbits.IOCB6=1;//RB6==IOCB
    IOCBbits.IOCB7=0;//RB7==IOCB
/////////////////////////////////////////////////
    INTCON2bits.NOT_RBPU=1;// FARA PULL UP


    /////////////INT0/1/2
    INTCON2bits.INTEDG0=1;//RISING EDGE
    INTCON2bits.INTEDG1=1;
    INTCON2bits.INTEDG2=1;

    INTCONbits.INT0IE=0;
    INTCON3bits.INT1IE=0;
    INTCON3bits.INT2IE=0;

    INTCONbits.INT0IF=0;
    INTCON3bits.INT1IF=0;
    INTCON3bits.INT2IF=0;
//
//    TRISBbits.TRISB0=1;
//    TRISBbits.TRISB1=1;
//    TRISBbits.TRISB2=1;
//    //////////////////////////////


    /////////////////INT SERIAL///////////
    PIE1bits.RC1IE=0;
 //   PIR1bits.RC1IF=0;

    
    
    
}






