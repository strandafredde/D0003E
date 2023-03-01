#include <stdbool.h>

#define SCC_0  0x1551
#define SCC_1  0x2080
#define SCC_2  0x1E11
#define SCC_3  0x1B11
#define SCC_4  0x0B50
#define SCC_5  0x1B41
#define SCC_6  0x1F41
#define SCC_7  0x0111
#define SCC_8  0x1F51
#define SCC_9  0x0B51

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
