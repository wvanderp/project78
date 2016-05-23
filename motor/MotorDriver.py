import RPi.GPIO as GPIO

class MotorDriver:
    def __init__(self, motorLPin,motorRPin) :
        GPIO.setmode(GPIO.BOARD)
        self.motorLPIn = motorLPin
        GPIO.setup(motorLPin,GPIO.OUT)
        self.motorL = GPIO.PWM(motorLPin,50)
        self.motorL.start(0)
        self.motorRPin = motorRPin
        GPIO.setup(motorRPin,GPIO.OUT)
        self.motorR = GPIO.PWM(motorRPin,50)
        self.motorR.start(0)
    def motorLF(self):
        self.motorL.ChangeDutyCycle(8.5)
    def motorRF(self):
        self. motorR.ChangeDutyCycle(8.5)
    def motorLR(self):
        self.motorL.ChangeDutyCycle(4.5)
    def motorRR(self):
        self.motorR.ChangeDutyCycle(4.5)
    def motorIdle(self):
        self.motorL.ChangeDutyCycle(0)
        self.motorR.ChangeDutyCycle(0)
    def forward(self):
        self.motorLF()
        self.motorRF()
    def left(self):
        self.motorLR()
        self.motorRF()
    def right(self):
        self.motorLF()
        self.motorRR()
    def reverse(self):
        self.motorLR()
        self.motorRR()


     



