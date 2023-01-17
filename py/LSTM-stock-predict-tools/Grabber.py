import os
import requests
import json
from pandas import DataFrame
import yaml
from external import re_search
import datetime
import tushare
import numpy as np

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
        pro = tushare.pro_api(token='619804f7abf81ef80389b842c3939064155c04131b99056104d10629')
        if code[:2] == '60':
            symbol = code + '.SH'
        elif code[:2] == '30':
            symbol = code + '.SZ'
        elif code[:2] == '00':
            symbol = code + '.SZ'
        elif code[:2] == '68':
            symbol = code + '.SH'
        r = pro.daily(ts_code=symbol)
        s = float(r['close'][0])
        return s

    def get_stdfenshi(self, code):
        fenshi = self.get_fenshi(code)
        stdprice = self.get_stdprice(code)
        stdfenshi = [*map(lambda x: x / stdprice * 100 - 100, fenshi)]
        return stdfenshi

    def _write_yaml(self, path, data):
        with open(path, 'w', encoding='utf-8') as f:
            yaml.dump(data, f)

    def sample(self, code, dirpath="data"):
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
        print("Done.")
        return

if __name__ == "__main__":
    grabber = Grabber()
    grabber.sample("002762")
