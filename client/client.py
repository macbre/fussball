import serial
import time
import re


def parse_message(line):
    """Parsing string and returns dictionary with gate number and time"""
    res = re.match(r"!([0-9]+):([0-9]+)", line)
    if res is None:
        return None

    gate = int(res.group(1))
    goalTime = int(res.group(2))

    if gate and goalTime:
        return {
            "gate": gate,
            "time": goalTime,
            "speed": None
        }


def get_speed(time):
    """Based on time and ball size calculates and returns speed in km/h"""
    return float(3500 * 36 / time)  # 3500 = ball size (3.5 cm)


def show_message(data):
    """Displays message on screen"""
    print "Ball got into the gate no.%i with %f speed [km/h].\n" % (data["gate"], data["speed"])

ser = serial.Serial('/dev/ttyS0', 115200)
try:
    print "To exit press Ctrl^C..."
    print 'Connected to %s' % ser.name
    while True:
        if ser.readable() is True:
            ser.flushInput()
            line = ser.readline()
            ballData = parse_message(line)
            if ballData is None:
                print(line)
            else:
                ballData["speed"] = get_speed(ballData["time"])
                print ballData
                show_message(ballData)
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
