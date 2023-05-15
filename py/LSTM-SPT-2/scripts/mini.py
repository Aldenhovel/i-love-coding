import yaml

from utils.Tokenizer import Tokenizer, MAX_LEN
from utils.StockDataset import StockDataset
from utils.DataReader import DataReader
from utils.Inference import Inference
from utils.Train import train_step, vaild_step
from utils.Ifttt import Ifttt
from models.LSTMDecoder import LSTMDecoder

import torch
import torch.nn as nn
from torchinfo import summary
from torch.utils.data import DataLoader
import tqdm

# SETUP
date_postfix = "2023-05-12"
TEST_DIR = f"data/test/test-90-{date_postfix}/"
#CKPT = "checkpoints/90-model-m.pt"
CKPT = "checkpoints/model-latest.pt"

device = torch.device("cpu")
model = LSTMDecoder(vocab_size=102, hidden_dim=512, layer=2, bi=True, device=device)
model = torch.load(CKPT, map_location=device)
inference = Inference(model=model)

import tqdm
datareader = DataReader(TEST_DIR)
all_files = [*datareader.listfiles(re_path="*.yaml")]

scores_result = []
pbar = tqdm.tqdm(total=len(all_files), ncols=50)

for file_path in all_files:
    next_3_avg, uphill, downhill = inference.predict_one(file_path, beam_size=10, predict_step=3)
    s = next_3_avg
    scores_result.append((file_path, (s - 50) * 0.2, uphill, downhill))
    pbar.update(1)
pbar.close()

scores_result = sorted(scores_result, key=lambda x: x[1], reverse=True)
codes = [*map(lambda x: x[0].stem, scores_result)]
scores = [*map(lambda x: round(x[1], 1), scores_result)]
uphill = [*map(lambda x: round(x[2], 1), scores_result)]
downhill = [*map(lambda x: round(x[3], 1), scores_result)]
pvp = [*map(lambda x: round(x[2] / x[3], 1), scores_result)]
result = [*zip(codes, scores, uphill, downhill, pvp)]

result = result[:50]
result = sorted(result, key=lambda x: x[4], reverse=True)[:25]

result = [*map(lambda x: (x[0], x[1], x[-1]), result)]


with open(f"./history/{date_postfix}.yaml", "w") as f:
    yaml.dump({
        "codes": [*map(lambda x: x[0], result)],
        "scores": [*map(lambda x: x[1], result)],
        "pvp": [*map(lambda x: x[2], result)],
    }, f)
print("save file ok")
ifttt = Ifttt()
ifttt.send_cnsp(result, date=date_postfix)
