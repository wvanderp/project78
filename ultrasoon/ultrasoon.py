from time import sleep
import serial
from random import randint

ser = serial.Serial(
    port="/dev/ttyAMA0",
    baudrate=4800,
    parity=serial.PARITY_NONE,
    stopbits=serial.STOPBITS_ONE,
    bytesize=serial.EIGHTBITS,
    timeout=1
)

array = [0] * 180

#for i in range(0, 179):
#    print str(i)+":"+str(array[i])

while 1:
    print "new line"
    x = ser.readline()
    if x != "":
        print x
        deg, dist = x.split(":", 2)
        dist = int(dist.rstrip())
        deg = int(deg)	
        array[deg-1] = dist
        print str(deg) + " en " + str(dist)

