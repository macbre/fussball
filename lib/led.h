#include "../macros.h"

#define LED_PORT PORTB
#define LED1 1
#define LED2 0

void led_init();
void led_startup();

void led_on(unsigned char);
void led_off(unsigned char);

