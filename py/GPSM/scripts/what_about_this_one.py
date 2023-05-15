import pathlib
import yaml
import requests
from utils.Ifttt import Ifttt
import tushare as ts
from utils.pvp import max_drawdown, max_drawup
import datetime

def what_about_this(code):

    END_DATE = datetime.datetime.today()
    TIME_DELTA = datetime.timedelta(days=90)
    START_DATE = END_DATE - TIME_DELTA


    START_DATE = str(START_DATE)
    END_DATE = str(END_DATE)


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
    i=0
    # 筛洗条件
    try:
        if not current_r < 4 and current_r > -3: raise Exception("NOW < -3 or > 4")
        if not low_r > -5: raise Exception("L < -5")
        if not high_r - current_r < 5: raise Exception("H - NOW >= 5")
        if not high_r - low_r < 8: raise Exception("H - L >= 8")

        if not mdu > 20: raise Exception("MAX DRAWUP <= 20")

        if not current > ma10_lastday: raise Exception("NOW < MA10")

        print("NO PROBLEM")
    except Exception as e:

        print(e)

what_about_this("300528")