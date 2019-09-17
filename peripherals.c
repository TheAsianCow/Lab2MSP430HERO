/*
 * peripherals.c
 *
 *  Created on: Jan 29, 2014
 *      Author: deemer
 *  Updated on Jan 3, 2016
 *  	smj
 *  Updated on Jan 14, 2018
 *      smj
 *  Updated on Aug 22, 2018
 *      smj
  *  Updated on Jan 9, 2019
 *      smj
 *
 */

#include "peripherals.h"

// Globals
tContext g_sContext;    // user defined type used by graphics library
int nextNote = 0;

void initLeds(void)
{
    // Configure LEDs as outputs, initialize to logic low (off)
    // Note the assigned port pins are out of order test board
    // Red     P6.2
    // Green   P6.1
    // Blue    P6.3
    // Yellow  P6.4
    // smj -- 27 Dec 2016

    P6SEL &= ~(BIT4|BIT3|BIT2|BIT1);
    P6DIR |=  (BIT4|BIT3|BIT2|BIT1);
    P6OUT &= ~(BIT4|BIT3|BIT2|BIT1);
}

void setLeds(unsigned char state)
{
    // Turn on 4 colored LEDs on P6.1-6.4 to match the hex value
    // passed in on low nibble state. Unfortunately the LEDs are
    // out of order with 6.2 is the left most (i.e. what we think
    // of as MSB), then 6.1 followed by 6.3 and finally 6.4 is
    // the right most (i.e.  what we think of as LSB) so we have
    // to be a bit clever in implementing our LEDs
    //
    // Input: state = hex values to display (in low nibble)
    // Output: none
    //
    // smj, ECE2049, 27 Dec 2015

    unsigned char mask = 0;

    // Turn all LEDs off to start
    P6OUT &= ~(BIT4|BIT3|BIT2|BIT1);

    if (state & BIT0)
        mask |= BIT4;   // Right most LED P6.4
    if (state & BIT1)
        mask |= BIT3;   // next most right LED P.3
    if (state & BIT2)
        mask |= BIT1;   // third most left LED P6.1
    if (state & BIT3)
        mask |= BIT2;   // Left most LED on P6.2
    P6OUT |= mask;
}

void setUserLED(unsigned char state){
    unsigned char mask = 0;

    P6OUT &= ~(BIT4|BIT3|BIT2|BIT1);

    if(state & BIT0) mask |= BIT4;
    if(state & BIT1) mask |= BIT3;

    P6OUT |= mask;
}

void configBtn(void){

    //Configure buttons for I/O
    P7SEL &= ~(BIT4|BIT0);
    P3SEL &= ~(BIT6);
    P2SEL &= ~(BIT2);

    P7DIR &= ~(BIT4 | BIT0);
    P3DIR &= ~(BIT6);
    P2DIR &= ~(BIT2);

    P7REN |=  (BIT4 | BIT0);
    P3REN |=  (BIT6);
    P2REN |=  (BIT2);

    P7OUT |=  (BIT4 | BIT0);
    P3OUT |=  (BIT6);
    P2OUT |=  (BIT2);
}

unsigned char getBtn(void){
    char out = 0;

    if(~(P7IN & BIT0)) out |= BIT0;
    if(~(P7IN & BIT4)) out |= BIT4;
    if(~(P3IN & BIT6)) out |= BIT6;
    if(~(P2IN & BIT2)) out |= BIT2;

    return out;
}

/*
 * Enable a PWM-controlled buzzer on P3.5
 * This function makes use of TimerB0.
 */

/*
void BuzzerOn(void)
{
    // Initialize PWM output on P3.5, which corresponds to TB0.5
    P3SEL |= BIT5; // Select peripheral output mode for P3.5
    P3DIR |= BIT5;

    TB0CTL  = (TBSSEL__ACLK|ID__1|MC__UP);  // Configure Timer B0 to use ACLK, divide by 1, up mode
    TB0CTL  &= ~TBIE;                       // Explicitly Disable timer interrupts for safety

    // Now configure the timer period, which controls the PWM period
    // Doing this with a hard coded values is NOT the best method
    // We do it here only as an example. You will fix this in Lab 2.
    TB0CCR0   = 128;                    // Set the PWM period in ACLK ticks
    TB0CCTL0 &= ~CCIE;                  // Disable timer interrupts

    // Configure CC register 5, which is connected to our PWM pin TB0.5
    TB0CCTL5  = OUTMOD_7;                   // Set/reset mode for PWM
    TB0CCTL5 &= ~CCIE;                      // Disable capture/compare interrupts
    TB0CCR5   = TB0CCR0/2;                  // Configure a 50% duty cycle
}
*/

