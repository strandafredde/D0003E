#include <stdbool.h>
#include <stdlib.h>
#include <math.h>
#include <avr/io.h>
#include <stdio.h>

#include "Gui.h"

//Array to store numbers

int numArr[10] = {SCC_0, SCC_1 , SCC_2, SCC_3, SCC_4, SCC_5, SCC_6, SCC_7, SCC_8, SCC_9};


typedef struct {
	Object super;
}guiClass;

void LCD_init() {

    /* Function: LCD_init
     * -------------------
     * initiation code for LCD
     *
     * returns: none
     */

    /* Asynchronous clock, 1/3 bias, 1/4 duty cycle,   25 segments */
    LCDCRB = (1<<LCDCS) | (1<<LCDMUX1) | (1<<LCDMUX0) | (1<<LCDPM2) | (1<<LCDPM1) | (1<<LCDPM0);
    /* Set volt to 3.35V */
    LCDCCR = (1<<LCDCC3) |(1<<LCDCC2) | (1<<LCDCC1) | (1<<LCDCC0);
    /* Clock division factor to 8, and prescaler to 16 */
    LCDFRR = (1<<LCDCD2) | (1<<LCDCD1) | (1<<LCDCD0);
    /* low power waveform, no frame interrupt, no blanking */
    LCDCRA = (1<<LCDAB) | (1<<LCDEN);

}

void writeChar(char ch, int pos){

    /* Function: WriteChar
     * -------------------
     * writes character (char ch) to LCD, at
     * position (int pos) if within fixed range.
     *
     * returns: none
     */

    int i = 0;

    /* checks if pos is within fixed range */
    if(pos < 0 || pos > 5) {
        return;
    }

    /* index select of character */
    switch(ch){
        case '0':
            i = 0;
            break;
        case '1':
            i = 1;
            break;
        case '2':
            i = 2;
            break;
        case '3':
            i = 3;
            break;
        case '4':
            i = 4;
            break;
        case '5':
            i = 5;
            break;
        case '6':
            i = 6;
            break;
        case '7':
            i = 7;
            break;
        case '8':
            i = 8;
            break;
        case '9':
            i = 9;
            break;
        default:
            break;
    }

    /* writes translated char at pos to LCD */
    switch(pos){
        case 0:
            LCDDR0  = (LCDDR0&0x00F0)  |  (numArr[i] & 0x000F) | 0x0004;
            LCDDR5  = (LCDDR5&0x00F0)  | ((numArr[i] & 0x00F0))>>4;
            LCDDR10 = (LCDDR10&0x00F0) | ((numArr[i] & 0x0F00))>>8;
            LCDDR15 = (LCDDR15&0x00F0) | ((numArr[i] & 0xF000))>>12;
            break;
        case 1:
            LCDDR0  = (LCDDR0&0x000F)  |  ((numArr[i] & 0x000F))<<4;
            LCDDR5  = (LCDDR5&0x000F)  |   (numArr[i] & 0x00F0);
            LCDDR10 = (LCDDR10&0x000F) |  ((numArr[i] & 0x0F00))>>4;
            LCDDR15 = (LCDDR15&0x000F) |  ((numArr[i] & 0xF000))>>8;
            break;
        case 2:
            LCDDR1  = (LCDDR1&0x00F0)  |  (numArr[i] & 0x000F);
            LCDDR6  = (LCDDR6&0x00F0)  |  ((numArr[i] & 0x00F0))>>4;
            LCDDR11 = (LCDDR11&0x00F0) |  ((numArr[i] & 0x0F00))>>8;
            LCDDR16 = (LCDDR16&0x00F0) |  ((numArr[i] & 0xF000))>>12;
            break;
        case 3:
            LCDDR1  = (LCDDR1&0x000F)  |  ((numArr[i] & 0x000F))<<4;
            LCDDR6  = (LCDDR6&0x000F)  |   (numArr[i] & 0x00F0);
            LCDDR11 = (LCDDR11&0x000F) |  ((numArr[i] & 0x0F00))>>4;
            LCDDR16 = (LCDDR16&0x000F) |  ((numArr[i] & 0xF000))>>8;
            break;
        case 4:
            LCDDR2  = (LCDDR2&0x00F0)  | ((numArr[i] & 0x000F));
            LCDDR7  = (LCDDR7&0x00F0)  | ((numArr[i] & 0x00F0))>>4;
            LCDDR12 = (LCDDR12&0x00F0) | ((numArr[i] & 0x0F00))>>8;
            LCDDR17 = (LCDDR17&0x00F0) | ((numArr[i] & 0xF000))>>12;
            break;
        case 5:
            LCDDR2  = (LCDDR2&0x000F)  |  ((numArr[i] & 0x000F))<<4;
            LCDDR7  = (LCDDR7&0x000F)  |  (numArr[i] & 0x00F0);
            LCDDR12 = (LCDDR12&0x000F) |  ((numArr[i] & 0x0F00))>>4;
            LCDDR17 = (LCDDR17&0x000F) |  ((numArr[i] & 0xF000))>>8;
            break;
        default:
            break;
    }

}

bool is_prime(long i) {

    /* Function: is_prime
     * -------------------
     * determines whether (long i) is
     * a prime value or not.
     *
     * returns: bool
     */

    for (int j = 2; j < i; j++) {
        if(i % j == 0) {
            /* is not prime */
            return false;
        }
    }
    /* is prime */
    return true;
}

void printAt(long num, int pos) {
    /* Function: printAt
     * -------------------
     * calls function to write char
     * at fixed positions 0 and 1.
     *
     * returns: none
     */

    int pp = pos;
    writeChar( (num % 100) / 10 + '0', pp);
    pp++;
    writeChar( num % 10 + '0', pp);
}

void generatorChange(int *side) {
	if(*side == 1) {
		LCDDR0 |= 0x04;
		LCDDR0 &= 0xBF;
	}
	if(*side == 2) {
		LCDDR0 |= 0x40;
		LCDDR0 &= 0xFB;
	}
}