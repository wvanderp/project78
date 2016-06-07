import qrcode

from docx import Document
from docx.shared import Inches

data = 'L;100;F;200;R;100'

img = qrcode.make(data)
img.save('qr.jpg')

document = Document()
document.add_picture('qr.jpg', width=Inches(6))
document.add_page_break()
document.save('demo.docx')
