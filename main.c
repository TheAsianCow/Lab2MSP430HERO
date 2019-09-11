/**************   ECE2049 LAB 2   ******************/
/**************    MSP430 HERO    ******************/
/**************  BY JEFFREY HUANG ******************/
/************** AND MICHAEL MCCUE ******************/
/***************************************************/

#include <msp430.h>
#include "peripherals.h"
#include <stdlib.h>
#include <stdio.h>

struct note{int pitch, duration;char led;};
struct note song[28];

void main(void){
    WDTCTL = WDTPW | WDTHOLD;    // Stop watchdog timer. Always need to stop this!!
                                 // You can then configure it properly, if desired
    initLeds();
    configDisplay();
    configKeypad();
    configBtn();

    unsigned char currKey;
    unsigned int gameStart = 0, countDown = 0, i = 0, j = 0;

    //initialize the song

    while (1){
        currKey = getKey();

        if (currKey == '*'){
            gameStart = 1;
            countDown = 1;
        };

        if (countDown == 1){
            for (i = 0; i <= 20000; i++){
                if (i == 0){
                    Graphics_clearDisplay(&g_sContext);
                    Graphics_drawStringCentered(&g_sContext, "3",AUTO_STRING_LENGTH,48, 48,TRANSPARENT_TEXT);
                    Graphics_flushBuffer(&g_sContext);
                    setUserLED(1);
                }
                if (i == 8000){
                    Graphics_clearDisplay(&g_sContext);
                    Graphics_drawStringCentered(&g_sContext, "2",AUTO_STRING_LENGTH,48, 48,TRANSPARENT_TEXT);
                    Graphics_flushBuffer(&g_sContext);
                    setUserLED(2);
                }
                if (i == 16000){
                    Graphics_clearDisplay(&g_sContext);
                    Graphics_drawStringCentered(&g_sContext, "1",AUTO_STRING_LENGTH,48, 48,TRANSPARENT_TEXT);
                    Graphics_flushBuffer(&g_sContext);
                    setUserLED(1);
                }
                if (i == 20000){
                    Graphics_clearDisplay(&g_sContext);
                    Graphics_drawStringCentered(&g_sContext, "START",AUTO_STRING_LENGTH,48, 48,TRANSPARENT_TEXT);
                    Graphics_flushBuffer(&g_sContext);
                    setUserLED(3);
                    j = 16000;
                    while(j)j--;
                    setUserLED(0);
                }
            }

            countDown = 0;
            Graphics_clearDisplay(&g_sContext);
            Graphics_drawStringCentered(&g_sContext, "Playing game", AUTO_STRING_LENGTH, 48, 48, TRANSPARENT_TEXT);
            Graphics_flushBuffer(&g_sContext);

        }
        else if(gameStart){

        }
        else{
            Graphics_drawStringCentered(&g_sContext, "MSP430 HERO", AUTO_STRING_LENGTH, 48, 48, TRANSPARENT_TEXT);
            Graphics_flushBuffer(&g_sContext);
        }

    }
}
