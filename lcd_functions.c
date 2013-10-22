/*
 * lcd_functions.c
 *
 *  Created on: Oct 21, 2013
 *      Author: C15Payden.McBee
 */
#include "lcd.h"

void INITSPI(){
	  //your SPI initialization code goes here
		// |= bis.s
		// &= ~  bis.c
						UCB0CTL1|=UCSWRST;

					    UCB0CTL0|=UCCKPH; 	//The LCD driver chip expects data to be read on the first clock edge and changed on the second.

						UCB0CTL1&= ~UCCKPL; 	//The LCD driver chip expects the clock should be low when not trasnmitting.

	       			    UCB0CTL0|=UCMSB|UCMST|UCSYNC;     // don't forget UCSYNC!

	                    UCB0CTL1|=UCSSEL1;             // select a clock to use!

	                    UCB0STAT|=UCLISTEN;   //enables internal loopback

	                    P1SEL|=BIT5;   //make UCA0CLK available on P1.4
	                    P1SEL2|=BIT5;

	                    P1SEL|=BIT7;          // make UCA0SSIMO available on P1.2
	                    P1SEL2|=BIT7;

	       			    P1SEL|=BIT6;          //make UCA0SSOMI available on P1.1
	       				P1SEL2|=BIT6;

	      				UCB0CTL1 &= ~UCSWRST;     //enable subsystem

	      			    P1DIR|= BIT3;

}
void LCDINIT(){

}
void LCDCLR(){

}

// void INITBUTTONS();
//void determineMsg();
//I'll implement this when I do B functionality
//let's get required working first

void cursorToLineTwo(){

}

void cursorToLineOne(){

}

void writeChar(char asciiChar){

}

void writeString(char * string){

}

void scrollString(char * string1, char * string2){

}

// Here are some helper functions from my LCD.c
// I don't expose these in my header, but may be helpful to you.

void writeDataByte(char dataByte){

}
void writeCommandNibble(char commandNibble){

}
void writeCommandByte(char commandByte){

}


