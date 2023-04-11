/*
 * Gui.h
 *
 * Created: 2023-03-13 13:19:10
 *  Author: stran
 */ 

#ifndef GUI_H_
#define GUI_H_

#include <stdbool.h>
#include <stdint.h>
#include "TinyTimber.h"

typedef struct {
  Object super;
  uint8_t pos;
} guiClass;



void LCD_init(guiClass *self);

void printAt(uint8_t num, int pp);

#define initGUI(pos) {initObject(), pos}
	
#endif