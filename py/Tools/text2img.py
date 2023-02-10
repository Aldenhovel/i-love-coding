import PIL
from PIL import Image, ImageDraw, ImageFont

def txt2img(text):
    im = Image.new("RGB", (100, 300), (255, 255, 255))
    dr = ImageDraw.Draw(im)
    font = ImageFont.truetype(font="arial.ttf", size=20)
    dr.text((10, 5), text,font=font, fill="#000000")
    im.show()
    im.save(r'x/res.png')