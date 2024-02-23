/*
 * trafficLights.h
 *
 * Created: 2023-03-13 13:26:48
 *  Author: stran
 */ 


#ifndef BRIDGE_H_
#define BRIDGE_H_
#include <stdbool.h>
#include "Gui.h"

#include "TinyTimber.h"

#define northGreen 0
#define southGreen 1

typedef struct {
	Object super;

    // - Direction control.
	int direction;
	int northQueue;
	int southQueue;

    // - Bridge setting control.
	int onBridge;
	int lockBridge;
	
} Bridge;

#define initBridge() {initObject(), 1, 0, 0, 0, 0}
	
// - arrival of cars.
void SouthboundArrival(Bridge *self);
void NorthboundArrival(Bridge *self);

// - Bridge entry of cars.
void enterSouth(Bridge *self);
void enterNorth(Bridge *self);

// - Light check and permission setting.
void carsEnter(Bridge *self);

// - Car demolition.
void carDestroy(Bridge *self);

// - LCD car and light writing.
void printCars(Bridge *self);

void transmit_lights(Bridge *self);
// - transmits pattern for traffic light status to simulation.

void init(Bridge *self);
#endif /* BRIDGE_H_ */