
#include <stdbool.h>
#include "trafficLights.h"
#include "TinyTimber.h"
#include <avr/io.h>

void NorthboundArrival(Bridge *self) {
    // adds car to the northbound bridge queue.
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
    // AFTER(SEC(5), self, carDestroy, NULL); // 5 sec to cross bridge
    ASYNC(self, printCars, NULL);
}



void enterNorth(Bridge *self) {
    // Creates car event on bridge from north
    self->northQueue -= 1;
    self->onBridge += 1;
    // AFTER(SEC(5), self, carDestroy, NULL); // 5 sec to cross bridge
    ASYNC(self, printCars, NULL);
}

void carsEnter(Bridge *self) {
    // Allow up to 5 cars from the current direction to enter the bridge
    if(self->onBridge < 5 && self->carsPassed <= 5) {
        if(self->direction == southGreen && self->southQueue > 0) {
            printf(self->carsPassed);
			self->carsPassed++;
            USART_Transmit(0b0100);
 
        }
        if(self->direction == northGreen && self->northQueue > 0) {
			self->carsPassed++;
            printf(self->carsPassed);
            USART_Transmit(0b0001);

        }
    }

    // If 5 cars have passed or no more cars in current direction, switch direction
    if (self->carsPassed >= 5 || (self->direction == southGreen && self->southQueue == 0) || (self->direction == northGreen && self->northQueue == 0)) {
        if(self->onBridge==0 ) {
            if(self->direction == southGreen) {
                self->direction = northGreen;
            } else if(self->direction == northGreen) {
                self->direction = southGreen;
            }
            self->carsPassed = 0; // Reset the count of cars passed
        }
    }

    // If no cars on the bridge and no cars in queue in current direction, switch direction
    if(self->onBridge==0 ) {
        if(self->direction == southGreen && self->southQueue == 0) {
            self->direction = northGreen;
        }
        if(self->direction == northGreen && self->northQueue == 0) {
            self->direction = southGreen;
        }
    }

    AFTER(SEC(1), self, carsEnter, NULL);
}
	

void carDestroy(Bridge *self) {
    // demolishes car from simulation
	if(self->onBridge > 0) {
		self->onBridge -= 1;
		ASYNC(self, printCars, NULL);
	}
}

void init(Bridge *self) {
	// initiates bridge and starts car event.
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