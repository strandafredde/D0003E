#include <avr/io.h>
#include <stdio.h>
#include "trafficLights.h"
#include "TinyTimber.h"
#include "Gui.h"
#include "USART_Receive.h"
#include <avr/interrupt.h>

#define BAUD 9600
#define F_CPU 8000000UL
#define UBRR_VALUE (F_CPU / (BAUD * 16UL) )

// - creation of inits.
guiClass GUI = initGUI(NULL); // (pos)
Bridge B = initBridge(&GUI, 1); // (gui, direction)
USART_Receive UR = USART_ReceiveInit(&B);

void USART_init(void){
	// - Set baud rate prescaler.
	UBRR0H = (UBRR_VALUE >> 8);
	UBRR0L = UBRR_VALUE;
	// - Enable receiver and transmitter
	UCSR0B |= (1 << RXEN0) | (1 << TXEN0) | (1<<RXCIE0);
	// - Set frame format: 8 data bits, no parity, 1 stop bit.
	UCSR0C |= (1 << UCSZ01) | (1 << UCSZ00);
}


// - handles input data from simulation.



int main() {
	USART_init(); // - initiate USART settings.
	LCD_init(&GUI); // - initiate LCD.
	INSTALL(&B, UR, USART0_RX_vect);
	TINYTIMBER(&B, init, NULL);

}
// int main(){
// 	USART_init();
// 	LCD_init();
// 	
// 	while (!(UCSR0A & (1 << RXC0)));
// 	volatile uint8_t data = UDR0;
// 	if(data == 0b0001) {
// 		async()
// 	}
// }

			
	
