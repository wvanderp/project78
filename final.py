from picamera import PiCamera
from inspect import getmembers
from time import sleep
import serial
import math
import zbar
from PIL import Image

ser = serial.Serial(
    port="/dev/ttyAMA0",
    baudrate=4800,
    parity=serial.PARITY_NONE,
    stopbits=serial.STOPBITS_ONE,
    bytesize=serial.EIGHTBITS,
    timeout=1
)

# qr code vars
##################
camera = PiCamera()

scanner = zbar.ImageScanner()
scanner.parse_config('enable')

sizeQrCode = 22.0
# in cm de diagonaal van de qr

qrCodeDiag = 675.0
# the diagonal of the qr in px
distance = 50
# in cm in real life

distfac = (distance / qrCodeDiag)
# in cm/px de size moet ook in cm zijn

# lidar vars
#############################
array = [0] * 180

# qr code data
# error correction
##################

qrData = ""
sum = 0


def scan():
    camera.capture('/home/pi/Desktop/image.jpg')

    pil = Image.open('/home/pi/Desktop/image.jpg').convert('L')
    width, height = pil.size

    raw = pil.tostring()
    image = zbar.Image(width, height, 'Y800', raw)

    scanner.scan(image)

    for symbol in image:
        # do something useful with results
        print 'decoded', symbol.type, 'symbol', '"%s"' % symbol.data
        # pprint.pprint(getmembers(symbol))
        x1 = (symbol.location[0][0])
        x2 = (symbol.location[2][0])
        y1 = (symbol.location[0][1])
        y2 = (symbol.location[2][1])

        qrCenter = ((x1 + x2) / 2.0)
        imgCenter = width / 2.0
        centerDiff = imgCenter - qrCenter

        qrdiag = math.sqrt(math.pow(x2 - x1, 2) + math.pow(y2 - y1, 2))

        scalefac = (10 / qrdiag)
        # scale factor for the backplain

        backplain = centerDiff * scalefac

        imageDistance = qrdiag * distfac

        angle = math.degrees(math.atan(backplain / imageDistance))

        return (angle,symbol.data)


while True:
    # qr code reading
    angle, data = scan()

    if qrData == data:
        # sending qr data over serial
        ser.write(data)

    # reading serial connection
    x = ser.readline()
    thing, rest = x.split(";")
    if thing == "s":
        if x != "":
            x = rest
            print x
            deg, dist = x.split(":", 2)
            dist = int(dist.rstrip())
            deg = int(deg)
            array[deg - 1] = dist
            print str(deg) + " en " + str(dist)
    elif thing == "e":
        if rest != qrData:
            ser.write(qrData)
    sleep(1)
