class Tokenizer:
    def __init__(self, grid=100, maxlen=250):
        self.grid = grid
        self.tick = 10 / (self.grid / 2)
        self.maxlen = maxlen
        self.pad = 0
        self.vocab_size = self.grid + 1

    def show(self):
        print(f"grid: {self.grid}")
        print(f"tick: {self.tick}")

    def tokenize(self, seq):
        seq = [*map(lambda x: x // self.tick + self.grid / 2, seq)]
        seq = [*map(lambda x: x if x < self.grid else self.grid, seq)]
        seq = [*map(lambda x: x if x > 0 else 0, seq)]
        seqlen = len(seq)
        seq = [seq[0] + 1] + [*map(lambda x: x + 1, seq)] + [self.pad] * self.maxlen
        seq = seq[:self.maxlen]
        return seq, seqlen