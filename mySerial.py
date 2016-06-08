from time import sleep
import serial

ser = serial.Serial(
	port = "/dev/ttyAMA0",
	baudrate = 4800,
	parity = serial.PARITY_NONE,
	stopbits = serial.STOPBITS_ONE,
	bytesize = serial.EIGHTBITS,
	timeout = 1 
)

counter = 0 

#while 1:
#	x = ser.readline()
#	print x

while 1:
	ser.write("counter is: %d\n"%(counter))
	sleep(1)
	counter += 1
