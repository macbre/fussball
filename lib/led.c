#include <util/delay.h>
#include "led.h"

void led_init() {
	sbi(DDR(LED_PORT), LED1); // LED1 as output
	sbi(DDR(LED_PORT), LED2); // LED2 as output
}

void led_startup() {
	// on
	led_on(LED1);
	led_on(LED2);

	_delay_ms(500);

	// off
	led_off(LED1);
	led_off(LED2);
}

void led_on(unsigned char led) {
	cbi(PORTB, led);
}

void led_off(unsigned char led) {
	sbi(PORTB, led);
}
