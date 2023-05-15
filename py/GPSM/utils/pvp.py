import pandas as pd

def max_drawdown(arr):
    df_seq = pd.DataFrame(arr)
    df_seq = df_seq.cumsum(axis=0)
    arr = list(df_seq[0])
    mdd = []
    for i in range(0, len(arr) - 1):
        mdd.append(min(arr[i + 1:]) - arr[i])
    return abs(min(mdd))


def max_drawup(arr):
    df_seq = pd.DataFrame(arr)
    df_seq = df_seq.cumsum(axis=0)
    arr = list(df_seq[0])
    mdu = []
    for i in range(0, len(arr) - 1):
        mdu.append(max(arr[i + 1:]) - arr[i])
    return abs(max(mdu))