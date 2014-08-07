#include <avr/io.h>
#include <avr/interrupt.h>

#include "detectors.h"
#include "led.h"
#include "rs.h"

volatile unsigned long timer_detector_1 = 0;

// set up interrupts from IR detectors
void detectors_init() {
	// INT0 - PD2
	// Any logical change on INT0 generates an interrupt request
	MCUCR |= (1 << ISC00);

	// allow INT0 interrupt
	GICR |= (1 << INT0);

	// Timer Overflow
	TIMSK |= (1 << TOIE0);               // Timer/Counter0 Overflow Interrupt Enable
	//TCCR0 |= (1 << CS00) + (1 << CS02);  // prescaler at CK/1024
	TCCR0 |= (1 << CS01) + (1 << CS00);  // prescaler at CK/32

	timer_reset();
}

void timer_reset() {
	// so let's "wait" 1ms
	// 1 ms = 1000 us (16 000 CPU ticks / 1024 => 15.625 timer ticks)
	// 1 ms = 1000 us (16 000 CPU ticks / 32 => 500 timer ticks)
	// 20 ticks -> 50 us
	TCNT0  = 255 - 20;
}

// run each time TCNT0 reaches the value of 255
// increase detectors timers every 50 us
SIGNAL(SIG_OVERFLOW0) {
	timer_detector_1++;
	timer_reset();
}

// edge detection for detector 1
SIGNAL(SIG_INTERRUPT0) {
	// INT0 - PD2
	if ((PIND & (1 << 2)) == 0) {
		// detecttor "closed" -> obstacle detected
		led_on(LED1);

		// let's start the timer
		timer_detector_1 = 0;
	}
	else {
		// detecttor "open" -> no obstacle
		led_off(LED1);

		timer_detector_1 *= 5; // scale to 10 us

		// !<detector ID>:<time in ms>
		rs_send('!');
		rs_send('1');
		rs_send(':');
		rs_long(timer_detector_1); // scale to 1 us
		rs_send('0');
		rs_send('\r');
		rs_send('\n');
	}
}
