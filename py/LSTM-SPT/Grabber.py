import os
import requests
import json
from pandas import DataFrame
import yaml
from external import re_search
import datetime
import numpy as np
import selenium
from selenium import webdriver
from selenium.webdriver.common.by import By
from bs4 import BeautifulSoup
import time
import external

class Grabber:
    def __init__(self):
        pass

    def get_fenshi(self, code):
        if code[:2] == '60':
            symbol = 'sh' + code
            url = f'http://push2ex.eastmoney.com/getStockFenShi?pagesize=4800&ut=7eea3edcaed734bea9cbfc24409ed989&dpt=wzfscj&cb=jQuery112403980350023749506_1627460255433&pageindex=0&id=605117&sort=1&ft=1&code={code}&market=1&_=1627460255439'
        elif code[:2] == '30':
            symbol = 'sz' + code
            url = f'http://push2ex.eastmoney.com/getStockFenShi?pagesize=4800&ut=7eea3edcaed734bea9cbfc24409ed989&dpt=wzfscj&cb=jQuery1124020373977062761606_1627641343509&pageindex=0&id=300346&sort=1&ft=1&code={code}&market=0&_=1627641343515'
        elif code[:2] == '00':
            symbol = 'sz' + code
            url = f'http://push2ex.eastmoney.com/getStockFenShi?pagesize=4800&ut=7eea3edcaed734bea9cbfc24409ed989&dpt=wzfscj&cb=jQuery112408276337240654512_1627641497200&pageindex=0&id=002340&sort=1&ft=1&code={code}&market=0&_=1627641497206'
        elif code[:2] == '68':
            symbol = 'sh' + code
            url = f'http://push2ex.eastmoney.com/getStockFenShi?pagesize=4800&ut=7eea3edcaed734bea9cbfc24409ed989&dpt=wzfscj&cb=jQuery112403458911126283384_1627641617104&pageindex=0&id=688981&sort=1&ft=1&code={code}&market=1&_=1627641617110'

        response = requests.get(url)
        table = json.loads(re_search(r'\(.*\)', response.text)[0][1:-1])
        df = DataFrame(table['data']['data'])
        df_len = len(df)
        price_seq = []
        for ix in range(df_len):
            if int(df.iloc[ix]['t'] <= 92500):
                continue
            else:
                try:
                    price = df.iloc[ix]['p'] / 1000.0
                    price_seq.append(float(price))

                except:
                    print('the NO.' + str(ix) + ' row wrong!')
        # 一般 eastmony 是每 3 秒刷新一次，所以 20 次为一分钟
        fenshi = price_seq[::20]
        return fenshi

    def get_stdprice(self, code):
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
        stdprice = float(response.text.split(",")[2])
        return stdprice

    def get_stdfenshi(self, code):
        fenshi = self.get_fenshi(code)
        stdprice = self.get_stdprice(code)
        stdfenshi = [*map(lambda x: x / stdprice * 100 - 100, fenshi)]
        return stdfenshi
    
    def clean_wencai_codelist(self):
        with open("data/codelist.txt", "r", encoding="utf-8") as f:
            lines = f.readlines()
            codelist = []
            for line in lines:
                if external.re_search(r"[0-9]{6}", line[:-1]):
                    codelist.append(external.re_search(r"[0-9]{6}", line[:-1])[0])
        print(f"{len(codelist)} items found ... ")
        return codelist
    
    def show_sample(self, filepath):
        with open(filepath, 'r', encoding='utf-8') as f:
            data = f.read()
            data = yaml.load(data, Loader=yaml.FullLoader)
        import matplotlib.pyplot as plt
        fig = plt.figure()
        plt.plot(data["stdfenshi"])
        return
        
    def _write_yaml(self, path, data):
        with open(path, 'w', encoding='utf-8') as f:
            yaml.dump(data, f)

    def sample(self, code, dirpath):
        filename = f'{str(datetime.date.today())}-{code}.yaml'
        stdprice = self.get_stdprice(code)
        fenshi = self.get_fenshi(code)
        stdfenshi = self.get_stdfenshi(code)
        path = os.path.join(dirpath, filename)
        data = {
            'date': datetime.date.today(),
            'code': code,
            'stdprice': stdprice,
            'fenshi': fenshi,
            'stdfenshi': stdfenshi
        }
        self._write_yaml(path, data)
        text = f"""
        code: {data["code"]}
        date: {data["date"]}
        slen: {len(data["stdfenshi"])}
        stdp: {data["stdprice"]}
        ssos: {data["fenshi"][0]}
        seos: {data["fenshi"][-1]}
        """
        #print(text)
        #print("Done.")
        return data["stdfenshi"]