import os
import yaml
class DataReader:
    def __init__(self):
        pass

    def readyaml(self, filename, dirpath="data"):
        with open(os.path.join(dirpath, filename), 'r', encoding='utf-8') as f:
            data = f.read()
            data = yaml.load(data, Loader=yaml.FullLoader)
            return data

    def listfiles(self, dirpath="data"):
        files = os.listdir(dirpath)
        return files


if __name__ == "__main__":
    dt = DataReader()
    print(dt.listfiles())