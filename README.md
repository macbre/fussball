fussball
========

IR-based goal system for football tables

## Electronics

<img src="https://raw.githubusercontent.com/macbre/fussball/master/schematics/main.png" />

* 2x LTE4206 (emitters)
* 2x IR photodiodes + TL082 (detectors)
* 2x white LEDs (goal indicators)
* ATmega16 uC (measures the time of ball passing and sends the data over RS232)

## Software

### Requirements

Linux AVR tools chain:

```
aptitude install eagle avrdude gcc-avr avr-libc
```

### Compiling and building

```
make
```
