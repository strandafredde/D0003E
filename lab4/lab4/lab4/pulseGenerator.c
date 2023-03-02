/*
 * pulseGenerator.h
 *
 * Created: 2023-03-01 12:08:03
 *  Author: stran
 */ 
#include "TinyTimber.h"
#include "Gui.h"

typedef struct {
	Object super;
	int side;
	long freq;
	long savedFreq;
	guiClass *gui;
}pulseGenerator;

void changeFreqUp(pulseGenerator *self){
	self->freq += 1;
}

void changeFreqDown(pulseGenerator *self){
	/*	Depending on the side chosen ( which generator)
		update the frequency shown on the display. */
	if (self->freq > 0){
		self->freq -= 1;
		if(self->side == 0) {
			ASYNC(self->gui, printAt, self->savedFreq);
		}
		if(self->side == 1) {
			ASYNC(self->gui, printAt, self->savedFreq);
		}
		
	}
}

void saveFreq(pulseGenerator *self) {
	if (self->savedFreq > 0) {
		self->savedFreq = self->freq;
		self->freq = 0;
	}
	else {
		self->freq = self->savedFreq;
	}
}