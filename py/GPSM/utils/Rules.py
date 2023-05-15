import datetime
import tushare as ts
import requests
import json
import numpy as np
import pandas as pd
from .pvp import max_drawdown, max_drawup
from .External import re_search

class Rules():
    def __init__(self):
        pass

    def _get_ts_source(self, code):
        END_DATE = datetime.datetime.today()
        TIME_DELTA = datetime.timedelta(days=90)
        START_DATE = END_DATE - TIME_DELTA
        START_DATE, END_DATE = str(START_DATE), str(END_DATE)
        df = ts.get_hist_data(code, start=START_DATE, end=END_DATE)
        return df

    def _get_sina_source(self, code):
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
        context = text.split(',')
        return context

    def _get_eastmoney_pankou(self, code):
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
        else:
            print(code)
            return 0, [], [], []
        response = requests.get(url)
        table = json.loads(re_search(r'\(.*\)', response.text)[0][1:-1])
        df = pd.DataFrame(table['data']['data'])

        df = df[df["t"] >= 92500]

        df_a = df[df["bs"] != 4]
        neg_mask = df_a['bs'] == 1
        pos_mask = df_a['bs'] == 2

        df_a.loc[neg_mask, ['v']] = -1 * df_a.loc[neg_mask, ['v']]
        # df_a["p_v"] = df_a["p"] * df_a["v"] / 10

        df_a["b_v"] = df_a["v"].map(lambda x: x if x > 0 else 0)
        df_a["s_v"] = df_a["v"].map(lambda x: x if x < 0 else 0)
        b_vol = df_a["b_v"].tolist()
        s_vol = df_a["s_v"].tolist()
        a_vol = df_a["v"].tolist()
        # a_pv = df_a["p_v"].tolist()

        avt = sum(np.abs(a_vol))
        av = np.cumsum(a_vol)
        bv = np.cumsum(b_vol)
        sv = np.cumsum(s_vol)

        strength = round(bv[-1] / -sv[-1], 2)
        print(code, strength)
        return strength, av, bv, sv

    def greater_than_ma10(self, code):
        df = self._get_ts_source(code)
        context = self._get_sina_source(code)
        ma10 = df["ma10"][0]
        current = float(context[3])
        return current > ma10

    def now_good_price(self, code):
        context = self._get_sina_source(code)
        last_day_p = float(context[2])
        current_r = (float(context[3]) / last_day_p) * 100 - 100
        return -3 < current_r < 4

    def low_volatility(self, code):
        context = self._get_sina_source(code)
        last_day_p = float(context[2])
        high_r = (float(context[4]) / last_day_p) * 100 - 100
        low_r = (float(context[5]) / last_day_p) * 100 - 100
        return high_r - low_r < 8

    def positive_pankou(self, code):
        s, _, _, _ = self._get_eastmoney_pankou(code)
        return s > 1

    def get_pvp(self, code):
        df = self._get_ts_source(code)
        p_change_30 = [*df["p_change"][:30]]
        mdd = max_drawdown(p_change_30)
        mdu = max_drawup(p_change_30)
        pvp = round(mdu / mdd, 1)

        return pvp



if __name__ == "__main__":
    R = Rules()
    print(R.positive_pankou("600201"))
