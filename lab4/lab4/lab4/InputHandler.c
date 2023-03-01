/*
 * InputHandler.c
 *
 * Created: 2023-03-01 11:45:47
 *  Author: stran
 */ 
//#include "InputHandler.h"
#include "TinyTimber.h"
#include "Gui.h"
#include "pulseGenerator.h"
#include <avr/io.h>


typedef struct {
	Object super;
	guiClass *gui;
	pulseGenerator *p1;
	pulseGenerator *p2;
}InputHandler;


void joystickLeftRight(InputHandler *self){
	    PORTE |= (1<<3);
	    if(!(PINE & (0X0008))) {
		    /* Pulse generator 2 */
			self->p2->side = 1;
			self->p1->side = 1;
			ASYNC(self->gui, generatorChange, self->p2->side);
	    }
	    PORTE |= (1<<2);
	    if(!(PINE & (0X0004))) {
		    /* Pulse generator 1 */
			self->p1->side = 0;
			self->p2->side = 0;;
			ASYNC(self->gui, generatorChange, self->p1->side);
	    }
	}

void joystickUpDownCenter(InputHandler *self){
	pulseGenerator *generator;
	if (self->p1->side == 0) {
		 generator = self -> p1;
	}
	
	if (self->p2->side == 1) {
		generator = self -> p2;
	}
	PORTB |= (1<<6);
	if(!(PINB & 0x0040)) {
		AFTER(SEC(1), &generator,  changeFreqUp, NULL);
	}
	
	PORTB |= (1<<7);
	if(!(PINB & 0x0080)) {
		AFTER(SEC(1), &generator,  changeFreqDown, NULL);
	}
	
	PORTB |= (1<<4);
	if((PINB & (1<<PINB4)) == 0) {
		AFTER(SEC(1), &generator,  saveFreq, NULL);
	}

}

