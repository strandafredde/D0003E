#ifndef GUI_H_
#define GUI_H_



#include <stdbool.h>

void LCD_init();
void writeChar(char ch, int pos);
bool is_prime(long i);
void printAt(long num, int pos);

typedef struct {
	Object super;
}guiClass;


void printAt(long num, int pos);
void generatorChange(int *side);
void LCD_init();
#define initguiClass() \
{initObject()}

#endif /* GUI_H_ */