// Song functions
/*
struct Note hotel_cali[] = {octaveUp(D6), octaveUp(B6), octaveUp(Fs6),
                                    octaveUp(D6), octaveUp(B6), octaveUp(Fs6),
                                    octaveUp(D6), octaveUp(B6), octaveUp(Fs6),
                                    octaveUp(D6), octaveUp(B6), octaveUp(Fs6),
                                    octaveUp(D6), octaveUp(B6), octaveUp(Fs8),

                                    octaveUp(Cs6), octaveUp(As6), octaveUp(Fs6),
                                    octaveUp(Cs6), octaveUp(As6), octaveUp(Fs6),
                                    octaveUp(Cs6), octaveUp(As6),

                                    rest6, rest6, rest6, rest8,

                                    octaveUp(Cs6), octaveUp(A6), octaveUp(E6),
                                    octaveUp(Cs6), octaveUp(A6), octaveUp(E6),
                                    octaveUp(Cs6), octaveUp(A6), octaveUp(E6),
                                    octaveUp(Cs6), octaveUp(A6), octaveUp(E6),
                                    octaveUp(Cs6), octaveUp(A6), octaveUp(E8),

                                    octaveUp(B6), octaveUp(Gs6), octaveUp(E6),
                                    octaveUp(B6), octaveUp(Gs6), octaveUp(E6),
                                    octaveUp(B6), octaveUp(Gs6),

                                    rest6, rest6, rest6, rest8
        };
*/

int playNote(struct Note in, int bpm) {
    // enable interrupt
    _BIS_SR(GIE);
    // enable interupt
    // Init
    P3SEL |= BIT5;
    P3DIR |= BIT5;

    // B0 timer control
    TB0CTL  = (TBSSEL__ACLK|ID__1|MC__UP);
    TB0CTL  &= ~TBIE;

    // A2 timer control
    TA2CTL  = (TASSEL__ACLK|ID__1|MC__UP);

    TB0CCR0   = CLK_SPEED/in.freq;         // clock frequency/note frequency = pwm period
    TB0CCTL0 &= ~CCIE;

    // counts notes based on beat
    // ex: whole note 4 beats (at 60 bpm it is 1 note per second
    //note time 1 whole 2 half 4 for quarter 8 for eighth and 16 for sixteenth
    if(in.freq == 0) BuzzerOff();
    TA2CCR0  = (CLK_SPEED * (bpm / 15)) / in.time;
    TA2CCTL0 = CCIE; // IE

    TB0CCTL5  = OUTMOD_7;
    TB0CCTL5 &= ~CCIE;
    TB0CCR5   = TB0CCR0/2;
    nextNote = 1;
    return 0;
}

#pragma vector=TIMER2_A0_VECTOR
interrupt void Timer_A2 (void) {
    // Turns off buzzer resets timers
    TB0CCTL0 = 0;
    TB0CCTL5 = 0;
    TA2CCTL0 = 0;
    nextNote = 0;
}


void playSong(struct Note song[SONG_LENGTH], int songBpm) {
    //Plays the song
    int i;
    for (i = 0; i < SONG_LENGTH; i++) {
            playNote(song[i], songBpm);
            while (nextNote == 1);
    }
}

struct Note octaveUp(struct Note in) {
    struct Note out = {2 * in.freq, in.time};
    //moves a note up an octave
    return out;
}

struct Note octaveDown(struct Note in) {
    // Moves note down an octave
    struct Note out = {in.freq / 2, in.time};
    return out;
}

void BuzzerOn(int freq)
{
    // Initialize PWM output on P3.5, which corresponds to TB0.5
    P3SEL |= BIT5; // Select peripheral output mode for P3.5
    P3DIR |= BIT5;

    TB0CTL  = (TBSSEL__ACLK|ID__1|MC__UP);  // Configure Timer B0 to use ACLK, divide by 1, up mode
    TB0CTL  &= ~TBIE;                       // Explicitly Disable timer interrupts for safety

    // Now configure the timer period, which controls the PWM period
    // Doing this with a hard coded values is NOT the best method
    // We do it here only as an example. You will fix this in Lab 2.
    TB0CCR0   = freq;                    // Set the PWM period in ACLK ticks
    TB0CCTL0 &= ~CCIE;                  // Disable timer interrupts

    // Configure CC register 5, which is connected to our PWM pin TB0.5
    TB0CCTL5  = OUTMOD_7;                   // Set/reset mode for PWM
    TB0CCTL5 &= ~CCIE;                      // Disable capture/compare interrupts
    TB0CCR5   = TB0CCR0/2;                  // Configure a 50% duty cycle
}


/*
 * Disable the buzzer on P7.5
 */
void BuzzerOff(void)
{
    // Disable both capture/compare periods
    TB0CCTL0 = 0;
    TB0CCTL5 = 0;
}


