import qrcode

from docx import Document
from docx.shared import Inches

data = '90&2:'

img = qrcode.make(data)
img.save('qr.jpg')

document = Document()
document.add_picture('qr.jpg', width=Inches(6))
document.add_page_break()
document.save('demo.docx')
