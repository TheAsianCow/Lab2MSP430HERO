/**************   ECE2049 LAB 2   ******************/
/**************    MSP430 HERO    ******************/
/**************  BY JEFFREY HUANG ******************/
/************** AND MICHAEL MCCUE ******************/
/***************************************************/

#include <msp430.h>
#include "peripherals.h"
#include <stdlib.h>
#include <stdio.h>



void main(void){
    WDTCTL = WDTPW | WDTHOLD;    // Stop watchdog timer. Always need to stop this!!
                                 // You can then configure it properly, if desired
    initLeds();
    configDisplay();
    configKeypad();

    //note will be stored in a struct, which will have pitch, duration, and LED
    //song will be stored in an array of structs
    //length of song will depend on what song we choose/how we compose it
    //the amount of memory taken up by the song will be # of notes * sizeof(struct note)

}
