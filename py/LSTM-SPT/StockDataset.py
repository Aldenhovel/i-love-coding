from torch.utils.data import Dataset, DataLoader
import torch
from DataReader import DataReader
from Tokenizer import Tokenizer

class StockDataset(Dataset):
    def __init__(self, datadir):
        Dataset.__init__(self)
        self.datadir = datadir
        self.reader = DataReader(datadir=datadir)
        self.tk = Tokenizer(grid=100, maxlen=250)
        self.files = self.reader.listfiles()
        self.file_size = len(self.files)

    def __getitem__(self, index):
        file = self.reader.readyaml(self.files[index])
        stdfenshi = file["stdfenshi"]
        stdfenshi, seqlen = self.tk.tokenize(stdfenshi)
        stdfenshi = torch.LongTensor(stdfenshi)
        return stdfenshi, seqlen

    def __len__(self):
        return self.file_size