//
// Created by Justin Gavrell on 2023-04-08.
//
#include "trafficLights.h"
#include "Gui.h"
#include "USART_Receive.h"
#include <avr/io.h>

// - handles input data from simulation.
uint8_t USART_Receive2() {

    // - Wait for data to be received in buffer.
    while(!(UCSR0A & (1<<RXC0)));

    // - Make received input data from buffer 8 bit length for comparing.
    volatile uint8_t input = UDR0;

    return input;

}


void USART_Transmit(unsigned char data) {
    // - Transmit light status to simulation.
    while(!(UCSR0A & (1<<UDRE0)));
    UDR0 = data;
}