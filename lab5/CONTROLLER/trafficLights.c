
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
	if(self->onBridge < 5) {
		if(self->direction == southGreen && self->southQueue > 0) {
			USART_Transmit(0b0100);

			
		}
		if(self->direction == northGreen && self->northQueue > 0) {
			USART_Transmit(0b0001);

			
		}
		
	}
	AFTER(SEC(1), self, carsEnter, NULL);





    // checks status of lights and permits or denies cars entry on bridge.
		// South side

		/*
		if(self->direction == southGreen && self->onBridge == 0) {
			if(self->southQueue == 0) {
                // no cars in south queue, switch lights.
				self->direction = northGreen;
				USART_Transmit(0b0001);
				USART_Transmit(0b1000);
			}
			else {
				USART_Transmit(0b0100);
				AFTER(SEC(1), self, enterSouth, NULL);
				
			}
		}
		// North side
		if(self->direction == northGreen && self->onBridge == 0) {
			if(self->northQueue == 0) {
                // no cars in north queue, switch lights.
				self->direction = southGreen;
				USART_Transmit(0b0100);
				USART_Transmit(0b0010);
			}
			else {
				USART_Transmit(0b0001);
				AFTER(SEC(1), self, enterNorth, NULL);
				
			}
		}

        AFTER(SEC(1), self, carsEnter, NULL); // - transmit light status to simulation.
		*/
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