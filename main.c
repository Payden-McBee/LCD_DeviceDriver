//Created by: C2C Payden W. McBee
//Created on: 21 Oct 2013
//Last Revised: 21 October 2013
//Purpose: Displays a message on the LCD, implemented with C code

#include <msp430.h> 
//#include  <.cdecls> //these give me errors
//#include <C,LIST>
#include "lcd.h"
#include "buttons/button.h"
#include "clockFrequency.h"
/*
 * main.c
 */
 char firstMessage[]="ECE382 is my favorite class! ";
 char * secondMessage; //this will be the chosen message
 char topLine[]="Message?";
 char bottomLine[]="Press123";
 char msg1[]="Message 1 is displaying";
 char msg2[]="Message 2 is displaying";
 char msg3[]="Message 3 is displaying";

void main(void) {
    WDTCTL = WDTPW | WDTHOLD;	// Stop watchdog timer
    void RunAt8Hz();
    INITSPI();
    LCDINIT();
    LCDCLR();
    writeString(topLine);
    cursorToLineTwo();
    writeString(bottomLine);

    configureP1PinAsButton(BIT1|BIT2|BIT3);         // configure pins 1, 2, and 3 as buttons

     P1DIR |= BIT0|BIT6;                             // set launchpad LEDs to output


         char buttons[] = {BIT1, BIT2, BIT3};
         char pressedButton = pollP1Buttons(buttons, 3);

         switch (pressedButton)
         {
             case BIT1:
                 secondMessage = msg1;
                 break;
             case BIT2:
                 secondMessage = msg2;
                 break;
             case BIT3:
            	 secondMessage = msg3;
                 // toggle LEDs and wait for release
                 P1OUT ^= BIT0|BIT6;
                 waitForP1ButtonRelease(BIT3);
                 break;
         }


    scrollString(firstMessage,secondMessage);

    while(1) {} //trap CPU
}
