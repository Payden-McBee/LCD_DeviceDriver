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
	  	  	  	  	  SET_SS_HI();

	                  LCDCON=0;                                        // initialize control bits

	                  LCDDATA=3;                                       // function set
	                  LCDWRT4();
	                  LCDDELAY2();

	                  LCDDATA=3;                        //function set
	                  LCDWRT4();
	                  LCDDELAY1();

	                  LCDDATA=3;                         // function set
	                  LCDWRT4();
	                  LCDDELAY1();

	                  LCDDATA=2;                        //set 4-bit interface
	                  LCDWRT4();
	                  LCDDELAY1();

	                  LCDSEND=0x28;                    // 2 lines, 5x7
	                  LCDWRT8();
	                  LCDDELAY2();

	                  LCDSEND=0x0C;                   // display on, cursor, blink off
	                  LCDWRT8();
	                  LCDDELAY2();

	                  LCDSEND=1;             //clear, cursor home
	                  LCDWRT8();
	                  LCDDELAY1();

	                  LCDSEND=6;                      //cursor increment, shift off
	                  LCDWRT8();
	                  LCDDELAY2();

	                  LCDSEND=1;            //clear, cursor home
	                  LCDWRT8();
	                  LCDDELAY2();

	                  LCDSEND=2;                   //cursor home
	                  LCDWRT8();
	                  LCDDELAY2();

	                  mov.b   #0, r5                              //clear register
	                  SPISEND();
	                  LCDDELAY1();
}
void SET_SS_HI(){

              //your set SS high code goes here

				P1OUT|=BIT3;

}

/*Subroutine Name: SET_SS_LO
;Author: C2C Payden McBee, USAF
;Function:  Sets your slave select to low (enabled)
;Inputs:none
;Outputs: none
;Registers destroyed: none
;Subroutines used:none
*/
void SET_SS_LO(){

                  //your set SS low code goes here
				P1OUT&=~BIT3;

}


/*---------------------------------------------------
;Subroutine Name: LCDDELAY1
;Author: C2C Payden McBee, USAF
;Function: Implements a 40.5 microsecond delay
;Inputs:delay1, a constant number to iterate the loop
;Outputs: none
;Registers destroyed: none
;Subroutines used:none
;---------------------------------------------------*/
void LCDDELAY1(){

                  ; your 40.5 microsecond delay
                  push r5
                  mov.w #delay1, r5	//nine is used to make the delay iterate 27 times
                  nop
delay			  dec r5
				  jnz delay
				  pop r5
}


/*;---------------------------------------------------
;Subroutine Name: LCDDELAY1
;Author: C2C Payden McBee, USAF
;Function: Implements a 1.65 millisecond delay
;Inputs:delay1, a constant number to iterate the loop
;Outputs: none
;Registers destroyed: none
;Subroutines used:none
;---------------------------------------------------*/
void LCDDELAY2(){

                 // your 1.65 millisecond delay code goes here
 				  push r5
                  mov.w #delay2, r5	;hex 23F is used to make the delay iterate 575 decimal times
                  nop
delay2			  dec r5
				  jnz delay
				  pop r5
}

/*---------------------------------------------------
; Subroutine Name: LCDCLR
; Author: Capt Todd Branchflower, USAF
; Function: Clears LCD, sets cursor to home
; Inputs: none
; Outputs: none
; Registers destroyed: none
; Subroutines used: LCDWRT8, LCDDELAY1, LCDDELAY2
;---------------------------------------------------*/
void LCDCLR(){
                  mov.b   #0, &LCDCON                                            // clear RS
                  mov.b   #1, &LCDSEND                                           // send clear
                  call    #LCDWRT8
                  call    #LCDDELAY1
                  mov.b   #0x40, &LCDCON                                         // set RS
                  call    #LCDDELAY2
}

/*---------------------------------------------------
; Subroutine Name: LCDWRT8
; Author: C2C Payden McBee
; Function: Send full byte to LCD
; Inputs: LCDSEND
; Outputs: none
; Registers destroyed: none
; Subroutines used: LCDWRT4
; Documentation: The code was created by
;  Capt Branchflower in assembly, I converted it to C.
;---------------------------------------------------*/
void LCDWRT8(){
                  push.w  r5

                  mov.b   &LCDSEND, r5                                          // load full byte
                  and.b   #0xf0, r5                                             // shift in four zeros on the left
                  rrc.b   r5
                  rrc.b   r5
                  rrc.b   r5
                  rrc.b   r5
                  mov.b   r5, &LCDDATA                                          // store send data
                  call    #LCDWRT4                                              // write upper nibble
                  mov.b   &LCDSEND, r5                                          // load full byte
                  and.b   #0x0f, r5                                             // clear upper nibble
                  mov.b   r5, &LCDDATA
                  call    #LCDWRT4                                              //write lower nibble

                  pop.w   r5

}
/*---------------------------------------------------
; Subroutine Name: LCDWRT4
; Author: C2C Payden McBee
; Function: Send 4 bits of data to LCD via SPI.
; sets upper four bits to match LCDCON.
; Inputs: LCDCON, LCDDATA
; Outputs: none
; Registers destroyed: none
; Subroutines used: LCDDELAY1
; Documentation: The code was created by
;  Capt Branchflower in assembly, I converted it to C.
;---------------------------------------------------*/
void LCDWRT4(){

                  int holdLCDDATA;
                  holdLCDDATA=LCDDATA;					 //load data to send
                  holdLCDDATA&=0x0f;                     //ensure upper half of byte is clear
                  holdLCDDATA|=LCDCON;                   //set LCD control nibble
                  holdLCDDATA&=0x7f;        			 //set E low
                  SPISEND(holdLCDDATA);
                  LCDDELAY1();
                  holdLCDDATA|=0x80;	                 //set E high
                  SPISEND(holdLCDDATA);
                  LCDDELAY1();
                  holdLCDDATA&=0x7f;                     //set E low
                  SPISEND(holdLCDDATA);
                  LCDDELAY1();

}

/*---------------------------------------------------
; Subroutine Name: SPISEND
; Author: C2C Payden McBee
; Function: Sends contents of r5 to SPI.
; Waits for Rx flag, clears by reading.
; Sets slave select accordingly.
; Outputs: none
; Registers destroyed: none
; Subroutines used: LCDWRT8, LCDDELAY1, LCDDELAY2
; Documentation: The code was created by
;  Capt Branchflower in assembly, I converted it to C.
;---------------------------------------------------*/

void SPISEND(int holdLCDDATA){

                  SET_SS_LO();
                  UCB0TXBUF=holdLCDDATA;       //I'm assuming that this variable is only 2 bytes long   //transfer byte

                  while (UCB0RXIFG==IFG2) {			 //wait for transfer completion
                     holdLCDDATA=holdLCDDATA; //do nothing
                  }
                  SET_SS_HI();

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


