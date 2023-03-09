
/*
 * inputHandler.c
 *
 * Created: 2023-03-01 11:45:47
 *  Author: stran
 */ 

#include <avr/io.h>
#include <stdbool.h>

#include "TinyTimber.h"
#include "Gui.h"
#include "pulseGenerator.h"
#include "InputHandler.h"

void initialize (inputHandler *self) {
    SYNC(self->gui[0], LCD_init, 0);
    SYNC(self->pGen[0], generatePulse , NULL);
    ASYNC(self->pGen[1], generatePulse , NULL);
	ASYNC(self->gui[0], printAt, 1);
	ASYNC(self->gui[1], printAt, 1);
	ASYNC(self->gui[0], generatorChange, NULL);
}

void joystickUpDownCenter (inputHandler *self) {
	/*	Choose which generator to be used depending on which side is chosen.
		Execute and change the frequency or save the frequency
		with a delay of 0.5s depending on which
		button is pressed. */
	
	
	//Push
	PORTB |= (1<<4);
	if((PINB & (1<<PINB4)) == 0) {
		if(self->press){
			ASYNC(self->pGen[self->current], saveFreq, NULL);
			self->press = false;
			self->tryck = true;
		}
		AFTER(MSEC(200), self, bounce, NULL);
	}

    //Up

	PORTB |= (1<<6);
	if(!(PINB & 0x0040)) {
		if (self->press){
			AFTER(MSEC(500),self->pGen[self->current],  (changeFreqUp), NULL);
			self->press = false;
			self->tryck = true;
			
		}
		if(self->tryck) {
			AFTER(MSEC(200), self, bounce, NULL);
			self->tryck = false;
		}
    }
	
    //Down
	PORTB |= (1<<7);
		if(!(PINB & 0x0080)) {
			if(self->press) {
				AFTER(MSEC(500), self->pGen[self->current],  changeFreqDown, NULL);
				self->press = false;
				self->tryck = true;
				
			}
			if(self->tryck) {
				AFTER(MSEC(200), self, bounce, NULL);
				self->tryck = false;
			}
			

		}
	
}

void bounce(inputHandler *self) {
	self->press = true;
}



void joystickLeftRight(inputHandler *self) {
	/*	Choose which pulse generator to use and which
		side to display frequency on. 
		
		Asynchronously invoke method generator change on object self 
		with the chosen side as argument.   */
	
	    PORTE |= (1<<3);
	    if(!(PINE & (0X0008))) {
		    /* Pulse generator 2 */
			if (self->current < 1) {
				ASYNC(self->gui[self->current], generatorChange, NULL);
				self->current += 1;
				ASYNC(self->gui[self->current], generatorChange, NULL);
			}
	    }
	    PORTE |= (1<<2);
	    if(!(PINE & (0X0004))) {
		    /* Pulse generator 1 */
		if (self->current > 0) {
			ASYNC(self->gui[self->current], generatorChange, NULL);
			self->current -= 1;
			ASYNC(self->gui[self->current], generatorChange, NULL);
		}
	    }
	}

