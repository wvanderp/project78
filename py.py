print('start ')

from picamera import PiCamera
from inspect import getmembers
from time import sleep

#print('it works ')
import pprint

import zbar
#print('zbar ok ')

from PIL import Image
#print('it works0 ')

camera = PiCamera()

scanner = zbar.ImageScanner()
scanner.parse_config('enable')

def scan():
	camera.capture('/home/pi/Desktop/image.jpg')

#	pil = Image.open('/home/pi/Desktop/image.jpg').convert('L')
	pil = Image.open('/home/pi/Desktop/qr.jpg').convert('L')
	width, height = pil.size

	raw = pil.tostring()
#	print('it works1 ')
	image = zbar.Image(width, height, 'Y800', raw)

	scanner.scan(image)
#	print('it works2 ')

	for symbol in image:
	    # do something useful with results
	    print 'decoded', symbol.type, 'symbol', '"%s"' % symbol.data
	    print(symbol.get_location_size ())
#            pprint.pprint(getmembers(symbol))

#	print('it works3 ')
	return;

while True:
        scan()
        sleep(1)
