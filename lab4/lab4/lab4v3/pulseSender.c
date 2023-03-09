/*
 * pulseSender.c
 *
 * Created: 2023-03-05 11:08:17
 *  Author: stran
 */

#include <avr/io.h>
#include <stdint.h>

#include "pulseSender.h"


void sendPulse(pulseSender *self, uint8_t pin){

    //Invert bit at position pin
    PORTE ^= 0x1 << pin;
}   

void resetPin(pulseSender *self, uint8_t pin) {
    PORTE &= ~(0x1 << pin);
}