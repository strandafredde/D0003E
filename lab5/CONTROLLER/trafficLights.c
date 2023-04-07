/*
 * trafficLights.c
 *
 * Created: 2023-03-13 13:27:11
 *  Author: stran
 */ 
#include <stdbool.h>
#include "trafficLights.h"

void updateNorth(trafficLights *self) {
	self->northQueue += 1;
	ASYNC(self, printCars, NULL);
}

void updateSouth(trafficLights *self) {
	self->southQueue += 1;
	ASYNC(self, printCars, NULL);
}
void updateLights(trafficLights *self) {
	if(self->direction == southGreen) {
		// 
	}
	if(self->direction == northGreen) {
		//
	}
}

void enterSouth(trafficLights *self) {
	self->southQueue -= 1;
	self->onBridge += 1;
	AFTER(SEC(5), carDestroy, NULL);
	ASYNC(self, printCars, NULL);
}

void enterNorth(trafficLights *self) {
	self->northQueue -= 1;
	self->onBridge += 1;
	AFTER(SEC(5), carDestroy, NULL);
	ASYNC(self, printCars, NULL);
}

void carsEnter(trafficLights *self) {
	while(1) {
		// South side
		if(self->direction == southGreen) {
			if(self->southQueue == 0 && self->onBridge == 0) {
				self->direction == northGreen;
			}
			else {
				AFTER(SEC(1), self, enterSouth, NULL);
			}
		}
		// North side
		if(self->direction == northGreen) {
			if(self->northQueue == 0 && self->onBridge == 0) {
				self->direction == southGreen;
			}
			else {
				ASYNC(SEC(1), self, enterNorth, NULL);
			}
		}
	}

}

void carDestroy(trafficLights *self) {
	if(self->onBridge > 0) {
		self->onBridge -= 1;
		ASYNC(self, printCars, NULL);
	}
}


void printCars(trafficLights *self) {
	printAt(self->southQueue,0);
	printAt(self->onBridge,2);
	printAt(self->northQueue,4);
}