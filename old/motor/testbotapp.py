import urllib, sched, time,MotorDriver, RPi.GPIO as GPIO

s = sched.scheduler(time.time, time.sleep)
url = "http://145.24.222.235/get_product.php"
motorDriver = MotorDriver.MotorDriver(8,10)

def checkApp(sc):
    response = urllib.urlopen(url).read()
    if response == '10':
	motorDriver.forward()
    elif response == '20':
        motorDriver.reverse()
    elif response == '01':
        motorDriver.left()
    elif response == '02':
        motorDriver.right()
    else :
        motorDriver.motorIdle()
    print response
    sc.enter(0.01, 1, checkApp, (sc,))
s.enter(0.01, 1, checkApp, (s,))
s.run()
