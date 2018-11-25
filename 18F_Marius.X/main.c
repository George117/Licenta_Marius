/*
 * File:   main.c
 * Author: georg
 *
 * Created on October 27, 2018, 10:59 AM
 */

#define _XTAL_FREQ 16000000
#include <xc.h>
#include <stdio.h>
#include "bit_settings.h"
#include "config.h"
#include "i2c_display.h"
#define Trigger_Left LATDbits.LATD7
#define Trigger_Center LATDbits.LATD6
#define Trigger_Right LATDbits.LATD5

unsigned int delay,distanta_stanga, distanta_fata, distanta_dreapta, cor,a,TMR, contor, cnt,start,vit_norm,vit_offset,corectie_mst,corectie_mdr_dreapta;
signed int diff_centru;
unsigned long timp_us = 0;

int buffer[4];

void get_distance();

void main(void) {
    config();
    
    while(1)
    {
       // Lcd_Clear();
        get_distance();
        
        
        
        
        
        Lcd_Set_Cursor(1,1);
        Lcd_Write_String("S=");
        sprintf(buffer, "%03u", distanta_stanga);
        Lcd_Write_String(buffer);
        Lcd_Write_String("cm");
        
        Lcd_Write_String("  ");
        
        Lcd_Write_String("D=");
        sprintf(buffer, "%03u", distanta_dreapta);
        Lcd_Write_String(buffer);
        Lcd_Write_String("cm");
        
        Lcd_Set_Cursor(2,6);
        Lcd_Write_String("F=");
        sprintf(buffer, "%03u", distanta_fata);
        Lcd_Write_String(buffer);
        Lcd_Write_String("cm");
        
        
        __delay_ms(20);
    }
    
    return;
}


void get_distance()
{
           
    INTCONbits.RBIE=1;//IOC INT
    __delay_ms(20);
    contor=1;
    Trigger_Right=1;
    __delay_us(10);
    Trigger_Right=0;
    __delay_us(10);


    __delay_ms(20);
    contor=2;
    Trigger_Center=1;
    __delay_us(10);
    Trigger_Center=0;      

    __delay_ms(20);
    contor=3;
    Trigger_Left=1;
    __delay_us(10);
    Trigger_Left=0;
    __delay_us(10);
             
}



void interrupt  ISR()
{
       INTCONbits.PEIE=0;//INT PERIFERICE

 ///////////////////SENZOR DREAPTA////////////////////////////
      if(INTCONbits.RBIF==1 && contor==1 )//dreapta
      {

        
       cor=PORTB;//iocb corectie
    while(!PORTBbits.RB4);//Waiting for Echo
    {
        TMR1H=TMR1L=0X00;
        T1CONbits.TMR1ON=1;//Timer Starts
    }
   
    while(PORTBbits.RB4);               //Waiting for Echo goes LOW
    {
    T1CONbits.TMR1ON=0;               //Timer Stops

      TMR = (unsigned int) TMR1H << 8;
      TMR = TMR + TMR1L;

      timp_us = (TMR/10) * 20;  // Duration Formula = TMR * 0.2us(Clock speed) * 4 (Timer Prescale)
      distanta_dreapta = (timp_us / 58)+1 ;   // Refer HC-SR04 Datasheetdu
     

    }
    
      }
///////////////////////////////////////////////////////////////


//////////////////SENZOR FATA/////////////////////////////////
  
      if(INTCONbits.RBIF==1 && contor==2 )//fata
      {


       cor=PORTB;//iocb corectie
    while(!PORTBbits.RB5);//Waiting for Echo
    {
        TMR1H=TMR1L=0X00;
        T1CONbits.TMR1ON=1;//Timer Starts
    }

    while(PORTBbits.RB5);               //Waiting for Echo goes LOW
    {
    T1CONbits.TMR1ON=0;               //Timer Stops

      TMR = (unsigned int) TMR1H << 8;
      TMR = TMR + TMR1L;

      timp_us = (TMR/10) * 20;  // Duration Formula = TMR * 0.2us(Clock speed) * 4 (Timer Prescale)
      distanta_fata = (timp_us / 58)+1 ;   // Refer HC-SR04 Datasheetdu

    }

      }

 ///////////////////////////////////////////////

       //////////////////SENZOR STANGA/////////////////////////////////

      if(INTCONbits.RBIF==1 && contor==3 )//stanga
      {


       cor=PORTB;//iocb corectie
    while(!PORTBbits.RB6);//Waiting for Echo
    {
        TMR1H=TMR1L=0X00;
        T1CONbits.TMR1ON=1;//Timer Starts
    }

    while(PORTBbits.RB6);               //Waiting for Echo goes LOW
    {
    T1CONbits.TMR1ON=0;               //Timer Stops

      TMR = (unsigned int) TMR1H << 8;
      TMR = TMR + TMR1L;

      timp_us = (TMR/10) * 20;  // Duration Formula = TMR * 0.2us(Clock speed) * 4 (Timer Prescale)
      distanta_stanga = (timp_us / 58)+1 ;   // Refer HC-SR04 Datasheetdu
   

    }

      }

 ///////////////////////////////////////////////

        INTCONbits.RBIF=0;//IOCB FLAG CLEAR
        INTCONbits.PEIE=1;//INT PERIFERICE
}