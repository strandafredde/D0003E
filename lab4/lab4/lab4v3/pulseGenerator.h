/*
 * pulseGenerator.h
 *
 * Created: 2023-03-01 12:08:17
 *  Author: stran
 */ 

#ifndef PULSEGENERATOR_H_
#define PULSEGENERATOR_H_


#include <stdint.h>
#include "pulseSender.h"
#include "TinyTimber.h"

typedef struct {
    Object super;
    uint8_t pin;
    uint8_t freq;
    uint8_t savedFreq;
    pulseSender *pSender;
    guiClass *gui;
} pulseGenerator;

#define initPulseGen(pin) {initObject(), pin, 1, 0, NULL, NULL}

void generatePulse(pulseGenerator *self);
void changeFreqUp(pulseGenerator *self);
void changeFreqDown(pulseGenerator *self);
void saveFreq(pulseGenerator *self);


#endif /* PULSEGENERATOR_H_ */