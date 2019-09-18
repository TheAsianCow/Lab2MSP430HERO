/*
 * peripherals.h
 *
 *  Created on: Jan 29, 2014
 *      Author:  ndemarinis
 *  Update on: 9 Jan 2019, 22 Aug 2018 -- smj
 */

#ifndef PERIPHERALS_H_
#define PERIPHERALS_H_

#include <msp430.h>
#include <stdint.h>
#include "grlib.h"

#include "LcdDriver/Sharp96x96.h"
#include "LcdDriver/HAL_MSP_EXP430FR5529_Sharp96x96.h"


/*
 * DAC pin assignment is as follows
 * LDAC			P3.7
 * CS			P8.2
 * MOSI/SDI		P3.0
 * SCLK			P3.2
 */
#define DAC_PORT_LDAC_SEL		P3SEL
#define DAC_PORT_LDAC_DIR		P3DIR
#define DAC_PORT_LDAC_OUT		P3OUT

#define DAC_PORT_CS_SEL			P8SEL
#define DAC_PORT_CS_DIR			P8DIR
#define DAC_PORT_CS_OUT			P8OUT

#define DAC_PORT_SPI_SEL		P3SEL
#define DAC_PORT_SPI_DIR		P3DIR

#define DAC_PIN_MOSI			BIT0
#define DAC_PIN_SCLK			BIT2
#define DAC_PIN_CS				BIT2
#define DAC_PIN_LDAC			BIT7

#define DAC_SPI_REG_CTL0		UCB0CTL0
#define DAC_SPI_REG_CTL1		UCB0CTL1
#define DAC_SPI_REG_BRL			UCB0BR0
#define DAC_SPI_REG_BRH			UCB0BR1
#define DAC_SPI_REG_IFG			UCB0IFG
#define DAC_SPI_REG_STAT		UCB0STAT
#define DAC_SPI_REG_TXBUF		UCB0TXBUF
#define DAC_SPI_REG_RXBUF		UCB0RXBUF


// Song Stats
#define CLK_SPEED 32768
#define SONG_BPM 74
#define SONG_LENGTH 54
struct Note {
        int freq, time; //note frequency
        //note time 1 whole 2 half 4 for quarter 8 for eighth and 16 for sixteenth
};

// Notes:
/*
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
*/

/*
 * UCSI SPI Clock parameters
 * The actual clock frequency is given in number of
 * ticks of the specified clock source.
 *
 * For our configuration, we use SMCLK */
#define DAC_SPI_CLK_SRC		(UCSSEL__SMCLK)
#define DAC_SPI_CLK_TICKS	0

// Globals
extern tContext g_sContext;	// user defined type used by graphics library

// Prototypes for functions defined implemented in peripherals.c

//void DACInit(void);
//void DACSetValue(unsigned int dac_code);
//void setupSPI_DAC(void);
void initLeds(void);
void setLeds(unsigned char state);
void setUserLED(unsigned char state);
void configBtn(void);
unsigned char getBtn(void);

int playNote(struct Note in, int bpm);
__interrupt void Timer_A2 (void);
void playSong(struct Note song[SONG_LENGTH], int songBpm);
struct Note octaveUp(struct Note in);
struct Note octaveDown(struct Note in);


void configDisplay(void);
void BuzzerOn(int freq);
void BuzzerOff(void);

void configKeypad(void);
unsigned char getKey(void);

#endif /* PERIPHERALS_H_ */
