#include <avr/io.h>

#include "rs.h"

// initialize USART communication
void rs_init(unsigned long rate) {
	// Baud rate selection
	UBRRH = (unsigned char) (USART_BAUDRATE(rate) >> 8);
	UBRRL = (unsigned char) USART_BAUDRATE(rate);

	// USART setup (p. 151)
	UCSRA = (1<<U2X);                // enable double speed
	UCSRB = (1<<RXEN) | (1<<TXEN);   // enable receiver and transmitter
	UCSRC = (1<<URSEL) | (1<<UCSZ1) | (1<<UCSZ0);  // asynchronous mode, 8N1

	return;
}

// send data (blocking mode)
void rs_send(unsigned char data) {
	// wait for empty send buffer
	while ( !( UCSRA & (1<<UDRE)) );

	// send data
	UDR = data;
}

// send a string
void rs_text(char txt[]) {
	unsigned char c;

	while( (c = *(txt++)) != 0x00 ) {
		rs_send(c);
	}
}

// send a PGM string (from program memory, i.e. flash)
void rs_text_P(PGM_P txt) {
	unsigned char c;

	while ((c = pgm_read_byte(txt++))) {
		rs_send(c);
	}
}

// send an integer
void rs_int(int value) {
	char buf[8];
	rs_text( itoa(value, buf, 10) );
}
