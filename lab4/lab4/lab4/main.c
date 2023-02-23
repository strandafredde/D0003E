/*
 * lab4.c
 *
 * Created: 2023-02-23 10:03:44
 * Author : stran
 */ 

#include <avr/io.h>
#include "Gui.h"

int main(void) {
	//Initialize button
	
	LCD_init();
	button();
	//LCDDR0 |= 0x04; // 1
	//LCDDR0 |= 0x40; // 2
// 	printAt(4,0);
// 	printAt(7,4);
	
}

