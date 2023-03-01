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
#include "TinyTimber.h"
int main(void) {
	//Initialize button
	LCD_init();
	
	guiClass gui = initguiClass();
	pulseGenerator p1 = initPulseGenerator(0, 0, 0, gui);
	pulseGenerator p2 = initPulseGenerator(0, 0, 0, gui);
	InputHandler hand = initInputHandler(gui, p1, p2);

	
}

