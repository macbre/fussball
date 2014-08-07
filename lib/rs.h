#include <stdlib.h>
#include <avr/pgmspace.h>

// calculaye UBBR value from baud rate (in bps)
#define USART_BAUDRATE(br) (F_CPU/1000*125/br-1)

// initialize USART communication
void rs_init(unsigned long);

// send data (blocking mode)
void rs_send(unsigned char);

// send a string
void rs_text(char[]);

// send a PGM string (from program memory, i.e. flash)
void rs_text_P(PGM_P);

// send an integer
void rs_int(int);
