/*
 * pulseSender.h
 *
 * Created: 2023-03-05 11:08:17
 *  Author: stran
 */



#ifndef _PULSESENDER_
#define _PULSESENDER_

#include <stdint.h>

#include "TinyTimber.h"
#include "Gui.h"

typedef struct {
    Object super;
} pulseSender;

#define initPulseSender() {initObject()}

void sendPulse(pulseSender *self, uint8_t pin);

void resetPin(pulseSender *self, uint8_t pin);

#endif /* PULSESENDER_H_ */