#include <avr/io.h>
#include <util/delay.h>

// helper macros
#define cbi(sfr, bit) (_SFR_BYTE(sfr) &= ~(1<<bit))
#define sbi(sfr, bit) (_SFR_BYTE(sfr) |= (1<<bit))

// set the pin direction and pull-up/down
#define DDR(x) (_SFR_IO8(_SFR_IO_ADDR(x)-1))
#define PIN(x) (_SFR_IO8(_SFR_IO_ADDR(x)-2))

#define nop() __asm__ __volatile__ ("nop")
