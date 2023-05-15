import pathlib
import yaml
import requests
from utils.Ifttt import Ifttt
import tushare as ts
from utils.pvp import max_drawdown, max_drawup
import datetime
from utils.Rules import Rules as Rules

def tellMeWhatToBuy(mode):

    assert mode in {"STRICT", "LIMITED", "FREE"}
    history_files = [*pathlib.Path("./history").glob("*")]
    history_files = sorted(history_files, reverse=True)[:5]

    codes = []
    for path in history_files:
        with open(path, 'r') as f:
            data = f.read()
            data = yaml.load(data, Loader=yaml.FullLoader)
            codes.extend(data["codes"])
    codes = set(codes)
    print(len(codes))
    END_DATE = datetime.datetime.today()
    TIME_DELTA = datetime.timedelta(days=90)
    START_DATE = END_DATE - TIME_DELTA


    START_DATE = str(START_DATE)
    END_DATE = str(END_DATE)

    res = []
    for code in codes:
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
        print(code)
        last_day_p = float(context[2])
        current = float(context[3])
        current_r = (float(context[3]) / last_day_p) * 100 - 100
        high_r = (float(context[4]) / last_day_p) * 100 - 100
        low_r = (float(context[5]) / last_day_p) * 100 - 100
        volume = float(context[9]) / 1e8

        df = ts.get_hist_data(code[2:], start=START_DATE, end=END_DATE)
        p_change_30 = [*df["p_change"][:30]]

        mdd = max_drawdown(p_change_30)
        mdu = max_drawup(p_change_30)
        pvp = round(mdu / mdd, 1)
        ma5_lastday = df["ma5"][0]
        ma10_lastday = df["ma10"][0]
        vol_lastday = df["volume"][0]
        # 筛洗条件
        if mode == "STRICT":
            """
            **非常严格的过滤模式，剩下的基本是走势很稳健的，在苟时很有用**
            当前涨跌幅介于 -3~4 之间
            最低点不跌超过-5
            当前距离最高点回调不超过5个点
            振幅小于8个点
            30日最大涨幅大于20个点
            当前高于10日线
            """
            try:
                if not current_r < 4 and current_r > -3: raise Exception("NOW < -3 or > 4")
                if not low_r > -5: raise Exception("L < -5")
                if not high_r - current_r < 5: raise Exception("H - NOW >= 5")
                if not high_r - low_r < 8: raise Exception("H - L >= 8")

                if not mdu > 20: raise Exception("MAX DRAWUP <= 20")

                if not current > ma10_lastday: raise Exception("NOW < MA10")

                res.append((code[2:], pvp))
            except Exception as e:
                print(e)

        elif mode == "LIMITED":
            try:
                if not current_r < 6 and current_r > -4: raise Exception("NOW < -4 or > 6")
                if not low_r > -8: raise Exception("L < -8")
                if not high_r - current_r < 6: raise Exception("H - NOW >= 6")
                if not high_r - low_r < 10: raise Exception("H - L >= 10")

                if not mdu > 30: raise Exception("MAX DRAWUP <= 30")

                if not current > ma10_lastday: raise Exception("NOW < MA10")

                res.append((code[2:], pvp))
            except Exception as e:
                print(e)

        else:
            try:
                if not current_r > -2: raise Exception("NOW <= 2")
                if not current > ma10_lastday: raise Exception("NOW < MA10")
                if not low_r > -5: raise Exception("L <= -5")
                res.append(code[2:])
            except Exception as e:
                print(e)

    #res = sorted(res, key=lambda x: x[1], reverse=True)[:25]
    ifttt = Ifttt()
    ifttt.send_c(res)


def tellMeWhatToBuy2():
    history_files = [*pathlib.Path("./history").glob("*")]
    history_files = sorted(history_files, reverse=True)[:5]

    codes = []
    for path in history_files:
        with open(path, 'r') as f:
            data = f.read()
            data = yaml.load(data, Loader=yaml.FullLoader)
            codes.extend(data["codes"])
    codes = set(codes)
    print(len(codes))

    res = []
    rules = Rules()
    for code in codes:
        try:
            assert rules.positive_pankou(code)
            assert rules.greater_than_ma10(code)
            assert rules.low_volatility(code)
            assert rules.now_good_price(code)
            pvp = rules.get_pvp(code)
            res.append((code, pvp))
        except Exception as e:
            print(e)

    print(res)
    ifttt = Ifttt()
    ifttt.send_cnp(res)

tellMeWhatToBuy2()