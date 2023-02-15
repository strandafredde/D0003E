#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <avr/io.h>
#include "tinythreads.h"

int pp;
int count;
bool pressP4 = true;

uint16_t countP4 = 15625;
uint16_t cycle = 15625;
int lastTime;
uint16_t deltaTime;

#define SCC_0  0x1551
#define SCC_1  0x2080
#define SCC_2  0x1E11
#define SCC_3  0x1B11
#define SCC_4  0x0B50
#define SCC_5  0x1B41
#define SCC_6  0x1F41
#define SCC_7  0x0111
#define SCC_8  0x1F51
#define SCC_9  0x0B51
//Array to store numbers
#define numArr (int[]) {SCC_0, SCC_1 , SCC_2, SCC_3, SCC_4, SCC_5, SCC_6, SCC_7, SCC_8, SCC_9}

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

void LCD_clear(){

    /* Function: LCD_clear
     * -------------------
     * clear code for LCD
     *
     * returns: none
     */

    LCDDR0 = (LCDDR0 & 0x0000);
    LCDDR5 = (LCDDR5 & 0x0000);
    LCDDR10 = (LCDDR10 & 0x0000);
    LCDDR15 = (LCDDR11 & 0x0000);

    LCDDR1 = (LCDDR1 & 0x0066);
    LCDDR6 = (LCDDR6 & 0x0000);
    LCDDR11 = (LCDDR11 & 0x0000);
    LCDDR16 = (LCDDR16 & 0x0000);

    LCDDR2 = (LCDDR2 & 0x0040);
    LCDDR7 = (LCDDR7 & 0x0000);
    LCDDR12 = (LCDDR12 & 0x0000);
    LCDDR17 = (LCDDR17 & 0x0000);
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
            LCDDR0  = (LCDDR0&0x00F0)  |  numArr[i] & 0x000F;
            LCDDR5  = (LCDDR5&0x00F0)  | (numArr[i] & 0x00F0)>>4;
            LCDDR10 = (LCDDR10&0x00F0) | (numArr[i] & 0x0F00)>>8;
            LCDDR15 = (LCDDR15&0x00F0) | (numArr[i] & 0xF000)>>12;
            break;
        case 1:
            LCDDR0  = (LCDDR0&0x000F)  |  (numArr[i] & 0x000F)<<4;
            LCDDR5  = (LCDDR5&0x000F)  |   numArr[i] & 0x00F0;
            LCDDR10 = (LCDDR10&0x000F) |  (numArr[i] & 0x0F00)>>4;
            LCDDR15 = (LCDDR15&0x000F) |  (numArr[i] & 0xF000)>>8;
            break;
        case 2:
            LCDDR1  = (LCDDR1&0x00F0)  |   numArr[i] & 0x000F;
            LCDDR6  = (LCDDR6&0x00F0)  |  (numArr[i] & 0x00F0)>>4;
            LCDDR11 = (LCDDR11&0x00F0) |  (numArr[i] & 0x0F00)>>8;
            LCDDR16 = (LCDDR16&0x00F0) |  (numArr[i] & 0xF000)>>12;
            break;
        case 3:
            LCDDR1  = (LCDDR1&0x000F)  |  (numArr[i] & 0x000F)<<4;
            LCDDR6  = (LCDDR6&0x000F)  |   numArr[i] & 0x00F0;
            LCDDR11 = (LCDDR11&0x000F) |  (numArr[i] & 0x0F00)>>4;
            LCDDR16 = (LCDDR16&0x000F) |  (numArr[i] & 0xF000)>>8;
            break;
        case 4:
            LCDDR2  = (LCDDR2&0x00F0)  | ( numArr[i] & 0x000F);
            LCDDR7  = (LCDDR7&0x00F0)  | (numArr[i] & 0x00F0)>>4;
            LCDDR12 = (LCDDR12&0x00F0) | (numArr[i] & 0x0F00)>>8;
            LCDDR17 = (LCDDR17&0x00F0) | (numArr[i] & 0xF000)>>12;
            break;
        case 5:
            LCDDR2  = (LCDDR2&0x000F)  |  (numArr[i] & 0x000F)<<4;
            LCDDR7  = (LCDDR7&0x000F)  |  numArr[i] & 0x00F0;
            LCDDR12 = (LCDDR12&0x000F) |  (numArr[i] & 0x0F00)>>4;
            LCDDR17 = (LCDDR17&0x000F) |  (numArr[i] & 0xF000)>>8;
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

    pp = pos;
    writeChar( (num % 100) / 10 + '0', pp);
    pp++;
    writeChar( num % 10 + '0', pp);

}

void computePrimes(int pos) {

    /* Function: computePrimes
     * -------------------
     * writes prime values to LCD
     * at positions 0 and 1.
     * returns: none
     */

    long n;
    for(n = 1; ; n++) {
        if (is_prime(n)) {
            printAt(n, pos);
        }
    }

}

void button() {

    /* Function: button
     * -------------------
     * code that counts button activations
     * and writes them onto LCD.
     *
     * returns: none
     */

    PORTB = 0x0080;
    while(true) {
        if(!(PINB & (0X0080))) {

            if(pressP4){
                count ++;
                pressP4 = false;
            }
        }
        if(PINB & (0X0080)) {
            pressP4 = true;
        }
        printAt(count, 4);
    }
}

void blink() {
	
    /* Function: blink
     * -------------------
     * activates segment of LCD at
     * a 1Hz rate.
     *
     * returns: none
     */
	while (true) {
		if(getBlinkCounter() == 0){
			LCDDR2 = 0x0040;
		}
		if(getBlinkCounter() == 1) {
			LCDDR2 = 0x0000;
			resetBlinkCounter();
		}
	}

}

int main() {
	CLKPR = (0x80);
	CLKPR = (0x00);
	LCD_init();
	//blink();
    //spawn(blink, 0);
	spawn(computePrimes, 0);
    //button();
	
}