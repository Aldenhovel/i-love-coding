from Grabber import Grabber
from Tokenizer import Tokenizer
from DataReader import DataReader
from StockDataset import StockDataset
from Model import LSTMDecoder
import external

import torch
import torch.nn as nn
import matplotlib.pyplot as plt
from torch.utils.data import DataLoader
import numpy as np

def inference(seq, seqlen, model, beam_size, device):
    model.eval()
    model.to(device)
    with torch.no_grad():
        h_state, c_state = model.init_h0(torch.zeros(1, model.vocab_size).to(device)), model.init_c0(
            torch.zeros(1, model.vocab_size).to(device))
        h_state, c_state = h_state.unsqueeze(0).repeat(model.layer * model.bi_factor, 1, 1), c_state.unsqueeze(
            0).repeat(model.layer * model.bi_factor, 1, 1)
        k = beam_size
        for i in range(seqlen):
            current = float(seq[i].clone().detach().cpu().numpy())
            in_id = seq[i].unsqueeze(0)
            _, h_state, c_state = model.decode(in_id, h_state, c_state)

        topk_prev_tokens = torch.LongTensor([[seq[seqlen - 1]]] * k).to(device)  # [k, 1]
        topk_sequences = topk_prev_tokens  # [k, 1]
        topk_logps = torch.zeros(k, 1).to(device)  # [k, 1]
        complete_sequences, complete_sequence_logps = [], []
        h_state, c_state = h_state.repeat(1, beam_size, 1), c_state.repeat(1, beam_size, 1)
        step = 1
        while True:
            logit, h_state, c_state = model.decode(topk_prev_tokens.squeeze(1), h_state, c_state)

            logp = torch.nn.functional.log_softmax(logit, dim=1)  # [k, vocab_size]
            logp = topk_logps.expand_as(logp) + logp  # [k, vocab_size]
            if step == 1:
                topk_logps, topk_tokens = logp[0].topk(k, 0, True, True)  # [k,]
            else:
                topk_logps, topk_tokens = logp.view(-1).topk(k, 0, True, True)  # [k,]
            prev_tokens = torch.div(topk_tokens, model.vocab_size, rounding_mode='trunc')
            next_tokens = topk_tokens % model.vocab_size
            topk_sequences = torch.cat((topk_sequences[prev_tokens], next_tokens.unsqueeze(1)), dim=1)  # [k, step + 1]
            incomplete_indices = [indice for indice, next_token in enumerate(next_tokens)]
            complete_indices = list(set(range(len(next_tokens))) - set(incomplete_indices))
            if len(complete_indices) > 0:
                complete_sequences.extend(topk_sequences[complete_indices].tolist())
                complete_sequence_logps.extend(topk_logps[complete_indices])
            k -= len(complete_indices)
            # Proceed with incomplete sequences
            if k == 0:
                break
            topk_sequences = topk_sequences[incomplete_indices]
            h_state = h_state[:, prev_tokens[incomplete_indices], :]
            c_state = c_state[:, prev_tokens[incomplete_indices], :]
            topk_logps = topk_logps[incomplete_indices].unsqueeze(1)
            topk_prev_tokens = next_tokens[incomplete_indices].unsqueeze(1)
            if step > 10:  # (250 - seqlen):
                if len(complete_indices) == 0:
                    complete_sequences.extend(topk_sequences.tolist())
                    complete_sequence_logps.extend(topk_logps[incomplete_indices])
                break

            # Update step
            step += 1

        i_s = torch.topk(torch.Tensor(complete_sequence_logps), beam_size, sorted=True).indices
        res = []
        for i in i_s:
            res_1 = [*map(lambda x: x - 1, complete_sequences[i])]
            res.append(complete_sequences[i])
        avgpred = sum([*map(lambda x: x[-1], res)]) / len(i_s)
        return res, avgpred, current


def plot_res(front, res, gt=None, gtlen=None, savefig=None):
    fig = plt.figure(figsize=[10, 5])
    xmax = 250

    if gt is not None and gtlen is not None:
        plt.plot(gt[gtlen], color="purple", label="gt")
        xmax = gtlen - 1
    for i in range(len(res)):
        plt.plot((front + res[i])[:xmax], label="pred")
    plt.plot(front, color="black")
    plt.vlines(len(front) - 1, 50, front[-1], linestyles="dashed", colors="blue")
    plt.hlines(50, 0, xmax, linestyles="dashed", colors="red")
    plt.xlim([0, xmax])
    plt.ylim([-1, 101])
    plt.xlabel("time step")
    plt.ylabel("price range %")
    plt.title(f"{len(front)}")
    # plt.legend()
    if savefig is not None:
        plt.savefig(f"{savefig}.jpg", format="jpg")
    plt.show()
    return fig

DEVICE = torch.device("cuda:0")
train_ds = StockDataset("data/train")
test_ds = StockDataset("data/train")
train_dl = DataLoader(train_ds, batch_size=32, shuffle=True)
test_dl = DataLoader(test_ds, batch_size=1, shuffle=True)

model = torch.load("checkpoints/model.pt")
model.eval()
with torch.no_grad():
    datareader = DataReader("data")
    data = datareader.readyaml("valid/2023-01-18-002238.yaml")

    seq = data["stdfenshi"]
    seq, seqlen = train_ds.tk.tokenize(seq)
    seq = torch.Tensor(seq).long()

    msk = 150#seqlen
    mskseq = torch.cat((seq[:msk], torch.zeros(250-msk)), dim=0).long().to(DEVICE)
    mskseqlen = msk
    res, avgpred, current = inference(mskseq, mskseqlen, model, beam_size=10, device=DEVICE)
    plot_res(front=mskseq[1:mskseqlen].detach().cpu().numpy().tolist(),
             res=res,
             gt=None,
             gtlen=None)

grabber = Grabber()
codelst = grabber.clean_wencai_codelist()[:10]
print(f"{len(codelst)} items in queue.")

scorelst = []
for ix, code in enumerate(codelst):
    seq = grabber.sample(dirpath="x", code=code)
    model.eval()
    with torch.no_grad():
        seq, seqlen = train_ds.tk.tokenize(seq)
        seq = torch.Tensor(seq).long()
        k = 1
        avgpredlst, currentlst = [], []
        for i in range(1, seqlen // k):
            msk = k*i#seqlen
            mskseq = torch.cat((seq[:msk], torch.zeros(250-msk)), dim=0).long().to(DEVICE)
            mskseqlen = msk
            res, avgpred, current = inference(mskseq, mskseqlen, model, beam_size=20, device=DEVICE)
            avgpredlst.append(avgpred)
            currentlst.append(current)
        performance = np.asarray(currentlst[20:]) - np.asarray(avgpredlst[10:-10])
        score = sum(performance) / len(performance)
        scorelst.append((code, score))
        print(ix, code, len(seq), score)

scorelst = sorted(scorelst, key=lambda x: x[1], reverse=True)
import datetime
resfile = f"x/00-{datetime.date.today()}.txt"
with open(resfile, "a+") as f:
    for code, score in scorelst:
        if score > 2:
            f.write(f"{code}\n")

print("-"*30)
print(f"process done. See in x/00-{datetime.date.today()}.txt")
for code, score in scorelst:
    print(code, score)