
#include <stdbool.h>
#include "trafficLights.h"
#include "TinyTimber.h"
#include <avr/io.h>

void NorthboundArrival(Bridge *self) {
    // adds car to the northbound bridge queue.
	writeChar('1',1);
	self->northQueue += 1;
	ASYNC(self, printCars, NULL);
}

void SouthboundArrival(Bridge *self) {
    // adds car to the southbound bridge queue.
	self->southQueue += 1;
	ASYNC(self, printCars, NULL);
}

void enterSouth(Bridge *self) {
    // Creates car event on bridge from south
    self->southQueue -= 1;
    self->onBridge += 1;
    AFTER(SEC(5), self, carDestroy, NULL); // 5 sec to cross bridge
    ASYNC(self, printCars, NULL);
}

void enterNorth(Bridge *self) {
    // Creates car event on bridge from north
    self->northQueue -= 1;
    self->onBridge += 1;
    AFTER(SEC(5), self, carDestroy, NULL); // 5 sec to cross bridge
    ASYNC(self, printCars, NULL);
}

void carsEnter(Bridge *self) {
    // checks status of lights and permits or denies cars entry on bridge.
	while(1) {
		// South side
		if(self->direction == southGreen && self->onBridge == 0) {
			if(self->southQueue == 0) {
                // no cars in south queue, switch lights.
				self->direction = northGreen;
			}
			else {
				AFTER(SEC(1), self, enterSouth, NULL);
			}
		}
		// North side
		if(self->direction == northGreen && self->onBridge == 0) {
			if(self->northQueue == 0) {
                // no cars in north queue, switch lights.
				self->direction = southGreen;
			}
			else {
				AFTER(SEC(1), self, enterNorth, NULL);
			}
		}

        ASYNC(self, transmit_lights, NULL);
	}

}

void transmit_lights(Bridge *self){
    // - transmits pattern for traffic light status to simulation.

    if(self->direction == southGreen) // - transmit binary pattern for south light green.
    {
        UDR0 = 0b0110; // - write to serial
        return;
    }
    if(self->direction == northGreen) // - transmit binary pattern for north light green.
    {
        UDR0 = 0b0110; // - write to serial
        return;
    }
}

void carDestroy(Bridge *self) {
    // demolishes car from simulation
	if(self->onBridge > 0) {
		self->onBridge -= 1;
		ASYNC(self, printCars, NULL);
	}
}

void init(Bridge *self) {
	printAt(self->southQueue,0);
 	printAt(self->onBridge,2);
	printAt(self->northQueue,4);
	

}

void printCars(Bridge *self) {
    // prints cars in queue and on bridge to LCD-display.
	printAt(self->southQueue,0);
	printAt(self->onBridge,2);
	printAt(self->northQueue,4);
}