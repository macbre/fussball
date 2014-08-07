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
#include "lib/led.h"
#include "lib/rs.h"

// flash memory strings
const char HELLO_MESSAGE[] PROGMEM =  "# Hi!\r\n" \
	"# " __DATE__ " " __TIME__ "\r\n" \
	"# avr-gcc v" __AVR_LIBC_VERSION_STRING__ " (" __AVR_LIBC_DATE_STRING__ ")\r\n";

// set up interrupts from IR detectors
void detectors_init() {
	// INT0 - PD2
	// Any logical change on INT0 generates an interrupt request
	MCUCR |= (1 << ISC00);

	// allow INT0 interrupt
	GICR |= (1 << INT0);
}

SIGNAL(SIG_INTERRUPT0) {
	unsigned char value = PIND & (1 << 2); // INT0 - PD2

	// value === 0 - detecttor "closed" -> obstacle detected
	// value > 0 - detecttor "open" -> no obstacle
	rs_send('!');
	rs_send('1');
	rs_send(':');
	rs_text(value == 0 ? "closed" : "open");
	rs_send('\r');
	rs_send('\n');

	if (value == 0) {
		led_on(LED1);
	}
	else {
		led_off(LED1);
	}
}

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

