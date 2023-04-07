// #include <avr/io.h>
// #include <stdio.h>
// 
// #define BAUD 9600
// #define F_CPU 8000000UL
// #define UBRR_VALUE (F_CPU / (BAUD * 16UL) )
// 
// void USART_Transmit(unsigned char data) {
// 	// Wait for empty transmit buffer
// 	while(!(UCSR0A & (1<<UDRE0)));
// 	// Put data into buffer, sends the data
// 	UDR0 = data;
// }
// 
// unsigned char USART_Receive(void) {
// 	// Wait for data to be received
// 	while(!(UCSR0A & (1<<RXC0)));
// 	// Get and return received data from buffer
// 	return UDR0;
// }
// 
// int main()
// {
// 	unsigned int ubrr = UBRR_VALUE;
// 	// Set BAUD Rate
// 	UBRR0H = (UBRR_VALUE>>8);
// 	UBRR0L = (UBRR_VALUE);
// 	// Enable transmitter and receiver
// 	UCSR0B = (1<<RXEN0)|(1<<TXEN0)|(1<<RXCIE0);
// 	// Set frame format: 8data, 1stop bit
// 	UCSR0C = (0<<USBS0)|(1<<UCSZ00)|(1<<UCSZ01);
// 	
// 	while(1) {
// 		unsigned char data = USART_Receive();
// 		USART_Transmit(data);
// 	}
// 	return 0;
// }