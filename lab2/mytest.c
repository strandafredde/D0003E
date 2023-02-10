#include "tinythreads.h"
#include <stdbool.h>
#include <avr/io.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <stdint.h>

// ASCII character range(0-9)
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
int numArr[10] = {SCC_0, SCC_1 , SCC_2, SCC_3, SCC_4, SCC_5, SCC_6, SCC_7, SCC_8, SCC_9};
int pp;

mutex m = MUTEX_INIT;

	
void LCD_init() { // Den här har vi lagt till -------------------------------------------------------
	
	// Asynchronous clock, 1/3 bias, 1/4 duty cycle,   25 segments
	LCDCRB = (1<<LCDCS) | (1<<LCDMUX1) | (1<<LCDMUX0) | (1<<LCDPM2) | (1<<LCDPM1) | (1<<LCDPM0);
	// Set volt to 3.35V
	LCDCCR = (1<<LCDCC3) |(1<<LCDCC2) | (1<<LCDCC1) | (1<<LCDCC0);
	//Clock division factor to 8, and prescaler to 16
	LCDFRR = (1<<LCDCD2) | (1<<LCDCD1) | (1<<LCDCD0);
	//low power waveform, no frame interrupt, no blanking
	LCDCRA = (1<<LCDAB) | (1<<LCDEN);

}

void LCD_clear(){ // Den här har vi lagt till -------------------------------------------------------
	
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

void writeChar(char ch, int pos){ // Den här har vi lagt till -------------------------------------------------------
	int i = 0;
    // if outside supported range, do nothing
    if(pos < 0 || pos > 5) {
        return;
    }

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


    /* assign registers with correct values
     * according to SCC conversion in the
     * correct positions.
     */
    switch(pos){
        case 0:
			// ha med case 1 i masken
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
            LCDDR2  = (LCDDR2&0x00F0)  |  numArr[i] & 0x000F;
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

bool is_prime(long i) { // Den här har vi lagt till -------------------------------------------------------
	// check if i is divisible with any number that is not 1 or itself
	for (int j = 2; j < i; j++) {
		if(i % j == 0) {
			return false;
		}
	}
	return true;
} 

void printAt(long num, int pos) {
	lock(&m);
	//LCD_clear();// Den här ar vi lagt till ------------------------------------------------------------------
    pp = pos;
    writeChar( (num % 100) / 10 + '0', pp);
	for(volatile int i=0;i<10000;i++);
    pp++;
    writeChar( num % 10 + '0', pp);
	unlock(&m);
}

void computePrimes(int pos) {
	
    long n;
    for(n = 1; ; n++) {
        if (is_prime(n)) {
			;
            printAt(n, pos);
			
        }
    }
	
}

int main() {
	CLKPR = (0x80);
	CLKPR = (0x00);
	LCD_init();
    spawn(computePrimes, 0);
	computePrimes(3);
}
