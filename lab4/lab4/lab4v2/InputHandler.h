/*
 * InputHandler.h
 *
 * Created: 2023-03-01 11:46:02
 *  Author: stran
 */ 


#ifndef INPUTHANDLER_H_
#define INPUTHANDLER_H_


#include "TinyTimber.h"
#include "Gui.h"
#include "pulseGenerator.h"
#include <stdbool.h>

typedef struct inputHandler {
  Object super;
  pulseGenerator *pGen[2];
  guiClass *gui[2];
  int current;
  bool press;
} inputHandler;

#define initInputHandler() {initObject(), NULL, NULL, 0, true}

void initialize(inputHandler *self);

void joystickUpDownCenter(inputHandler *self);

void joystickLeftRight(inputHandler *self);

void bounce(inputHandler *self);

#endif /* INPUTHANDLER_H_ */