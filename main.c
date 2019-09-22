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

    WDTCTL = WDTPW | WDTHOLD;
    // enable interrupt
    _BIS_SR(GIE);
    // For Loops use:
    // CLK_SPEED = 32768
    // SONG_BPM = 75
    // SONG_LENGTH = 54

    // Song
//    struct Note hotel_cali[] = {
//                                octaveUp(D6), octaveUp(B6), octaveUp(Fs6), // 15 // 54 total Notes
//                                octaveUp(D6), octaveUp(B6), octaveUp(Fs6),
//                                octaveUp(D6), octaveUp(B6), octaveUp(Fs6),
//                                octaveUp(D6), octaveUp(B6), octaveUp(Fs6),
//                                octaveUp(D6), octaveUp(B6), octaveUp(Fs8),
//
//                                octaveUp(Cs6), octaveUp(As6), octaveUp(Fs6), //8
//                                octaveUp(Cs6), octaveUp(As6), octaveUp(Fs6),
//                                octaveUp(Cs6), octaveUp(As6),
//
//                                rest6, rest6, rest6, rest8, // 4
//
//                                octaveUp(Cs6), octaveUp(A6), octaveUp(E6), // 15
//                                octaveUp(Cs6), octaveUp(A6), octaveUp(E6),
//                                octaveUp(Cs6), octaveUp(A6), octaveUp(E6),
//                                octaveUp(Cs6), octaveUp(A6), octaveUp(E6),
//                                octaveUp(Cs6), octaveUp(A6), octaveUp(E8),
//
//                                octaveUp(B6), octaveUp(Gs6), octaveUp(E6), // 8
//                                octaveUp(B6), octaveUp(Gs6), octaveUp(E6),
//                                octaveUp(B6), octaveUp(Gs6),
//
//                                rest6, rest6, rest6, rest8 // 4
//    };


    // Notes
//    const struct Note A4 = {440, 4};
//    const struct Note A8 = {440, 8};
    const struct Note A6 = {440, 16, BIT0};

//    const struct Note As4 = {466, 4};
//    const struct Note As8 = {466, 8};
    const struct Note As6 = {466, 16, BIT1};

//    const struct Note B4 = {494, 4};
//    const struct Note B8 = {494, 8};
    const struct Note B6 = {494, 16, BIT2};

//    const struct Note C4 = {523, 4};
//    const struct Note C8 = {523, 8};
//    const struct Note C6 = {523, 16};

//    const struct Note Cs4 = {554, 4};
//    const struct Note Cs8 = {554, 8};
    const struct Note Cs6 = {554, 16, BIT2};

//    const struct Note D4 = {587, 4};
//    const struct Note D8 = {587, 8};
    const struct Note D6 = {587, 16, BIT0};

//    const struct Note Ds4 = {622, 4};
//    const struct Note Ds8 = {622, 8};
//    const struct Note Ds6 = {622, 16};

//    const struct Note E4 = {659, 4};
    const struct Note E8 = {659, 8, BIT1};
    const struct Note E6 = {659, 16, BIT1};

//    const struct Note F4 = {698, 4};
//    const struct Note F8 = {698, 8};
//    const struct Note F6 = {698, 16};

//    const struct Note Fs4 = {740, 4};
    const struct Note Fs8 = {740, 8, BIT3};
    const struct Note Fs6 = {740, 16, BIT3};

//    const struct Note G4 = {784, 4};
//    const struct Note G8 = {784, 8};
//    const struct Note G6 = {784, 16};

//    const struct Note Gs4 = {831, 4};
//    const struct Note Gs8 = {831, 8};
    const struct Note Gs6 = {831, 16, BIT3};