void configKeypad(void)
{
    // Configure digital IO for keypad
    // smj -- 27 Dec 2015

    // Col1 = P1.5 =
    // Col2 = P2.4 =
    // Col3 = P2.5 =
    // Row1 = P4.3 =
    // Row2 = P1.2 =
    // Row3 = P1.3 =
    // Row4 = P1.4 =

    P1SEL &= ~(BIT5|BIT4|BIT3|BIT2);
    P2SEL &= ~(BIT5|BIT4);
    P4SEL &= ~(BIT3);

    // Columns are ??
    P2DIR |= (BIT5|BIT4);
    P1DIR |= BIT5;
    P2OUT |= (BIT5|BIT4); //
    P1OUT |= BIT5;        //

    // Rows are ??
    P1DIR &= ~(BIT2|BIT3|BIT4);
    P4DIR &= ~(BIT3);
    P4REN |= (BIT3);  //
    P1REN |= (BIT2|BIT3|BIT4);
    P4OUT |= (BIT3);  //
    P1OUT |= (BIT2|BIT3|BIT4);
}


unsigned char getKey(void)
{
    // Returns ASCII value of key pressed from keypad or 0.
    // Does not decode or detect when multiple keys pressed.
    // smj -- 27 Dec 2015
    // Updated -- 14 Jan 2018

    unsigned char ret_val = 0;

    // Set Col1 = ?, Col2 = ? and Col3 = ?
    P1OUT &= ~BIT5;
    P2OUT |= (BIT5|BIT4);
    // Now check value from each rows
    if ((P4IN & BIT3)==0)
        ret_val = '1';
    if ((P1IN & BIT2)==0)
        ret_val = '4';
    if ((P1IN & BIT3)==0)
        ret_val = '7';
    if ((P1IN & BIT4)==0)
        ret_val = '*';
    P1OUT |= BIT5;

    // Set Col1 = ?, Col2 = ? and Col3 = ?
    P2OUT &= ~BIT4;
    // Now check value from each rows
    if ((P4IN & BIT3)==0)
        ret_val = '2';
    if ((P1IN & BIT2)==0)
        ret_val = '5';
    if ((P1IN & BIT3)==0)
        ret_val = '8';
    if ((P1IN & BIT4)==0)
        ret_val = '0';
    P2OUT |= BIT4;

    // Set Col1 = ?, Col2 = ? and Col3 = ?
    P2OUT &= ~BIT5;
    // Now check value from each rows
    if ((P4IN & BIT3)==0)
        ret_val = '3';
    if ((P1IN & BIT2)==0)
        ret_val = '6';
    if ((P1IN & BIT3)==0)
        ret_val = '9';
    if ((P1IN & BIT4)==0)
        ret_val = '#';
    P2OUT |= BIT5;

    return(ret_val);
}


void configDisplay(void)
{
    // Enable use of external clock crystals
     P5SEL |= (BIT5|BIT4|BIT3|BIT2);

	// Initialize the display peripheral
	Sharp96x96_Init();

    // Configure the graphics library to use this display.
	// The global g_sContext is a data structure containing information the library uses
	// to send commands for our particular display.
	// You must pass this parameter to each graphics library function so it knows how to
	// communicate with our display.
    Graphics_initContext(&g_sContext, &g_sharp96x96LCD);


    Graphics_setForegroundColor(&g_sContext, ClrBlack);
    Graphics_setBackgroundColor(&g_sContext, ClrWhite);
    Graphics_setFont(&g_sContext, &g_sFontFixed6x8);
    Graphics_clearDisplay(&g_sContext);
    Graphics_flushBuffer(&g_sContext);
}

/*
void setupSPI_DAC(void)
{
// ** Set UCSI A0 Reset=1 to configure control registers **
     UCB0CTL1 |= UCSWRST;
     // 3-pin (SCLK, SIMO, SOMI), 8-bit, this MSP430 is SPI master,
     // Clock polarity high, send data MSB first
     UCB0CTL0 = UCMST + UCSYNC + UCCKPH + UCMSB;
     // Use SMCLK as clock source, keep RESET = 1
     UCB0CTL1 = UCSWRST + UCSSEL_2;

     UCB0BR0 = 2;   // SCLK = SMCLK/2 = 524288Hz
     UCB0BR1 = 0;

     //UCB0MCTL = 0;   // write MCTL as 0

     // Enable UCSI A0
     UCB0CTL1 &= ~UCSWRST;
}
*/

//------------------------------------------------------------------------------
// Timer1 A0 Interrupt Service Routine
//------------------------------------------------------------------------------
#pragma vector=TIMER1_A0_VECTOR
__interrupt void TIMER1_A0_ISR (void)
{
	// Display is using Timer A1
	// Not sure where Timer A1 is configured?
	Sharp96x96_SendToggleVCOMCommand();  // display needs this toggle < 1 per sec
}
