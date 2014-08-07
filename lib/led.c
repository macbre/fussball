#include <util/delay.h>
#include "led.h"

void led_init() {
	sbi(DDR(LED_PORT), LED1); // LED1 as output
	sbi(DDR(LED_PORT), LED2); // LED2 as output
}

void led_startup() {
	// on
	cbi(PORTB, LED1);
	cbi(PORTB, LED2);

	_delay_ms(500);

	// off
	sbi(PORTB, LED1);
	sbi(PORTB, LED2);
}
