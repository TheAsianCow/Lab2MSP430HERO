/**************  ECE2049 LAB 1 *********************/
/**************  BY JEFFREY HUANG ******************/
/**************  AND MICHAEL MCCUE *****************/
/***************************************************/

#include <msp430.h>
#include "peripherals.h"
#include <stdlib.h>
#include <stdio.h>

void drawScreen();
void clearBoard();

char gameBoard[8][5][2];

enum State{START, INPUT, DESCEND, ADVANCE, DEFAULT};

void main(void){
    WDTCTL = WDTPW | WDTHOLD;    // Stop watchdog timer. Always need to stop this!!
                                 // You can then configure it properly, if desired
    initLeds();
    configDisplay();
    configKeypad();

    unsigned char currKey = 0;
    unsigned long int loopCnt = 0, i = 0;
    unsigned int gameStart = 0, difficulty = 0, a = 0, aliens = 0, rows = 0;
    enum State s = DEFAULT;
    char level[10] = "LEVEL 1";
    //loopCnt counts the number of loops during the game, gameStart 0 to not start count, 1 to start counting during game
    //difficulty is used to calculate how fast the aliens descend

//    for(i = 0; i < 1; i++){
//        for(a = 0; a < 5; a++) {
//            gameBoard[i][a][0] = ((rand() % 6) + 0x30);
//            if(gameBoard[i][a][0] == '0') gameBoard[i][a][0] = ' ';
//            else aliens++;
//        }
//    }

    while(1){
        currKey = getKey();
        if(currKey == '*' && !gameStart) s = START;
        if(gameStart){
          if(currKey>=1&&currKey<=5) s = INPUT;
          if(loopCnt%(500-20*difficulty)==0) s = DESCEND;
          if(aliens==0&&rows==0) s = ADVANCE;
        }
        switch(s){
          case START:
            //start game countdown
            //only does something if gameStart !=0
            for(a = 0; a < 5; a++) {
                gameBoard[i][a][0] = ((rand() % 6) + 0x30);
                 if(gameBoard[i][a][0] == '0') gameBoard[i][a][0] = ' ';
                 else aliens++;
            }

            Graphics_clearDisplay(&g_sContext);
            Graphics_drawStringCentered(&g_sContext, level, AUTO_STRING_LENGTH, 48, 48, OPAQUE_TEXT);
            Graphics_flushBuffer(&g_sContext);
            i = 100000;
            while(i)i--;

            gameStart = 1;
            Graphics_clearDisplay(&g_sContext);
            Graphics_drawStringCentered(&g_sContext, "Starting in: ", AUTO_STRING_LENGTH, 48, 48, TRANSPARENT_TEXT);
            Graphics_flushBuffer(&g_sContext);
            i = 50000;
            while(i)i--;
            for(i = 0; i <= 20000; i++){
              if(i==0){
                Graphics_clearDisplay(&g_sContext);
                Graphics_drawStringCentered(&g_sContext, "3", AUTO_STRING_LENGTH, 48, 48, TRANSPARENT_TEXT);
                Graphics_flushBuffer(&g_sContext);
              }
              if(i==8000){
                Graphics_clearDisplay(&g_sContext);
                Graphics_drawStringCentered(&g_sContext, "2", AUTO_STRING_LENGTH, 48, 48, TRANSPARENT_TEXT);
                Graphics_flushBuffer(&g_sContext);
              }
              if(i==16000){
                Graphics_clearDisplay(&g_sContext);
                Graphics_drawStringCentered(&g_sContext, "1", AUTO_STRING_LENGTH, 48, 48, TRANSPARENT_TEXT);
                Graphics_flushBuffer(&g_sContext);
              }
              if(i==20000){
                Graphics_clearDisplay(&g_sContext);
                Graphics_drawStringCentered(&g_sContext, "START", AUTO_STRING_LENGTH, 48, 48, TRANSPARENT_TEXT);
                Graphics_flushBuffer(&g_sContext);
              }
            }
            drawScreen();
            s = INPUT;
            break;

          case INPUT:
            //checks for player input and kills aliens in lowest row if valid input 1-5
             for(i = 8; i > 0; i--){
               for(a = 0; a < 5; a++) {
                 if(currKey == gameBoard[i-1][a][0] && currKey!=0){
                     gameBoard[i-1][a][0] = ' ';
                     aliens--;
                     drawScreen();
                     i=1;
                     a=4;
                 }
               }
             }
            break;

          case DESCEND: //descends the alien and checks if gameOver
            for(i = 7; i > 0; i--) {
                for (a = 0; a < 5; a++) {
                    gameBoard[i][a][0] = gameBoard[i-1][a][0];
                    if(rows==0) gameBoard[i-1][a][0]=' ';
                }
            }

            if(rows){
                for(a = 0; a < 5; a++) {
                    gameBoard[0][a][0] = ((rand() % 6) + 0x30);
                    if(gameBoard[0][a][0] == '0') gameBoard[0][a][0] = ' ';
                    else aliens++;
                }
                rows--;
            }
            //checks to see if the next descent ends the game
            for(a = 0; a < 5; a++){
                if(gameBoard[5][a][0]>='1'&&gameBoard[5][a][0]<='5'){
                    drawScreen();
                    i = 20000;
                    while(i)i--;
                    BuzzerOn();
                    Graphics_clearDisplay(&g_sContext);
                    Graphics_drawStringCentered(&g_sContext, "GAME OVER", AUTO_STRING_LENGTH, 48, 48, TRANSPARENT_TEXT);
                    Graphics_flushBuffer(&g_sContext);
                    s = DEFAULT;
                    loopCnt = 0;
                    gameStart = 0;
                    aliens = 0;
                    rows = 0;
                    level[6] = '1';
                    difficulty = 0;
                    clearBoard();
                    i = 100000;
                    while(i)i--;
                    Graphics_clearDisplay(&g_sContext);
                    BuzzerOff();
                    break;
                }
            }
            if(gameStart){
                drawScreen();
                s = INPUT;
            }

            break;

          case ADVANCE:
              difficulty++;
              level[6] = difficulty+49;
              Graphics_clearDisplay(&g_sContext);
              Graphics_drawStringCentered(&g_sContext, level, AUTO_STRING_LENGTH, 48, 48, TRANSPARENT_TEXT);
              Graphics_flushBuffer(&g_sContext);
              i = 100000;
              while(i)i--;

              for(a = 0; a < 5; a++) {
                  gameBoard[i][a][0] = ((rand() % 6) + 0x30);
                  if(gameBoard[i][a][0] == '0') gameBoard[i][a][0] = ' ';
                  else aliens++;
              }

              drawScreen();

              rows = difficulty*4;
              s = INPUT;
              break;

          default:
            if(!gameStart){
                Graphics_drawStringCentered(&g_sContext, "SPACE INVADERS", AUTO_STRING_LENGTH, 48, 48, TRANSPARENT_TEXT);
                Graphics_flushBuffer(&g_sContext);
            }
            break;
        }

      if(gameStart) loopCnt++;

    }

}

void drawScreen() {
    Graphics_clearDisplay(&g_sContext);
    int i,a;
    for(i = 0; i < 8; i++)for(a = 0; a < 5; a++) Graphics_drawStringCentered(&g_sContext, gameBoard[i][a], AUTO_STRING_LENGTH, 16+(16*a), 12+(i*12), TRANSPARENT_TEXT);
    Graphics_flushBuffer(&g_sContext);
}

void clearBoard(){
    int i,j;
    for(i = 0; i<8; i++)for(j = 0; j < 5; j++)gameBoard[i][j][0] = ' ';
}
