from PIL import Image
import math

print('start ')


def arc2xy(arc, dist, start_x, start_y):
    rads = math.pi * arc / 180

    x = start_x + dist * math.cos(rads)
    y = start_y + dist * math.sin(rads)

    return x, y


def render_image():
    img = Image.new('RGB', (255, 255), "black")
    pixels = img.load()
    height, width = img.size

    for i in range(360):
        x, y = arc2xy(i, 100, height/2, width/2)
        x = round(x)
        y = round(y)

        pixels[x, y] = (255, 255, 255)

    img.show()
    return


render_image()
