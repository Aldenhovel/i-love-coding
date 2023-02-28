import requests
import re
import json
import py2ifttt
from py2ifttt import IFTTT
import datetime

def get_code_name(code):
    headers = {'referer': 'http://finance.sina.com.cn'}
    if code[:2] == '60':
        code = 'sh' + code
    elif code[:2] == '30':
        code = 'sz' + code
    elif code[:2] == '00':
        code = 'sz' + code
    elif code[:2] == '68':
        code = 'sh' + code
    url = f"http://hq.sinajs.cn/list={code}"
    response = requests.get(url, headers=headers)
    text = response.text
    codename = re.search(r'[\u4e00-\u9fa5]+', text).group()
    return codename

def create_text(code_score_list):
    text = f"<br/>{datetime.datetime.now()}<br/><br/>" + "="*15 + "<br/>"
    for ix, (code, score) in enumerate(code_score_list):
        print(code, score)
        text += f"{ix}\t\t{code}\t\t{get_code_name(code)}\t\t{round(float(score), 2)}<br/>"
    text += "="*15 + "<br/>"
    return text


class Ifttt():
    
    def __init__(self, key="c5fQLgMhc1JhwzJyH7dNVDcRocfBDn3S080z3a5fQBl", event_name="test"):
        self.ifttt = IFTTT(key=key, event_name=event_name)
        
    def send(self, code_score_list):
        text = create_text(code_score_list)
        self.ifttt.notify(value1=text)
        print(f"[{datetime.datetime.now()}] IFTTT message was sent.")