//    const struct Note rest4 = {0, 4};
    const struct Note rest8 = {0, 8, 0};
    const struct Note rest6 = {0, 16, 0};

    hotel_cali[0] = D6;
    hotel_cali[1] = B6;
    hotel_cali[2] = Fs6;

    hotel_cali[3] = D6;
    hotel_cali[4] = B6;
    hotel_cali[5] = Fs6;

    hotel_cali[6] = D6;
    hotel_cali[7] = B6;
    hotel_cali[8] = Fs6;

    hotel_cali[9] = D6;
    hotel_cali[10] = B6;
    hotel_cali[11] = Fs6;

    hotel_cali[12] = D6;
    hotel_cali[13] = B6;
    hotel_cali[14] = Fs8;

    hotel_cali[15] = Cs6;
    hotel_cali[16] = As6;
    hotel_cali[17] = Fs6;

    hotel_cali[18] = Cs6;
    hotel_cali[19] = As6;
    hotel_cali[20] = Fs6;

    hotel_cali[21] = Cs6;
    hotel_cali[22] = As6;

    hotel_cali[23] = rest6;
    hotel_cali[24] = rest6;
    hotel_cali[25] = rest6;
    hotel_cali[26] = rest8;

    hotel_cali[27] = Cs6;
    hotel_cali[28] = A6;
    hotel_cali[29] = E6;

    hotel_cali[30] = Cs6;
    hotel_cali[31] = A6;
    hotel_cali[32] = E6;

    hotel_cali[33] = Cs6;
    hotel_cali[34] = A6;
    hotel_cali[35] = E6;

    hotel_cali[36] = Cs6;
    hotel_cali[37] = A6;
    hotel_cali[38] = E6;

    hotel_cali[39] = Cs6;
    hotel_cali[40] = A6;
    hotel_cali[41] = E8;

    hotel_cali[42] = B6;
    hotel_cali[43] = Gs6;
    hotel_cali[44] = E6;

    hotel_cali[45] = B6;
    hotel_cali[46] = Gs6;
    hotel_cali[47] = E6;

    hotel_cali[48] = B6;
    hotel_cali[49] = Gs6;

    hotel_cali[50] = rest6;
    hotel_cali[51] = rest6;
    hotel_cali[52] = rest6;
    hotel_cali[53] = rest8;

    initLeds();
    configDisplay();
    configKeypad();
    configBtn();
    initTimer();

    unsigned char currKey, currBtn;
    unsigned int j = 0;
    gameStart = 0;
    countdown = 0;
    starting = 4;
    timerCount = 0;
    hit = 0;
    misses = 10;
    for(j = 0; j < 10; j++) health[j] = 1;
    won = 0;

    while (1){
        currKey = getKey();
        currBtn = getBtn();

        if (!gameStart && currKey == '*')countdown = 1;

        if (countdown == 1){
//            for (i = 0; i <= 20000; i++){
//                if (i == 0){
//                    Graphics_clearDisplay(&g_sContext);
//                    Graphics_drawStringCentered(&g_sContext, "3",AUTO_STRING_LENGTH,48, 48,TRANSPARENT_TEXT);
//                    Graphics_flushBuffer(&g_sContext);
//                    setUserLED(1);
//                }
//                if (i == 8000){
//                    Graphics_clearDisplay(&g_sContext);
//                    Graphics_drawStringCentered(&g_sContext, "2",AUTO_STRING_LENGTH,48, 48,TRANSPARENT_TEXT);
//                    Graphics_flushBuffer(&g_sContext);
//                    setUserLED(2);
//                }
//                if (i == 16000){
//                    Graphics_clearDisplay(&g_sContext);
//                    Graphics_drawStringCentered(&g_sContext, "1",AUTO_STRING_LENGTH,48, 48,TRANSPARENT_TEXT);
//                    Graphics_flushBuffer(&g_sContext);
//                    setUserLED(1);
//                }
//                if (i == 20000){
//                    Graphics_clearDisplay(&g_sContext);
//                    Graphics_drawStringCentered(&g_sContext, "START",AUTO_STRING_LENGTH,48, 48,TRANSPARENT_TEXT);
//                    Graphics_flushBuffer(&g_sContext);
//                    setUserLED(3);
//                    j = 16000;
//                    while(j)j--;
//                    setUserLED(0);
//                }
//            }
//
//            countdown = 0;
//            gameStart = 1;
//
//            Graphics_clearDisplay(&g_sContext);
//            Graphics_drawStringCentered(&g_sContext, "Playing game", AUTO_STRING_LENGTH, 48, 48, TRANSPARENT_TEXT);
//            Graphics_flushBuffer(&g_sContext);

        }
        else if(gameStart==1&&currKey=='#'){
            reset();
        }
        else if(gameStart==1){
            if(hotel_cali[note].led==BIT0 && currBtn==BIT4){
                hit = 1;
                Graphics_clearDisplay(&g_sContext);
                Graphics_drawStringCentered(&g_sContext, "HIT", AUTO_STRING_LENGTH, 48,48, TRANSPARENT_TEXT);
                drawHealth();
            }
            else if(hotel_cali[note].led==BIT1 && currBtn==BIT2){
                hit = 1;
                Graphics_clearDisplay(&g_sContext);
                Graphics_drawStringCentered(&g_sContext, "HIT", AUTO_STRING_LENGTH, 48,48, TRANSPARENT_TEXT);
                drawHealth();
            }
            else if(hotel_cali[note].led==BIT2 && currBtn==BIT6){
                hit = 1;
                Graphics_clearDisplay(&g_sContext);
                Graphics_drawStringCentered(&g_sContext, "HIT", AUTO_STRING_LENGTH, 48,48, TRANSPARENT_TEXT);
                drawHealth();
            }
            else if(hotel_cali[note].led==BIT3 && currBtn==BIT0){
                hit = 1;
                Graphics_clearDisplay(&g_sContext);
                Graphics_drawStringCentered(&g_sContext, "HIT", AUTO_STRING_LENGTH, 48,48, TRANSPARENT_TEXT);
                drawHealth();
            }
            else if(misses==0){
                Graphics_clearDisplay(&g_sContext);
                Graphics_drawStringCentered(&g_sContext, "GAMEOVER", AUTO_STRING_LENGTH, 48,48, TRANSPARENT_TEXT);
                Graphics_flushBuffer(&g_sContext);
                reset();
                j = 32000;
                while(j)j--;
            }
            Graphics_flushBuffer(&g_sContext);

        }
        else if(gameStart==2){
            Graphics_clearDisplay(&g_sContext);
            for(j = 0; j < 10; j++) health[j] = 1;
            misses = 10;
            gameStart = 0;

        }
        else{
            Graphics_drawStringCentered(&g_sContext, "MSP430 HERO", AUTO_STRING_LENGTH, 48, 48, TRANSPARENT_TEXT);
            Graphics_flushBuffer(&g_sContext);
        }

    }
}


