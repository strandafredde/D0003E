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

void printAt(guiClass *self, uint8_t num);

void generatorChange(guiClass *self);

#define initGUI(pos) {initObject(), pos}
	
#endif