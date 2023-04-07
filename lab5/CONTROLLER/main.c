#include <avr/io.h>
#include <stdio.h>
#define BAUD 9600
#define F_CPU 8000000UL
#define UBRR_VALUE (F_CPU / (BAUD * 16UL) )

void USART_init(void)
{	// Set baud rate prescaler
	UBRR0H = (UBRR_VALUE >> 8);
	UBRR0L = UBRR_VALUE;
	// Enable receiver and transmitter
	UCSR0B |= (1 << RXEN0) | (1 << TXEN0);
	// Set frame format: 8 data bits, no parity, 1 stop bit
	UCSR0C |= (1 << UCSZ01) | (1 << UCSZ00);
}

unsigned char USART_Receive(void) {
	// Wait for data to be received
	while(!(UCSR0A )); // & (1<<RXC0)
	// Get and return received data from buffer
	volatile uint8_t data = UDR0;
	if (UDR0 == 0b0001) {
		writeChar('1',1);
	}
}

int main(){
	UBRR0H = (UBRR_VALUE>>8);
	UBRR0L = (UBRR_VALUE);
	// Enable transmitter and receiver
	UCSR0B = (1<<RXEN0)|(1<<TXEN0)|(1<<RXCIE0);
	// Set frame format: 8data, 1stop bit
	UCSR0C = (1<<UCSZ00)|(1<<UCSZ01); // (0<<USBS0)|
	LCD_init();
	
	USART_Receive();
	writeChar('1',5);
			
	

// 	unsigned int ubrr = UBRR_VALUE;
// 	
	// Set BAUD Rate

	
// 	while(1) {
//         unsigned char data = USART_Receive();
//         USART_Transmit(data);
// 		}	
//         return 0;
}