import serial
import time
import re
import subprocess
import random


def parse_message(line):
    """Parsing string and returns dictionary with goal number and time"""
    res = re.match(r"!([0-9]+):([0-9]+)", line)
    if res is None:
        return None

    goal = int(res.group(1))
    goalTime = int(res.group(2))

    if goal and goalTime:
        return {
            "goal": goal,
            "time": goalTime,
            "speed": None
        }


def get_speed(time):
    """Based on time and ball size calculates and returns speed in km/h"""
    return float(3500 * 36 / time)  # 3500 = ball size (3.5 cm)


def show_message(data):
    """Displays message on screen"""
    print "Ball got into the goal no.%i with %f speed [km/h].\n" % (data["goal"], data["speed"])


def play_sound():
    """Plays a sound with mplayer"""
    sounds = [
        './sounds/goal1.wav',
        './sounds/goal2.wav',
        './sounds/goal3.wav',
        './sounds/goal4.wav',
        './sounds/goal5.wav'
    ]
    try:
        print sounds
        random.shuffle(sounds)
        print sounds
        sound = sounds[0]
        print sound
        subprocess.call(['mplayer', sound, '-really-quiet'])
    except OSError:
        print "Could not play sound. File not found."

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
                play_sound()
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
