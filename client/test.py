import serial
import kbhit
import time
from random import randint


def write_fake_msg(ser):
    """Writes random ![int]:[int] message to the serial port"""
    gate = randint(1, 2)
    speed = randint(1000, 1000000)
    message = '!' + str(gate) + ':' + str(speed)
    print("Sending '%s'..." % message)
    ser.write(message + "\n")

ser = serial.Serial('/dev/pts/2', 19200)
print 'Connected to %s' % ser.name
try:
    print "Press any key to exit..."
    while True:
        if kbhit.kbhit():
            ser.close()
            print('Exit.')
            break
        else:
            write_fake_msg(ser)
            time.sleep(2)
except KeyboardInterrupt:
    ser.close()
    print "Exit."
except ValueError:
    print "Oops! Invalid parameter. Try again..."
except serial.SerialException:
    print "Oops! Can't find or configure the device..."
