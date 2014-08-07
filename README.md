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
apt-get install eagle avrdude gcc-avr avr-lib gtkterm
```

### Compiling and building

```
make
```

### Serial communication

> Serial communication runs at the speed of 115200 bps (8N1)

```
gtkterm --port /dev/ttyS0 --speed 115200 --bits 8 --stopbits 1 --parity none
 ```

#### Messages

* Diagnostic messages (with leading ``#``)

```
# Hi!
# Aug  7 2014 11:11:41
# avr-gcc v1.7.1 (20110216)
```

* Time measurements

```
!<detector ID>:<time in ms>
!1:124
!2:98
```

