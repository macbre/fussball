/*
 * main.c
 *
 *  Created on: 2014-07-31
 *      Author: macbre
 */
#include <avr/io.h>
#include <util/delay.h>
#include "macros.h"

// libraries
#include "lib/led.h"

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
