/**************  ECE2049 LAB 1 *********************/
/**************  BY JEFFREY HUANG ******************/
/**************  AND MICHAEL MCCUE *****************/
/***************************************************/

#include <msp430.h>
#include "peripherals.h"
#include <stdlib.h>
#include <stdio.h>

void drawScreen();

char gameBoard[8][5][2];

enum State{START, INPUT, DESCEND, DEFAULT};

void main(void){
    WDTCTL = WDTPW | WDTHOLD;    // Stop watchdog timer. Always need to stop this!!
                                 // You can then configure it properly, if desired
    initLeds();
    configDisplay();
    configKeypad();

    unsigned char currKey = 0;
    unsigned long int loopCnt = 0;
    unsigned int gameStart = 0, difficulty = 0, i = 0, a = 0;
    enum State s = DEFAULT;
    //loopCnt counts the number of loops during the game, gameStart 0 to not start count, 1 to start counting during game
    //difficulty is used to calculate how fast the aliens descend

    for(i = 0; i < 5; i++){
        for(a = 0; a < 5; a++) {
            gameBoard[i][a][0] = ((rand() % 6) + 0x30);
            gameBoard[i][a][1] = '\0';
            if(gameBoard[i][a][0] == '0') gameBoard[i][a][0] = ' ';
        }
    }

    while(1){
        currKey = getKey();
        if(currKey == '*' && !gameStart) s = START;
        if(gameStart){
          if(currKey>=1&&currKey<=5) s = INPUT;
          if(loopCnt%(40000-500*difficulty)==0) s = DESCEND;
        }
        switch(s){
          case START:
            //start game countdown
            //only does something if gameStart !=0
            gameStart = 1;
            Graphics_clearDisplay(&g_sContext);
            Graphics_drawStringCentered(&g_sContext, "Starting game in: ", AUTO_STRING_LENGTH, 48, 48, TRANSPARENT_TEXT);
            for(i = 0; i <= 10000; i++){
              if(i==0){
                Graphics_clearDisplay(&g_sContext);
                Graphics_drawStringCentered(&g_sContext, "3", AUTO_STRING_LENGTH, 48, 48, TRANSPARENT_TEXT);
                Graphics_flushBuffer(&g_sContext);
              }
              if(i==4000){
                Graphics_clearDisplay(&g_sContext);
                Graphics_drawStringCentered(&g_sContext, "2", AUTO_STRING_LENGTH, 48, 48, TRANSPARENT_TEXT);
                Graphics_flushBuffer(&g_sContext);
              }
              if(i==8000){
                Graphics_clearDisplay(&g_sContext);
                Graphics_drawStringCentered(&g_sContext, "1", AUTO_STRING_LENGTH, 48, 48, TRANSPARENT_TEXT);
                Graphics_flushBuffer(&g_sContext);
              }
              if(i==10000){
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
            //makes buzzer sounds if nonvalid character is given
            if (!(currKey>=0x31&&currKey<=0x35)&&currKey!=0) BuzzerOn();
            else {
              for(i = 7; i >= 0; i--){
                for(a = 0; a < 5; a++) {
                  if(currKey == gameBoard[i][a][0]){
                      gameBoard[i][a][0] = ' ';
                      break;
                  }
                }
              }
            }
            break;
          case DESCEND: //descends the alien and checks if gameOver
            for(i = 0; i < 8; i++) {
                for(a = 0; a < 5; a++){
                    if(gameBoard[i][a][0] != ' '){
                        Graphics_clearDisplay(&g_sContext);
                        Graphics_drawStringCentered(&g_sContext, , "GAME OVER", AUTO_STRING_LENGTH, 48, 48, TRANSPARENT_TEXT);
                        Graphics_flushBuffer(&g_sContext);
                        s = DEFAULT;
                        break;
                    }
                }
            }

            for(i = 0; i < 7; i++) {
                for (a = 0; a < 5; a++) {
                    gameBoard[i+1][a][0] = gameBoard[i][a][0];
                }
            }

            for(a = 0; a < 7; a++) {
                gameBoard[0][a][0] = ((rand() % 6) + 0x30);
                gameBoard[0][a][1] = '\0';
                if(gameBoard[0][a][0] == '0') gameBoard[0][a][0] = ' ';
            }
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
    for(i = 0; i < 8; i++){
        for(a = 0; a < 5; a++) {
            Graphics_drawStringCentered(&g_sContext, gameBoard[i][a], AUTO_STRING_LENGTH, 16 + (16 * a) , 12 + (i * 12), TRANSPARENT_TEXT);
            Graphics_flushBuffer(&g_sContext);
        }
    }
}
