//Created by: C2C Payden W. McBee
//Created on: 21 Oct 2013
//Last Revised: 21 October 2013
//Purpose: Displays a message on the LCD, implemented with C code

#include <msp430.h> 
//#include  <.cdecls> //these give me errors
//#include <C,LIST>
#include "lcd.h"
/*
 * main.c
 */
 char * firstMessage="ECE382 is my favorite class!#";
void main(void) {
    WDTCTL = WDTPW | WDTHOLD;	// Stop watchdog timer
    INITSPI();
    LCDINIT();
    LCDCLR();
    //writeString(firstMessage);
    scrollString(firstMessage,firstMessage);
    while(1) {} //trap CPU
}
