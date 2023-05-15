import tushare as ts
import yaml
import datetime
import tqdm
import threading
import os
import shutil

END_DATE = datetime.date(2023, 5, 12)
TIME_DELTA = datetime.timedelta(days=90)
START_DATE = END_DATE - TIME_DELTA


START_DATE = str(START_DATE)
END_DATE = str(END_DATE)
DIR = f"./data/test/test-90-{END_DATE}"
try:
    shutil.rmtree(DIR)
except:
    pass
finally:
    os.mkdir(DIR)
print(START_DATE, END_DATE)


# 获取股票列表并筛选 volumn > 1亿 者

pro = ts.pro_api(token=r'619804f7abf81ef80389b842c3939064155c04131b99056104d10629')
df = pro.daily(trade_date=f'{END_DATE.replace("-", "")}')
print(df.keys())
df = df[df['amount'] > 100000]
print(df)
ts_codes = [*df['ts_code']]
symbols = [*df['ts_code']]
print(symbols)

# 开始爬数据
pbar = tqdm.tqdm(total=len(ts_codes))
global count
count = 0
def thd(symbols):
    for symbol in symbols:
        stdcode = symbol[:-3]
        df = ts.get_hist_data(stdcode, start=START_DATE, end=END_DATE)
        try:
            pct_chg = [*df['p_change']][::-1]
            # 筛选： 高于均线
            assert len(pct_chg) > 30
            assert df['close'][0] > df['ma5'][0]
            assert df['close'][0] > df['ma10'][0]
            assert df['close'][0] > df['ma20'][0]

            sample = {
                'date': datetime.datetime.today(),
                'start': START_DATE,
                'end': END_DATE,
                'code': stdcode,
                'stdchange': pct_chg,
            }

            with open(f'{DIR}/{stdcode}.yaml', 'w+') as f:
                yaml.dump(sample, f)
            pbar.update(1)
            count += 1
        except Exception as e:
            print(e)

th1 = threading.Thread(target=thd, args=(symbols[:500], ))
th1.start()
th2 = threading.Thread(target=thd, args=(symbols[500: 1000], ))
th2.start()
th3 = threading.Thread(target=thd, args=(symbols[1000: 1500], ))
th3.start()
th4 = threading.Thread(target=thd, args=(symbols[1500: 2000], ))
th4.start()
th5 = threading.Thread(target=thd, args=(symbols[2000: 2500], ))
th5.start()
th6 = threading.Thread(target=thd, args=(symbols[2500: 3000], ))
th6.start()
th7 = threading.Thread(target=thd, args=(symbols[3000: 3500], ))
th7.start()
th8 = threading.Thread(target=thd, args=(symbols[3500: 4000], ))
th8.start()
th9 = threading.Thread(target=thd, args=(symbols[4000: 4500], ))
th9.start()
th10 = threading.Thread(target=thd, args=(symbols[4500: ], ))
th10.start()

print(count)


