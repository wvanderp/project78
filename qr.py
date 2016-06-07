print('start ')

from picamera import PiCamera
from inspect import getmembers
from time import sleep
import math

#print('it works ')
import pprint

import zbar
#print('zbar ok ')

from PIL import Image
#print('it works0 ')

camera = PiCamera()

scanner = zbar.ImageScanner()
scanner.parse_config('enable')

# in centimeters
sizeqrcode = 10


distance = 10
#in cm
qrdignal = 10
#in cm
distfac = 1/(distance/qrdignal)
#in cm/cm de size moet ook in cm zijn



def scan():
 #	camera.capture('/home/pi/Desktop/image.jpg')

	pil = Image.open('/home/pi/Desktop/qrOfCenter2.jpg').convert('L')
	width, height = pil.size

	raw = pil.tostring()
#	print('it works1 ')
	image = zbar.Image(width, height, 'Y800', raw)

	scanner.scan(image)
#	print('it works2 ')

	for symbol in image:
	    # do something useful with results
	    print 'decoded', symbol.type, 'symbol', '"%s"' % symbol.data
            #pprint.pprint(getmembers(symbol))
            x1 = (symbol.location[0][0]) 
            x2 = (symbol.location[2][0])
            y1 = (symbol.location[0][1])
            y2 = (symbol.location[2][1])
            qrmill = ((x1+x2)/2.0)
            picmill = width/2.0
            diff = picmill - qrmill
            qrdiag = math.sqrt(math.pow(x2-x1,2)+math.pow(y2-y1,2))
            scalefac = (10/qrdiag) 
            lenoverstaande = diff * scalefac
      
            aanligende = (qrdiag * scalefac)*distfac

            deg = math.degrees(math.atan(lenoverstaande/aanligende))      
#            print qrmill
#            print picmill
            #print diff
            #print (qrdiag * scalefac)
            #print scalefac
            #print lenoverstaande
            print deg
#            print x1
#            print x2
#            print y1
#            print y2

            
#	print('it works3 ')
	return;

while True:
        scan()
	break
        sleep(1)
		
