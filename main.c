/*
 * main.c
 *
 *  Created on: 2014-07-31
 *      Author: macbre
 */
#include <avr/io.h>
#include <avr/pgmspace.h>
#include <avr/interrupt.h>
#include <util/delay.h>

#include "macros.h"

// setuo
#define RS_BAUD 115200

// libraries
#include "lib/detectors.h"
#include "lib/led.h"
#include "lib/rs.h"

// flash memory strings
const char HELLO_MESSAGE[] PROGMEM =  "# Hi!\r\n" \
	"# " __DATE__ " " __TIME__ "\r\n" \
	"# avr-gcc v" __AVR_LIBC_VERSION_STRING__ " (" __AVR_LIBC_DATE_STRING__ ")\r\n";

void init() {
	rs_init(RS_BAUD);
	rs_text_P(HELLO_MESSAGE);

	led_init();
	led_startup();

	detectors_init();
}

int main() {
	// enable interrupts
	sei();

	init();

	for(;;);
}

