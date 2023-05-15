import os
import tushare as ts
import numpy as np
import requests
import json
from pandas import DataFrame
import yaml
from utils.External import re_search
import datetime
import pickle
import tqdm



class Grabber:
    def __init__(self):
        pass

    def get_pankou(self, code):
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
        df = DataFrame(table['data']['data'])

        df = df[df["t"] >= 92500]

        df_a = df[df["bs"] != 4]
        neg_mask = df_a['bs'] == 1
        pos_mask = df_a['bs'] == 2

        df_a.loc[neg_mask, ['v']] = -1 * df_a.loc[neg_mask, ['v']]
        #df_a["p_v"] = df_a["p"] * df_a["v"] / 10

        df_a["b_v"] = df_a["v"].map(lambda x: x if x > 0 else 0)
        df_a["s_v"] = df_a["v"].map(lambda x: x if x < 0 else 0)
        b_vol = df_a["b_v"].tolist()
        s_vol = df_a["s_v"].tolist()
        a_vol = df_a["v"].tolist()
        #a_pv = df_a["p_v"].tolist()

        avt = sum(np.abs(a_vol))
        av = np.cumsum(a_vol)
        bv = np.cumsum(b_vol)
        sv = np.cumsum(s_vol)

        strength = round(bv[-1] / -sv[-1], 2)
        print(code, strength)
        return strength, av, bv, sv




if __name__ == "__main__":

    END_DATE = datetime.date(2023, 5, 12)
    END_DATE = str(END_DATE)


    pro = ts.pro_api(token=r'619804f7abf81ef80389b842c3939064155c04131b99056104d10629')
    df = pro.daily(trade_date=f'{END_DATE.replace("-", "")}')
    print(df.keys())
    df = df[df['amount'] > 50000]
    print(df)
    ts_codes = [*df['ts_code']]
    symbols = [*df['ts_code']]
    print(symbols)
    codes = [*map(lambda x: x[:-3], symbols)]
    print(len(codes))

    res = []
    gb = Grabber()
    for ix, code in enumerate(tqdm.tqdm(codes)):
        s, av, bv, sv = gb.get_pankou(code)
        res.append((code, s))

    data = {}
    data["codeStrength"] = res
    data["strength"] = [*map(lambda x: x[1], res)]
    with open(f"./history_pankou/2023-05-15.pkl", "wb") as f:
        pickle.dump(data, f)




    with open(f"./history_pankou/2023-05-15.pkl", "rb") as f:
        ndt = pickle.load(f)
        print(ndt)

    import matplotlib.pyplot as plt
    import collections
    c = collections.Counter(ndt["strength"])
    c = list(c.items())
    c = sorted(c, key=lambda x: x[0])

    print(c)

    X_strength = np.asarray([*map(lambda x: x[0], c)]) * 100
    Y_count = np.asarray([*map(lambda x: x[1], c)])

    if X_strength[-1] == np.inf:
        X_strength = X_strength[:-1]
        Y_count = Y_count[:-1]


    plt.bar(X_strength, Y_count)
    plt.title(np.sum(X_strength * Y_count) / np.sum(Y_count))
    plt.show()

    print(c)




