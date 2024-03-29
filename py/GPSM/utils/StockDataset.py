import torch
import torch.nn as nn
from torch.utils.data import Dataset, DataLoader
from .Tokenizer import Tokenizer, MAX_LEN
from .DataReader import DataReader
import os

class StockDataset(Dataset):
    def __init__(self, datadir, re_path, tokenizer):
        Dataset.__init__(self)
        self.reader = DataReader(datadir)
        self.tk = tokenizer
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
    
    def checkds(self):
        for ix in range(self.file_size):
            file = self.reader.readyaml(self.files[ix])
            stdfenshi = file["stdchange"]
            stdfenshi, seqlen = self.tk.tokenize(stdfenshi)
            if seqlen < 31:
                file_path = str(self.files[ix]).replace('\\', '/')
                os.remove(file_path)
                print(file_path)
        
        
class StockDatasetCHL(Dataset):
    def __init__(self, datadir, re_path):
        Dataset.__init__(self)
        self.reader = DataReader(datadir)
        self.tk = Tokenizer(grid=100, maxlen=MAX_LEN)
        self.files = self.reader.listfiles(re_path)
        self.file_size = len(self.files)
        
    def __getitem__(self, index):
        file = self.reader.readyaml(self.files[index])
        stdfenshi = file["stdchange"]
        stdhigh = file["stdhigh"]
        stdlow = file["stdlow"]
        stdfenshi, seqlen = self.tk.tokenize(stdfenshi)
        stdhigh, seqlen_h = self.tk.tokenize(stdhigh)
        stdlow, seqlen_l = self.tk.tokenize(stdlow)
        assert seqlen == seqlen_h == seqlen_l
        stdfenshi = torch.Tensor(stdfenshi).long()
        stdhigh = torch.Tensor(stdhigh).long()
        stdlow = torch.Tensor(stdlow).long()
        return stdfenshi, stdhigh, stdlow, seqlen
    
    def __len__(self):
        return self.file_size