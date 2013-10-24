/*
 * lcd.h
 *
 *  Created on: Oct 21, 2013
 *      Author: C15Payden.McBee
 *      Description: Library to interact with the Geek Box LCD.
 *      Documentation: Some of these function names were taken from Capt Branchflower's code.
 */

#ifndef LCD_H_
#define LCD_H_

//void runAt1Hz(); do this for A functionality
#define RS_MASK 0x40

void INITSPI();
void LCDINIT();
void LCDCLR();

// void INITBUTTONS();
//void determineMsg();
//I'll implement this when I do B functionality
//let's get required working first

void cursorToLineTwo();
//add a comment
void cursorToLineOne();

void writeChar(char asciiChar);

void writeString(char * string);

void scrollString(char * string1, char * string2);

// Here are some helper functions from my LCD.c
// I don't expose these in my header, but may be helpful to you.

void writeDataByte(char dataByte);
void writeCommandNibble(char commandNibble);
void writeCommandByte(char commandByte);


#endif /* LCD_H_ */
