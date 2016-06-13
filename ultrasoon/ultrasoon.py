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
for i in range(0, 179):
    print str(i)+":"+str(array[i])

while 1:
    x = ser.readline()
    # x = "110:123"
    (deg, dist) = x.split(":")
    array[deg-1] = dist
    print deg + " en " + dist


