/*
 * trafficLights.h
 *
 * Created: 2023-03-13 13:26:48
 *  Author: stran
 */ 


#ifndef TRAFFICLIGHTS_H_
#define TRAFFICLIGHTS_H_
#include <stdbool.h>

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

#endif /* TRAFFICLIGHTS_H_ */