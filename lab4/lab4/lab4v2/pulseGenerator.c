/*
 * pulseGenerator.c
 *
 * Created: 2023-03-01 12:08:03
 *  Author: stran
 */ 

#include <stdint.h>
#include <avr/io.h>

#include "pulseGenerator.h"
#include "pulseSender.h"
#include "TinyTimber.h"
#include "Gui.h"


void generatePulse(pulseGenerator *self) {
    if (self->freq > 0) {
        ASYNC(self->pSender, sendPulse, self->pin);
        AFTER(MSEC(1000/(self->freq*2)), self, generatePulse, NULL);
    } else {
        ASYNC(self->pSender, resetPin, self->pin);
    }
}

void saveFreq(pulseGenerator *self) {
	if (self->freq > 0) {
		self->savedFreq = self->freq;
		self->freq = 0;
	}
	else {
		self->freq = self->savedFreq;
	}
	ASYNC(self->gui, printAt, self->freq);
}

void changeFreqUp(pulseGenerator *self){
	self->freq += 1;
	if(self->freq <= 99){
		ASYNC(self->gui, printAt, self->freq);
	
	
		PORTB |= (1<<6);
		if(!(PINB & 0x0040)) { // Up
			AFTER(MSEC(200), self,  changeFreqUp, NULL);
		}
	}
	

}

void changeFreqDown(pulseGenerator *self){
	self->freq -= 1;
	if(self->freq >= 0) {
		ASYNC(self->gui, printAt, self->freq);
			
			
		PORTB |= (1<<7);
		if(!(PINB & 0x0080)) { // Up
			AFTER(MSEC(200), self,  changeFreqDown, NULL);
		}
	}
	

}

