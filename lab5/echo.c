// /*
//  * echo.c
//  *
//  * Created: 2023-03-14 12:08:36
//  *  Author: stran
//  */ 
// #include <avr/io.h>
// #include <stdio.h>
// 
// #define BAUD 9600
// #define F_CPU 8000000
// #define UBRR_VALUE ((F_CPU / (BAUD * 16UL)) - 1)
// 
// int main()
// {
// 	int i = 0;
// 	unsigned int ubrr = UBRR_VALUE;
// 	
// 	// Set BAUD Rate
// 	UBRR0H = (UBRR_VALUE>>8);
// 	UBRR0L = (UBRR_VALUE);
// 	// Enable transmitter and receiver
// 	UCSR0B = (1<<RXEN0)|(1<<TXEN0)|(1<<RXCIE0);
// 	// Set frame format: 8data, 1stop bit
// 	UCSR0C = (0<<USBS0)|(1<<UCSZ00)|(1<<UCSZ01);
// 	
// 	while(1) {
// 		while (!( UCSR0A & (1<<UDRE0)));
// 		UDR0 = 5;
// 	}
// }