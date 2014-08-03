/*
 * main.c
 *
 *  Created on: 2014-07-31
 *      Author: macbre
 */
#include "main.h"

void led_init() {
	sbi(DDR(PORTB), 1); // LED1 as output
	sbi(DDR(PORTB), 0); // LED2 as output
}

void led_startup() {
	// on
	cbi(PORTB, 1);
	cbi(PORTB, 0);

	_delay_ms(500);

	// off
	sbi(PORTB, 1);
	sbi(PORTB, 0);
}

int main() {
	led_init();
	led_startup();

	for(;;) {
		sbi(PORTB, 1);
		_delay_ms(500);

		cbi(PORTB, 1);
		_delay_ms(5);
	}
}
