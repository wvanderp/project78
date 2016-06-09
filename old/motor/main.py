from MotorDriver import MotorDriver as Motor
from time import sleep
motor = Motor(8,10)

while(True):
	motor.drive(50,50)


