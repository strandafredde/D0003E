/*
 * pulseGenerator.h
 *
 * Created: 2023-03-01 12:08:17
 *  Author: stran
 */ 
#ifndef PULSEGENERATOR_H_
#define PULSEGENERATOR_H_


#include "TinyTimber.h"


typedef struct {
	Object super;
	int side;
	long freq;
	long savedFreq;
	guiClass *gui;
}pulseGenerator;

#define initPulseGenerator(side, freq, savedFreq, gui) \
{initObject(), side, freq, savedFreq, gui}

void changeFreqUp(pulseGenerator *self);
void changeFreqDown(pulseGenerator *self);
void saveFreq(pulseGenerator *self);







#endif /* PULSEGENERATOR_H_ */