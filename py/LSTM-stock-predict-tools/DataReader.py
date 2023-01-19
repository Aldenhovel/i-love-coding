import os
import yaml

class DataReader:
    def __init__(self, datadir="data"):
        self.datadir = datadir

    def readyaml(self, filename):
        with open(os.path.join(self.datadir, filename), 'r', encoding='utf-8') as f:
            data = f.read()
            data = yaml.load(data, Loader=yaml.FullLoader)
            return data

    def listfiles(self):
        files = os.listdir(self.datadir)
        return files