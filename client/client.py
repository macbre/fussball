import serial
import time

ser = serial.Serial('/dev/pts/1', 19200)

try:
    print "To exit press Ctrl^C..."
    while True:
        if ser.readable() is True:
            ser.flushInput()
            read = ser.readline()
            print(read)
            time.sleep(.01)
        else:
            ser.close()
            raise IOError("Port not readable.")
except KeyboardInterrupt:
    ser.close()
    print "Exit."
except ValueError:
    print "Oops! Invalid parameter. Try again..."
except serial.SerialException:
    print "Oops! Can't find or configure the device..."
