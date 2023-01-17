from Grabber import Grabber
from Tokenizer import Tokenizer
from DataReader import DataReader

import matplotlib.pyplot as plt

datareader = DataReader()
tk = Tokenizer(grid=100)

files = datareader.listfiles()
for file in files:
    dt = datareader.readyaml(file)
    stdfenshi = dt["stdfenshi"]
    tokens = tk.tokenize(stdfenshi)
    plt.plot(tokens)
    plt.show()