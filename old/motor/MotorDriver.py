import RPi.GPIO as GPIO

class MotorDriver:
    def __init__(self, motorLPin, motorRPin) :
        GPIO.setmode(GPIO.BOARD)
        
	self.motorLPIn = motorLPin
        GPIO.setup(motorLPin,GPIO.OUT)
        self.motorL = GPIO.PWM(motorLPin,50)
        self.motorL.start(0)
        
	self.motorRPin = motorRPin
        GPIO.setup(motorRPin,GPIO.OUT)
        self.motorR = GPIO.PWM(motorRPin,50)
	self.motorR.start(0)

    def drive(self, l, r):

        lpwm = self.intmap(l, 0.0, 100.0, 5.0, 10.0)
        rpwm = self.intmap(r, 0.0, 100.0, 5.0, 10.0)

	lpwm = 15- lpwm

	print type(rpwm)
	print lpwm
	print rpwm


        self.motorR.ChangeDutyCycle(rpwm)
        self.motorL.ChangeDutyCycle(lpwm) 

    def intmap(self, x, in_min, in_max, out_min, out_max):	 
        return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;


