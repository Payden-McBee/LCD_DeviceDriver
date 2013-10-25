/*
 * clockFrequency.c
 *
 *  Created on: Oct 24, 2013
 *      Author: C15Payden.McBee
 */
#include "clockFrequency.h"
#include <msp430.h>
/*---------------------------------------------------
;Function Name: RunAt1Hz
;Author: C2C Payden McBee, USAF
;Function: sets the clock to run at 1Hz
;Inputs:none
;Outputs: none
;Registers destroyed: none
;---------------------------------------------------*/
void RunAt1Hz()
{
				   //Set DCO to 1 MHz:
                  BCSCTL1=0x00;
				  DCOCTL=0x00; //Select lowest DCOx and MODx settings
				  BCSCTL1=CALBC1_1MHZ;   //Set range
				  DCOCTL=CALDCO_1MHZ;   //Set DCO step + modulation
}

/*---------------------------------------------------
;Function Name: RunAt8Hz
;Author: C2C Payden McBee, USAF
;Function: sets the clock to run at 8Hz
;Inputs:none
;Outputs: none
;Registers destroyed: none
;---------------------------------------------------*/
void RunAt8Hz()
{
				   //Set DCO to 1 MHz:
                  BCSCTL1=0x00;
				  DCOCTL=0x00; //Select lowest DCOx and MODx settings
				  BCSCTL1=CALBC1_8MHZ;   //Set range
				  DCOCTL=CALDCO_8MHZ;   //Set DCO step + modulation
}

/*---------------------------------------------------
;Function Name: RunAt12Hz
;Author: C2C Payden McBee, USAF
;Function: sets the clock to run at 12Hz
;Inputs:none
;Outputs: none
;Registers destroyed: none
;---------------------------------------------------*/
void RunAt12Hz()
{
				   //Set DCO to 1 MHz:
                  BCSCTL1=0x00;
				  DCOCTL=0x00; //Select lowest DCOx and MODx settings
				  BCSCTL1=CALBC1_12MHZ;   //Set range
				  DCOCTL=CALDCO_12MHZ;   //Set DCO step + modulation
}

/*---------------------------------------------------
;Function Name: RunAt16Hz
;Author: C2C Payden McBee, USAF
;Function: sets the clock to run at 16Hz
;Inputs:none
;Outputs: none
;Registers destroyed: none
;---------------------------------------------------*/
void RunAt16Hz()
{
				   //Set DCO to 1 MHz:
                  BCSCTL1=0x00;
				  DCOCTL=0x00; //Select lowest DCOx and MODx settings
				  BCSCTL1=CALBC1_16MHZ;   //Set range
				  DCOCTL=CALDCO_16MHZ;   //Set DCO step + modulation
}
