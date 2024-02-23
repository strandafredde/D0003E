#include "controllerHandler.h"
#include "trafficLights.h"
#include "Gui.h"
#include "USART_Receive.h"
#include <avr/io.h>
#include <stdio.h>
#include "TinyTimber.h"

void dataHandler(ControllerHandler *self) {
    uint8_t input = USART_Receive2();

    if (input & 0b00000010) // - car enters bridge northbound.
    {
        ASYNC(self->bridge, enterNorth, NULL); // - Add queueing car to bridge.
        AFTER(SEC(5), self->bridge, carDestroy, NULL);
    }
    if (input & 0b00001000) // - car enters bridge southbound.
    {
        ASYNC(self->bridge, enterSouth, NULL); // - Add queueing car to bridge.
        AFTER(SEC(5), self->bridge, carDestroy, NULL);
    }
    if (input & 0b00000001) // - car enters queue northbound.
    {
        ASYNC(self->bridge, NorthboundArrival, NULL); // - Add arriving car to queue.
    }
    if (input & 0b00000100) // - car enters queue southbound.
    {
        ASYNC(self->bridge, SouthboundArrival, NULL); // - Add arriving car to queue.
    }

}

void initiate(ControllerHandler *self) {
    ASYNC(self->bridge, carsEnter, NULL);
}