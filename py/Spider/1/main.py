import requests
from bs4 import BeautifulSoup
import xml.etree.ElementTree as ET
import re

def reSearch(rule, text):
    '''
    封装的正则筛选方法
    '''
    try:
        block = re.search(rule, text).span()
        res = text[block[0]:block[1]]
        return (res,block[1])
    except:
        return None

def PrettyXml(element, indent='\t', newline='\n', level=0):
    '''
    将xml文件整理成符合阅读的格式
    '''
    if element:
        if (element.text is None) or element.text.isspace():
            element.text = newline + indent * (level + 1)
        else:
            element.text = newline + indent * (level + 1) + element.text.strip() + newline + indent * (level + 1)
    temp = list(element)
    for subelement in temp:
        if temp.index(subelement) < (len(temp) - 1):
            subelement.tail = newline + indent * (level + 1)
        else:
            subelement.tail = newline + indent * level
        PrettyXml(subelement, indent, newline, level=level + 1)


def _getPageText(url):
    '''
    获取对应URL的网页源代码
    '''
    return requests.get(url).text

def _getCellPhoneData(text):
    '''
    从_getPageText()返回的网页源代码中整理出各个手机的信息，包括：
        手机名：name
        详细信息URL地址：URL
        图片URL地址：picURL
    以列表形式返回
    '''
    soup = BeautifulSoup(text, features='html.parser')
    body = soup.body
    dt = body.find('div', class_='wrapper clearfix')\
                    .find('div', class_='content')\
                    .find('div', class_='pic-mode-box')\
                    .find('ul', id='J_PicMode')\
                    .find_all('li')
    res_dt = []
    for block in dt:
        try:
            name = reSearch('.*（', block.a.img['alt'])[0][:-1]
            URL = block.a['href']
            pictURL = block.a.img['.src']
            res_dt.append({'name':name, 'URL':URL, 'picURL':pictURL})
        except:
            pass
    return res_dt

def _saveToXML(dt):
    '''
    将_getCellPhoneData()的返回列表存储到"./phones.xml上"
    '''
    path = "phones.xml"
    tree = ET.parse(path)
    root = tree.getroot()
    for data in dt:
        phone = ET.Element("phone")
        name = ET.Element("name")
        name.text = data['name']
        URL = ET.Element("URL")
        URL.text = data['URL']
        picURL = ET.Element('picURL')
        picURL.text = data['picURL']
        phone.append(name)
        phone.append(URL)
        phone.append(picURL)
        root.append(phone)
    PrettyXml(root)
    tree.write(path, encoding='utf-8', xml_declaration=True)
    print('finish...')
    
def _getScore():
    '''
    根据"./phones.xml"记录的手机型号爬取对应的评分，包括：
        总体评价：total_score
        性价比：v4m
        性能：power
        续航：battery
        外观：look
        拍照：snap
    存储到"./phones.xml"中
    '''
    path = "phones.xml"
    tree = ET.parse(path)
    root = tree.getroot()
    phones = root.findall('phone')
    count = 0
    for phone in phones:
        try:
            phone_id = reSearch(r'[0-9]{7}', phone.find('URL').text)[0]
            score_url = 'https://detail.zol.com.cn/1327/$/review.shtml'.replace('$', phone_id)
            text = requests.get(score_url).text
            soup = BeautifulSoup(text)
            body = soup.body
            dt = []
            block = body.find_all('div', class_='wrapper clearfix')[1]\
                              .find('div', class_='content')\
                              .find('div', class_='review-comments-score new-review-comments')\
                              .find('div', class_='total-bd clearfix')
            total_score = block.find('div', class_='total-score').find('strong').text
            dt.append(total_score)
            score_block_list = block.find('div', class_='features-score features-score-5')\
                              .find_all('div', class_='features-circle')
            for score_block in score_block_list:
                score = score_block.find('div', class_='circle-value').text
                dt.append(score)
            total_score = ET.Element('total_score')
            total_score.text = dt[0]
            value_for_money = ET.Element('v4m')
            value_for_money.text = dt[1]
            power = ET.Element('power')
            power.text = dt[2]
            battery = ET.Element('battery')
            battery.text = dt[3]
            look = ET.Element('look')
            look.text = dt[4]
            snap = ET.Element('snap')
            snap.text = dt[5]
            phone.append(total_score)
            phone.append(value_for_money)
            phone.append(power)
            phone.append(battery)
            phone.append(look)
            phone.append(snap)
            print(dt)
            PrettyXml(root)
            tree.write(path, encoding='utf-8', xml_declaration=True)
            count += 1
            print(str(count)+' finish...'+phone.find('name').text)
        except:
            print('已跳过一条......')


if __name__ == "__main__":
    for i in range(1, 15):
        url = 'https://detail.zol.com.cn/cell_phone_index/subcate57_0_list_1_0_1_2_0_$.html'.replace('$', str(i))
        text = _getPageText(url)
        dt = _getCellPhoneData(text)
        _saveToXML(dt)
        print(i)
    _getScore()