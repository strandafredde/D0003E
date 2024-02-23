/*
 * controllerHandler.h
 *
 * Created: 2023-03-13 13:26:48
 *  Author: stran
 */ 



#ifndef CONTROLLERHANDLER_H_
#define CONTROLLERHANDLER_H_

#include "TinyTimber.h"
#include "trafficLights.h"

typedef struct {
    Object super;
    Bridge *bridge;
} ControllerHandler;

#define initControllerHandler(bridge) {initObject(),bridge}
void dataHandler(ControllerHandler *self);
void initiate(ControllerHandler *self);

#endif /* CONTROLLERHANDLER_H_ */
