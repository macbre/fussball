#include <avr/io.h>
#include <avr/interrupt.h>

#include "led.h"
#include "rs.h"

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
