/**************   ECE2049 LAB 2   ******************/
/**************    MSP430 HERO    ******************/
/**************  BY JEFFREY HUANG ******************/
/************** AND MICHAEL MCCUE ******************/
/***************************************************/

#include <msp430.h>
#include "peripherals.h"
#include <stdlib.h>
#include <stdio.h>

// Notes
struct Note A4 = {440, 4};
struct Note A8 = {440, 8};
struct Note A6 = {440, 16};

struct Note As4 = {466, 4};
struct Note As8 = {466, 8};
struct Note As6 = {466, 16};

struct Note B4 = {494, 4};
struct Note B8 = {494, 8};
struct Note B6 = {494, 16};

struct Note C4 = {523, 4};
struct Note C8 = {523, 8};
struct Note C6 = {523, 16};

struct Note Cs4 = {554, 4};
struct Note Cs8 = {554, 8};
struct Note Cs6 = {554, 16};

struct Note D4 = {587, 4};
struct Note D8 = {587, 8};
struct Note D6 = {587, 16};

struct Note Ds4 = {622, 4};
struct Note Ds8 = {622, 8};
struct Note Ds6 = {622, 16};

struct Note E4 = {659, 4};
struct Note E8 = {659, 8};
struct Note E6 = {659, 16};

struct Note F4 = {698, 4};
struct Note F8 = {698, 8};
struct Note F6 = {698, 16};

struct Note Fs4 = {740, 4};
struct Note Fs8 = {740, 8};
struct Note Fs6 = {740, 16};

struct Note G4 = {784, 4};
struct Note G8 = {784, 8};
struct Note G6 = {784, 16};

struct Note Gs4 = {831, 4};
struct Note Gs8 = {831, 8};
struct Note Gs6 = {831, 16};

struct Note rest4 = {0, 4};
struct Note rest8 = {0, 8};
struct Note rest6 = {0, 16};

void main(void){
    WDTCTL = WDTPW | WDTHOLD;
    // enable interrupt
    _BIS_SR(GIE);
    // For Loops use:
    // CLK_SPEED = 32768
    // SONG_BPM = 74
    // SONG_LENGTH = 54

    // Song
    struct Note hotel_cali[] = {
                                octaveUp(D6), octaveUp(B6), octaveUp(Fs6), // 15 // 54 total Notes
                                octaveUp(D6), octaveUp(B6), octaveUp(Fs6),
                                octaveUp(D6), octaveUp(B6), octaveUp(Fs6),
                                octaveUp(D6), octaveUp(B6), octaveUp(Fs6),
                                octaveUp(D6), octaveUp(B6), octaveUp(Fs8),

                                octaveUp(Cs6), octaveUp(As6), octaveUp(Fs6), //8
                                octaveUp(Cs6), octaveUp(As6), octaveUp(Fs6),
                                octaveUp(Cs6), octaveUp(As6),

                                rest6, rest6, rest6, rest8, // 4

                                octaveUp(Cs6), octaveUp(A6), octaveUp(E6), // 15
                                octaveUp(Cs6), octaveUp(A6), octaveUp(E6),
                                octaveUp(Cs6), octaveUp(A6), octaveUp(E6),
                                octaveUp(Cs6), octaveUp(A6), octaveUp(E6),
                                octaveUp(Cs6), octaveUp(A6), octaveUp(E8),

                                octaveUp(B6), octaveUp(Gs6), octaveUp(E6), // 8
                                octaveUp(B6), octaveUp(Gs6), octaveUp(E6),
                                octaveUp(B6), octaveUp(Gs6),

                                rest6, rest6, rest6, rest8 // 4
    };

    initLeds();
    configDisplay();
    configKeypad();
    configBtn();
    initTimer();

    unsigned char currKey;
    unsigned int i = 0, j = 0;
    gameStart = 0;
    countdown = 0;

    //initialize the song

    while (1){
        currKey = getKey();

        if (!gameStart && currKey == '*'){
            gameStart = 1;
            countdown = 1;
        };

        if (countdown == 1){
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

            countdown = 0;
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


