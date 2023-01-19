import torch
import torch.nn as nn
from torch.utils.data import DataLoader
import numpy as np
import matplotlib.pyplot as plt

from DataReader import DataReader
from Tokenizer import Tokenizer
from Grabber import Grabber
from StockDataset import StockDataset
from Model import LSTMDecoder

import tqdm
from torch.nn.utils.rnn import pack_padded_sequence


train_ds = StockDataset("data/train")
valid_ds = StockDataset("data/train")    # 由于还没有 test valid 数据集，暂时先用这个代替
train_dl = DataLoader(train_ds, batch_size=32, shuffle=True)
valid_dl = DataLoader(valid_ds, batch_size=1, shuffle=True)


def train_step(model, optimizer, criterion, loader, epoch, device):
    losslst = []
    model.to(device)
    model.train()
    pbar = tqdm.tqdm(enumerate(loader), total=len(loader), ncols=100)
    for i, (seqs, seqlens) in pbar:
        seqs = seqs.to(device)
        seqlens = seqlens.to(device)
        logits, sorted_seqs, sorted_decode_len, sorted_seq_indices = model(seqs, seqlens)
        logits = pack_padded_sequence(logits, sorted_decode_len).data
        gt = sorted_seqs[:, 1:]
        gt = pack_padded_sequence(gt, sorted_decode_len, batch_first=True).data
        loss = criterion(logits.to(device), gt)
        optimizer.zero_grad()
        loss.backward()
        optimizer.step()
        losslst.append(loss)
        pbar.set_description(f"E: {epoch}, loss: {(sum(losslst) / len(losslst)):.5f}")
    return loss


def vaild_step(model, loader, epoch, device):
    corr, tot = 0, 0
    model.to(device)
    model.eval()
    pbar = tqdm.tqdm(enumerate(loader), total=len(loader), ncols=100)
    for i, (seqs, seqlens) in pbar:
        seqs = seqs.to(device)
        seqlens = seqlens.to(device)
        logits, sorted_seqs, sorted_decode_len, sorted_seq_indices = model(seqs, seqlens)
        logits_copy = logits.clone()
        _, preds = torch.max(logits_copy, dim=2)
        preds = preds.t()
        preds = pack_padded_sequence(preds, sorted_decode_len, batch_first=True).data
        gt = sorted_seqs[:, 1:].detach().cpu()
        gt = pack_padded_sequence(gt, sorted_decode_len, batch_first=True).data
        for i in (gt - preds):
            if i == 0:
                corr += 1
            tot += 1
        pbar.set_description(f"E: {epoch}, _acc: {(corr / tot):.5f} ({corr}/{tot})")
    return corr / tot


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
            prev_tokens = topk_tokens // model.vocab_size  # [k,]
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
            if step > 50:  # (250 - seqlen):
                if len(complete_indices) == 0:
                    complete_sequences.extend(topk_sequences.tolist())
                    complete_sequence_logps.extend(topk_logps[incomplete_indices])
                break

            # Update step
            step += 1

        i_s = torch.topk(torch.Tensor(complete_sequence_logps), beam_size, sorted=True).indices
        res = []
        for i in i_s:
            res.append(complete_sequences[i])
        '''
        i = complete_sequence_logps.index(max(complete_sequence_logps))
        res = [complete_sequences[i]]
        '''
        return res


def plot_res(front, res, gt=None, gtlen=None, savefig=None):
    fig = plt.figure(figsize=[7, 5])
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


if __name__ == "__main__":
    device = torch.device("cuda")
    model = LSTMDecoder(vocab_size=102, hidden_dim=512, layer=2, bi=True, device=device)
    criterion = nn.CrossEntropyLoss()
    optimizer = torch.optim.RMSprop(model.parameters(), lr=1e-3)

    for i in range(10):
        train_step(model, optimizer, criterion, train_dl, i, device)
        if i % 10 == 0:
            vaild_step(model, train_dl, i, device)
            torch.save(model, "checkpoints/model.pt")



    import matplotlib.pyplot as plt
    model = torch.load("checkpoints/model.pt")
    data = train_ds.reader.readyaml("../valid/2023-01-18-301009.yaml")
    seq = data["stdfenshi"]
    seq, seqlen = train_ds.tk.tokenize(seq)
    seq = torch.LongTensor(seq)

    msk = 50#seqlen
    mskseq = torch.cat((seq[:msk], torch.zeros(250-msk)), dim=0).long().to(device)
    mskseqlen = msk
    res = inference(mskseq, mskseqlen, model, beam_size=50, device=device)
    plot_res(front=mskseq[1:mskseqlen].detach().cpu().numpy().tolist(),
             res=res,
             gt=None,
             gtlen=None)


