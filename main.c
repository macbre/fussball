/*
 * main.c
 *
 *  Created on: 2014-07-31
 *      Author: macbre
 */
#include <avr/io.h>
#include <util/delay.h>
#include <avr/pgmspace.h>

#include "macros.h"

// setuo
#define RS_BAUD 115200

// libraries
#include "lib/led.h"
#include "lib/rs.h"

// flash memory strings
const char HELLO_MESSAGE[] PROGMEM =  "# Hi!\r\n" \
	"# " __DATE__ " " __TIME__ "\r\n" \
	"# avr-gcc v" __AVR_LIBC_VERSION_STRING__ " (" __AVR_LIBC_DATE_STRING__ ")\r\n";

void init() {
	led_init();
	led_startup();

	rs_init(RS_BAUD);
	rs_text_P(HELLO_MESSAGE);
}

int main() {
	init();

	for(;;) {
		sbi(PORTB, 1);
		_delay_ms(500);

		cbi(PORTB, 1);
		_delay_ms(5);
	}
}

