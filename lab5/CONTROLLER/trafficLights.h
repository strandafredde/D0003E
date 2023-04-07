/*
 * trafficLights.h
 *
 * Created: 2023-03-13 13:26:48
 *  Author: stran
 */ 


#ifndef TRAFFICLIGHTS_H_
#define TRAFFICLIGHTS_H_
#include <stdbool.h>

#define northGreen 0
#define southGreen 1

typedef struct {
	Object super;
	guiClass gui;
	int direction;
	int northQueue;
	int southQueue;
	int onBridge;
	int lockBridge;
	
} trafficLights;


#define initTrafficLights(pos) {initObject(), gui, direction}
	
void printCars(trafficLights *self);
void updateSouth(trafficLights *self)
void updateNorth(trafficLights *self) 

#endif /* TRAFFICLIGHTS_H_ */