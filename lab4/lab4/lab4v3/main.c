/*
 * lab4.c
 *
 * Created: 2023-02-23 10:03:44
 * Author : stran
 */ 

#include <avr/io.h>

#include "Gui.h"
#include "InputHandler.h"
#include "pulseGenerator.h"
#include "pulseSender.h"
#include "TinyTimber.h"


pulseSender pSender = initPulseSender();
pulseGenerator pGen[] = {initPulseGen(4), initPulseGen(6)};
guiClass gui[] = {initGUI(0), initGUI(4)};
inputHandler handler = initInputHandler();



int main(void){	
	
	
	pGen[0].pSender = &pSender;
	pGen[1].pSender = &pSender;
	pGen[0].gui = &gui[0];
	pGen[1].gui = &gui[1];

    handler.pGen[0] = &pGen[0];
	handler.pGen[1] = &pGen[1];
    handler.gui[0] = &gui[0];
	handler.gui[1] = &gui[1];
	
	INSTALL(&handler, joystickUpDownCenter, IRQ_PCINT1);
	INSTALL(&handler, joystickLeftRight, IRQ_PCINT0);
	
	TINYTIMBER(&handler, initialize, NULL);
}

