/*
 * InputHandler.h
 *
 * Created: 2023-03-01 11:46:02
 *  Author: stran
 */ 

#include "TinyTimber.h"
#include "pulseGenerator.h"
#include "Gui.h"

#ifndef INPUTHANDLER_H_
#define INPUTHANDLER_H_

typedef struct {
	Object super;
	guiClass *gui;
	pulseGenerator *p1;
	pulseGenerator *p2;
	}InputHandler;
	
#define initInputHandler(gui, p1, p2) \
		{initObject(), gui, p1, p2}

void joystickLeftRight(InputHandler *self);
void joystickUpDownCenter(InputHandler *self);



#endif /* INPUTHANDLER_H_ */