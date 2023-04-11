//
// Created by Justin Gavrell on 2023-04-08.
//
#include "trafficLights.h"
#include "Gui.h"
#include "USART_Receive.h"
#include <avr/io.h>

// - handles input data from simulation.
ISR(USART_RX_vect) {
void USART_Receive(Bridge *b) {

    // - Wait for data to be received in buffer.
    while(!(UCSR0A & (1<<RXC0)));

    // - Make received input data from buffer 8 bit length for comparing.
    volatile uint8_t input = UDR0;

    if (input & 0b0011) // - car enters bridge northbound.
    {
        ASYNC(&b, enterNorth, NULL); // - Add queueing car to bridge.
        return;
    }
    if (input & 0b1100) // - car enters bridge southbound.
    {
        ASYNC(&b, enterSouth, NULL); // - Add queueing car to bridge.
        return;
    }
    if (input & 0b0001) // - car enters queue northbound.
    {
        ASYNC(&b, NorthboundArrival, NULL); // - Add arriving car to queue.
        return;
    }
    if (input & 0b0100) // - car enters queue southbound.
    {
        ASYNC(&b, SouthboundArrival, NULL); // - Add arriving car to queue.
        return;
    }

}
}