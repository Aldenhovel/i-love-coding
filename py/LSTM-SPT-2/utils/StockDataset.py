import torch
import torch.nn as nn
from torch.utils.data import Dataset, DataLoader
from .Tokenizer import Tokenizer, MAX_LEN
from .DataReader import DataReader

class StockDataset(Dataset):
    def __init__(self, datadir, re_path):
        Dataset.__init__(self)
        self.reader = DataReader(datadir)
        self.tk = Tokenizer(grid=100, maxlen=MAX_LEN)
        self.files = self.reader.listfiles(re_path)
        self.file_size = len(self.files)
        
    def __getitem__(self, index):
        file = self.reader.readyaml(self.files[index])
        stdfenshi = file["stdchange"]
        stdfenshi, seqlen = self.tk.tokenize(stdfenshi)
        stdfenshi = torch.Tensor(stdfenshi).long()
        return stdfenshi, seqlen
    
    def __len__(self):
        return self.file_size
        
        