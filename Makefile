# Fussball makefile
all: compile write

compile: main.c
	avr-gcc -mmcu=atmega16 -Os -DF_CPU=16000000UL -Wall main.c -o main.o
	avr-objcopy -O ihex main.o hex.hex

write: hex.hex
	sudo avrdude -c usbasp -p m16 -e -U flash:w:hex.hex

clean:
	rm -f main.o hex.hex

.PHONY: all clean
